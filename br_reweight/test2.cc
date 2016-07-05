#include <iostream>

#include "BrfReweightDict.h"
#include "BrfCorrectionTable.h"

int main() {

  BrfCorrectionTable brf_correction_table("dat/brf_corrections.dat");

  int n = static_cast<int>(BrfReweightCode::null);
  for (int i = 0; i < n; ++i) {
    BrfReweightCode c = static_cast<BrfReweightCode>(i);
    if (brf_correction_table.is_valid_entry(c)) {
      std::cout << brfcode2string(c) << " ";
      std::cout << brf_correction_table.brf(c) << " ";
      std::cout << brf_correction_table.fluc(c) << std::endl;
    } else {
      std::cout << brfcode2string(c) << std::endl;
    }
  }
  return 0;
}
