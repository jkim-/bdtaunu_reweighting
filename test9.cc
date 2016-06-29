#include <iostream>
#include <vector>
#include <fstream>
#include <string>

#include <CLHEP/Vector/LorentzVector.h>

#include "ff_reweight_defs.h"
#include "BDss0lnuDecayRate.h"
#include "BD1primelnuDecayRate.h"
#include "BD1lnuDecayRate.h"

template <typename DecayRateT>
void print_dGamma_dw_density(
    std::ostream &os, const DecayRateT& dec_model, int n_steps) {
  double wmin = dec_model.wmin(), wmax = dec_model.wmax();
  double delta = (wmax-wmin)/n_steps;
  for (int i = 0; i <= n_steps; ++i) {
    double w = wmin + i * delta;
    os << w << " " << dec_model.dGamma_dw_density(w) << std::endl;
  }
}

int main() {

  std::ofstream fout;

  // B0 -> D*_0 e nu
  fout.open("BDss0enu_ISGW2.csv");
  BDss0lnuDecayRate BDss0enu_ISGW2(mB0, mDss0, mE, "ISGW2");
  print_dGamma_dw_density(fout, BDss0enu_ISGW2, 1000);
  fout.close();

  fout.open("BDss0enu_LLSWB1.csv");
  BDss0lnuDecayRate BDss0enu_LLSWB1(mB0, mDss0, mE, "LLSWB1");
  print_dGamma_dw_density(fout, BDss0enu_LLSWB1, 1000);
  fout.close();

  fout.open("BDss0enu_LLSWB2.csv");
  BDss0lnuDecayRate BDss0enu_LLSWB2(mB0, mDss0, mE, "LLSWB2");
  print_dGamma_dw_density(fout, BDss0enu_LLSWB2, 1000);
  fout.close();

  // B0 -> D'_1 e nu
  fout.open("BD1primeenu_ISGW2.csv");
  BD1primelnuDecayRate BD1primeenu_ISGW2(mB0, mD1prime, mE, "ISGW2");
  print_dGamma_dw_density(fout, BD1primeenu_ISGW2, 1000);
  fout.close();

  fout.open("BD1primeenu_LLSWB1.csv");
  BD1primelnuDecayRate BD1primeenu_LLSWB1(mB0, mD1prime, mE, "LLSWB1");
  print_dGamma_dw_density(fout, BD1primeenu_LLSWB1, 1000);
  fout.close();

  fout.open("BD1primeenu_LLSWB2.csv");
  BD1primelnuDecayRate BD1primeenu_LLSWB2(mB0, mD1prime, mE, "LLSWB2");
  print_dGamma_dw_density(fout, BD1primeenu_LLSWB2, 1000);
  fout.close();

  // B0 -> D_1 e nu
  fout.open("BD1enu_ISGW2.csv");
  BD1lnuDecayRate BD1enu_ISGW2(mB0, mD1p, mE, "ISGW2");
  print_dGamma_dw_density(fout, BD1enu_ISGW2, 1000);
  fout.close();

  fout.open("BD1enu_LLSWB1.csv");
  BD1lnuDecayRate BD1enu_LLSWB1(mB0, mD1p, mE, "LLSWB1");
  print_dGamma_dw_density(fout, BD1enu_LLSWB1, 1000);
  fout.close();

  fout.open("BD1enu_LLSWB2.csv");
  BD1lnuDecayRate BD1enu_LLSWB2(mB0, mD1p, mE, "LLSWB2");
  print_dGamma_dw_density(fout, BD1enu_LLSWB2, 1000);
  fout.close();

  return 0;
}
