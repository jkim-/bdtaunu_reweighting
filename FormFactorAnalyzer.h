#ifndef __FORMFACTORANALYZER_H__
#define __FORMFACTORANALYZER_H__

#include <vector>

#include <BPlnuDecayRate.h>
#include <BVlnuDecayRate.h>

#include "McDecayGraph.h"
#include "McDecayModeCurator.h"
#include "BSemiLepDict.h"
#include "BToDlnuMode.h"
#include "BToDslnuMode.h"
#include "CLNReweighter.h"

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

    double compute_bdlnu_cln_weights(const BToDlnuMode&, double);
    double compute_bdslnu_cln_weights(const BToDslnuMode&, 
        double, double, double, double);
    void compute_ff_weights();


  private:

    BSemiLepDict bsl_dict_;
    CLNReweighter cln_reweighter_;
    bool ignore_fsr_;

    std::vector<BToDlnuMode> bdlnu_;
    std::vector<BToDslnuMode> bdslnu_;

    double cln_;

    ConstIntPropertyMap lund_pm_;
    ConstLorentzPropertyMap lorentz_pm_;

};

#endif
