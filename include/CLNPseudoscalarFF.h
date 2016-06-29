#ifndef __CLNPSEUDOSCALARFF_H__
#define __CLNPSEUDOSCALARFF_H__

// Author: Daniel Chao, dchao@caltech.edu
// Special thanks to EvtGen and Michael Mazur for providing 
// most of the physics formulas 

#include "PseudoscalarFF.h"

class CLNPseudoscalarFF : public PseudoscalarFF {
  public: 
    CLNPseudoscalarFF(double mB, double mD, 
        double rho2=1.186, double V11 = 1.0816, double Delta=1.0);

    ~CLNPseudoscalarFF();

    PseudoscalarFF* clone();

    void compute_ff(double q2, double &fplus, double &fminus) const;
  
  private:
    double mB_;
    double mD_;

    double rho2_;
    double V11_;
    double Delta_;
};

#endif
