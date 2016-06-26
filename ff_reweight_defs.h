#ifndef __FF_REWEIGHT_DEFS_H__
#define __FF_REWEIGHT_DEFS_H__

#define _USE_MATH_DEFINES
#include <cmath>
#include <cstdlib>

constexpr double twoPi = 2*M_PI;
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
