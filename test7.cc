#include <iostream>
#include <vector>
#include <fstream>
#include <string>

#include <PsqlReader.h>
#include <pgstring_utils.h>

#include "ff_reweight_utils.h"
#include "McDecayGraph.h"
#include "McDecayGraphAnalyzer.h"
#include "ParticleGraphWriter.h"
#include "BToDlnuMode.h"
#include "XSLKin.h"

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
        "mcenergy", "mcp3", "mccosth", "mcphi",
        "mcenergycm", "mcp3cm", "mccosthcm", "mcphicm"
      }, cursor_fetch_size);

  int eid, mc_n_vertices, mc_n_edges;
  std::vector<int> mc_from_vertices, mc_to_vertices, mc_lund_id;
  std::vector<float> mcmass; 
  std::vector<float> mcenergy, mcp3, mccosth, mcphi; 
  std::vector<float> mcenergycm, mcp3cm, mccosthcm, mcphicm; 

  // open output file
  std::ofstream fout("test.csv");

  // serialize
  while (psql.next()) {

    pu::string2type(psql.get("eid"), eid);
    pu::string2type(psql.get("mc_n_vertices"), mc_n_vertices);
    pu::string2type(psql.get("mc_n_edges"), mc_n_edges);
    pu::string2type(psql.get("mc_from_vertices"), mc_from_vertices);
    pu::string2type(psql.get("mc_to_vertices"), mc_to_vertices);
    pu::string2type(psql.get("mc_lund_id"), mc_lund_id);
    pu::string2type(psql.get("mcmass"), mcmass);
    pu::string2type(psql.get("mcenergy"), mcenergy);
    pu::string2type(psql.get("mcp3"), mcp3);
    pu::string2type(psql.get("mccosth"), mccosth);
    pu::string2type(psql.get("mcphi"), mcphi);
    pu::string2type(psql.get("mcenergycm"), mcenergycm);
    pu::string2type(psql.get("mcp3cm"), mcp3cm);
    pu::string2type(psql.get("mccosthcm"), mccosthcm);
    pu::string2type(psql.get("mcphicm"), mcphicm);

    std::vector<HepLorentzVector> lorentz_vectors = 
      make_lorentz_vector(mcenergy, mcp3, mccosth, mcphi);
    std::vector<HepLorentzVector> lorentz_vectors_cm = 
      make_lorentz_vector(mcenergycm, mcp3cm, mccosthcm, mcphicm);

    std::cout << lorentz_vectors_cm[2].m() << " ";

    /*McDecayGraphFactory graph_factory;
    McDecayGraph g = graph_factory.create_graph(mc_n_vertices, mc_n_edges, 
        mc_from_vertices, mc_to_vertices, 
        mc_lund_id, mcmass, mcenergycm, mcenergy, mcp3, mccosth, mcphi);

    McDecayGraphAnalyzer analyzer;
    analyzer.analyze(g);

    std::vector<BToDlnuMode> bdlnu = analyzer.get_bdlnu();
    for (auto it = bdlnu.begin(); it != bdlnu.end(); ++it) {
      XSLKin kin(it->get_BLab(), it->get_LepLab(), it->get_XLab());
      fout << kin.q2() << " ";
      fout << (it->get_ecmLep()) << std::endl;
    }*/

  }
  

  // clean up
  psql.close_cursor();
  psql.close_connection();

  return 0;
}
