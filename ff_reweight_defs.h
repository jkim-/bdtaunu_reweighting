#ifndef __FF_REWEIGHT_DEFS_H__
#define __FF_REWEIGHT_DEFS_H__

#define _USE_MATH_DEFINES
#include <cmath>
#include <cstdlib>

constexpr double twoPI = 6.2831853071795864769;
constexpr double PI = 3.1415926535897932384;
constexpr int Upsilon4SLund = 70553;
constexpr int B0Lund = 511;
constexpr int BpLund = 521;
constexpr int DstarpLund = 413;
constexpr int Dstar0Lund = 423;
constexpr int DpLund = 411;
constexpr int D0Lund = 421;
constexpr int eLund = 11;
constexpr int muLund = 13;
constexpr int tauLund = 15;
constexpr int nueLund = 12;
constexpr int numuLund = 14;
constexpr int nutauLund = 16;
constexpr int gammaLund = 22;

constexpr double mBp = 5.2792;
constexpr double mB0 = 5.2795;
constexpr double mDp = 1.8696;
constexpr double mD0 = 1.8648;
constexpr double mDps = 2.01025;
constexpr double mD0s = 2.00696;
constexpr double mTau = 1.7768;
constexpr double mMu  = 0.10566;
constexpr double mE   = 0.000511;
constexpr double Vcb  = 0.03912;
constexpr double V11  = 1.0816;
constexpr double GF   = 0.000011664;
constexpr double hbar = 6.582119e-25;
constexpr double mb_quark = 4.20;  // [GeV] in the MSbar scheme, evaluated at mb.
constexpr double mc_quark = 0.901; // From Xing, Zhang, Zhou (2008)

inline bool is_bmeson(int lund) {
  int abslund = abs(lund);
  return (abslund == B0Lund || abslund == BpLund) ? true : false; 
}

inline bool is_dstar(int lund) {
  int abslund = abs(lund);
  return (abslund == DstarpLund || abslund == Dstar0Lund) ? true : false; 
}

inline bool is_dmeson(int lund) {
  int abslund = abs(lund);
  return (abslund == DpLund || abslund == D0Lund) ? true : false; 
}

inline bool is_lepton(int lund) {
  int abslund = abs(lund);
  return (abslund == eLund || abslund == muLund || abslund == tauLund) ? true : false; 
}

inline bool is_neutrino(int lund) {
  int abslund = abs(lund);
  return (abslund == nueLund || abslund == numuLund || abslund == nutauLund) ? true : false; 
}

#endif
