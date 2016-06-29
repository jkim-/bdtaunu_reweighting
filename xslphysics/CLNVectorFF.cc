#include <cmath> 
#include <cstdlib> 

#include <ff_reweight_constants.h>
#include "CLNVectorFF.h"

CLNVectorFF::CLNVectorFF(double mB, double mDs,
    double F1, double rho2, double R0, double R1, double R2) 
  : mB_(mB), mDs_(mDs), F1_(F1), rho2_(rho2), R0_(R0), R1_(R1), R2_(R2) {}

CLNVectorFF::~CLNVectorFF() {}

VectorFF* CLNVectorFF::clone() {
  return new CLNVectorFF(mB_, mDs_, F1_, rho2_, R0_, R1_, R2_);
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
