#ifndef __CLNVECTORFF_H__
#define __CLNVECTORFF_H__

#include "VectorFF.h"
#include "CLNParams.h"

class CLNVectorFF : public VectorFF {
  public: 
    CLNVectorFF(double mB, double mDs);
    CLNVectorFF(double mB, double mDs, const CLNParams &cln_params);
    ~CLNVectorFF();

    VectorFF* clone();

    void compute_ff(double q2, 
        double &V, double &A0, double &A1, double &A2) const;
  
  private:
    double mB_;
    double mDs_;

    double F1_;
    double rho2_;
    double R0_;
    double R1_;
    double R2_;
};

#endif
