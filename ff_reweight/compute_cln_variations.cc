#include <cmath>
#include <iostream>
#include <vector>
#include <fstream>
#include <string>

#include <boost/program_options.hpp>

#include <CLHEP/Vector/LorentzVector.h>

#include <PsqlReader.h>
#include <CsvWriter.h>
#include <pgstring_utils.h>
#include <ff_reweight_constants.h>

#include "ff_reweight_utils.h"

#include "McDecayGraph.h"
#include "McDecayModeCurator.h"
#include "FormFactorAnalyzer.h"
#include "BToDlnuMode.h"

namespace po = boost::program_options;
namespace pu = pgstring_utils;
namespace pu = pgstring_utils;

void compute_cln_variations(const po::variables_map &vm);

int main(int argc, char **argv) {

  try {

    // define program options
    po::options_description generic("Generic options");
    generic.add_options()
        ("help,h", "produce help message")
    ;

    po::options_description config("Configuration options");
    config.add_options()
        ("dbname", po::value<std::string>(), 
             "database name. ")
        ("table_name", po::value<std::string>(), 
             "name of the table containing framework tuples. ")
        ("output_fname", po::value<std::string>(), 
             "output csv file name. ")
        ("cursor_fetch_size", po::value<int>()->default_value(5000), 
             "number of rows per cursor fetch. ")
    ;

    po::options_description hidden("Hidden options");
    hidden.add_options()
        ("config_file", po::value<std::string>(), 
             "name of a configuration file. ")
    ;

    po::options_description cmdline_options;
    cmdline_options.add(generic).add(config).add(hidden);

    po::options_description config_file_options;
    config_file_options.add(config);

    po::options_description visible;
    visible.add(generic).add(config);

    po::positional_options_description p;
    p.add("config_file", -1);

    // parse program options and configuration file
    po::variables_map vm;
    store(po::command_line_parser(argc, argv).
          options(cmdline_options).positional(p).run(), vm);
    notify(vm);

    if (vm.count("help") || !vm.count("config_file")) {
      std::cout << std::endl;
      std::cout << "Usage: ./compute_cln_variations ";
      std::cout << "[options] config_fname" << std::endl;
      std::cout << visible << "\n";
      return 0;
    }

    std::ifstream fin(vm["config_file"].as<std::string>());
    if (!fin) {
      std::cout << "cannot open config file: ";
      std::cout << vm["config_file"].as<std::string>() << std::endl;
      return 0;
    }

    store(parse_config_file(fin, config_file_options), vm);
    notify(vm);

    // main routine
    compute_cln_variations(vm);

  } catch(std::exception& e) {

    std::cerr << "error: " << e.what() << "\n";
    return 1;

  } catch(...) {

    std::cerr << "Exception of unknown type!\n";
    return 1;
  }

  return 0;
}

void compute_cln_variations(const po::variables_map &vm) {

  // open database connection and populate fields
  std::string dbname = vm["dbname"].as<std::string>();
  std::string table_name = vm["table_name"].as<std::string>();
  int cursor_fetch_size = vm["cursor_fetch_size"].as<int>();

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

  // open output csv file
  std::string output_fname = vm["output_fname"].as<std::string>();
  CsvWriter csv;
  csv.open(output_fname, {
      "eid", 
      "cln_D_rho2_up", "cln_D_rho2_down",
      "cln_Dstar_p0_up", "cln_Dstar_p0_down",
      "cln_Dstar_p1_up", "cln_Dstar_p1_down",
      "cln_Dstar_p2_up", "cln_Dstar_p2_down"
  });

  // setup cln parameter variations
  std::vector<CLNParams> cln_params(8);

  cln_params[0].set_d_rho2(1.239);
  cln_params[1].set_d_rho2(1.131);

  cln_params[2].set_dstar_rho2(1.2061);
  cln_params[2].set_dstar_R1(1.4047);
  cln_params[2].set_dstar_R2(0.8537);

  cln_params[3].set_dstar_rho2(1.2079);
  cln_params[3].set_dstar_R1(1.4073);
  cln_params[3].set_dstar_R2(0.8522);

  cln_params[4].set_dstar_rho2(1.2067);
  cln_params[4].set_dstar_R1(1.4062);
  cln_params[4].set_dstar_R2(0.8538);

  cln_params[5].set_dstar_rho2(1.2073);
  cln_params[5].set_dstar_R1(1.4058);
  cln_params[5].set_dstar_R2(0.8522);

  cln_params[6].set_dstar_rho2(1.2070);
  cln_params[6].set_dstar_R1(1.4060);
  cln_params[6].set_dstar_R2(0.8530);

  cln_params[7].set_dstar_rho2(1.20697);
  cln_params[7].set_dstar_R1(1.40598);
  cln_params[7].set_dstar_R2(0.85294);

  // initialize worker classes
  McDecayGraphFactory graph_factory;
  McDecayModeSummary summary;
  McDecayModeCurator curator;
  FormFactorAnalyzer analyzer;

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

    auto result = analyzer.analyze_cln(g, summary, cln_params);

    // NaN possible but rare. this can happen when w*w-1 < 0. 
    // need to look into why this edge case occurs. appears 
    // to be a problem inherent in the input data
    for (size_t i = 0; i < result.size(); ++i) {
      if (std::isnan(result[i])) { result[i] = 1.0; }
    }

    csv.set("eid", pu::type2string(eid));
    csv.set("cln_D_rho2_up", pu::type2string(result[0]));
    csv.set("cln_D_rho2_down", pu::type2string(result[1]));
    csv.set("cln_Dstar_p0_up", pu::type2string(result[2]));
    csv.set("cln_Dstar_p0_down", pu::type2string(result[3]));
    csv.set("cln_Dstar_p1_up", pu::type2string(result[4]));
    csv.set("cln_Dstar_p1_down", pu::type2string(result[5]));
    csv.set("cln_Dstar_p2_up", pu::type2string(result[6]));
    csv.set("cln_Dstar_p2_down", pu::type2string(result[7]));
    csv.commit();

  }
  

  // clean up
  psql.close_cursor();
  psql.close_connection();

  // close output file
  csv.close();


}

