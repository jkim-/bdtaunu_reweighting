#include <iostream>
#include <vector>
#include <fstream>
#include <string>

#include <PsqlReader.h>
#include <pgstring_utils.h>

#include "McDecayGraph.h"
#include "ParticleGraphWriter.h"

namespace pu = pgstring_utils;

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

  McDecayGraphFactory graph_factory;
  McDecayGraph g = graph_factory.create_graph(mc_n_vertices, mc_n_edges, 
      mc_from_vertices, mc_to_vertices, 
      mc_lund_id, mcmass, mcp3, mccosth, mcphi);
  

  auto index_pm = get_idx_pm(g);
  /*auto lund_pm = get_lund_pm(g);
  print_graph(std::cout, g, index_pm, 
              make_lund_id_writer(lund_pm, "pdt.dat"));*/

  auto mass_pm = get_mass_pm(g);
  print_graph(std::cout, g, index_pm, 
              make_basic_graph_writer(mass_pm));


  // clean up
  psql.close_cursor();
  psql.close_connection();

  return 0;
}
