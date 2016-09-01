#include <cmath> 
#include <cstdlib> 

#include <ff_reweight_constants.h>
#include "CLNPseudoscalarFF.h"

CLNPseudoscalarFF::CLNPseudoscalarFF(double mB, double mD) 
  : CLNPseudoscalarFF(mB, mD, CLNParams()) {}

CLNPseudoscalarFF::CLNPseudoscalarFF(double mB, double mD, const CLNParams &params) 
  : mB_(mB), 
    mD_(mD), 
    rho2_(params.get_d_rho2()), 
    V11_(params.get_d_v11()), 
    Delta_(params.get_d_delta()) {
}

CLNPseudoscalarFF::~CLNPseudoscalarFF() {}

PseudoscalarFF* CLNPseudoscalarFF::clone() {
  CLNParams params;
  params.set_d_rho2(rho2_);
  params.set_d_v11(V11_);
  params.set_d_delta(Delta_);
  return new CLNPseudoscalarFF(mB_, mD_, params);
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
