#ifndef __BPLNUDECAYRATE_H__
#define __BPLNUDECAYRATE_H__

#include <string>

#include "xslphysics_utils.h"
#include "PseudoscalarFF.h"

class BPlnuDecayRate {

  friend double dGamma_dq2_adapter<BPlnuDecayRate>(double, void*);

  public:


    // supported ff_model_name: "ISGW2", "CLN"
    BPlnuDecayRate();
    BPlnuDecayRate(double mB, double mD, double ml, 
                   const std::string &ff_model_name);
    BPlnuDecayRate(const BPlnuDecayRate&);
    BPlnuDecayRate& operator=(const BPlnuDecayRate&);
    ~BPlnuDecayRate();

    double q2min() const { return ml_*ml_; }
    double q2max() const { return (mB_-mD_)*(mB_-mD_); }

    double dGamma_dq2(double q2) const;
    double dGamma_dq2dctl(double q2, double ctl) const;

    double dGamma_dq2_density(double q2) const;
    double dGamma_dq2dctl_density(double q2, double ctl) const;

  private:
    void cleanup();

    void compute_pWhFF(double, double&, double&, double&, double&) const;
    double compute_non_angular(double, double) const;
    double compute_angular(double, double, double, double, double) const;

    double dGamma_dq2_aux(double q2) const;
    double dGamma_dq2dctl_aux(double q2, double ctl) const;

  private:
    double mB_;
    double mD_;
    double ml_;

    double norm_;

    PseudoscalarFF *ff_;
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
