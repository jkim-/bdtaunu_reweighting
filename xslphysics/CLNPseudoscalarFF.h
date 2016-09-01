#ifndef __CLNPSEUDOSCALARFF_H__
#define __CLNPSEUDOSCALARFF_H__

// Author: Daniel Chao, dchao@caltech.edu
// Special thanks to EvtGen and Michael Mazur for providing 
// most of the physics formulas 

#include "PseudoscalarFF.h"
#include "CLNParams.h"

class CLNPseudoscalarFF : public PseudoscalarFF {
  public: 

    CLNPseudoscalarFF(double mB, double mD);
    CLNPseudoscalarFF(double mB, double mD, const CLNParams &cln_params);

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
