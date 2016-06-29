#ifndef __PSEUDOSCALARFF_H__
#define __PSEUDOSCALARFF_H__

class PseudoscalarFF {
  public: 
    virtual ~PseudoscalarFF() {};
    virtual PseudoscalarFF* clone() = 0;
    virtual void compute_ff(double q2, double &fplus, double &fminus) const = 0;
};

#endif
