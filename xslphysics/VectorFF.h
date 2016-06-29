#ifndef __VECTORFF_H__
#define __VECTORFF_H__

class VectorFF {
  public: 
    virtual ~VectorFF() {};
    virtual VectorFF* clone() = 0;
    virtual void compute_ff(double q2, 
        double &V, double &A0, double &A1, double &A2) const = 0;
};

#endif
