#ifndef __MCDECAYGRAPHANALYZER_H__
#define __MCDECAYGRAPHANALYZER_H__

#include <vector>
#include <unordered_map>

#include <boost/graph/breadth_first_search.hpp>

#include "McDecayGraph.h"
#include "BToDlnuMode.h"

class McDecayGraphAnalyzer {

  private:

    using VertexProperties = McDecayGraphVtxProp;
    using Graph = McDecayGraph;
    using Vertex = McDecayGraphTraits::vertex_descriptor;
    using VertexIter = McDecayGraphTraits::vertex_iterator;
    using InEdgeIter = McDecayGraphTraits::in_edge_iterator;
    using OutEdgeIter = McDecayGraphTraits::out_edge_iterator;
    using IntPropertyMap = McDecayGraphIntPM;
    using DoublePropertyMap = McDecayGraphDoublePM;

  public: 

    McDecayGraphAnalyzer() {};
    ~McDecayGraphAnalyzer() {};

    void analyze(Graph g);

  private:
    void clear_cache();

  private:
    std::vector<BToDlnuMode> bdlnu_;

};

struct McDecayGraphData {

  public:
    using Vertex = McDecayGraphTraits::vertex_descriptor;

  public:
    std::unordered_map<Vertex, std::vector<Vertex>> b_mesons_;
    std::unordered_map<Vertex, std::vector<Vertex>> dstar_mesons_;
    
    void clear();
};

class McGraphBfsCrawler : public boost::default_bfs_visitor {

  public:
    using Graph = McDecayGraph;
    using Vertex = McDecayGraphTraits::vertex_descriptor;
    using Edge = McDecayGraphTraits::edge_descriptor;

  public:

    McGraphBfsCrawler(McDecayGraphData &result,
                      const McDecayGraphIntPM &lund_pm); 

    void tree_edge(Edge e, const Graph &g);

  private:
    McDecayGraphData &crawled_result_;
    McDecayGraphIntPM lund_pm_;

};

#endif
