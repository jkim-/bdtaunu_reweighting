#include <cmath> 
#include <cstdlib> 

#include "ff_reweight_defs.h"
#include "CLNPseudoscalarFF.h"

CLNPseudoscalarFF::CLNPseudoscalarFF(double mB, double mD, 
    double rho2, double V11, double Delta) 
  : mB_(mB), mD_(mD), rho2_(rho2), V11_(V11), Delta_(Delta) {}

CLNPseudoscalarFF::~CLNPseudoscalarFF() {}

PseudoscalarFF* CLNPseudoscalarFF::clone() {
  return new CLNPseudoscalarFF(mB_, mD_);
}

void CLNPseudoscalarFF::compute_ff(double q2, double &fplus, double &fminus) const {
  double w = (mB_*mB_+mD_*mD_-q2)/(2.*mB_*mD_);
  double z = (sqrt(w+1)-sqrt(2.))/(sqrt(w+1)+sqrt(2.));
  double V1 = V11_*(1.- 8.*rho2_*z + (51.*rho2_-10.)*z*z - (252.*rho2_-84.)*z*z*z);

  double wm1 = w - 1.0;
  double S1 = V1 * (1 +Delta_*(-0.019 + 0.041*wm1 - 0.015*wm1*wm1));

  double RD = (2*sqrt(mB_*mD_))/(mB_+mD_);
  double F1 = V1/RD;
  double F0 = (1-q2/pow(mB_+mD_,2))/RD*S1;

  fplus = F1;
  fminus = (F0 - F1) * (mB_*mB_-mD_*mD_) / q2;
}
