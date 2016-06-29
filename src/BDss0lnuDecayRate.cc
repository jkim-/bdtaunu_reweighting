#include <cmath>
#include <iostream>

#include "gauss_legendre.h"
#include "BDss0FF.h"
#include "BDss0lnuDecayRate.h"


BDss0lnuDecayRate::BDss0lnuDecayRate(double mB, double mDss, double ml,
                               const std::string &ff_model_name)
  : mB_(mB), mDss_(mDss), ml_(ml) {

  if (ff_model_name == "ISGW2") {

    ff_ = new ISGW2BDss0FF(mB_, mDss_);

  } else if (ff_model_name == "LLSWB1") {

    ff_ = new LLSWBDss0FF(mB_, mDss_, true);

  } else if (ff_model_name == "LLSWB2") {

    ff_ = new LLSWBDss0FF(mB_, mDss_, false);

  } else {

    std::string s = "BDss0lnuDecayRate: "; 
    s += ff_model_name + " form factor model not supported!. ";
    throw std::invalid_argument(s);

  }

  norm_ = gauss_legendre(256, dGamma_dw_adapter<BDss0lnuDecayRate>, this, wmin(), wmax());

}

BDss0lnuDecayRate::BDss0lnuDecayRate(const BDss0lnuDecayRate &rhs) {
  ff_ = rhs.ff_->clone();
}

BDss0lnuDecayRate& BDss0lnuDecayRate::operator=(const BDss0lnuDecayRate &rhs) {
  if (this != &rhs) {
    cleanup();
    ff_ = rhs.ff_->clone();
  }
  return *this;
}

void BDss0lnuDecayRate::cleanup() {
  delete ff_;
}

BDss0lnuDecayRate::~BDss0lnuDecayRate() {
  cleanup();
}

double BDss0lnuDecayRate::dGamma_dw_aux(double w) const {

  double gp, gm; 
  ff_->compute_ff(q2(w), gp, gm);

  double r = mDss_ / mB_;

  double result = (1+r)*gp-(1-r)*gm; 
  result *= result;
  result *= r*r*r*pow(w*w-1, 1.5);

  return result;
}
