#ifndef __ISGW2PSEUDOSCALARFF_H__
#define __ISGW2PSEUDOSCALARFF_H__

// Author: Daniel Chao, dchao@caltech.edu
// Special thanks to EvtGen and Michael Mazur for providing 
// most of the physics formulas 

#include "PseudoscalarFF.h"

class ISGW2PseudoscalarFF : public PseudoscalarFF {
  public: 
    ISGW2PseudoscalarFF(double mB, double mD);
    ~ISGW2PseudoscalarFF();

    PseudoscalarFF* clone();

    void compute_ff(double q2, double &fplus, double &fminus) const;
  
  private:
    double mB_;
    double mD_;
};

#endif
