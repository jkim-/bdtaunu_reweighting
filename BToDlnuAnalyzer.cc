#include <CLHEP/Vector/LorentzVector.h>

#include <ff_reweight_constants.h>

#include "BToDlnuAnalyzer.h"

void BToDlnuAnalyzer::analyze(
    const Graph &g, const McDecayModeSummary &summary) {

  bdlnu_.clear(); 
  lund_pm_ = get_lund_pm(g);
  lorentz_pm_ = get_lorentz_pm(g);

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
      CLHEP::HepLorentzVector BLab, XLab, LepLab;
      BLab = lorentz_pm_[u];
      for (const auto & v : it->second) {
        if (is_lepton(lund_pm_[v])) {
          LepLab = lorentz_pm_[v];
        } else if (is_dstar(lund_pm_[v])) {
          XLab = lorentz_pm_[v];
        }
      }
      bdlnu_.push_back({ BLab, XLab, LepLab });
    }
  }
}

