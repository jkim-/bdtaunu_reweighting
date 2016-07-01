#include <CLHEP/Vector/LorentzVector.h>

#include <ff_reweight_constants.h>

#include "FormFactorAnalyzer.h"

using CLHEP::HepLorentzVector;

FormFactorAnalyzer::FormFactorAnalyzer() 
: FormFactorAnalyzer(true) {}

FormFactorAnalyzer::FormFactorAnalyzer(bool ignore_fsr) : 
  bsl_dict_(), ignore_fsr_(ignore_fsr), 
  bdlnu_(), bdslnu_() {
  clear_cache();
  initialize_decay_models();
}

FormFactorAnalyzer::~FormFactorAnalyzer() {}

void FormFactorAnalyzer::clear_cache() {
  bdlnu_.clear();
  bdslnu_.clear();
  cln_ = 1.0;
}

void FormFactorAnalyzer::decay_lunds_from_vertices(
    std::vector<int> &decay_lunds, 
    Vertex mother_vertex,
    const std::vector<Vertex> &daughter_vertices) {

    decay_lunds.clear();

    decay_lunds.push_back(lund_pm_[mother_vertex]);
    for (const auto & v : daughter_vertices) {
      decay_lunds.push_back(lund_pm_[v]);
    }
}

BToDlnuMode FormFactorAnalyzer::create_bdlnu_mode(
    Vertex mother_vertex,
    const std::vector<Vertex> &daughter_vertices) {

  int Blund, Xlund, Leplund;
  Blund = Xlund = Leplund = 0;
  HepLorentzVector BLab, XLab, LepLab, NuLab;

  Blund = lund_pm_[mother_vertex];
  BLab = lorentz_pm_[mother_vertex];

  for (const auto & v : daughter_vertices) {
    int lund = lund_pm_[v];
    if (is_dmeson(lund)) {
      Xlund = lund;
      XLab = lorentz_pm_[v];
    } else if (is_lepton(lund)) {
      Leplund = lund;
      LepLab = lorentz_pm_[v];
    } else if (is_neutrino(lund)) {
      NuLab = lorentz_pm_[v];
    }
  }

  if (ignore_fsr_) { LepLab = BLab - XLab - NuLab; }

  return BToDlnuMode({ Blund, Xlund, Leplund, BLab, XLab, LepLab });
}

BToDslnuMode FormFactorAnalyzer::create_bdslnu_mode(
    Vertex mother_vertex,
    const std::vector<Vertex> &daughter_vertices, 
    const McDecayModeSummary &summary) {

  int Blund, Xlund, Leplund, Xdaulund, Softdaulund;
  Blund = Xlund = Leplund = Xdaulund = Softdaulund = 0;
  HepLorentzVector BLab, XLab, LepLab, NuLab, XdauLab;

  Blund = lund_pm_[mother_vertex];
  BLab = lorentz_pm_[mother_vertex];

  for (const auto & v : daughter_vertices) {

    int v_lund = lund_pm_[v];

    if (is_dstar(v_lund)) {
      Xlund = v_lund;
      XLab = lorentz_pm_[v];

      for (const auto &w : summary.dstar_modes().at(v)) {
        int w_lund = lund_pm_[w];
        if (is_dmeson(w_lund)) {
          Xdaulund = w_lund;
          XdauLab = lorentz_pm_[w];
        } else if (is_pion(w_lund)) {
          Softdaulund = w_lund;
        } else if (is_gamma(w_lund)) {
          // if statement to guard against fsr edge case
          if (Softdaulund == 0) { Softdaulund = w_lund; }
        }
      }

    } else if (is_lepton(v_lund)) {
      Leplund = v_lund;
      LepLab = lorentz_pm_[v];
    } else if (is_neutrino(v_lund)) {
      NuLab = lorentz_pm_[v];
    }
  }

  if (ignore_fsr_) { LepLab = BLab - XLab - NuLab; }

  return BToDslnuMode({ Blund, Xlund, Leplund, 
                        Xdaulund, Softdaulund, 
                        BLab, XLab, LepLab, XdauLab });
}

