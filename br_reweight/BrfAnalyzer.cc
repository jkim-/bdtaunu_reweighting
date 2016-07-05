#include <ff_reweight_constants.h>

#include "BrfAnalyzer.h"

BrfAnalyzer::BrfAnalyzer(
    const std::string &brf_correction_fname,
    bool ignore_fsr) : 
  ignore_fsr_(ignore_fsr), 
  brf_correction_table_(brf_correction_fname), 
  brf_mode_dict_() {
  clear_cache();
}

BrfAnalyzer::~BrfAnalyzer() {}

void BrfAnalyzer::clear_cache() { 
  brf_correction_weight_ = 1.0;
  b1_brf_mode_ = BrfReweightCode::null;
  b2_brf_mode_ = BrfReweightCode::null;
  return;
}

void BrfAnalyzer::decay_lunds_from_vertices(
    std::vector<int> &decay_lunds, 
    Vertex mother_vertex,
    const std::vector<Vertex> &daughter_vertices) {

    decay_lunds.clear();

    decay_lunds.push_back(lund_pm_[mother_vertex]);
    for (const auto & v : daughter_vertices) {
      decay_lunds.push_back(lund_pm_[v]);
    }
}


void BrfAnalyzer::analyze(
    const Graph &g, const McDecayModeSummary &summary) {

  // initialize cache
  clear_cache();
  lund_pm_ = get_lund_pm(g);

  // do not consider events without exactly 2 B decays. 
  if (summary.b_modes().size() != 2) { return; }

  // analyze b modes
  auto it = summary.b_modes().begin();
  std::vector<int> decay_lunds;
  decay_lunds_from_vertices(decay_lunds, it->first, it->second);
  b1_brf_mode_ = brf_mode_dict_.find(decay_lunds, ignore_fsr_);

  ++it; decay_lunds.clear();
  decay_lunds_from_vertices(decay_lunds, it->first, it->second);
  b2_brf_mode_ = brf_mode_dict_.find(decay_lunds, ignore_fsr_);

  // compute branching fraction correction weight
  brf_correction_weight_ = 1.0;
  if (brf_correction_table_.is_valid_entry(b1_brf_mode_)) {
    brf_correction_weight_ *= brf_correction_table_.brf(b1_brf_mode_);
  }

  if (brf_correction_table_.is_valid_entry(b2_brf_mode_)) {
    brf_correction_weight_ *= brf_correction_table_.brf(b2_brf_mode_);
  }

  return; 
}
