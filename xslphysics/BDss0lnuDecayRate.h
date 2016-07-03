#ifndef __BDSS0LNUDECAYRATE_H__
#define __BDSS0LNUDECAYRATE_H__

#include <cmath>
#include <string>
#include <iostream>

#include <ff_reweight_constants.h>
#include "xslphysics_utils.h"
#include "BDss0FF.h"

class BDss0lnuDecayRate {

  friend double dGamma_dw_adapter<BDss0lnuDecayRate>(double, void*);

  public:
    BDss0lnuDecayRate();
    BDss0lnuDecayRate(double mB, double mDss, double ml, 
                     const std::string &ff_model_name);
    BDss0lnuDecayRate(const BDss0lnuDecayRate&);
    BDss0lnuDecayRate& operator=(const BDss0lnuDecayRate&);
    ~BDss0lnuDecayRate();

    double wmin() const { return w(q2max()); }
    double wmax() const { return w(q2min()); }

    double dGamma_dq2_density(double q2) const;
    double dGamma_dw(double w) const;
    double dGamma_dwdctl(double w, double ctl) const;

    double dGamma_dw_density(double w) const;
    double dGamma_dwdctl_density(double w, double ctl) const;

  private:
    void cleanup();

    double q2min() const { return ml_*ml_; }
    double q2max() const { return (mB_-mDss_)*(mB_-mDss_); }
    double w(double q2) const { return (mB_*mB_+mDss_*mDss_-q2)/(2*mB_*mDss_); }
    double q2(double w) const { return (mB_*mB_+mDss_*mDss_-2*mB_*mDss_*w); }

    double dGamma_dw_aux(double w) const;
    double dGamma_dwdctl_aux(double w, double ctl) const;

  private:
    double mB_;
    double mDss_;
    double ml_;

    double norm_;

    BDss0FF *ff_;
};

inline double BDss0lnuDecayRate::dGamma_dq2_density(double q2) const {
  return dGamma_dw_aux(w(q2)) / norm_;
}

inline double BDss0lnuDecayRate::dGamma_dwdctl_aux(double w, double ctl) const {
  return dGamma_dw_aux(w) * (1-ctl*ctl);
}

inline double BDss0lnuDecayRate::dGamma_dw_density(double w) const {
  return dGamma_dw_aux(w) / norm_;
}

inline double BDss0lnuDecayRate::dGamma_dwdctl_density(double w, double ctl) const {
  return dGamma_dwdctl_aux(w, ctl) / norm_;
}

inline double BDss0lnuDecayRate::dGamma_dw(double w) const {
  return GF*GF*Vcb*Vcb*pow(mB_,5)/(48*pow(PI,3)) * dGamma_dw_aux(w);
}

inline double BDss0lnuDecayRate::dGamma_dwdctl(double w, double ctl) const {
  return GF*GF*Vcb*Vcb*pow(mB_,5)/(64*pow(PI,3)) * dGamma_dwdctl_aux(w, ctl);
}

#endif