void FormFactorAnalyzer::collect_decay_modes(
    const Graph &g, const McDecayModeSummary &summary) {

  std::vector<int> decay_lunds;

  for (auto it = summary.b_modes().begin();
       it != summary.b_modes().end(); ++it) {

    // create decay lund list from vertices
    decay_lunds_from_vertices(decay_lunds, it->first, it->second);

    // decide the type of sl decay
    BSemiLepCode sl_code = bsl_dict_.find(decay_lunds, ignore_fsr_);

    // create and append the appropriate decay mode object
    switch (sl_code) {
      case BSemiLepCode::Bc_D0_e:
      case BSemiLepCode::Bc_D0_mu:
      case BSemiLepCode::Bc_D0_tau:
      case BSemiLepCode::B0_Dc_e:
      case BSemiLepCode::B0_Dc_mu:
      case BSemiLepCode::B0_Dc_tau:
        bdlnu_.push_back(create_bdlnu_mode(it->first, it->second));
        break;
      case BSemiLepCode::Bc_Dstar0_e:
      case BSemiLepCode::Bc_Dstar0_mu:
      case BSemiLepCode::Bc_Dstar0_tau:
      case BSemiLepCode::B0_Dstarc_e:
      case BSemiLepCode::B0_Dstarc_mu:
      case BSemiLepCode::B0_Dstarc_tau:
        bdslnu_.push_back(create_bdslnu_mode(it->first, it->second, summary));
        break;
      default:
        ;
    }
  }
}

void FormFactorAnalyzer::compute_ff_weights() {

  cln_ = 1.0;

  for (const auto &m : bdlnu_) {
    cln_ *= compute_bdlnu_cln_weights(m, m.q2());
  }

  for (const auto &m : bdslnu_) {
    cln_ *= compute_bdslnu_cln_weights(m, m.q2(), m.ctl(), m.ctv(), m.chi());
  }

}

void FormFactorAnalyzer::analyze(
    const Graph &g, const McDecayModeSummary &summary) {

  // initialize cache
  clear_cache();
  lund_pm_ = get_lund_pm(g);
  lorentz_pm_ = get_lorentz_pm(g);

  // populate semileptonic decay mode objects
  collect_decay_modes(g, summary);

  // compute form factor weights
  compute_ff_weights();

  return; 
}

