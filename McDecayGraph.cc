#include "McDecayGraph.h"

McDecayGraphFactory::Graph 
McDecayGraphFactory::create_graph(int n_vertices, int n_edges,
  const std::vector<int> &from_vertices,
  const std::vector<int> &to_vertices,
  const std::vector<int> &lund_id,
  const std::vector<float> &mcmass,
  const std::vector<CLHEP::HepLorentzVector> &lorentz,
  const std::vector<CLHEP::HepLorentzVector> &lorentz_cm) {

  Graph g;

  construct_graph(g, n_vertices, n_edges, from_vertices, to_vertices);

  populate_attributes(g, lund_id, mcmass, lorentz, lorentz_cm);

  rip_irrelevant_particles(g);

  return g;

}

void McDecayGraphFactory::construct_graph(
    Graph &g,
    int n_vertices, int n_edges,
    const std::vector<int> &from_vertices,
    const std::vector<int> &to_vertices) {

  // check for argument consistency
  assert(from_vertices.size() == static_cast<unsigned>(n_vertices));
  assert(from_vertices.size() == to_vertices.size());

  // establish a mapping between vertex index and vertex descriptors
  std::vector<Vertex> vertex_map(n_vertices);

  // insert vertices and bind internal properties
  for (int i = 0; i < n_vertices; ++i) {
    Vertex u = boost::add_vertex(g);
    vertex_map[i] = u;
    g[u].idx_ = i;
  }

  // insert edges
  for (int i = 0; i < n_edges; ++i) {
    boost::add_edge(vertex_map[from_vertices[i]],
                    vertex_map[to_vertices[i]], g);
  }
}

void McDecayGraphFactory::populate_attributes(Graph &g, 
    const std::vector<int> &lund_id,
    const std::vector<float> &mcmass,
    const std::vector<CLHEP::HepLorentzVector> &lorentz,
    const std::vector<CLHEP::HepLorentzVector> &lorentz_cm) {

  assert(lund_id.size() == num_vertices(g));
  assert(mcmass.size() == num_vertices(g));
  assert(lorentz.size() == num_vertices(g));
  assert(lorentz_cm.size() == num_vertices(g));

  // populate attributes
  VertexIter vi, vi_end;
  for (std::tie(vi, vi_end) = vertices(g); vi != vi_end; ++vi) {
    g[*vi].lund_id_ = lund_id[g[*vi].idx_];
    g[*vi].mass_ = mcmass[g[*vi].idx_];
    g[*vi].lorentz_ = lorentz[g[*vi].idx_];
    g[*vi].lorentz_cm_ = lorentz_cm[g[*vi].idx_];
  }
}

void McDecayGraphFactory::rip_irrelevant_particles(Graph &g) {

  // set of particles that need to be ripped. keyed by mc idx_.
  std::unordered_set<int> to_rip;

  // stage the incoming e+ and e- particles for ripping
  // their mc indices are 0 and 1 by construction
  to_rip.insert(0);
  to_rip.insert(1);

  // rip vertices by contracting with its mother. in the case of 
  // no mothers, the procedure is equivalent to just removing 
  // the vertex and outgoing edges. 
  //
  // be careful with iterator invalidation
  VertexIter vi, vi_end;
  VertexIter next; std::tie(vi, vi_end) = vertices(g);
  for (next = vi; vi != vi_end; vi = next) {
    ++next;

    if (to_rip.find(g[*vi].idx_) != to_rip.end()) {

      // add edges from mother to daughters
      InEdgeIter ie, ie_end;
      for (std::tie(ie, ie_end) = in_edges(*vi, g); ie != ie_end; ++ie) {
        Vertex u = source(*ie, g);

        OutEdgeIter oe, oe_end;
        for (std::tie(oe, oe_end) = out_edges(*vi, g); oe != oe_end; ++oe) {
          Vertex v = target(*oe, g);
          add_edge(u, v, g);
        }
      }

      // clear and remove the vertex
      clear_vertex(*vi, g);
      remove_vertex(*vi, g);
    }
  }
}
