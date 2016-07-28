#include <iostream>
#include <cmath>
#include <vector>
#include <fstream>
#include <string>
#include <chrono>
#include <cassert>

#include <KernelDensity.h>

#include <utils/PsqlReader.h>
#include <utils/CsvWriter.h>
#include <utils/pgstring_utils.h>
#include <utils/general_utils.h>

namespace pu = pgstring_utils;

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

int main() {

  // timers
  std::chrono::high_resolution_clock::time_point start, end;
  std::chrono::duration<double> elapsed;

  // parameters 
  std::string offpeak_fname = "data/offpeak.gbdt300.csv";
  double offpeak_alpha = 0.5;
  double offpeak_pilot_bwx = 0.095;
  double offpeak_pilot_bwy = 0.073;
  double offpeak_adapt_bwx = 0.095;
  double offpeak_adapt_bwy = 0.073;

  std::string continuum_fname = "data/continuum.gbdt300.csv";
  double continuum_alpha = 0.5;
  double continuum_pilot_bwx = 0.106;
  double continuum_pilot_bwy = 0.062;
  double continuum_adapt_bwx = 0.106;
  double continuum_adapt_bwy = 0.062;
  
  double rel_tol = 1e-6;
  double abs_tol = 1e-8; 
  int max_leaf_size = 32768; 
  int gpu_block_size = 128; 

  std::string output_fname = "continuum_reweight.csv";

  // construct kernel density
  std::cout << "+ building kernel density for offpeak ";
  std::cout << " using file: " << offpeak_fname << std::endl;
  start = std::chrono::high_resolution_clock::now();
  KernelDensityType kde_offpeak =
    construct_kernel_density(
        offpeak_fname, offpeak_alpha, 
        offpeak_pilot_bwx, offpeak_pilot_bwy,
        offpeak_adapt_bwx, offpeak_adapt_bwy, 
        rel_tol, abs_tol, max_leaf_size, gpu_block_size);
  end = std::chrono::high_resolution_clock::now();
  elapsed = end - start;
  std::cout << "  running time: " << elapsed.count() << " s. \n" << std::endl;

  std::cout << "+ building kernel density for continuum ";
  std::cout << " using file: " << continuum_fname << std::endl;
  start = std::chrono::high_resolution_clock::now();
  KernelDensityType kde_continuum =
    construct_kernel_density(
        continuum_fname, continuum_alpha, 
        continuum_pilot_bwx, continuum_pilot_bwy,
        continuum_adapt_bwx, continuum_adapt_bwy, 
        rel_tol, abs_tol, max_leaf_size, gpu_block_size);
  end = std::chrono::high_resolution_clock::now();
  elapsed = end - start;
  std::cout << "  running time: " << elapsed.count() << " s. \n" << std::endl;

  // open output csv file
  CsvWriter csv;
  csv.open(output_fname, { "eid", "density_weight", "scale_weight"});

  // open database connection and populate fields
  std::string dbname = "bdtaunuhad_lite";
  std::string table_name = "continuum_reweight_inputs";
  int cursor_fetch_size = 5000;

  std::string z1_name = "logit_gbdt300_signal_score";
  std::string z2_name = "logit_gbdt300_dstartau_score";

  PsqlReader psql;
  psql.open_connection("dbname="+dbname);
  psql.open_cursor(table_name, { "eid", z1_name, z2_name }, cursor_fetch_size);

  int eid;
  double z1, z2;

  std::cout << "+ evaluating. " << std::endl;
  start = std::chrono::high_resolution_clock::now();

  size_t batch_size = 32768;
  if (batch_size <= 0) {
    throw std::invalid_argument("error: continuum_reweight: batch_size must be > 0");
  }

  std::vector<int> query_eid; query_eid.reserve(batch_size);
  std::vector<DataPointType> offpeak_queries; offpeak_queries.reserve(batch_size);
  std::vector<DataPointType> continuum_queries; continuum_queries.reserve(batch_size);

  size_t n = 0;

  // i != batch_size iff the database is empty
  size_t i = batch_size;
  while (i == batch_size) {

    // empty out query sets
    query_eid.clear();
    offpeak_queries.clear();
    continuum_queries.clear();

    // attempt to load a record only if the query set is not full
    for (i = 0; i < batch_size && psql.next(); ++i) {

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
      kde_offpeak.direct_eval(offpeak_queries);
      kde_continuum.direct_eval(continuum_queries);

      // compute weight and output to csv
      for (size_t j = 0; j < kde_offpeak.size(); ++j) {

        double density_weight = 1.0;
        double scale_weight = 1.0;

        double offpeak_value = offpeak_queries[j].attributes().value();
        double continuum_value = continuum_queries[j].attributes().value();
        if (offpeak_value > 0 && continuum_value > 0) {
          density_weight = offpeak_value / continuum_value;
        }

        csv.set("eid", pu::type2string(query_eid[j]));
        csv.set("density_weight", pu::type2string(density_weight));
        csv.set("scale_weight", pu::type2string(scale_weight));
        csv.commit();
      }
    }
    // break
    i--;
  }

  std::cout << n << std::endl;
  
  end = std::chrono::high_resolution_clock::now();
  elapsed = end - start;
  std::cout << "  running time: " << elapsed.count() << " s. \n" << std::endl;

  // clean up
  psql.close_cursor();
  psql.close_connection();

  // close output file
  csv.close();

  return 0;
}