void FormFactorAnalyzer::initialize_decay_models() {

  // B -> D l nu

  BcDenu_from_ = BPlnuDecayRate(mBp, mD0, mE, "ISGW2");
  BcDmunu_from_ = BPlnuDecayRate(mBp, mD0, mMu, "ISGW2");
  BcDtaunu_from_ = BPlnuDecayRate(mBp, mD0, mTau, "ISGW2");
  B0Denu_from_ = BPlnuDecayRate(mB0, mDp, mE, "ISGW2");
  B0Dmunu_from_ = BPlnuDecayRate(mB0, mDp, mMu, "ISGW2");
  B0Dtaunu_from_ = BPlnuDecayRate(mB0, mDp, mTau, "ISGW2");

  BcDenu_to_ = BPlnuDecayRate(mBp, mD0, mE, "CLN");
  BcDmunu_to_ = BPlnuDecayRate(mBp, mD0, mMu, "CLN");
  BcDtaunu_to_ = BPlnuDecayRate(mBp, mD0, mTau, "CLN");
  B0Denu_to_ = BPlnuDecayRate(mB0, mDp, mE, "CLN");
  B0Dmunu_to_ = BPlnuDecayRate(mB0, mDp, mMu, "CLN");
  B0Dtaunu_to_ = BPlnuDecayRate(mB0, mDp, mTau, "CLN");

  // B -> D* l nu

  BcDsenu_Dpi_lm_from_ = BVlnuDecayRate(mBp, mD0, mE, false, false, "LinearQ2");
  BcDsmunu_Dpi_lm_from_ = BVlnuDecayRate(mBp, mD0, mMu, false, false, "LinearQ2");
  BcDstaunu_Dpi_lm_from_ = BVlnuDecayRate(mBp, mD0, mTau, false, false, "ISGW2");
  B0Dsenu_Dpi_lm_from_ = BVlnuDecayRate(mB0, mDp, mE, false, false, "LinearQ2");
  B0Dsmunu_Dpi_lm_from_ = BVlnuDecayRate(mB0, mDp, mMu, false, false, "LinearQ2");
  B0Dstaunu_Dpi_lm_from_ = BVlnuDecayRate(mB0, mDp, mTau, false, false, "LinearQ2");
  BcDsenu_Dgamma_lm_from_ = BVlnuDecayRate(mBp, mD0, mE, true, false, "LinearQ2");
  BcDsmunu_Dgamma_lm_from_ = BVlnuDecayRate(mBp, mD0, mMu, true, false, "LinearQ2");
  BcDstaunu_Dgamma_lm_from_ = BVlnuDecayRate(mBp, mD0, mTau, true, false, "ISGW2");
  B0Dsenu_Dgamma_lm_from_ = BVlnuDecayRate(mB0, mDp, mE, true, false, "LinearQ2");
  B0Dsmunu_Dgamma_lm_from_ = BVlnuDecayRate(mB0, mDp, mMu, true, false, "LinearQ2");
  B0Dstaunu_Dgamma_lm_from_ = BVlnuDecayRate(mB0, mDp, mTau, true, false, "LinearQ2");
  BcDsenu_Dpi_lp_from_ = BVlnuDecayRate(mBp, mD0, mE, false, true, "LinearQ2");
  BcDsmunu_Dpi_lp_from_ = BVlnuDecayRate(mBp, mD0, mMu, false, true, "LinearQ2");
  BcDstaunu_Dpi_lp_from_ = BVlnuDecayRate(mBp, mD0, mTau, false, true, "ISGW2");
  B0Dsenu_Dpi_lp_from_ = BVlnuDecayRate(mB0, mDp, mE, false, true, "LinearQ2");
  B0Dsmunu_Dpi_lp_from_ = BVlnuDecayRate(mB0, mDp, mMu, false, true, "LinearQ2");
  B0Dstaunu_Dpi_lp_from_ = BVlnuDecayRate(mB0, mDp, mTau, false, true, "LinearQ2");
  BcDsenu_Dgamma_lp_from_ = BVlnuDecayRate(mBp, mD0, mE, true, true, "LinearQ2");
  BcDsmunu_Dgamma_lp_from_ = BVlnuDecayRate(mBp, mD0, mMu, true, true, "LinearQ2");
  BcDstaunu_Dgamma_lp_from_ = BVlnuDecayRate(mBp, mD0, mTau, true, true, "ISGW2");
  B0Dsenu_Dgamma_lp_from_ = BVlnuDecayRate(mB0, mDp, mE, true, true, "LinearQ2");
  B0Dsmunu_Dgamma_lp_from_ = BVlnuDecayRate(mB0, mDp, mMu, true, true, "LinearQ2");
  B0Dstaunu_Dgamma_lp_from_ = BVlnuDecayRate(mB0, mDp, mTau, true, true, "LinearQ2");

  BcDsenu_Dpi_lm_to_ = BVlnuDecayRate(mBp, mD0, mE, false, false, "CLN");
  BcDsmunu_Dpi_lm_to_ = BVlnuDecayRate(mBp, mD0, mMu, false, false, "CLN");
  BcDstaunu_Dpi_lm_to_ = BVlnuDecayRate(mBp, mD0, mTau, false, false, "CLN");
  B0Dsenu_Dpi_lm_to_ = BVlnuDecayRate(mB0, mDp, mE, false, false, "CLN");
  B0Dsmunu_Dpi_lm_to_ = BVlnuDecayRate(mB0, mDp, mMu, false, false, "CLN");
  B0Dstaunu_Dpi_lm_to_ = BVlnuDecayRate(mB0, mDp, mTau, false, false, "CLN");
  BcDsenu_Dgamma_lm_to_ = BVlnuDecayRate(mBp, mD0, mE, true, false, "CLN");
  BcDsmunu_Dgamma_lm_to_ = BVlnuDecayRate(mBp, mD0, mMu, true, false, "CLN");
  BcDstaunu_Dgamma_lm_to_ = BVlnuDecayRate(mBp, mD0, mTau, true, false, "CLN");
  B0Dsenu_Dgamma_lm_to_ = BVlnuDecayRate(mB0, mDp, mE, true, false, "CLN");
  B0Dsmunu_Dgamma_lm_to_ = BVlnuDecayRate(mB0, mDp, mMu, true, false, "CLN");
  B0Dstaunu_Dgamma_lm_to_ = BVlnuDecayRate(mB0, mDp, mTau, true, false, "CLN");
  BcDsenu_Dpi_lp_to_ = BVlnuDecayRate(mBp, mD0, mE, false, true, "CLN");
  BcDsmunu_Dpi_lp_to_ = BVlnuDecayRate(mBp, mD0, mMu, false, true, "CLN");
  BcDstaunu_Dpi_lp_to_ = BVlnuDecayRate(mBp, mD0, mTau, false, true, "CLN");
  B0Dsenu_Dpi_lp_to_ = BVlnuDecayRate(mB0, mDp, mE, false, true, "CLN");
  B0Dsmunu_Dpi_lp_to_ = BVlnuDecayRate(mB0, mDp, mMu, false, true, "CLN");
  B0Dstaunu_Dpi_lp_to_ = BVlnuDecayRate(mB0, mDp, mTau, false, true, "CLN");
  BcDsenu_Dgamma_lp_to_ = BVlnuDecayRate(mBp, mD0, mE, true, true, "CLN");
  BcDsmunu_Dgamma_lp_to_ = BVlnuDecayRate(mBp, mD0, mMu, true, true, "CLN");
  BcDstaunu_Dgamma_lp_to_ = BVlnuDecayRate(mBp, mD0, mTau, true, true, "CLN");
  B0Dsenu_Dgamma_lp_to_ = BVlnuDecayRate(mB0, mDp, mE, true, true, "CLN");
  B0Dsmunu_Dgamma_lp_to_ = BVlnuDecayRate(mB0, mDp, mMu, true, true, "CLN");
  B0Dstaunu_Dgamma_lp_to_ = BVlnuDecayRate(mB0, mDp, mTau, true, true, "CLN");

}

