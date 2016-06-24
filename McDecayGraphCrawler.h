#ifndef __MCDECAYGRAPHANALYZER_H__
#define __MCDECAYGRAPHANALYZER_H__

#include <vector>
#include <unordered_map>

#include <boost/graph/breadth_first_search.hpp>
#include <CLHEP/Vector/LorentzVector.h>

#include "McDecayGraph.h"
#include "McDecayGraphSummary.h"
#include "BToDlnuMode.h"

class McDecayGraphCrawler {

  private:

    using VertexProperties = McDecayGraphVtxProp;
    using Graph = McDecayGraph;
    using Vertex = McDecayGraphTraits::vertex_descriptor;
    using VertexIter = McDecayGraphTraits::vertex_iterator;
    using InEdgeIter = McDecayGraphTraits::in_edge_iterator;
    using OutEdgeIter = McDecayGraphTraits::out_edge_iterator;
    using IntPropertyMap = McDecayGraphIntPM;
    using DoublePropertyMap = McDecayGraphDoublePM;
    using LorentzPropertyMap = McDecayGraphLorentzPM;

  public: 

    McDecayGraphCrawler() {};
    ~McDecayGraphCrawler() {};

    void analyze(Graph g);

    std::vector<BToDlnuMode> get_bdlnu() { return bdlnu_; }

  private:
    void clear_cache();
    void extract_bdlnu(const McDecayGraphSummary &data);

  private:
    std::vector<BToDlnuMode> bdlnu_;
    IntPropertyMap lund_pm_;
    LorentzPropertyMap lorentz_pm_;
    LorentzPropertyMap lorentz_cm_pm_;

};

class McGraphBfsVisitor : public boost::default_bfs_visitor {

  public:
    using Graph = McDecayGraph;
    using Vertex = McDecayGraphTraits::vertex_descriptor;
    using Edge = McDecayGraphTraits::edge_descriptor;

  public:

    McGraphBfsVisitor(McDecayGraphSummary &result,
                      const McDecayGraphIntPM &lund_pm); 

    void tree_edge(Edge e, const Graph &g);

  private:
    McDecayGraphSummary &summary_;
    McDecayGraphIntPM lund_pm_;

};

#endif
