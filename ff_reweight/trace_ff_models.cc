#include <iostream>
#include <vector>
#include <fstream>
#include <string>

#include <CLHEP/Vector/LorentzVector.h>

#include <ff_reweight_constants.h>
#include <BPlnuDecayRate.h>
#include <BVlnuDecayRate.h>
#include <BDss0lnuDecayRate.h>
#include <BD1primelnuDecayRate.h>
#include <BD1lnuDecayRate.h>
#include <BD2lnuDecayRate.h>

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

  // B0 -> D*+ e- nu
  fout.open("BDsenu_ISGW2.csv");
  BVlnuDecayRate BDsenu_ISGW2(mB0, mDps, mE, false, false, "ISGW2");
  print_dGamma_dq2_density(fout, BDsenu_ISGW2, 1000);
  fout.close();

  fout.open("BDsenu_CLN.csv");
  BVlnuDecayRate BDsenu_CLN(mB0, mDps, mE, false, false, "CLN");
  print_dGamma_dq2_density(fout, BDsenu_CLN, 1000);
  fout.close();

  fout.open("BDsenu_LinearQ2.csv");
  BVlnuDecayRate BDsenu_LinearQ2(mB0, mDps, mE, false, false, "LinearQ2");
  print_dGamma_dq2_density(fout, BDsenu_LinearQ2, 1000);
  fout.close();

  // B0 -> D*+ mu- nu
  fout.open("BDsmunu_ISGW2.csv");
  BVlnuDecayRate BDsmunu_ISGW2(mB0, mDps, mMu, false, false, "ISGW2");
  print_dGamma_dq2_density(fout, BDsmunu_ISGW2, 1000);
  fout.close();

  fout.open("BDsmunu_CLN.csv");
  BVlnuDecayRate BDsmunu_CLN(mB0, mDps, mMu, false, false, "CLN");
  print_dGamma_dq2_density(fout, BDsmunu_CLN, 1000);
  fout.close();

  fout.open("BDsmunu_LinearQ2.csv");
  BVlnuDecayRate BDsmunu_LinearQ2(mB0, mDps, mMu, false, false, "LinearQ2");
  print_dGamma_dq2_density(fout, BDsmunu_LinearQ2, 1000);
  fout.close();

  // B0 -> D*+ tau- nu
  fout.open("BDstaunu_ISGW2.csv");
  BVlnuDecayRate BDstaunu_ISGW2(mB0, mDps, mTau, false, false, "ISGW2");
  print_dGamma_dq2_density(fout, BDstaunu_ISGW2, 1000);
  fout.close();

  fout.open("BDstaunu_CLN.csv");
  BVlnuDecayRate BDstaunu_CLN(mB0, mDps, mTau, false, false, "CLN");
  print_dGamma_dq2_density(fout, BDstaunu_CLN, 1000);
  fout.close();

  fout.open("BDstaunu_LinearQ2.csv");
  BVlnuDecayRate BDstaunu_LinearQ2(mB0, mDps, mTau, false, false, "LinearQ2");
  print_dGamma_dq2_density(fout, BDstaunu_LinearQ2, 1000);
  fout.close();

  // B0 -> D*_0 e nu
  fout.open("BDss0enu_ISGW2.csv");
  BDss0lnuDecayRate BDss0enu_ISGW2(mB0, mD0ssp, mE, "ISGW2");
  print_dGamma_dw_density(fout, BDss0enu_ISGW2, 1000);
  fout.close();

  fout.open("BDss0enu_LLSWB1.csv");
  BDss0lnuDecayRate BDss0enu_LLSWB1(mB0, mD0ssp, mE, "LLSWB1");
  print_dGamma_dw_density(fout, BDss0enu_LLSWB1, 1000);
  fout.close();

  fout.open("BDss0enu_LLSWB2.csv");
  BDss0lnuDecayRate BDss0enu_LLSWB2(mB0, mD0ssp, mE, "LLSWB2");
  print_dGamma_dw_density(fout, BDss0enu_LLSWB2, 1000);
  fout.close();

  // B0 -> D'_1 e nu
  fout.open("BD1primeenu_ISGW2.csv");
  BD1primelnuDecayRate BD1primeenu_ISGW2(mB0, mD1primep, mE, "ISGW2");
  print_dGamma_dw_density(fout, BD1primeenu_ISGW2, 1000);
  fout.close();

  fout.open("BD1primeenu_LLSWB1.csv");
  BD1primelnuDecayRate BD1primeenu_LLSWB1(mB0, mD1primep, mE, "LLSWB1");
  print_dGamma_dw_density(fout, BD1primeenu_LLSWB1, 1000);
  fout.close();

  fout.open("BD1primeenu_LLSWB2.csv");
  BD1primelnuDecayRate BD1primeenu_LLSWB2(mB0, mD1primep, mE, "LLSWB2");
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

  // B0 -> D_2 e nu
  fout.open("BD2enu_ISGW2.csv");
  BD2lnuDecayRate BD2enu_ISGW2(mB0, mD2p, mE, "ISGW2");
  print_dGamma_dw_density(fout, BD2enu_ISGW2, 1000);
  fout.close();

  fout.open("BD2enu_LLSWB1.csv");
  BD2lnuDecayRate BD2enu_LLSWB1(mB0, mD2p, mE, "LLSWB1");
  print_dGamma_dw_density(fout, BD2enu_LLSWB1, 1000);
  fout.close();

  fout.open("BD2enu_LLSWB2.csv");
  BD2lnuDecayRate BD2enu_LLSWB2(mB0, mD2p, mE, "LLSWB2");
  print_dGamma_dw_density(fout, BD2enu_LLSWB2, 1000);
  fout.close();

  // B0 -> D*_0 mu nu
  fout.open("BDss0munu_ISGW2.csv");
  BDss0lnuDecayRate BDss0munu_ISGW2(mB0, mD0ssp, mMu, "ISGW2");
  print_dGamma_dw_density(fout, BDss0munu_ISGW2, 1000);
  fout.close();

  fout.open("BDss0munu_LLSWB1.csv");
  BDss0lnuDecayRate BDss0munu_LLSWB1(mB0, mD0ssp, mMu, "LLSWB1");
  print_dGamma_dw_density(fout, BDss0munu_LLSWB1, 1000);
  fout.close();

  fout.open("BDss0munu_LLSWB2.csv");
  BDss0lnuDecayRate BDss0munu_LLSWB2(mB0, mD0ssp, mMu, "LLSWB2");
  print_dGamma_dw_density(fout, BDss0munu_LLSWB2, 1000);
  fout.close();

  // B0 -> D'_1 mu nu
  fout.open("BD1primemunu_ISGW2.csv");
  BD1primelnuDecayRate BD1primemunu_ISGW2(mB0, mD1primep, mMu, "ISGW2");
  print_dGamma_dw_density(fout, BD1primemunu_ISGW2, 1000);
  fout.close();

  fout.open("BD1primemunu_LLSWB1.csv");
  BD1primelnuDecayRate BD1primemunu_LLSWB1(mB0, mD1primep, mMu, "LLSWB1");
  print_dGamma_dw_density(fout, BD1primemunu_LLSWB1, 1000);
  fout.close();

  fout.open("BD1primemunu_LLSWB2.csv");
  BD1primelnuDecayRate BD1primemunu_LLSWB2(mB0, mD1primep, mMu, "LLSWB2");
  print_dGamma_dw_density(fout, BD1primemunu_LLSWB2, 1000);
  fout.close();

  // B0 -> D_1 mu nu
  fout.open("BD1munu_ISGW2.csv");
  BD1lnuDecayRate BD1munu_ISGW2(mB0, mD1p, mMu, "ISGW2");
  print_dGamma_dw_density(fout, BD1munu_ISGW2, 1000);
  fout.close();

  fout.open("BD1munu_LLSWB1.csv");
  BD1lnuDecayRate BD1munu_LLSWB1(mB0, mD1p, mMu, "LLSWB1");
  print_dGamma_dw_density(fout, BD1munu_LLSWB1, 1000);
  fout.close();

  fout.open("BD1munu_LLSWB2.csv");
  BD1lnuDecayRate BD1munu_LLSWB2(mB0, mD1p, mMu, "LLSWB2");
  print_dGamma_dw_density(fout, BD1munu_LLSWB2, 1000);
  fout.close();

  // B0 -> D_2 mu nu
  fout.open("BD2munu_ISGW2.csv");
  BD2lnuDecayRate BD2munu_ISGW2(mB0, mD2p, mMu, "ISGW2");
  print_dGamma_dw_density(fout, BD2munu_ISGW2, 1000);
  fout.close();

  fout.open("BD2munu_LLSWB1.csv");
  BD2lnuDecayRate BD2munu_LLSWB1(mB0, mD2p, mMu, "LLSWB1");
  print_dGamma_dw_density(fout, BD2munu_LLSWB1, 1000);
  fout.close();

  fout.open("BD2munu_LLSWB2.csv");
  BD2lnuDecayRate BD2munu_LLSWB2(mB0, mD2p, mMu, "LLSWB2");
  print_dGamma_dw_density(fout, BD2munu_LLSWB2, 1000);
  fout.close();

  // B0 -> D*_0 tau nu
  fout.open("BDss0taunu_ISGW2.csv");
  BDss0lnuDecayRate BDss0taunu_ISGW2(mB0, mD0ssp, mTau, "ISGW2");
  print_dGamma_dw_density(fout, BDss0taunu_ISGW2, 1000);
  fout.close();

  fout.open("BDss0taunu_LLSWB1.csv");
  BDss0lnuDecayRate BDss0taunu_LLSWB1(mB0, mD0ssp, mTau, "LLSWB1");
  print_dGamma_dw_density(fout, BDss0taunu_LLSWB1, 1000);
  fout.close();

  fout.open("BDss0taunu_LLSWB2.csv");
  BDss0lnuDecayRate BDss0taunu_LLSWB2(mB0, mD0ssp, mTau, "LLSWB2");
  print_dGamma_dw_density(fout, BDss0taunu_LLSWB2, 1000);
  fout.close();

  // B0 -> D'_1 tau nu
  fout.open("BD1primetaunu_ISGW2.csv");
  BD1primelnuDecayRate BD1primetaunu_ISGW2(mB0, mD1primep, mTau, "ISGW2");
  print_dGamma_dw_density(fout, BD1primetaunu_ISGW2, 1000);
  fout.close();

  fout.open("BD1primetaunu_LLSWB1.csv");
  BD1primelnuDecayRate BD1primetaunu_LLSWB1(mB0, mD1primep, mTau, "LLSWB1");
  print_dGamma_dw_density(fout, BD1primetaunu_LLSWB1, 1000);
  fout.close();

  fout.open("BD1primetaunu_LLSWB2.csv");
  BD1primelnuDecayRate BD1primetaunu_LLSWB2(mB0, mD1primep, mTau, "LLSWB2");
  print_dGamma_dw_density(fout, BD1primetaunu_LLSWB2, 1000);
  fout.close();

  // B0 -> D_1 tau nu
  fout.open("BD1taunu_ISGW2.csv");
  BD1lnuDecayRate BD1taunu_ISGW2(mB0, mD1p, mTau, "ISGW2");
  print_dGamma_dw_density(fout, BD1taunu_ISGW2, 1000);
  fout.close();

  fout.open("BD1taunu_LLSWB1.csv");
  BD1lnuDecayRate BD1taunu_LLSWB1(mB0, mD1p, mTau, "LLSWB1");
  print_dGamma_dw_density(fout, BD1taunu_LLSWB1, 1000);
  fout.close();

  fout.open("BD1taunu_LLSWB2.csv");
  BD1lnuDecayRate BD1taunu_LLSWB2(mB0, mD1p, mTau, "LLSWB2");
  print_dGamma_dw_density(fout, BD1taunu_LLSWB2, 1000);
  fout.close();

  // B0 -> D_2 tau nu
  fout.open("BD2taunu_ISGW2.csv");
  BD2lnuDecayRate BD2taunu_ISGW2(mB0, mD2p, mTau, "ISGW2");
  print_dGamma_dw_density(fout, BD2taunu_ISGW2, 1000);
  fout.close();

  fout.open("BD2taunu_LLSWB1.csv");
  BD2lnuDecayRate BD2taunu_LLSWB1(mB0, mD2p, mTau, "LLSWB1");
  print_dGamma_dw_density(fout, BD2taunu_LLSWB1, 1000);
  fout.close();

  fout.open("BD2taunu_LLSWB2.csv");
  BD2lnuDecayRate BD2taunu_LLSWB2(mB0, mD2p, mTau, "LLSWB2");
  print_dGamma_dw_density(fout, BD2taunu_LLSWB2, 1000);
  fout.close();

  return 0;
}
