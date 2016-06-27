#ifndef __BPLNUDECAYRATE_H__
#define __BPLNUDECAYRATE_H__

#include "ISGW2PseudoscalarFF.h"

class BPlnuDecayRate {

  public:
    BPlnuDecayRate(double mB, double mD, double ml);
    BPlnuDecayRate(const BPlnuDecayRate&);
    BPlnuDecayRate& operator=(const BPlnuDecayRate&);
    ~BPlnuDecayRate();

    double dGamma_dq2dctl(double q2, double ctl);

  private:
    void cleanup();

  private:
    double mB_;
    double mD_;
    double ml_;

    ISGW2PseudoscalarFF *ff_;
};

#endif
