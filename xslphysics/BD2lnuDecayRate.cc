#include <cmath>
#include <iostream>
#include <stdexcept>

#include <gauss_legendre.h>

#include "BD2FF.h"
#include "BD2lnuDecayRate.h"


BD2lnuDecayRate::BD2lnuDecayRate() {
  ff_ = nullptr;
}

BD2lnuDecayRate::BD2lnuDecayRate(double mB, double mDss, double ml,
                               const std::string &ff_model_name)
  : mB_(mB), mDss_(mDss), ml_(ml) {

  if (ff_model_name == "ISGW2") {

    ff_ = new ISGW2BD2FF(mB_, mDss_);

  } else if (ff_model_name == "LLSWB1") {

    ff_ = new LLSWBD2FF(mB_, mDss_, true);

  } else if (ff_model_name == "LLSWB2") {

    ff_ = new LLSWBD2FF(mB_, mDss_, false);

  } else {

    std::string s = "BD2lnuDecayRate: "; 
    s += ff_model_name + " form factor model not supported!. ";
    throw std::invalid_argument(s);

  }

  norm_ = gauss_legendre(256, dGamma_dw_adapter<BD2lnuDecayRate>, this, wmin(), wmax());

}

BD2lnuDecayRate::BD2lnuDecayRate(const BD2lnuDecayRate &rhs) {
  mB_ = rhs.mB_;
  mDss_ = rhs.mDss_;
  ml_ = rhs.ml_;
  norm_ = rhs.norm_;
  ff_ = rhs.ff_->clone();
}

BD2lnuDecayRate& BD2lnuDecayRate::operator=(const BD2lnuDecayRate &rhs) {
  if (this != &rhs) {
    cleanup();
    mB_ = rhs.mB_;
    mDss_ = rhs.mDss_;
    ml_ = rhs.ml_;
    norm_ = rhs.norm_;
    ff_ = rhs.ff_->clone();
  }
  return *this;
}

void BD2lnuDecayRate::cleanup() {
  delete ff_;
}

BD2lnuDecayRate::~BD2lnuDecayRate() {
  cleanup();
}

double BD2lnuDecayRate::dGamma_dw_aux(double w) const {

  double kV, kA1, kA3rkA2;
  ff_->compute_ff(q2(w), kV, kA1, kA3rkA2);

  double r = mDss_ / mB_;

  double result = (w-r)*kA1 + (w*w - 1.0)*kA3rkA2;
  result *= 2.0/3.0 * result;
  result += (1.0-2.0*r*w+r*r)*(kA1*kA1+(w*w-1.0)*kV*kV);
  result *= r*r*r*pow(w*w-1, 1.5);

  return result;
}
