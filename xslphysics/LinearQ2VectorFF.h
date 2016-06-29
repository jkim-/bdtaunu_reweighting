#ifndef __LINEARQ2VECTORFF_H__
#define __LINEARQ2VECTORFF_H__

#include "VectorFF.h"

class LinearQ2VectorFF : public VectorFF {
  public: 
    LinearQ2VectorFF(double mB, double mDs, 
        double rho2 = 0.77, double R1 = 1.33, double R2 = 0.92);
    ~LinearQ2VectorFF();

    VectorFF* clone();

    void compute_ff(double q2, 
        double &V, double &A0, double &A1, double &A2) const;
  
  private:
    double mB_;
    double mDs_;

    double rho2_;
    double R1_;
    double R2_;
};

#endif
