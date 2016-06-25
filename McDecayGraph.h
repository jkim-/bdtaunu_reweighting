#ifndef __MCDECAYGRAPH_H__
#define __MCDECAYGRAPH_H__

#include <vector>
#include <unordered_map>

#include <boost/graph/adjacency_list.hpp>

#include <CLHEP/Vector/LorentzVector.h>

// McDecayGraph definition
// -----------------------

// bundled internal property attached to each vertex of an McDecayGraph
struct McDecayGraphVtxProp {
  int idx_;
  int lund_id_;
  double mass_;
  CLHEP::HepLorentzVector lorentz_;
  CLHEP::HepLorentzVector lorentz_cm_;
};

// McDecayGraph definition
using McDecayGraph = boost::adjacency_list<
      boost::listS, boost::listS,
      boost::bidirectionalS, McDecayGraphVtxProp>;

// Associated typedefs
// -------------------

// graph property traits class
using McDecayGraphTraits = typename boost::graph_traits<McDecayGraph>;

// property map typedefs

using McDecayGraphIntPM = 
  typename boost::property_map<McDecayGraph, int McDecayGraphVtxProp::*>::type;

using ConstMcDecayGraphIntPM = 
  typename boost::property_map<
    McDecayGraph, int McDecayGraphVtxProp::*>::const_type;

using McDecayGraphDoublePM = 
  typename boost::property_map<
    McDecayGraph, double McDecayGraphVtxProp::*>::type;

using ConstMcDecayGraphDoublePM = 
  typename boost::property_map<
    McDecayGraph, double McDecayGraphVtxProp::*>::const_type;

using McDecayGraphLorentzPM = 
  typename boost::property_map<
    McDecayGraph, CLHEP::HepLorentzVector McDecayGraphVtxProp::*>::type;

using ConstMcDecayGraphLorentzPM = 
  typename boost::property_map<
    McDecayGraph, CLHEP::HepLorentzVector McDecayGraphVtxProp::*>::const_type;


// Associated non-member functions
// -------------------------------
    
inline McDecayGraphIntPM get_idx_pm(McDecayGraph &g) { 
  return get(&McDecayGraphVtxProp::idx_, g); 
}
    
inline ConstMcDecayGraphIntPM get_idx_pm(const McDecayGraph &g) { 
  return get(&McDecayGraphVtxProp::idx_, g); 
}

inline McDecayGraphIntPM get_lund_pm(McDecayGraph &g) { 
  return get(&McDecayGraphVtxProp::lund_id_, g); 
}

inline ConstMcDecayGraphIntPM get_lund_pm(const McDecayGraph &g) { 
  return get(&McDecayGraphVtxProp::lund_id_, g); 
}

inline McDecayGraphDoublePM get_mass_pm(McDecayGraph &g) { 
  return get(&McDecayGraphVtxProp::mass_, g); 
}

inline ConstMcDecayGraphDoublePM get_mass_pm(const McDecayGraph &g) { 
  return get(&McDecayGraphVtxProp::mass_, g); 
}

inline McDecayGraphLorentzPM get_lorentz_pm(McDecayGraph &g) { 
  return get(&McDecayGraphVtxProp::lorentz_, g); 
}

inline ConstMcDecayGraphLorentzPM get_lorentz_pm(const McDecayGraph &g) { 
  return get(&McDecayGraphVtxProp::lorentz_, g); 
}

inline McDecayGraphLorentzPM get_lorentz_cm_pm(McDecayGraph &g) { 
  return get(&McDecayGraphVtxProp::lorentz_cm_, g); 
}

inline ConstMcDecayGraphLorentzPM get_lorentz_cm_pm(const McDecayGraph &g) { 
  return get(&McDecayGraphVtxProp::lorentz_cm_, g); 
}


// Graph creation class
// --------------------

class McDecayGraphFactory {

  private:

    using Graph = McDecayGraph;
    using Vertex = McDecayGraphTraits::vertex_descriptor;
    using VertexIter = McDecayGraphTraits::vertex_iterator;
    using InEdgeIter = McDecayGraphTraits::in_edge_iterator;
    using OutEdgeIter = McDecayGraphTraits::out_edge_iterator;

  public: 

    McDecayGraphFactory() {};
    ~McDecayGraphFactory() {};

    // construct and return a McDecayGraph implied 
    // by the given the arguments  
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
