#ifndef __FF_REWEIGHT_DEFS_H__
#define __FF_REWEIGHT_DEFS_H__

#define _USE_MATH_DEFINES
#include <cmath>
#include <cstdlib>

extern const double twoPi;

extern const int Upsilon4SLund;
extern const int B0Lund;
extern const int BpLund;
extern const int DstarpLund;
extern const int Dstar0Lund;
extern const int DpLund;
extern const int D0Lund;
extern const int eLund;
extern const int muLund;
extern const int tauLund;
extern const int nueLund;
extern const int numuLund;
extern const int nutauLund;

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
