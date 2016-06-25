#ifndef __BTODLNUANALYZER_H__
#define __BTODLNUANALYZER_H__

#include <vector>

#include "McDecayGraph.h"
#include "McDecayGraphSummary.h"
#include "BToDlnuMode.h"

class BToDlnuAnalyzer {

  public:
    using Graph = McDecayGraph;
    using Vertex = McDecayGraphTraits::vertex_descriptor;
    using ConstIntPropertyMap = ConstMcDecayGraphIntPM;
    using ConstLorentzPropertyMap = ConstMcDecayGraphLorentzPM;

  public:
    void analyze(const Graph &g, const McDecayGraphSummary &summary);

    const std::vector<BToDlnuMode>& bdlnu() const { return bdlnu_; }

  private:
    std::vector<BToDlnuMode> bdlnu_;

    ConstIntPropertyMap lund_pm_;
    ConstLorentzPropertyMap lorentz_pm_;
    ConstLorentzPropertyMap lorentz_cm_pm_;
};

#endif
