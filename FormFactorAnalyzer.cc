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

void FormFactorAnalyzer::analyze(
    const Graph &g, const McDecayModeSummary &summary) {

  // initialize cache
  clear_cache();
  lund_pm_ = get_lund_pm(g);
  lorentz_pm_ = get_lorentz_pm(g);

  // populate semileptonic decay mode objects
  collect_decay_modes(g, summary);

  return; 
}
