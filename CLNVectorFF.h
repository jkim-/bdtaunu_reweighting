#ifndef __CLNVECTORFF_H__
#define __CLNVECTORFF_H__

#include "VectorFF.h"

class CLNVectorFF : public VectorFF {
  public: 
    CLNVectorFF(double mB, double mDs, 
        double F1 = 0.921, double rho2 = 1.207, 
        double R0 = 1.14, double R1 = 1.401, double R2 = 0.854);
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
