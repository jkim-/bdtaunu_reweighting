#ifndef __MCGRAPHBUILDER_H__
#define __MCGRAPHBUILDER_H__

#include <vector>
#include <unordered_map>

#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/depth_first_search.hpp>

class McGraphBuilder {

  public:

    struct VertexProperties {
      int idx_;
      int lund_id_;
      double mass_;
      double p3mag_;
      double costh_;
      double phi_;
    };

    using Graph = boost::adjacency_list<
          boost::listS, boost::listS,
          boost::bidirectionalS, VertexProperties>;

    using Vertex = typename boost::graph_traits<Graph>::vertex_descriptor;
    using VertexIter = typename boost::graph_traits<Graph>::vertex_iterator;
    using InEdgeIter = typename boost::graph_traits<Graph>::in_edge_iterator;
    using OutEdgeIter = typename boost::graph_traits<Graph>::out_edge_iterator;

    using IntPropertyMap = boost::property_map<
          Graph, int VertexProperties::*>::type;
    using DoublePropertyMap = boost::property_map<
          Graph, double VertexProperties::*>::type;

  public: 

    McGraphBuilder() {};
    ~McGraphBuilder() {};

    void set_graph(int n_vertices, int n_edges,
      const std::vector<int> &from_vertices,
      const std::vector<int> &to_vertices,
      const std::vector<int> &lund_id,
      const std::vector<float> &mcmass,
      const std::vector<float> &mcp3,
      const std::vector<float> &mccosth,
      const std::vector<float> &mcphi);

    Graph get_graph() const { return g_; }
    IntPropertyMap get_idx_pm() { return get(&VertexProperties::idx_, g_); }
    IntPropertyMap get_lund_pm() { return get(&VertexProperties::lund_id_, g_); }
    DoublePropertyMap get_mass_pm() { return get(&VertexProperties::mass_, g_); }
    DoublePropertyMap get_p3mag_pm() { return get(&VertexProperties::p3mag_, g_); }
    DoublePropertyMap get_costh_pm() { return get(&VertexProperties::costh_, g_); }
    DoublePropertyMap get_phi_pm() { return get(&VertexProperties::phi_, g_); }


  private:
    void clear_cache();

    void construct_graph(Graph &g,
        int n_vertices, int n_edges,
        const std::vector<int> &from_vertices,
        const std::vector<int> &to_vertices);

    void populate_attributes(Graph &g, 
        const std::vector<int> &lund_id,
        const std::vector<float> &mcmass,
        const std::vector<float> &mcp3,
        const std::vector<float> &mccosth,
        const std::vector<float> &mcphi);

    void rip_irrelevant_particles(Graph &g);

  private:
    Graph g_;
    std::unordered_map<int, Vertex> mcidx2vtx_;

};

#endif
