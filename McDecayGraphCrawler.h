#ifndef __MCDECAYGRAPHANALYZER_H__
#define __MCDECAYGRAPHANALYZER_H__

#include <vector>
#include <unordered_map>

#include <boost/graph/breadth_first_search.hpp>

#include "McDecayGraph.h"
#include "McDecayGraphSummary.h"

// class that curates information from a McDecayGraph
class McDecayGraphCrawler {

  private:

    using VertexProperties = McDecayGraphVtxProp;
    using Graph = McDecayGraph;
    using Vertex = McDecayGraphTraits::vertex_descriptor;
    using VertexIter = McDecayGraphTraits::vertex_iterator;
    using ConstIntPropertyMap = ConstMcDecayGraphIntPM;

  public: 

    McDecayGraphCrawler();
    ~McDecayGraphCrawler() {};

    // curate information from graph `g` and store the results to `summary`
    void analyze(const Graph &g, McDecayGraphSummary &summary);

};

// visitor customized for the curation
class McGraphBfsVisitor : public boost::default_bfs_visitor {

  public:
    using Graph = McDecayGraph;
    using Vertex = McDecayGraphTraits::vertex_descriptor;
    using Edge = McDecayGraphTraits::edge_descriptor;

  public:

    McGraphBfsVisitor(McDecayGraphSummary &result,
                      ConstMcDecayGraphIntPM &lund_pm); 

    void tree_edge(Edge e, const Graph &g);

  private:
    McDecayGraphSummary &summary_;
    ConstMcDecayGraphIntPM lund_pm_;

};

#endif
