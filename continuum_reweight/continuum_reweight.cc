#include <iostream>
#include <cmath>
#include <vector>
#include <fstream>
#include <string>
#include <chrono>
#include <cassert>

#include <boost/program_options.hpp>

#include <KernelDensity.h>

#include <utils/PsqlReader.h>
#include <utils/CsvWriter.h>
#include <utils/pgstring_utils.h>
#include <utils/general_utils.h>

namespace pu = pgstring_utils;
namespace po = boost::program_options;

namespace {
  using KernelType = bbrcit::EpanechnikovProductKernel2d<float>;
  using KernelDensityType = bbrcit::KernelDensity<2,KernelType,double>;
  using KdtreeType = KernelDensityType::KdtreeType;
  using DataPointType = KernelDensityType::DataPointType;
}

// construct (adapted) kernel density using data in `fname`
KernelDensityType construct_kernel_density(
  const std::string fname, double alpha,
  double pilot_bandwidth_x, double pilot_bandwidth_y,
  double adapt_bandwidth_x, double adapt_bandwidth_y,
  double rel_tol, double abs_tol,
  int leaf_max, int block_size) {

  std::vector<DataPointType> points = read_2dpoints<DataPointType>(fname);

  KernelDensityType kde(std::move(points), leaf_max);
  kde.kernel().set_bandwidths(pilot_bandwidth_x, pilot_bandwidth_y);
  kde.adapt_density(alpha, rel_tol, abs_tol, block_size);
  kde.kernel().set_bandwidths(adapt_bandwidth_x, adapt_bandwidth_y);

  return kde;
}


// main routine. 
void evaluate(const po::variables_map &vm);



int main(int argc, char **argv) {

  try {
    // define program options
    po::options_description generic("Generic options");
    generic.add_options()
        ("help,h", "produce help message")
    ;

    po::options_description config("Configuration options");
    config.add_options()

        ("max_leaf_size", po::value<int>(), "maximum leaf size in Kdtree. ")
        ("rel_tol", po::value<double>(), "relative tolerance for kde evaluations. ")
        ("abs_tol", po::value<double>(), "absolute tolerance for kde evaluations. ")
        ("cuda_device_number", po::value<int>(), "cuda device used for this session. ")
        ("gpu_block_size", po::value<int>(), "gpu block size. ")
        ("query_batch_size", po::value<int>(), "Number of records to evaluate at a time. ")

        ("dbname", po::value<std::string>(), "database containing the query data. ")
        ("table_name", po::value<std::string>(), "table containing the query data. ")
        ("z1_name", po::value<std::string>(), "column name of the first feature")
        ("z2_name", po::value<std::string>(), "column name of the second feature")
        ("cursor_fetch_size", po::value<int>(), "cursor fetch size. ")

        ("output_fname", po::value<std::string>(), "output file name. ")

        ("offpeak_fname", po::value<std::string>(), "file containing offpeak reference points. ")
        ("offpeak_alpha", po::value<double>(), "offpeak sensitivity parameter. ")
        ("offpeak_pilot_bwx", po::value<double>(), "offpeak pilot bandwidth in x. ")
        ("offpeak_pilot_bwy", po::value<double>(), "offpeak pilot bandwidth in y. ")
        ("offpeak_adapt_bwx", po::value<double>(), "offpeak evaluation bandwidth in x. ")
        ("offpeak_adapt_bwy", po::value<double>(), "offpeak evaluation bandwidth in y. ")

        ("continuum_fname", po::value<std::string>(), "file containing continuum reference points. ")
        ("continuum_alpha", po::value<double>(), "continuum sensitivity parameter. ")
        ("continuum_pilot_bwx", po::value<double>(), "continuum pilot bandwidth in x. ")
        ("continuum_pilot_bwy", po::value<double>(), "continuum pilot bandwidth in y. ")
        ("continuum_adapt_bwx", po::value<double>(), "continuum evaluation bandwidth in x. ")
        ("continuum_adapt_bwy", po::value<double>(), "continuum evaluation bandwidth in y. ")

        ("continuum_normalization_weight", po::value<double>(), "Fixed continuum normalization weight. ")

    ;

    po::options_description hidden("Hidden options");
    hidden.add_options()
        ("config_file", po::value<std::string>(), "name of a configuration file. ")
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
      std::cout << "Usage: continuum_reweight [options] config_fname" << std::endl;
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

    // begin evaluation
    evaluate(vm);

  } catch(std::exception& e) {

    std::cerr << "error: " << e.what() << "\n";
    return 1;

  } catch(...) {

    std::cerr << "Exception of unknown type!\n";
    return 1;
  }

  return 0;
}


