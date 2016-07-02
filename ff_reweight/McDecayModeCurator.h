#ifndef __MCDECAYMODECURATOR_H__
#define __MCDECAYMODECURATOR_H__

#include <vector>
#include <unordered_map>

#include <boost/graph/breadth_first_search.hpp>

#include "McDecayGraph.h"

class McDecayModeSummary {

  public:
    using Vertex = McDecayGraphTraits::vertex_descriptor;

  public:

    McDecayModeSummary() { clear(); }
    ~McDecayModeSummary() {};

    // returns reference to a map associating mother vertices to
    // their daughter vertices
    const std::unordered_map<Vertex, std::vector<Vertex>>& b_modes() const;
    std::unordered_map<Vertex, std::vector<Vertex>>& b_modes();

    const std::unordered_map<Vertex,std::vector<Vertex>>& dstar_modes() const;
    std::unordered_map<Vertex, std::vector<Vertex>>& dstar_modes();

    const std::unordered_map<Vertex,std::vector<Vertex>>& d_modes() const;
    std::unordered_map<Vertex, std::vector<Vertex>>& d_modes();

    // clears cached information
    void clear();

  private:

    std::unordered_map<Vertex, std::vector<Vertex>> b_modes_;
    std::unordered_map<Vertex, std::vector<Vertex>> dstar_modes_;
    std::unordered_map<Vertex, std::vector<Vertex>> d_modes_;
};


class McDecayModeCurator {

  private:

    using Graph = McDecayGraph;
    using Vertex = McDecayGraphTraits::vertex_descriptor;
    using VertexIter = McDecayGraphTraits::vertex_iterator;
    using ConstIntPropertyMap = ConstMcDecayGraphIntPM;

  public:

    McDecayModeCurator();
    ~McDecayModeCurator() {};

    // curate information from graph `g` and store the results to `summary`
    void curate(const Graph &g, McDecayModeSummary &summary);

};


// visitor customized for the curation
class McDecayModeVisitor : public boost::default_bfs_visitor {

  public:
    using Graph = McDecayGraph;
    using Vertex = McDecayGraphTraits::vertex_descriptor;
    using Edge = McDecayGraphTraits::edge_descriptor;

  public:

    McDecayModeVisitor(McDecayModeSummary &result,
                      ConstMcDecayGraphIntPM &lund_pm); 

    void tree_edge(Edge e, const Graph &g);

  private:
    McDecayModeSummary &summary_;
    ConstMcDecayGraphIntPM &lund_pm_;

};


#include "McDecayModeCuratorImpl.h"


#endif
