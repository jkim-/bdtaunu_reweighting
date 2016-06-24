#ifndef __MCDECAYGRAPH_H__
#define __MCDECAYGRAPH_H__

#include <vector>
#include <unordered_map>

#include <boost/graph/adjacency_list.hpp>

#include <CLHEP/Vector/LorentzVector.h>

struct McDecayGraphVtxProp {
  int idx_;
  int lund_id_;
  double mass_;
  CLHEP::HepLorentzVector lorentz_;
  CLHEP::HepLorentzVector lorentz_cm_;
};

using McDecayGraph = boost::adjacency_list<
      boost::listS, boost::listS,
      boost::bidirectionalS, McDecayGraphVtxProp>;

using McDecayGraphTraits = typename boost::graph_traits<McDecayGraph>;
using McDecayGraphIntPM = 
  typename boost::property_map<McDecayGraph, int McDecayGraphVtxProp::*>::type;
using McDecayGraphDoublePM = 
  typename boost::property_map<McDecayGraph, double McDecayGraphVtxProp::*>::type;
using McDecayGraphLorentzPM = 
  typename boost::property_map<
    McDecayGraph, CLHEP::HepLorentzVector McDecayGraphVtxProp::*>::type;

inline McDecayGraphIntPM get_idx_pm(McDecayGraph &g) { 
  return get(&McDecayGraphVtxProp::idx_, g); 
}

inline McDecayGraphIntPM get_lund_pm(McDecayGraph &g) { 
  return get(&McDecayGraphVtxProp::lund_id_, g); 
}

inline McDecayGraphDoublePM get_mass_pm(McDecayGraph &g) { 
  return get(&McDecayGraphVtxProp::mass_, g); 
}

inline McDecayGraphLorentzPM get_lorentz_pm(McDecayGraph &g) { 
  return get(&McDecayGraphVtxProp::lorentz_, g); 
}

inline McDecayGraphLorentzPM get_lorentz_cm_pm(McDecayGraph &g) { 
  return get(&McDecayGraphVtxProp::lorentz_cm_, g); 
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
    using LorentzPropertyMap = McDecayGraphLorentzPM;

  public: 

    McDecayGraphFactory() {};
    ~McDecayGraphFactory() {};

    Graph create_graph(int n_vertices, int n_edges,
      const std::vector<int> &from_vertices,
      const std::vector<int> &to_vertices,
      const std::vector<int> &lund_id,
      const std::vector<float> &mcmass,
      const std::vector<CLHEP::HepLorentzVector> &lorentz,
      const std::vector<CLHEP::HepLorentzVector> &lorentz_cm);


  private:
    void construct_graph(Graph &g,
        int n_vertices, int n_edges,
        const std::vector<int> &from_vertices,
        const std::vector<int> &to_vertices);

    void populate_attributes(Graph &g, 
        const std::vector<int> &lund_id,
        const std::vector<float> &mcmass,
        const std::vector<CLHEP::HepLorentzVector> &lorentz,
        const std::vector<CLHEP::HepLorentzVector> &lorentz_cm);

    void rip_irrelevant_particles(Graph &g);

};

#endif
