#include <cmath>

#include "ff_reweight_defs.h"
#include "BPlnuDecayRate.h"

inline double compute_coupling_size() {
  return GF*GF*Vcb*Vcb/pow(twoPI, 3);
}

BPlnuDecayRate::BPlnuDecayRate(double mB, double mD, double ml)
  : mB_(mB), mD_(mD), ml_(ml) {

  ff_ = new ISGW2PseudoscalarFF(mB, mD);
}

BPlnuDecayRate::BPlnuDecayRate(const BPlnuDecayRate &rhs) {
  ff_ = new ISGW2PseudoscalarFF(*(rhs.ff_));
}

BPlnuDecayRate& BPlnuDecayRate::operator=(const BPlnuDecayRate &rhs) {
  if (this != &rhs) {
    cleanup();
    ff_ = new ISGW2PseudoscalarFF(*(rhs.ff_));
  }
  return *this;
}

void BPlnuDecayRate::cleanup() {
  delete ff_;
}

BPlnuDecayRate::~BPlnuDecayRate() {
  cleanup();
}

void BPlnuDecayRate::compute_pWhFF(double q2, 
    double &pW, double &hl, double &hs, double &hsl) const {

  double fplus, fminus; 
  ff_->compute_ff(q2, fplus, fminus);

  pW = mB_*mB_*mB_*mB_ + mD_*mD_*mD_*mD_ + q2*q2 -
       2.0*mB_*mB_*mD_*mD_ - 2.0*mB_*mB_*q2 - 2.0*mD_*mD_*q2;
  double h0 = 2.0 * mB_ * pW * fplus / sqrt(q2);
  double ht = ((mB_*mB_-mD_*mD_)*fplus + q2*fminus) / sqrt(q2);
  hl = h0*h0;
  hs = 3.0*ht*ht;
  hsl = ht*h0;
}

double BPlnuDecayRate::dGamma_dq2(double q2) const {

  double pW, hl, hs, hsl;
  compute_pWhFF(q2, pW, hl, hs, hsl);

  double result = compute_non_angular(q2, pW);
  result *= (1+(ml_*ml_/(2.0*q2)))*hl + hs;
  result *= compute_coupling_size();

  return result;
}

double BPlnuDecayRate::dGamma_dq2dctl(double q2, double ctl) const {

  double pW, hl, hs, hsl;
  compute_pWhFF(q2, pW, hl, hs, hsl);

  double result = compute_non_angular(q2, pW);
  result *= compute_angular(q2, ctl, hl, hs, hsl);
  result *= compute_coupling_size();

  return result;
}
