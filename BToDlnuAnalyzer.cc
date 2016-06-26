#include <CLHEP/Vector/LorentzVector.h>

#include "ff_reweight_defs.h"
#include "BToDlnuAnalyzer.h"

void BToDlnuAnalyzer::analyze(
    const Graph &g, const McDecayGraphSummary &summary) {

  bdlnu_.clear(); 
  lund_pm_ = get_lund_pm(g);
  lorentz_pm_ = get_lorentz_pm(g);
  lorentz_cm_pm_ = get_lorentz_cm_pm(g);

  for (auto it = summary.b_modes().begin();
       it != summary.b_modes().end(); ++it) {

    std::vector<int> decay_lunds;

    Vertex u = it->first;
    decay_lunds.push_back(lund_pm_[u]);
    for (const auto & v : it->second) {
      decay_lunds.push_back(lund_pm_[v]);
    }

    BSemiLepCode sl_code = bsl_dict_.find(decay_lunds);
    if (sl_code == BSemiLepCode::B_Dstar_e) {
      CLHEP::HepLorentzVector BLab, BCM, XLab, XCM, LepLab, LepCM;
      BLab = lorentz_pm_[u];
      BCM = lorentz_cm_pm_[u];
      for (const auto & v : it->second) {
        if (is_lepton(lund_pm_[v])) {
          LepLab = lorentz_pm_[v];
          LepCM = lorentz_cm_pm_[v];
        } else if (is_dstar(lund_pm_[v])) {
          XLab = lorentz_pm_[v];
          XCM = lorentz_cm_pm_[v];
        }
      }
      bdlnu_.push_back({ BLab, XLab, LepLab, BCM, XCM, LepCM});
    }
  }

  /*for (auto it = summary.b_modes().begin();
       it != summary.b_modes().end(); ++it) {

    if (it->second.size() != 3) continue;

    CLHEP::HepLorentzVector BLab, BCM, XLab, XCM, LepLab, LepCM;

    Vertex u = it->first;
    BLab = lorentz_pm_[u];
    BCM = lorentz_cm_pm_[u];

    bool has_neutrino = false, has_lepton = false, has_dmeson = false;
    for (const auto & v : it->second) {
      if (is_neutrino(lund_pm_[v])) {
        has_neutrino = true;
      } else if (is_lepton(lund_pm_[v])) {
        has_lepton = true;
        LepLab = lorentz_pm_[v];
        LepCM = lorentz_cm_pm_[v];
      } else if (is_dmeson(lund_pm_[v])) {
        has_dmeson = true;
        XLab = lorentz_pm_[v];
        XCM = lorentz_cm_pm_[v];
      }
    }

    if (has_neutrino && has_lepton && has_dmeson) {
      bdlnu_.push_back({ BLab, XLab, LepLab, BCM, XCM, LepCM});
    }
  }
  */
}