void evaluate(const po::variables_map &vm) {

  // 1. setup general utilities

  // timers
  std::chrono::high_resolution_clock::time_point start, end;
  std::chrono::duration<double> elapsed;
  
  // performance parameters
  int max_leaf_size = vm["max_leaf_size"].as<int>();
  double rel_tol = vm["rel_tol"].as<double>();
  double abs_tol = vm["abs_tol"].as<double>();

  std::cout << "+ performance parameters: \n" << std::endl;

  std::cout << "  max leaf size: " << max_leaf_size << std::endl;
  std::cout << "  relative tolerance: " << rel_tol << std::endl;
  std::cout << "  absolute tolerance: " << abs_tol << std::endl;
  std::cout << std::endl;

  int cuda_device_number = vm["cuda_device_number"].as<int>();
  cudaSetDevice(cuda_device_number);
  cudaDeviceProp deviceProp;
  cudaGetDeviceProperties(&deviceProp, cuda_device_number);
  std::cout << "  gpu device number used for this session: ";
  std::cout << cuda_device_number << "\n";
  std::cout << "  device name: " << deviceProp.name << std::endl;

  int gpu_block_size = vm["gpu_block_size"].as<int>();
  std::cout << "  gpu block size: " << gpu_block_size << std::endl;
  std::cout << std::endl;

  // 2. construct kernel densities

  // read kde parameters 
  std::string offpeak_fname = vm["offpeak_fname"].as<std::string>();
  double offpeak_alpha = vm["offpeak_alpha"].as<double>();
  double offpeak_pilot_bwx = vm["offpeak_pilot_bwx"].as<double>();
  double offpeak_pilot_bwy = vm["offpeak_pilot_bwy"].as<double>();
  double offpeak_adapt_bwx = vm["offpeak_adapt_bwx"].as<double>();
  double offpeak_adapt_bwy = vm["offpeak_adapt_bwy"].as<double>();

  std::string continuum_fname = vm["continuum_fname"].as<std::string>();
  double continuum_alpha = vm["continuum_alpha"].as<double>();
  double continuum_pilot_bwx = vm["continuum_pilot_bwx"].as<double>();
  double continuum_pilot_bwy = vm["continuum_pilot_bwy"].as<double>();
  double continuum_adapt_bwx = vm["continuum_adapt_bwx"].as<double>();
  double continuum_adapt_bwy = vm["continuum_adapt_bwy"].as<double>();

  // construct kernel densities
  std::cout << "+ building offpeak kernel density. \n" << std::endl;

  std::cout << "  file name: " << offpeak_fname << std::endl;
  std::cout << "  alpha: " << offpeak_alpha << std::endl;
  std::cout << "  pilot bandwidths (x, y): " << offpeak_pilot_bwx << ", " << offpeak_pilot_bwy << std::endl;
  std::cout << "  adapt bandwidths (x, y): " << offpeak_adapt_bwx << ", " << offpeak_adapt_bwy << std::endl;
  std::cout << std::endl;

  start = std::chrono::high_resolution_clock::now();
  KernelDensityType offpeak_kde =
    construct_kernel_density(
        offpeak_fname, offpeak_alpha, 
        offpeak_pilot_bwx, offpeak_pilot_bwy,
        offpeak_adapt_bwx, offpeak_adapt_bwy, 
        rel_tol, abs_tol, max_leaf_size, gpu_block_size);
  end = std::chrono::high_resolution_clock::now();
  elapsed = end - start;
  std::cout << "  running time: " << elapsed.count() << " s. \n" << std::endl;

  std::cout << "+ building continuum kernel density. \n" << std::endl;

  std::cout << "  file name: " << continuum_fname << std::endl;
  std::cout << "  alpha: " << continuum_alpha << std::endl;
  std::cout << "  pilot bandwidths (x, y): " << continuum_pilot_bwx << ", " << continuum_pilot_bwy << std::endl;
  std::cout << "  adapt bandwidths (x, y): " << continuum_adapt_bwx << ", " << continuum_adapt_bwy << std::endl;
  std::cout << std::endl;

  start = std::chrono::high_resolution_clock::now();
  KernelDensityType continuum_kde =
    construct_kernel_density(
        continuum_fname, continuum_alpha, 
        continuum_pilot_bwx, continuum_pilot_bwy,
        continuum_adapt_bwx, continuum_adapt_bwy, 
        rel_tol, abs_tol, max_leaf_size, gpu_block_size);
  end = std::chrono::high_resolution_clock::now();
  elapsed = end - start;
  std::cout << "  running time: " << elapsed.count() << " s. \n" << std::endl;


  // 3. evaluate and save results

  // read in parameters
  std::string output_fname = vm["output_fname"].as<std::string>();
  std::string dbname = vm["dbname"].as<std::string>();
  std::string table_name = vm["table_name"].as<std::string>();
  std::string z1_name = vm["z1_name"].as<std::string>();
  std::string z2_name = vm["z2_name"].as<std::string>();

  int cursor_fetch_size = vm["cursor_fetch_size"].as<int>();
  int query_batch_size = vm["query_batch_size"].as<int>();

  if (query_batch_size <= 0) {
    throw std::invalid_argument("error: continuum_reweight: query_batch_size must be > 0");
  }

  double continuum_normalization_weight = vm["continuum_normalization_weight"].as<double>();

  // open output csv file
  CsvWriter csv;
  csv.open(output_fname, { "eid", "density_weight", "normalization_weight"});

  // open database connection and initialize cache
  PsqlReader psql;
  psql.open_connection("dbname="+dbname);
  psql.open_cursor(table_name, { "eid", z1_name, z2_name }, cursor_fetch_size);
  int eid;
  double z1, z2;

  // open database connection and initialize cache
  std::cout << "+ evaluating. " << std::endl;
  start = std::chrono::high_resolution_clock::now();

  std::vector<int> query_eid; query_eid.reserve(query_batch_size);
  std::vector<DataPointType> offpeak_queries; offpeak_queries.reserve(query_batch_size);
  std::vector<DataPointType> continuum_queries; continuum_queries.reserve(query_batch_size);


  // loop over and evaluate the weights for every record in the database.
  // proceed in batches: load records from the database until the query 
  // set is full and evaluate them at once. continue until all records 
  // have been loaded and evaluated. 

  // counter to keep track of the number of records processed
  size_t n = 0;

  // stopping condition is as follows: 
  // (i != query_batch_size) iff all records in the database have been completed 
  // initialze to query_batch_size to indicate that there might still be records 
  int i = query_batch_size;
  while (i == query_batch_size) {

    // empty out query sets
    query_eid.clear();
    offpeak_queries.clear();
    continuum_queries.clear();

    // attempt to load a record only if the query set is not full
    for (i = 0; i < query_batch_size && psql.next(); ++i) {

      // fetch record
      pu::string2type(psql.get("eid"), eid);
      pu::string2type(psql.get(z1_name), z1);
      pu::string2type(psql.get(z2_name), z2);


      // insert into query batches
      query_eid.push_back(eid);
      offpeak_queries.push_back({{ z1, z2 }, {1.0}});
      continuum_queries.push_back({{ z1, z2 }, {1.0}});
      ++n;
    }
    assert(query_eid.size() == offpeak_queries.size());
    assert(offpeak_queries.size() == continuum_queries.size());

    // evaluate query set if it is non-empty
    if (i > 0) { 

      // evaluate
      offpeak_kde.direct_eval(offpeak_queries);
      continuum_kde.direct_eval(continuum_queries);

      // compute weight and output to csv
      for (size_t j = 0; j < query_eid.size(); ++j) {

        double density_weight = 1.0;
        double normalization_weight = continuum_normalization_weight;

        double offpeak_value = offpeak_queries[j].attributes().value();
        double continuum_value = continuum_queries[j].attributes().value();

        // note: reweight only when both evaluations are non-zero. 
        // any better ideas? 
        if (offpeak_value > 0 && continuum_value > 0) {
          density_weight = offpeak_value / continuum_value;
        }

        // write line
        csv.set("eid", pu::type2string(query_eid[j]));
        csv.set("density_weight", pu::type2string(density_weight));
        csv.set("normalization_weight", pu::type2string(normalization_weight));
        csv.commit();
      }
    }
  }
  
  end = std::chrono::high_resolution_clock::now();
  elapsed = end - start;
  std::cout << "  running time: " << elapsed.count() << " s. \n" << std::endl;

  // clean up
  psql.close_cursor();
  psql.close_connection();

  // close output file
  csv.close();

  std::cout << "+ done. reweighted " << n << " records. " << std::endl;

}
