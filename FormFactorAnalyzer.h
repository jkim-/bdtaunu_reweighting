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
    void initialize_decay_models();

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
    bool ignore_fsr_;

    std::vector<BToDlnuMode> bdlnu_;
    std::vector<BToDslnuMode> bdslnu_;

    double cln_;

    ConstIntPropertyMap lund_pm_;
    ConstLorentzPropertyMap lorentz_pm_;

    BPlnuDecayRate BcDenu_from_, BcDenu_to_;
    BPlnuDecayRate BcDmunu_from_, BcDmunu_to_;
    BPlnuDecayRate BcDtaunu_from_, BcDtaunu_to_;
    BPlnuDecayRate B0Denu_from_, B0Denu_to_;
    BPlnuDecayRate B0Dmunu_from_, B0Dmunu_to_;
    BPlnuDecayRate B0Dtaunu_from_, B0Dtaunu_to_;

    BVlnuDecayRate BcDsenu_Dpi_lm_from_, BcDsenu_Dpi_lm_to_;
    BVlnuDecayRate BcDsmunu_Dpi_lm_from_, BcDsmunu_Dpi_lm_to_;
    BVlnuDecayRate BcDstaunu_Dpi_lm_from_, BcDstaunu_Dpi_lm_to_;
    BVlnuDecayRate B0Dsenu_Dpi_lm_from_, B0Dsenu_Dpi_lm_to_;
    BVlnuDecayRate B0Dsmunu_Dpi_lm_from_, B0Dsmunu_Dpi_lm_to_;
    BVlnuDecayRate B0Dstaunu_Dpi_lm_from_, B0Dstaunu_Dpi_lm_to_;

    BVlnuDecayRate BcDsenu_Dgamma_lm_from_, BcDsenu_Dgamma_lm_to_;
    BVlnuDecayRate BcDsmunu_Dgamma_lm_from_, BcDsmunu_Dgamma_lm_to_;
    BVlnuDecayRate BcDstaunu_Dgamma_lm_from_, BcDstaunu_Dgamma_lm_to_;
    BVlnuDecayRate B0Dsenu_Dgamma_lm_from_, B0Dsenu_Dgamma_lm_to_;
    BVlnuDecayRate B0Dsmunu_Dgamma_lm_from_, B0Dsmunu_Dgamma_lm_to_;
    BVlnuDecayRate B0Dstaunu_Dgamma_lm_from_, B0Dstaunu_Dgamma_lm_to_;

    BVlnuDecayRate BcDsenu_Dpi_lp_from_, BcDsenu_Dpi_lp_to_;
    BVlnuDecayRate BcDsmunu_Dpi_lp_from_, BcDsmunu_Dpi_lp_to_;
    BVlnuDecayRate BcDstaunu_Dpi_lp_from_, BcDstaunu_Dpi_lp_to_;
    BVlnuDecayRate B0Dsenu_Dpi_lp_from_, B0Dsenu_Dpi_lp_to_;
    BVlnuDecayRate B0Dsmunu_Dpi_lp_from_, B0Dsmunu_Dpi_lp_to_;
    BVlnuDecayRate B0Dstaunu_Dpi_lp_from_, B0Dstaunu_Dpi_lp_to_;

    BVlnuDecayRate BcDsenu_Dgamma_lp_from_, BcDsenu_Dgamma_lp_to_;
    BVlnuDecayRate BcDsmunu_Dgamma_lp_from_, BcDsmunu_Dgamma_lp_to_;
    BVlnuDecayRate BcDstaunu_Dgamma_lp_from_, BcDstaunu_Dgamma_lp_to_;
    BVlnuDecayRate B0Dsenu_Dgamma_lp_from_, B0Dsenu_Dgamma_lp_to_;
    BVlnuDecayRate B0Dsmunu_Dgamma_lp_from_, B0Dsmunu_Dgamma_lp_to_;
    BVlnuDecayRate B0Dstaunu_Dgamma_lp_from_, B0Dstaunu_Dgamma_lp_to_;

};

#endif
