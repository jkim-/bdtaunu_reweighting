#ifndef __FORMFACTORANALYZER_H__
#define __FORMFACTORANALYZER_H__

#include <vector>

#include "McDecayGraph.h"
#include "McDecayModeCurator.h"
#include "BSemiLepDict.h"
#include "BToDlnuMode.h"
#include "BToDslnuMode.h"

class FormFactorAnalyzer {

  public:
    using Graph = McDecayGraph;
    using Vertex = McDecayGraphTraits::vertex_descriptor;
    using ConstIntPropertyMap = ConstMcDecayGraphIntPM;
    using ConstLorentzPropertyMap = ConstMcDecayGraphLorentzPM;

  public:

    FormFactorAnalyzer();
    FormFactorAnalyzer(bool ignore_fsr);
    ~FormFactorAnalyzer();

    void analyze(const Graph &g, const McDecayModeSummary &summary);

    double cln_weight() const { return cln_; }

    const std::vector<BToDlnuMode>& bdlnu() const { return bdlnu_; }
    const std::vector<BToDslnuMode>& bdslnu() const { return bdslnu_; }

  private:
    void clear_cache();

    void decay_lunds_from_vertices(
        std::vector<int>&, Vertex, const std::vector<Vertex>&);

    void collect_decay_modes(
        const Graph&, const McDecayModeSummary&);

    BToDlnuMode create_bdlnu_mode(Vertex, const std::vector<Vertex>&);
    BToDslnuMode create_bdslnu_mode(Vertex,
        const std::vector<Vertex>&, const McDecayModeSummary&);

  private:

    BSemiLepDict bsl_dict_;
    bool ignore_fsr_;

    std::vector<BToDlnuMode> bdlnu_;
    std::vector<BToDslnuMode> bdslnu_;

    double cln_;

    ConstIntPropertyMap lund_pm_;
    ConstLorentzPropertyMap lorentz_pm_;
};

#endif
