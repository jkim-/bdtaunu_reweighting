#ifndef __BRFANALYZER_H__
#define __BRFANALYZER_H__

#include <vector>
#include <string>

#include "McLundGraph.h"
#include "McDecayModeCurator.h"

#include "BrfReweightDict.h"
#include "BrfCorrectionTable.h"

class BrfAnalyzer {

  public:
    using Graph = McLundGraph;
    using Vertex = McLundGraphTraits::vertex_descriptor;
    using ConstIntPropertyMap = ConstMcLundGraphIntPM;

  public:

    BrfAnalyzer(const std::string &brf_correction_fname, 
                bool ignore_fsr=true);
    ~BrfAnalyzer();

    void analyze(const Graph &g, const McDecayModeSummary &summary);

    double brf_correction_weight() const { return brf_correction_weight_; }
    BrfReweightCode b1_brf_mode() const { return b1_brf_mode_; }
    BrfReweightCode b2_brf_mode() const { return b2_brf_mode_; }
    std::string b1_brf_mode_string() const { return brfcode2string(b1_brf_mode_); }
    std::string b2_brf_mode_string() const { return brfcode2string(b2_brf_mode_); }

  private:
    void clear_cache();

    void decay_lunds_from_vertices(
        std::vector<int>&, Vertex, const std::vector<Vertex>&);

  private:
    bool ignore_fsr_;
    BrfCorrectionTable brf_correction_table_;
    BrfReweightDict brf_mode_dict_;

    double brf_correction_weight_;
    BrfReweightCode b1_brf_mode_;
    BrfReweightCode b2_brf_mode_;

    ConstIntPropertyMap lund_pm_;

};

#endif
