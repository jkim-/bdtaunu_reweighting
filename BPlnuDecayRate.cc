#include <cmath>

#include "ff_reweight_defs.h"
#include "BPlnuDecayRate.h"

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

double BPlnuDecayRate::dGamma_dq2dctl(double q2, double ctl) {

  // fplus, fminus
  double fplus, fminus;
  ff_->compute_ff(q2, fplus, fminus);

  double pW = 
    mB_*mB_*mB_*mB_ + mD_*mD_*mD_*mD_ + q2*q2 -
    2.0*mB_*mB_*mD_*mD_ - 2.0*mB_*mB_*q2 - 2.0*mD_*mD_*q2;

  double h0 = 2.0 * mB_ * pW * fplus / sqrt(q2);
  double ht = ((mB_*mB_-mD_*mD_)*fplus + q2*fminus) / sqrt(q2);
  double hl = h0*h0;
  double hs = 3.0*ht*ht;
  double hsl = ht*h0;

  double result = 
    0.75*(1-ctl*ctl)*hl +
    (ml_*ml_/(2.0*q2)) * (1.5*ctl*ctl*hl + 0.5*hs + 3.0*ctl*hsl);

  result *= (q2-ml_*ml_)*(q2-ml_*ml_)*pW / (12*mB_*mB_*q2);
  result *= GF*GF*Vcb*Vcb/pow(twoPI, 3);

  return result;
}
