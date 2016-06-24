#ifndef __MCDECAYGRAPH_H__
#define __MCDECAYGRAPH_H__

#include <vector>
#include <unordered_map>

#include <boost/graph/adjacency_list.hpp>

struct McDecayGraphVtxProp {
  int idx_;
  int lund_id_;
  double mass_;
  double energycm_;
  double energy_;
  double p3mag_;
  double costh_;
  double phi_;
};

using McDecayGraph = boost::adjacency_list<
      boost::listS, boost::listS,
      boost::bidirectionalS, McDecayGraphVtxProp>;

using McDecayGraphTraits = typename boost::graph_traits<McDecayGraph>;
using McDecayGraphIntPM = 
  typename boost::property_map<McDecayGraph, int McDecayGraphVtxProp::*>::type;
using McDecayGraphDoublePM = 
  typename boost::property_map<McDecayGraph, double McDecayGraphVtxProp::*>::type;

inline McDecayGraphIntPM get_idx_pm(McDecayGraph &g) { 
  return get(&McDecayGraphVtxProp::idx_, g); 
}

inline McDecayGraphIntPM get_lund_pm(McDecayGraph &g) { 
  return get(&McDecayGraphVtxProp::lund_id_, g); 
}

inline McDecayGraphDoublePM get_mass_pm(McDecayGraph &g) { 
  return get(&McDecayGraphVtxProp::mass_, g); 
}

inline McDecayGraphDoublePM get_energycm_pm(McDecayGraph &g) { 
  return get(&McDecayGraphVtxProp::energycm_, g); 
}

inline McDecayGraphDoublePM get_energy_pm(McDecayGraph &g) { 
  return get(&McDecayGraphVtxProp::energy_, g); 
}

inline McDecayGraphDoublePM get_p3mag_pm(McDecayGraph &g) { 
  return get(&McDecayGraphVtxProp::p3mag_, g); 
}

inline McDecayGraphDoublePM get_costh_pm(McDecayGraph &g) { 
  return get(&McDecayGraphVtxProp::costh_, g); 
}

inline McDecayGraphDoublePM get_phi_pm(McDecayGraph &g) { 
  return get(&McDecayGraphVtxProp::phi_, g); 
}


class McDecayGraphFactory {

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

    McDecayGraphFactory() {};
    ~McDecayGraphFactory() {};

    Graph create_graph(int n_vertices, int n_edges,
      const std::vector<int> &from_vertices,
      const std::vector<int> &to_vertices,
      const std::vector<int> &lund_id,
      const std::vector<float> &mcmass,
      const std::vector<float> &mcenergycm,
      const std::vector<float> &mcenergy,
      const std::vector<float> &mcp3,
      const std::vector<float> &mccosth,
      const std::vector<float> &mcphi);


  private:
    void construct_graph(Graph &g,
        int n_vertices, int n_edges,
        const std::vector<int> &from_vertices,
        const std::vector<int> &to_vertices);

    void populate_attributes(Graph &g, 
        const std::vector<int> &lund_id,
        const std::vector<float> &mcmass,
        const std::vector<float> &mcenergycm,
        const std::vector<float> &mcenergy,
        const std::vector<float> &mcp3,
        const std::vector<float> &mccosth,
        const std::vector<float> &mcphi);

    void rip_irrelevant_particles(Graph &g);

};

#endif
