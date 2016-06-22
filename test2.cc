#include <iostream>
#include <cmath>

#include "XSLKin.h"
#include "ff_reweight_utils.h"

int main() {

  HepLorentzVector v = make_lorentz_vector(12.1007, 5.85557, 0.999825, 3.13608);
  std::cout << v.m() << std::endl;

  return 0;
}
