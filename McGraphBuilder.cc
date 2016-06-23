#include "McGraphBuilder.h"

void McGraphBuilder::clear_cache() {
  g_.clear();
  mcidx2vtx_.clear();
}


void McGraphBuilder::set_graph(int n_vertices, int n_edges,
  const std::vector<int> &from_vertices,
  const std::vector<int> &to_vertices,
  const std::vector<int> &lund_id,
  const std::vector<float> &mcmass,
  const std::vector<float> &mcp3,
  const std::vector<float> &mccosth,
  const std::vector<float> &mcphi) {

  clear_cache();

  construct_graph(g_, n_vertices, n_edges, from_vertices, to_vertices);

  populate_attributes(g_, lund_id, mcmass, mcp3, mccosth, mcphi);

  rip_irrelevant_particles(g_);

  mcidx2vtx_.clear();
  VertexIter vi, vi_end;
  for (std::tie(vi, vi_end) = vertices(g_);
       vi != vi_end; ++vi) {
    mcidx2vtx_[g_[*vi].idx_] = *vi;
  }
}

void McGraphBuilder::construct_graph(
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

void McGraphBuilder::populate_attributes(Graph &g, 
    const std::vector<int> &lund_id,
    const std::vector<float> &mcmass,
    const std::vector<float> &mcp3,
    const std::vector<float> &mccosth,
    const std::vector<float> &mcphi) {

  assert(lund_id.size() == num_vertices(g));
  assert(mcmass.size() == num_vertices(g));
  assert(mcp3.size() == num_vertices(g));
  assert(mccosth.size() == num_vertices(g));
  assert(mcphi.size() == num_vertices(g));

  // populate attributes
  VertexIter vi, vi_end;
  for (std::tie(vi, vi_end) = vertices(g); vi != vi_end; ++vi) {
    g[*vi].lund_id_ = lund_id[g[*vi].idx_];
    g[*vi].mass_ = mcmass[g[*vi].idx_];
    g[*vi].p3mag_ = mcp3[g[*vi].idx_];
    g[*vi].costh_ = mccosth[g[*vi].idx_];
    g[*vi].phi_ = mcphi[g[*vi].idx_];
  }
}

void McGraphBuilder::rip_irrelevant_particles(Graph &g) {

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
