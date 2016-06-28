#include <cmath>
#include <iostream>

#include "gauss_legendre.h"
#include "ff_reweight_defs.h"
#include "ISGW2PseudoscalarFF.h"
#include "CLNPseudoscalarFF.h"
#include "BPlnuDecayRate.h"

namespace {

inline double compute_coupling_size() {
  return GF*GF*Vcb*Vcb/pow(twoPI, 3);
}

}

BPlnuDecayRate::BPlnuDecayRate(double mB, double mD, double ml,
                               const std::string &ff_model_name)
  : mB_(mB), mD_(mD), ml_(ml) {

  if (ff_model_name == "ISGW2") {

    ff_ = new ISGW2PseudoscalarFF(mB_, mD_);

  } else if (ff_model_name == "CLN") {

    ff_ = new CLNPseudoscalarFF(mB_, mD_);

  } else {

    std::string s = "BPlnuDecayRate: "; 
    s += ff_model_name + " form factor model not supported!. ";
    throw std::invalid_argument(s);

  }

  norm_ = gauss_legendre(256, BPlnu_dGamma_dq2_adapter, this, q2min(), q2max());

}

BPlnuDecayRate::BPlnuDecayRate(const BPlnuDecayRate &rhs) {
  ff_ = rhs.ff_->clone();
}

BPlnuDecayRate& BPlnuDecayRate::operator=(const BPlnuDecayRate &rhs) {
  if (this != &rhs) {
    cleanup();
    ff_ = rhs.ff_->clone();
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
  pW = (pW < 0) ? 0 : sqrt(pW)/(2.0*mB_);
  double h0 = 2.0 * mB_ * pW * fplus / sqrt(q2);
  double ht = ((mB_*mB_-mD_*mD_)*fplus + q2*fminus) / sqrt(q2);
  hl = h0*h0;
  hs = 3.0*ht*ht;
  hsl = ht*h0;
}

double BPlnuDecayRate::dGamma_dq2_aux(double q2) const {

  double pW, hl, hs, hsl;
  compute_pWhFF(q2, pW, hl, hs, hsl);

  double result = compute_non_angular(q2, pW);
  result *= hl + (ml_*ml_/(2.0*q2))*(hl+hs);
  return result;

}

double BPlnuDecayRate::dGamma_dq2dctl_aux(double q2, double ctl) const {

  double pW, hl, hs, hsl;
  compute_pWhFF(q2, pW, hl, hs, hsl);

  double result = compute_non_angular(q2, pW);
  result *= compute_angular(q2, ctl, hl, hs, hsl);

  return result;
}

double BPlnuDecayRate::dGamma_dq2(double q2) const {
  return compute_coupling_size() * dGamma_dq2_aux(q2);
}

double BPlnuDecayRate::dGamma_dq2dctl(double q2, double ctl) const {
  return compute_coupling_size() * dGamma_dq2dctl_aux(q2, ctl);
}

double BPlnuDecayRate::dGamma_dq2_density(double q2) const {
  return dGamma_dq2_aux(q2) / norm_;
}

double BPlnuDecayRate::dGamma_dq2dctl_density(double q2, double ctl) const {
  return dGamma_dq2dctl_aux(q2, ctl) / norm_;
}
