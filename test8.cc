#include <iostream>
#include <vector>
#include <fstream>
#include <string>

#include <CLHEP/Vector/LorentzVector.h>

#include "ff_reweight_defs.h"
#include "BPlnuDecayRate.h"

int main() {

  std::ofstream fout("test8.csv");
  double q2min = mTau*mTau, q2max = (mB0-mDp)*(mB0-mDp);
  int n_steps = 1000; double delta = (q2max-q2min)/n_steps;

  BPlnuDecayRate B0ToDenu(mB0, mDp, mTau, "CLN");
  //BPlnuDecayRate B0ToDenu(mB0, mDp, mTau, "ISGW2");
  for (int i = 0; i <= n_steps; ++i) {
    double q2 = q2min + i * delta;
    fout << q2 << " " << B0ToDenu.dGamma_dq2_density(q2) << std::endl;
  }

  return 0;
}
