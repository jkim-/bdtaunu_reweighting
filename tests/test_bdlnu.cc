#include <iostream>
#include <vector>
#include <fstream>
#include <string>

#include <CLHEP/Vector/LorentzVector.h>

#include <ff_reweight_constants.h>
#include <BPlnuDecayRate.h>
#include <BVlnuDecayRate.h>

template <typename DecayRateT>
void print_dGamma_dq2_density(
    std::ostream &os, const DecayRateT& dec_model, int n_steps) {
  double q2min = dec_model.q2min(), q2max = dec_model.q2max();
  double delta = (q2max-q2min)/n_steps;
  for (int i = 0; i <= n_steps; ++i) {
    double q2 = q2min + i * delta;
    os << q2 << " " << dec_model.dGamma_dq2_density(q2) << std::endl;
  }
}

int main() {

  std::ofstream fout;

  // B0 -> Dc e nu
  fout.open("BDenu_ISGW2.csv");
  BPlnuDecayRate BDenu_ISGW2(mB0, mDp, mE, "ISGW2");
  print_dGamma_dq2_density(fout, BDenu_ISGW2, 1000);
  fout.close();

  fout.open("BDenu_CLN.csv");
  BPlnuDecayRate BDenu_CLN(mB0, mDp, mE, "CLN");
  print_dGamma_dq2_density(fout, BDenu_CLN, 1000);
  fout.close();

  // B0 -> Dc mu nu
  fout.open("BDmunu_ISGW2.csv");
  BPlnuDecayRate BDmunu_ISGW2(mB0, mDp, mMu, "ISGW2");
  print_dGamma_dq2_density(fout, BDmunu_ISGW2, 1000);
  fout.close();

  fout.open("BDmunu_CLN.csv");
  BPlnuDecayRate BDmunu_CLN(mB0, mDp, mMu, "CLN");
  print_dGamma_dq2_density(fout, BDmunu_CLN, 1000);
  fout.close();

  // B0 -> Dc tau nu
  fout.open("BDtaunu_ISGW2.csv");
  BPlnuDecayRate BDtaunu_ISGW2(mB0, mDp, mTau, "ISGW2");
  print_dGamma_dq2_density(fout, BDtaunu_ISGW2, 1000);
  fout.close();

  fout.open("BDtaunu_CLN.csv");
  BPlnuDecayRate BDtaunu_CLN(mB0, mDp, mTau, "CLN");
  print_dGamma_dq2_density(fout, BDtaunu_CLN, 1000);
  fout.close();

  // B0 -> D*+ e- nu, D*+ -> D0 pi+
  fout.open("BDsenu_Dpi_lminus_ISGW2.csv");
  BVlnuDecayRate BDsenu_ISGW2_Dpi_lminus(mB0, mDp, mE, false, false, "ISGW2");
  print_dGamma_dq2_density(fout, BDsenu_ISGW2_Dpi_lminus, 1000);
  fout.close();

  fout.open("BDsenu_Dpi_lminus_CLN.csv");
  BVlnuDecayRate BDsenu_CLN_Dpi_lminus(mB0, mDp, mE, false, false, "CLN");
  print_dGamma_dq2_density(fout, BDsenu_CLN_Dpi_lminus, 1000);
  fout.close();

  fout.open("BDsenu_Dpi_lminus_LinearQ2.csv");
  BVlnuDecayRate BDsenu_LinearQ2_Dpi_lminus(mB0, mDp, mE, false, false, "LinearQ2");
  print_dGamma_dq2_density(fout, BDsenu_LinearQ2_Dpi_lminus, 1000);
  fout.close();

  // B0 -> D*+ mu- nu, D*+ -> D0 pi+
  fout.open("BDsmunu_Dpi_lminus_ISGW2.csv");
  BVlnuDecayRate BDsmunu_ISGW2_Dpi_lminus(mB0, mDp, mMu, false, false, "ISGW2");
  print_dGamma_dq2_density(fout, BDsmunu_ISGW2_Dpi_lminus, 1000);
  fout.close();

  fout.open("BDsmunu_Dpi_lminus_CLN.csv");
  BVlnuDecayRate BDsmunu_CLN_Dpi_lminus(mB0, mDp, mMu, false, false, "CLN");
  print_dGamma_dq2_density(fout, BDsmunu_CLN_Dpi_lminus, 1000);
  fout.close();

  fout.open("BDsmunu_Dpi_lminus_LinearQ2.csv");
  BVlnuDecayRate BDsmunu_LinearQ2_Dpi_lminus(mB0, mDp, mMu, false, false, "LinearQ2");
  print_dGamma_dq2_density(fout, BDsmunu_LinearQ2_Dpi_lminus, 1000);
  fout.close();

  // B0 -> D*+ tau- nu, D*+ -> D0 pi+
  fout.open("BDstaunu_Dpi_lminus_ISGW2.csv");
  BVlnuDecayRate BDstaunu_ISGW2_Dpi_lminus(mB0, mDp, mTau, false, false, "ISGW2");
  print_dGamma_dq2_density(fout, BDstaunu_ISGW2_Dpi_lminus, 1000);
  fout.close();

  fout.open("BDstaunu_Dpi_lminus_CLN.csv");
  BVlnuDecayRate BDstaunu_CLN_Dpi_lminus(mB0, mDp, mTau, false, false, "CLN");
  print_dGamma_dq2_density(fout, BDstaunu_CLN_Dpi_lminus, 1000);
  fout.close();

  fout.open("BDstaunu_Dpi_lminus_LinearQ2.csv");
  BVlnuDecayRate BDstaunu_LinearQ2_Dpi_lminus(mB0, mDp, mTau, false, false, "LinearQ2");
  print_dGamma_dq2_density(fout, BDstaunu_LinearQ2_Dpi_lminus, 1000);
  fout.close();

  return 0;
}
