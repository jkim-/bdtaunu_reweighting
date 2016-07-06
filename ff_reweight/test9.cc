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
  std::string table_name = "ff_reweight_inputs_small_sp1235";
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
  std::ofstream BDe_fout("BDe.csv");
  std::ofstream BDmu_fout("BDmu.csv");
  std::ofstream BDtau_fout("BDtau.csv");
  std::ofstream BDse_fout("BDse.csv");
  std::ofstream BDsmu_fout("BDsmu.csv");
  std::ofstream BDstau_fout("BDstau.csv");

  std::ofstream BD0e_fout("BD0e.csv");
  std::ofstream BD1e_fout("BD1e.csv");
  std::ofstream BD2e_fout("BD2e.csv");
  std::ofstream BD1primee_fout("BD1primee.csv");

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

    for (const auto &sl : analyzer.bdlnu()) {
      switch (sl.bdlnu_type()) {
        case BToDlnuType::Bc_D0_e:
        case BToDlnuType::B0_Dc_e:
          BDe_fout << sl.w() << std::endl;
          break;
        case BToDlnuType::Bc_D0_mu:
        case BToDlnuType::B0_Dc_mu:
          BDmu_fout << sl.w() << std::endl;
          break;
        case BToDlnuType::Bc_D0_tau:
        case BToDlnuType::B0_Dc_tau:
          BDtau_fout << sl.w() << std::endl;
          break;
        default:
          ;
      }
    }

    for (const auto &sl : analyzer.bdslnu()) {
      switch (sl.bdslnu_type()) {
        case BToDslnuType::Bc_Dstar0_e_Dpi_lminus:
        case BToDslnuType::Bc_Dstar0_e_Dgamma_lminus:
        case BToDslnuType::Bc_Dstar0_e_Dpi_lplus:
        case BToDslnuType::Bc_Dstar0_e_Dgamma_lplus:
        case BToDslnuType::B0_Dstarc_e_Dpi_lminus:
        case BToDslnuType::B0_Dstarc_e_Dgamma_lminus:
        case BToDslnuType::B0_Dstarc_e_Dpi_lplus:
        case BToDslnuType::B0_Dstarc_e_Dgamma_lplus:
          BDse_fout << sl.w() << std::endl;
          break;
        case BToDslnuType::Bc_Dstar0_mu_Dpi_lminus:
        case BToDslnuType::Bc_Dstar0_mu_Dgamma_lminus:
        case BToDslnuType::Bc_Dstar0_mu_Dpi_lplus:
        case BToDslnuType::Bc_Dstar0_mu_Dgamma_lplus:
        case BToDslnuType::B0_Dstarc_mu_Dpi_lminus:
        case BToDslnuType::B0_Dstarc_mu_Dgamma_lminus:
        case BToDslnuType::B0_Dstarc_mu_Dpi_lplus:
        case BToDslnuType::B0_Dstarc_mu_Dgamma_lplus:
          BDsmu_fout << sl.w() << std::endl;
          break;
        case BToDslnuType::Bc_Dstar0_tau_Dpi_lminus:
        case BToDslnuType::Bc_Dstar0_tau_Dgamma_lminus:
        case BToDslnuType::Bc_Dstar0_tau_Dpi_lplus:
        case BToDslnuType::Bc_Dstar0_tau_Dgamma_lplus:
        case BToDslnuType::B0_Dstarc_tau_Dpi_lminus:
        case BToDslnuType::B0_Dstarc_tau_Dgamma_lminus:
        case BToDslnuType::B0_Dstarc_tau_Dpi_lplus:
        case BToDslnuType::B0_Dstarc_tau_Dgamma_lplus:
          BDstau_fout << sl.w() << std::endl;
          break;
        default:
          ;
      }
    }
  

    for (const auto &sl : analyzer.bdsslnu()) {
      switch (sl.bdsslnu_type()) {
        case BToDsslnuType::Bc_D0ss0_e:
        case BToDsslnuType::B0_D0ssc_e:
          BD0e_fout << sl.w() << std::endl;
          break;
        case BToDsslnuType::Bc_D10_e:
        case BToDsslnuType::B0_D1c_e:
          BD1e_fout << sl.w() << std::endl;
          break;
        case BToDsslnuType::Bc_D20_e:
        case BToDsslnuType::B0_D2c_e:
          BD2e_fout << sl.w() << std::endl;
          break;
        case BToDsslnuType::Bc_D1prime0_e:
        case BToDsslnuType::B0_D1primec_e:
          BD1primee_fout << sl.w() << std::endl;
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
