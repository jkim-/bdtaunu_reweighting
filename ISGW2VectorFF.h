#ifndef __ISGW2VECTORFF_H__
#define __ISGW2VECTORFF_H__

#include "VectorFF.h"

class ISGW2VectorFF : public VectorFF {
  public: 
    ISGW2VectorFF(double mB, double mDs);
    ~ISGW2VectorFF();

    VectorFF* clone();

    void compute_ff(double q2, 
        double &V, double &A0, double &A1, double &A2) const;
  
  private:
    double mB_;
    double mDs_;
};

#endif
