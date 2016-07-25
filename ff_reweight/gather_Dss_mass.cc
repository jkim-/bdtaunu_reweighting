#include <cmath>
#include <iostream>
#include <vector>
#include <fstream>
#include <string>

#include <CLHEP/Vector/LorentzVector.h>

#include <PsqlReader.h>
#include <pgstring_utils.h>
#include <ff_reweight_constants.h>

#include "ff_reweight_utils.h"

#include "McDecayGraph.h"
#include "McDecayModeCurator.h"
#include "FormFactorAnalyzer.h"
#include "BToDlnuMode.h"

namespace pu = pgstring_utils;

int main() {

  // open database connection and populate fields
  std::string dbname = "bdtaunuhad_lite";
  std::string table_name = "ff_reweight_inputs_small";
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

  // initialize worker classes
  McDecayGraphFactory graph_factory;
  McDecayModeSummary summary;
  McDecayModeCurator curator;
  FormFactorAnalyzer analyzer;

  // output file
  std::ofstream D0ss0_fout("D0ss0.csv");
  std::ofstream D0ssc_fout("D0ssc.csv");
  std::ofstream D10_fout("D10.csv");
  std::ofstream D1c_fout("D1c.csv");
  std::ofstream D20_fout("D20.csv");
  std::ofstream D2c_fout("D2c.csv");
  std::ofstream D1prime0_fout("D1prime0.csv");
  std::ofstream D1primec_fout("D1primec.csv");

  // main loop
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

    std::vector<CLHEP::HepLorentzVector> lorentz = 
      make_lorentz_vector(mcenergy, mcp3, mccosth, mcphi);
    std::vector<CLHEP::HepLorentzVector> lorentz_cm = 
      make_lorentz_vector(mcenergycm, mcp3cm, mccosthcm, mcphicm);

    McDecayGraph g = graph_factory.create_graph(
        mc_n_vertices, mc_n_edges, 
        mc_from_vertices, mc_to_vertices, 
        mc_lund_id, mcmass, lorentz, lorentz_cm);
    curator.curate(g, summary);
    analyzer.analyze(g, summary);

    for (const auto &sl : analyzer.bdsslnu()) {
      switch (abs(sl.Xlund())) {
        case D1pLund:
          D1c_fout << sl.XLab().m() << std::endl;
          break;
        case D10Lund:
          D10_fout << sl.XLab().m() << std::endl;
          break;
        case D2pLund:
          D2c_fout << sl.XLab().m() << std::endl;
          break;
        case D20Lund:
          D20_fout << sl.XLab().m() << std::endl;
          break;
        case D1primepLund:
          D1primec_fout << sl.XLab().m() << std::endl;
          break;
        case D1prime0Lund:
          D1prime0_fout << sl.XLab().m() << std::endl;
          break;
        case D0sspLund:
          D0ssc_fout << sl.XLab().m() << std::endl;
          break;
        case D0ss0Lund:
          D0ss0_fout << sl.XLab().m() << std::endl;
          break;
        default:
          ;
      }
    }

  }
  

  // clean up
  psql.close_cursor();
  psql.close_connection();

  return 0;
}
