#include <cmath> 
#include <cstdlib> 

#include <ff_reweight_constants.h>
#include "LinearQ2VectorFF.h"

LinearQ2VectorFF::LinearQ2VectorFF(double mB, double mDs,
    double rho2, double R1, double R2) 
  : mB_(mB), mDs_(mDs), rho2_(rho2), R1_(R1), R2_(R2) {}

LinearQ2VectorFF::~LinearQ2VectorFF() {}

VectorFF* LinearQ2VectorFF::clone() {
  return new LinearQ2VectorFF(mB_, mDs_, rho2_, R1_, R2_);
}

void LinearQ2VectorFF::compute_ff(double q2, 
    double &V, double &A0, double &A1, double &A2) const {

  double w = (mB_*mB_+mDs_*mDs_-q2)/(2.*mB_*mDs_);
  double RDs = 2*sqrt(mB_*mDs_)/(mB_+mDs_);

  double hA1 = 1-rho2_*(w-1);
  A1 = hA1* RDs*(w+1)/2.;
  V  = hA1* R1_/RDs;
  A2 = hA1* R2_/RDs;
  A0 = 0.;
}
