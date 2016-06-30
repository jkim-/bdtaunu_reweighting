#ifndef __BTODLNUANALYZER_H__
#define __BTODLNUANALYZER_H__

#include <vector>

#include "McDecayGraph.h"
#include "McDecayModeCurator.h"
#include "BSemiLepDict.h"
#include "BToDlnuMode.h"

class BToDlnuAnalyzer {

  public:
    using Graph = McDecayGraph;
    using Vertex = McDecayGraphTraits::vertex_descriptor;
    using ConstIntPropertyMap = ConstMcDecayGraphIntPM;
    using ConstLorentzPropertyMap = ConstMcDecayGraphLorentzPM;

  public:

    void analyze(const Graph &g, const McDecayModeSummary &summary);

    const std::vector<BToDlnuMode>& bdlnu() const { return bdlnu_; }

  private:
    std::vector<BToDlnuMode> bdlnu_;

    BSemiLepDict bsl_dict_;

    ConstIntPropertyMap lund_pm_;
    ConstLorentzPropertyMap lorentz_pm_;
};

#endif
