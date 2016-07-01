#include <cmath>
#include <iostream>

#include <gauss_legendre.h>

#include "BD1FF.h"
#include "BD1lnuDecayRate.h"

BD1lnuDecayRate::BD1lnuDecayRate() {
  ff_ = nullptr;
}

BD1lnuDecayRate::BD1lnuDecayRate(double mB, double mDss, double ml,
                               const std::string &ff_model_name)
  : mB_(mB), mDss_(mDss), ml_(ml) {

  if (ff_model_name == "ISGW2") {

    ff_ = new ISGW2BD1FF(mB_, mDss_);

  } else if (ff_model_name == "LLSWB1") {

    ff_ = new LLSWBD1FF(mB_, mDss_, true);

  } else if (ff_model_name == "LLSWB2") {

    ff_ = new LLSWBD1FF(mB_, mDss_, false);

  } else {

    std::string s = "BD1lnuDecayRate: "; 
    s += ff_model_name + " form factor model not supported!. ";
    throw std::invalid_argument(s);

  }

  norm_ = gauss_legendre(256, dGamma_dw_adapter<BD1lnuDecayRate>, this, wmin(), wmax());

}

BD1lnuDecayRate::BD1lnuDecayRate(const BD1lnuDecayRate &rhs) {
  ff_ = rhs.ff_->clone();
}

BD1lnuDecayRate& BD1lnuDecayRate::operator=(const BD1lnuDecayRate &rhs) {
  if (this != &rhs) {
    cleanup();
    ff_ = rhs.ff_->clone();
  }
  return *this;
}

void BD1lnuDecayRate::cleanup() {
  delete ff_;
}

BD1lnuDecayRate::~BD1lnuDecayRate() {
  cleanup();
}

double BD1lnuDecayRate::dGamma_dw_aux(double w) const {

  double fA, fV1, fV3rfV2;
  ff_->compute_ff(q2(w), fA, fV1, fV3rfV2);

  double r = mDss_ / mB_;

  double result = (w-r)*fV1 + (w*w - 1.0)*fV3rfV2;
  result *= result;
  result += 2.0*(1.0-2.0*r*w+r*r)*(fV1*fV1+(w*w-1.0)*fA*fA);
  result *= r*r*r*pow(w*w-1, 0.5);

  return result;
}
