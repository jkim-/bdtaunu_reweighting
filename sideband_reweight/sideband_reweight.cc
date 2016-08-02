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
#include <utils/custom_program_option_utils.h>

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

        ("control_fname", po::value<std::string>(), "file containing control reference points. ")
        ("control_alpha", po::value<double>(), "control sensitivity parameter. ")
        ("control_pilot_bwx", po::value<double>(), "control pilot bandwidth in x. ")
        ("control_pilot_bwy", po::value<double>(), "control pilot bandwidth in y. ")
        ("control_adapt_bwx", po::value<double>(), "control evaluation bandwidth in x. ")
        ("control_adapt_bwy", po::value<double>(), "control evaluation bandwidth in y. ")

        ("target_fname", po::value<std::string>(), "file containing target reference points. ")
        ("target_alpha", po::value<double>(), "target sensitivity parameter. ")
        ("target_pilot_bwx", po::value<double>(), "target pilot bandwidth in x. ")
        ("target_pilot_bwy", po::value<double>(), "target pilot bandwidth in y. ")
        ("target_adapt_bwx", po::value<double>(), "target evaluation bandwidth in x. ")
        ("target_adapt_bwy", po::value<double>(), "target evaluation bandwidth in y. ")

        ("nested_fnames", po::value<std::string>(), "files containing nested kde reference points. ")
        ("nested_alphas", po::value<std::string>(), "nested sensitivity parameters. ")
        ("nested_pilot_bwxs", po::value<std::string>(), "nested pilot bandwidths in x. ")
        ("nested_pilot_bwys", po::value<std::string>(), "nested pilot bandwidths in y. ")
        ("nested_adapt_bwxs", po::value<std::string>(), "nested evaluation bandwidths in x. ")
        ("nested_adapt_bwys", po::value<std::string>(), "nested evaluation bandwidths in y. ")
        
        ("nested_proportions", po::value<std::string>(), "nested component proportions. ")

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
      std::cout << "Usage: sideband_reweight [options] config_fname" << std::endl;
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

  // read conrol and target kde parameters 
  std::string control_fname = vm["control_fname"].as<std::string>();
  double control_alpha = vm["control_alpha"].as<double>();
  double control_pilot_bwx = vm["control_pilot_bwx"].as<double>();
  double control_pilot_bwy = vm["control_pilot_bwy"].as<double>();
  double control_adapt_bwx = vm["control_adapt_bwx"].as<double>();
  double control_adapt_bwy = vm["control_adapt_bwy"].as<double>();

  std::string target_fname = vm["target_fname"].as<std::string>();
  double target_alpha = vm["target_alpha"].as<double>();
  double target_pilot_bwx = vm["target_pilot_bwx"].as<double>();
  double target_pilot_bwy = vm["target_pilot_bwy"].as<double>();
  double target_adapt_bwx = vm["target_adapt_bwx"].as<double>();
  double target_adapt_bwy = vm["target_adapt_bwy"].as<double>();

  // read nested kde parameters
  std::vector<std::string> nested_fnames =
      tokenize<std::string>(vm["nested_fnames"].as<std::string>());

  size_t n_nested_components = nested_fnames.size();

  std::vector<double> nested_alphas =
    tokenize<double>(vm["nested_alphas"].as<std::string>());
  std::vector<double> nested_pilot_bwxs =
    tokenize<double>(vm["nested_pilot_bwxs"].as<std::string>());
  std::vector<double> nested_pilot_bwys =
    tokenize<double>(vm["nested_pilot_bwys"].as<std::string>());
  std::vector<double> nested_adapt_bwxs =
    tokenize<double>(vm["nested_adapt_bwxs"].as<std::string>());
  std::vector<double> nested_adapt_bwys =
    tokenize<double>(vm["nested_adapt_bwys"].as<std::string>());

  if (
      (nested_alphas.size() != n_nested_components) ||
      (nested_pilot_bwxs.size() != n_nested_components) ||
      (nested_pilot_bwys.size() != n_nested_components) ||
      (nested_adapt_bwxs.size() != n_nested_components) ||
      (nested_adapt_bwys.size() != n_nested_components)) {
    throw std::invalid_argument(
        "evaluate(): must have same number of "
        "adaptive kernel parameters as there are components. ");
  }

  // read in nested proportions
  std::vector<double> nested_proportions =
        tokenize<double>(vm["nested_proportions"].as<std::string>());
  if (nested_proportions.size() != n_nested_components) {
    throw std::invalid_argument(
        "evaluate(): must have same number of "
        "nested proportions as there are nested components. ");
  }

  double proportion_sum = 0.0;
  for (size_t c = 0; c < n_nested_components; ++c) {
    if (nested_proportions[c] < 0) {
      throw std::invalid_argument(
          "evaluate(): nested proportions must be positive. ");
    }
    proportion_sum += nested_proportions[c];
  }
  if (proportion_sum >= 1) {
      throw std::invalid_argument(
          "evaluate(): nested proportions must sum to less than 1.0. ");
  }

  // construct kernel densities
  std::cout << "+ building control kernel density. \n" << std::endl;

  std::cout << "  file name: " << control_fname << std::endl;
  std::cout << "  alpha: " << control_alpha << std::endl;
  std::cout << "  pilot bandwidths (x, y): " << control_pilot_bwx << ", " << control_pilot_bwy << std::endl;
  std::cout << "  adapt bandwidths (x, y): " << control_adapt_bwx << ", " << control_adapt_bwy << std::endl;
  std::cout << std::endl;

  start = std::chrono::high_resolution_clock::now();
  KernelDensityType control_kde =
    construct_kernel_density(
        control_fname, control_alpha, 
        control_pilot_bwx, control_pilot_bwy,
        control_adapt_bwx, control_adapt_bwy, 
        rel_tol, abs_tol, max_leaf_size, gpu_block_size);
  end = std::chrono::high_resolution_clock::now();
  elapsed = end - start;
  std::cout << "  running time: " << elapsed.count() << " s. \n" << std::endl;

  std::cout << "+ building target kernel density. \n" << std::endl;

  std::cout << "  file name: " << target_fname << std::endl;
  std::cout << "  alpha: " << target_alpha << std::endl;
  std::cout << "  pilot bandwidths (x, y): " << target_pilot_bwx << ", " << target_pilot_bwy << std::endl;
  std::cout << "  adapt bandwidths (x, y): " << target_adapt_bwx << ", " << target_adapt_bwy << std::endl;
  std::cout << std::endl;

  start = std::chrono::high_resolution_clock::now();
  KernelDensityType target_kde =
    construct_kernel_density(
        target_fname, target_alpha, 
        target_pilot_bwx, target_pilot_bwy,
        target_adapt_bwx, target_adapt_bwy, 
        rel_tol, abs_tol, max_leaf_size, gpu_block_size);
  end = std::chrono::high_resolution_clock::now();
  elapsed = end - start;
  std::cout << "  running time: " << elapsed.count() << " s. \n" << std::endl;

  std::cout << "  + building nested kernel densities: \n" << std::endl;

  std::vector<KernelDensityType> nested_kdes(n_nested_components);
  for (size_t c = 0; c < n_nested_components; ++c) {

    std::cout << "  nested component " << c << ":" << std::endl;
    std::cout << "  file name: " << nested_fnames[c] << std::endl;
    std::cout << "  alpha: " << nested_alphas[c] << std::endl;
    std::cout << "  pilot bandwidths (x, y): " << nested_pilot_bwxs[c] << ", " << nested_pilot_bwys[c] << std::endl;
    std::cout << "  adaptive bandwidths (x, y): " << nested_adapt_bwxs[c] <<", " << nested_adapt_bwys[c] << std::endl;
    std::cout << "  proportion: " << nested_proportions[c] << std::endl;
    std::cout << std::endl;

    start = std::chrono::high_resolution_clock::now();
    nested_kdes[c] =
      construct_kernel_density(
          nested_fnames[c], nested_alphas[c], 
          nested_pilot_bwxs[c], nested_pilot_bwys[c],
          nested_adapt_bwxs[c], nested_adapt_bwys[c], 
          rel_tol, abs_tol, max_leaf_size, gpu_block_size);
    end = std::chrono::high_resolution_clock::now();
    elapsed = end - start;
    std::cout << "  running time: " << elapsed.count() << " s. \n" << std::endl;

  }

  std::cout << "  nested proportion sum: " << proportion_sum << std::endl;
  std::cout << std::endl;


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
    throw std::invalid_argument("error: sideband_reweight: query_batch_size must be > 0");
  }

  // open output csv file
  CsvWriter csv;
  csv.open(output_fname, { "eid", "sideband_weight"});

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
  std::vector<DataPointType> control_queries; control_queries.reserve(query_batch_size);
  std::vector<DataPointType> target_queries; target_queries.reserve(query_batch_size);
  std::vector<std::vector<DataPointType>> nested_queries(n_nested_components);
  for (size_t c = 0; c < n_nested_components; ++c) { nested_queries[c].reserve(query_batch_size); }


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
    control_queries.clear();
    target_queries.clear();
    for (size_t c = 0; c < n_nested_components; ++c) { nested_queries[c].clear(); }

    // attempt to load a record only if the query set is not full
    for (i = 0; i < query_batch_size && psql.next(); ++i) {

      // fetch record
      pu::string2type(psql.get("eid"), eid);
      pu::string2type(psql.get(z1_name), z1);
      pu::string2type(psql.get(z2_name), z2);


      // insert into query batches
      query_eid.push_back(eid);
      control_queries.push_back({{ z1, z2 }, {1.0}});
      target_queries.push_back({{ z1, z2 }, {1.0}});
      for (size_t c = 0; c < n_nested_components; ++c) { 
        nested_queries[c].push_back({{ z1, z2 }, {1.0}}); 
      }
      ++n;
    }
    assert(query_eid.size() == control_queries.size());
    assert(control_queries.size() == target_queries.size());
    for (size_t c = 0; c < n_nested_components; ++c) {
      assert(control_queries.size() == nested_queries[c].size());
    }

    // evaluate query set if it is non-empty
    if (i > 0) { 

      // evaluate
      control_kde.direct_eval(control_queries);
      target_kde.direct_eval(target_queries);
      for (size_t c = 0; c < n_nested_components; ++c) {
        nested_kdes[c].direct_eval(nested_queries[c]);
      }

      // compute weight and output to csv
      for (size_t j = 0; j < query_eid.size(); ++j) {

        double sideband_weight = 1.0;

        double control_value = control_queries[j].attributes().value();
        double target_value = target_queries[j].attributes().value();

        // note: reweight only when adjusted control density is positive
        // any better ideas? 
        double adjusted_control_value = control_value;
        for (size_t c = 0; c < n_nested_components; ++c) {
          adjusted_control_value -= nested_proportions[c] * nested_queries[c][j].attributes().value();
        }
        adjusted_control_value /= (1 - proportion_sum);
        if (adjusted_control_value > 0 && target_value > 0) { 
          sideband_weight = adjusted_control_value / target_value; 
        }

        // write line
        csv.set("eid", pu::type2string(query_eid[j]));
        csv.set("sideband_weight", pu::type2string(sideband_weight));
        csv.commit();
      }
    }
    --i;
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
