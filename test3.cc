#include <iostream>
#include <vector>
#include <fstream>
#include <string>

#include <PsqlReader.h>
#include <CsvWriter.h>
#include <pgstring_utils.h>

#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/depth_first_search.hpp>

#include "ParticleGraphWriter.h"

namespace pu = pgstring_utils;

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


void construct_graph(Graph &g,
    int n_vertices, int n_edges,
    const std::vector<int> &from_vertices,
    const std::vector<int> &to_vertices) {

  // check for argument consistency
  if (from_vertices.size() != static_cast<unsigned>(n_edges)) {
    throw std::invalid_argument(
        "TruthMatcher::construct_graph(): n_vertices and "
        "from_vertices.size() must agree. "
    );
  }

  if (to_vertices.size() != from_vertices.size()) {
    throw std::invalid_argument(
        "construct_graph(): from_vertices.size() "
        "must agree with to_vertices.size(). "
    );
  }

  // clear the graph
  g.clear();

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

void populate_attributes(Graph &g, 
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

void rip_irrelevant_particles(Graph &g) {

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


void construct_particle_decay_graph(
    Graph &g,
    int n_vertices, int n_edges,
    const std::vector<int> &from_vertices, 
    const std::vector<int> &to_vertices, 
    const std::vector<int> &lund_id, 
    const std::vector<float> &mcmass,
    const std::vector<float> &mcp3,
    const std::vector<float> &mccosth,
    const std::vector<float> &mcphi) {

  g.clear();

  // build the graph
  construct_graph(
      g, n_vertices, n_edges, 
      from_vertices, to_vertices);

  // attach internal properties
  populate_attributes(g, lund_id, mcmass, mcp3, mccosth, mcphi);

  // remove irrelevant particles
  //rip_irrelevant_particles(g);

}

int main() {

  // open database connection and populate fields
  std::string dbname = "testing";
  std::string table_name = "ff_reweight_input_sigmc";
  int cursor_fetch_size = 5000;

  PsqlReader psql;
  psql.open_connection("dbname="+dbname);
  psql.open_cursor(table_name, { 
        "eid", 
        "mc_n_vertices", "mc_n_edges",
        "mc_from_vertices", "mc_to_vertices", 
        "mc_lund_id", "mcmass",
        "mcp3", "mccosth", "mcphi", "mcenergy"
      }, cursor_fetch_size);

  int eid, mc_n_vertices, mc_n_edges;
  std::vector<int> mc_from_vertices, mc_to_vertices, mc_lund_id;
  std::vector<float> mcmass, mcp3, mccosth, mcphi, mcenergy; 

  // serialize
  psql.next();

  pu::string2type(psql.get("eid"), eid);
  pu::string2type(psql.get("mc_n_vertices"), mc_n_vertices);
  pu::string2type(psql.get("mc_n_edges"), mc_n_edges);
  pu::string2type(psql.get("mc_from_vertices"), mc_from_vertices);
  pu::string2type(psql.get("mc_to_vertices"), mc_to_vertices);
  pu::string2type(psql.get("mc_lund_id"), mc_lund_id);
  pu::string2type(psql.get("mcmass"), mcmass);
  pu::string2type(psql.get("mcp3"), mcp3);
  pu::string2type(psql.get("mccosth"), mccosth);
  pu::string2type(psql.get("mcphi"), mcphi);
  pu::string2type(psql.get("mcenergy"), mcenergy);

  Graph g;

  construct_particle_decay_graph(g, 
      mc_n_vertices, mc_n_edges, 
      mc_from_vertices, mc_to_vertices, 
      mc_lund_id, mcmass, mcp3, mccosth, mcphi);

  IntPropertyMap index_pm = get(&VertexProperties::idx_, g);
  IntPropertyMap lund_pm = get(&VertexProperties::lund_id_, g);
  print_graph(std::cout, g, index_pm, 
              make_lund_id_writer(lund_pm, "pdt.dat"));
  /*DoublePropertyMap mass_pm = get(&VertexProperties::mass_, g);
  print_graph(std::cout, g, index_pm, 
              make_basic_graph_writer(mass_pm));*/


  // clean up
  psql.close_cursor();
  psql.close_connection();

  return 0;
}