double FormFactorAnalyzer::compute_bdlnu_cln_weights(
    const BToDlnuMode &m, double q2) {

  double result = 1.0;

  switch (m.bdlnu_type()) {
    case BToDlnuType::Bc_D0_e:
      result = BcDenu_to_.dGamma_dq2_density(q2) / 
               BcDenu_from_.dGamma_dq2_density(q2);
      break;
    case BToDlnuType::Bc_D0_mu:
      result = BcDmunu_to_.dGamma_dq2_density(q2) / 
               BcDmunu_from_.dGamma_dq2_density(q2);
      break;
    case BToDlnuType::Bc_D0_tau:
      result = BcDtaunu_to_.dGamma_dq2_density(q2) / 
               BcDtaunu_from_.dGamma_dq2_density(q2);
      break;
    case BToDlnuType::B0_Dc_e:
      result = B0Denu_to_.dGamma_dq2_density(q2) / 
               B0Denu_from_.dGamma_dq2_density(q2);
      break;
    case BToDlnuType::B0_Dc_mu:
      result = B0Dmunu_to_.dGamma_dq2_density(q2) / 
               B0Dmunu_from_.dGamma_dq2_density(q2);
      break;
    case BToDlnuType::B0_Dc_tau:
      result = B0Dtaunu_to_.dGamma_dq2_density(q2) / 
               B0Dtaunu_from_.dGamma_dq2_density(q2);
      break;
    default:
      ;
  }

  return result;
  
}

