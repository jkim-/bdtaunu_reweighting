#include <cmath>
#include <iostream>
#include <stdexcept>

#include <gauss_legendre.h>

#include "BD1primeFF.h"
#include "BD1primelnuDecayRate.h"

BD1primelnuDecayRate::BD1primelnuDecayRate() {
  ff_ = nullptr;
}

BD1primelnuDecayRate::BD1primelnuDecayRate(double mB, double mDss, double ml,
                               const std::string &ff_model_name)
  : mB_(mB), mDss_(mDss), ml_(ml) {

  if (ff_model_name == "ISGW2") {

    ff_ = new ISGW2BD1primeFF(mB_, mDss_);

  } else if (ff_model_name == "LLSWB1") {

    ff_ = new LLSWBD1primeFF(mB_, mDss_, true);

  } else if (ff_model_name == "LLSWB2") {

    ff_ = new LLSWBD1primeFF(mB_, mDss_, false);

  } else {

    std::string s = "BD1primelnuDecayRate: "; 
    s += ff_model_name + " form factor model not supported!. ";
    throw std::invalid_argument(s);

  }

  norm_ = gauss_legendre(256, dGamma_dw_adapter<BD1primelnuDecayRate>, this, wmin(), wmax());

}

BD1primelnuDecayRate::BD1primelnuDecayRate(const BD1primelnuDecayRate &rhs) {
  mB_ = rhs.mB_;
  mDss_ = rhs.mDss_;
  ml_ = rhs.ml_;
  norm_ = rhs.norm_;
  ff_ = rhs.ff_->clone();
}

BD1primelnuDecayRate& BD1primelnuDecayRate::operator=(const BD1primelnuDecayRate &rhs) {
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

void BD1primelnuDecayRate::cleanup() {
  delete ff_;
}

BD1primelnuDecayRate::~BD1primelnuDecayRate() {
  cleanup();
}

double BD1primelnuDecayRate::dGamma_dw_aux(double w) const {

  double gA, gV1, gV3rgV2;
  ff_->compute_ff(q2(w), gA, gV1, gV3rgV2);

  double r = mDss_ / mB_;

  double result = (w-r)*gV1 + (w*w - 1.0)*gV3rgV2;
  result *= result;
  result += 2.0*(1.0-2.0*r*w+r*r)*(gV1*gV1+(w*w-1.0)*gA*gA);
  result *= r*r*r*pow(w*w-1, 0.5);

  return result;
}
