#include <cmath> 
#include <cstdlib> 

#include <ff_reweight_constants.h>
#include "CLNVectorFF.h"

CLNVectorFF::CLNVectorFF(double mB, double mDs) 
  : CLNVectorFF(mB, mDs, CLNParams()) {}

CLNVectorFF::CLNVectorFF(double mB, double mDs, const CLNParams &params) 
  : mB_(mB), 
    mDs_(mDs), 
    F1_(params.get_dstar_F1()), 
    rho2_(params.get_dstar_rho2()),
    R0_(params.get_dstar_R0()),
    R1_(params.get_dstar_R1()),
    R2_(params.get_dstar_R2()) {
}

CLNVectorFF::~CLNVectorFF() {}

VectorFF* CLNVectorFF::clone() {
  CLNParams params;
  params.set_dstar_F1(F1_);
  params.set_dstar_rho2(rho2_);
  params.set_dstar_R0(R0_);
  params.set_dstar_R1(R1_);
  params.set_dstar_R2(R2_);
  return new CLNVectorFF(mB_, mDs_, params);
}

void CLNVectorFF::compute_ff(double q2, 
    double &V, double &A0, double &A1, double &A2) const {

  double w = (mB_*mB_+mDs_*mDs_-q2)/(2.*mB_*mDs_);
  double z = (sqrt(w+1.)-sqrt(2.))/(sqrt(w+1.)+sqrt(2.));
  double hA1 = F1_*(1.- 8.*rho2_*z + (53.*rho2_-15.)*z*z - (231.*rho2_-91.)*z*z*z);
  double wm1 = w - 1.0;
  double RDs = 2*sqrt(mB_*mDs_)/(mB_+mDs_);

  A1 = hA1* RDs*(w+1)/2.;
  V  = hA1* (R1_ - 0.12*wm1 + 0.05*wm1*wm1) / RDs;
  A2 = hA1* (R2_ + 0.11*wm1 - 0.06*wm1*wm1) / RDs;
  A0 = hA1* (R0_ - 0.11*wm1 + 0.01*wm1*wm1) / RDs;
}
