#include <CLHEP/Vector/LorentzVector.h>

#include <ff_reweight_constants.h>

#include "FormFactorAnalyzer.h"

using CLHEP::HepLorentzVector;

FormFactorAnalyzer::FormFactorAnalyzer() 
: FormFactorAnalyzer(true) {}

FormFactorAnalyzer::FormFactorAnalyzer(bool ignore_fsr) : 
  bsl_dict_(), 
  cln_reweighter_(), 
  llsw_reweighter_(), 
  ignore_fsr_(ignore_fsr), 
  bdlnu_(), bdslnu_(), bdsslnu_() {
  clear_cache();
}

FormFactorAnalyzer::~FormFactorAnalyzer() {}

void FormFactorAnalyzer::clear_cache() {
  bdlnu_.clear();
  bdslnu_.clear();
  bdsslnu_.clear();
  cln_ = 1.0;
  llswb1_ = 1.0;
  llswb2_ = 1.0;
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

  // trick to get around fsr effects
  if (ignore_fsr_) { LepLab = BLab - XLab - NuLab; }

  return BToDslnuMode({ Blund, Xlund, Leplund, 
                        Xdaulund, Softdaulund, 
                        BLab, XLab, LepLab, XdauLab });
}

BToDsslnuMode FormFactorAnalyzer::create_bdsslnu_mode(
    Vertex mother_vertex,
    const std::vector<Vertex> &daughter_vertices) {

  int Blund, Xlund, Leplund;
  Blund = Xlund = Leplund = 0;
  HepLorentzVector BLab, XLab, LepLab, NuLab;

  Blund = lund_pm_[mother_vertex];
  BLab = lorentz_pm_[mother_vertex];

  for (const auto & v : daughter_vertices) {
    int lund = lund_pm_[v];
    if (is_dsstar(lund)) {
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

  return BToDsslnuMode({ Blund, Xlund, Leplund, BLab, XLab, LepLab });
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
      case BSemiLepCode::B_D_l:
        bdlnu_.push_back(create_bdlnu_mode(it->first, it->second));
        break;
      case BSemiLepCode::B_Ds_l:
        bdslnu_.push_back(create_bdslnu_mode(it->first, it->second, summary));
        break;
      case BSemiLepCode::B_Dss_l:
        bdsslnu_.push_back(create_bdsslnu_mode(it->first, it->second));
        break;
      default:
        ;
    }
  }
}

void FormFactorAnalyzer::compute_ff_weights() {

  cln_ = 1.0;
  llswb1_ = 1.0;
  llswb2_ = 1.0;

  for (const auto &m : bdlnu_) {
    cln_ *= cln_reweighter_.compute_bdlnu_cln_weights(m, m.q2());
  }

  for (const auto &m : bdslnu_) {
    cln_ *= cln_reweighter_.compute_bdslnu_cln_weights(
        m, m.q2(), m.ctl(), m.ctv(), m.chi());
  }

  for (const auto &m : bdsslnu_) {
    llswb1_ *= llsw_reweighter_.compute_bdsslnu_llswb1_weights(m, m.q2());
    llswb2_ *= llsw_reweighter_.compute_bdsslnu_llswb2_weights(m, m.q2());
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