double FormFactorAnalyzer::compute_bdslnu_cln_weights(
    const BToDslnuMode &m, double q2, double ctl, double ctv, double chi) {

  double result = 1.0;

  switch (m.bdslnu_type()) {
    case BToDslnuType::Bc_Dstar0_e_Dpi_lminus:
      result = BcDsenu_Dpi_lm_to_.dGamma_dq2dangles_density(q2, ctl, ctv, chi) / 
               BcDsenu_Dpi_lm_from_.dGamma_dq2dangles_density(q2, ctl, ctv, chi);
      break;
    case BToDslnuType::Bc_Dstar0_mu_Dpi_lminus:
      result = BcDsmunu_Dpi_lm_to_.dGamma_dq2dangles_density(q2, ctl, ctv, chi) / 
               BcDsmunu_Dpi_lm_from_.dGamma_dq2dangles_density(q2, ctl, ctv, chi);
      break;
    case BToDslnuType::Bc_Dstar0_tau_Dpi_lminus:
      result = BcDstaunu_Dpi_lm_to_.dGamma_dq2dangles_density(q2, ctl, ctv, chi) / 
               BcDstaunu_Dpi_lm_from_.dGamma_dq2dangles_density(q2, ctl, ctv, chi);
      break;
    case BToDslnuType::B0_Dstarc_e_Dpi_lminus:
      result = B0Dsenu_Dpi_lm_to_.dGamma_dq2dangles_density(q2, ctl, ctv, chi) / 
               B0Dsenu_Dpi_lm_from_.dGamma_dq2dangles_density(q2, ctl, ctv, chi);
      break;
    case BToDslnuType::B0_Dstarc_mu_Dpi_lminus:
      result = B0Dsmunu_Dpi_lm_to_.dGamma_dq2dangles_density(q2, ctl, ctv, chi) / 
               B0Dsmunu_Dpi_lm_from_.dGamma_dq2dangles_density(q2, ctl, ctv, chi);
      break;
    case BToDslnuType::B0_Dstarc_tau_Dpi_lminus:
      result = B0Dstaunu_Dpi_lm_to_.dGamma_dq2dangles_density(q2, ctl, ctv, chi) / 
               B0Dstaunu_Dpi_lm_from_.dGamma_dq2dangles_density(q2, ctl, ctv, chi);
      break;
    case BToDslnuType::Bc_Dstar0_e_Dgamma_lminus:
      result = BcDsenu_Dgamma_lm_to_.dGamma_dq2dangles_density(q2, ctl, ctv, chi) / 
               BcDsenu_Dgamma_lm_from_.dGamma_dq2dangles_density(q2, ctl, ctv, chi);
      break;
    case BToDslnuType::Bc_Dstar0_mu_Dgamma_lminus:
      result = BcDsmunu_Dgamma_lm_to_.dGamma_dq2dangles_density(q2, ctl, ctv, chi) / 
               BcDsmunu_Dgamma_lm_from_.dGamma_dq2dangles_density(q2, ctl, ctv, chi);
      break;
    case BToDslnuType::Bc_Dstar0_tau_Dgamma_lminus:
      result = BcDstaunu_Dgamma_lm_to_.dGamma_dq2dangles_density(q2, ctl, ctv, chi) / 
               BcDstaunu_Dgamma_lm_from_.dGamma_dq2dangles_density(q2, ctl, ctv, chi);
      break;
    case BToDslnuType::B0_Dstarc_e_Dgamma_lminus:
      result = B0Dsenu_Dgamma_lm_to_.dGamma_dq2dangles_density(q2, ctl, ctv, chi) / 
               B0Dsenu_Dgamma_lm_from_.dGamma_dq2dangles_density(q2, ctl, ctv, chi);
      break;
    case BToDslnuType::B0_Dstarc_mu_Dgamma_lminus:
      result = B0Dsmunu_Dgamma_lm_to_.dGamma_dq2dangles_density(q2, ctl, ctv, chi) / 
               B0Dsmunu_Dgamma_lm_from_.dGamma_dq2dangles_density(q2, ctl, ctv, chi);
      break;
    case BToDslnuType::B0_Dstarc_tau_Dgamma_lminus:
      result = B0Dstaunu_Dgamma_lm_to_.dGamma_dq2dangles_density(q2, ctl, ctv, chi) / 
               B0Dstaunu_Dgamma_lm_from_.dGamma_dq2dangles_density(q2, ctl, ctv, chi);
      break;
    case BToDslnuType::Bc_Dstar0_e_Dpi_lplus:
      result = BcDsenu_Dpi_lp_to_.dGamma_dq2dangles_density(q2, ctl, ctv, chi) / 
               BcDsenu_Dpi_lp_from_.dGamma_dq2dangles_density(q2, ctl, ctv, chi);
      break;
    case BToDslnuType::Bc_Dstar0_mu_Dpi_lplus:
      result = BcDsmunu_Dpi_lp_to_.dGamma_dq2dangles_density(q2, ctl, ctv, chi) / 
               BcDsmunu_Dpi_lp_from_.dGamma_dq2dangles_density(q2, ctl, ctv, chi);
      break;
    case BToDslnuType::Bc_Dstar0_tau_Dpi_lplus:
      result = BcDstaunu_Dpi_lp_to_.dGamma_dq2dangles_density(q2, ctl, ctv, chi) / 
               BcDstaunu_Dpi_lp_from_.dGamma_dq2dangles_density(q2, ctl, ctv, chi);
      break;
    case BToDslnuType::B0_Dstarc_e_Dpi_lplus:
      result = B0Dsenu_Dpi_lp_to_.dGamma_dq2dangles_density(q2, ctl, ctv, chi) / 
               B0Dsenu_Dpi_lp_from_.dGamma_dq2dangles_density(q2, ctl, ctv, chi);
      break;
    case BToDslnuType::B0_Dstarc_mu_Dpi_lplus:
      result = B0Dsmunu_Dpi_lp_to_.dGamma_dq2dangles_density(q2, ctl, ctv, chi) / 
               B0Dsmunu_Dpi_lp_from_.dGamma_dq2dangles_density(q2, ctl, ctv, chi);
      break;
    case BToDslnuType::B0_Dstarc_tau_Dpi_lplus:
      result = B0Dstaunu_Dpi_lp_to_.dGamma_dq2dangles_density(q2, ctl, ctv, chi) / 
               B0Dstaunu_Dpi_lp_from_.dGamma_dq2dangles_density(q2, ctl, ctv, chi);
      break;
    case BToDslnuType::Bc_Dstar0_e_Dgamma_lplus:
      result = BcDsenu_Dgamma_lp_to_.dGamma_dq2dangles_density(q2, ctl, ctv, chi) / 
               BcDsenu_Dgamma_lp_from_.dGamma_dq2dangles_density(q2, ctl, ctv, chi);
      break;
    case BToDslnuType::Bc_Dstar0_mu_Dgamma_lplus:
      result = BcDsmunu_Dgamma_lp_to_.dGamma_dq2dangles_density(q2, ctl, ctv, chi) / 
               BcDsmunu_Dgamma_lp_from_.dGamma_dq2dangles_density(q2, ctl, ctv, chi);
      break;
    case BToDslnuType::Bc_Dstar0_tau_Dgamma_lplus:
      result = BcDstaunu_Dgamma_lp_to_.dGamma_dq2dangles_density(q2, ctl, ctv, chi) / 
               BcDstaunu_Dgamma_lp_from_.dGamma_dq2dangles_density(q2, ctl, ctv, chi);
      break;
    case BToDslnuType::B0_Dstarc_e_Dgamma_lplus:
      result = B0Dsenu_Dgamma_lp_to_.dGamma_dq2dangles_density(q2, ctl, ctv, chi) / 
               B0Dsenu_Dgamma_lp_from_.dGamma_dq2dangles_density(q2, ctl, ctv, chi);
      break;
    case BToDslnuType::B0_Dstarc_mu_Dgamma_lplus:
      result = B0Dsmunu_Dgamma_lp_to_.dGamma_dq2dangles_density(q2, ctl, ctv, chi) / 
               B0Dsmunu_Dgamma_lp_from_.dGamma_dq2dangles_density(q2, ctl, ctv, chi);
      break;
    case BToDslnuType::B0_Dstarc_tau_Dgamma_lplus:
      result = B0Dstaunu_Dgamma_lp_to_.dGamma_dq2dangles_density(q2, ctl, ctv, chi) / 
               B0Dstaunu_Dgamma_lp_from_.dGamma_dq2dangles_density(q2, ctl, ctv, chi);
      break;

    default:
      ;

  }

  return result;
}
