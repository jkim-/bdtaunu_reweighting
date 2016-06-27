#ifndef __BPLNUDECAYRATE_H__
#define __BPLNUDECAYRATE_H__

#include "ISGW2PseudoscalarFF.h"

class BPlnuDecayRate {

  public:
    BPlnuDecayRate(double mB, double mD, double ml);
    BPlnuDecayRate(const BPlnuDecayRate&);
    BPlnuDecayRate& operator=(const BPlnuDecayRate&);
    ~BPlnuDecayRate();

    double dGamma_dq2(double q2) const;
    double dGamma_dq2dctl(double q2, double ctl) const;

  private:
    void cleanup();
    void compute_pWhFF(double, double&, double&, double&, double&) const;
    double compute_non_angular(double, double) const;
    double compute_angular(double, double, double, double, double) const;

  private:
    double mB_;
    double mD_;
    double ml_;

    ISGW2PseudoscalarFF *ff_;
};


inline double BPlnuDecayRate::compute_non_angular(double q2, double pW) const {
  return (q2-ml_*ml_)*(q2-ml_*ml_)*pW / (12.0*mB_*mB_*q2);
}

inline double BPlnuDecayRate::compute_angular(
    double q2, double ctl, double hl, double hs, double hsl) const {
  return 0.75*(1-ctl*ctl)*hl +
         (ml_*ml_/(2.0*q2)) * (1.5*ctl*ctl*hl + 0.5*hs + 3.0*ctl*hsl);
}

#endif
