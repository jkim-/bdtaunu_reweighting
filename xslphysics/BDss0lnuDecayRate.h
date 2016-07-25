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

    double wmin() const { return w(q2max(mDss_)); }
    double wmin(double mDss) const { return w(q2max(mDss)); }
    double wmax() const { return w(q2min()); }

    double q2min() const { return ml_*ml_; }
    double q2max() const { return q2max(mDss_); }
    double q2max(double mDss) const { return (mB_-mDss)*(mB_-mDss); }

    double normalization() const { return norm_; }

    double dGamma_dw_unnormed(double w, double mDss) const;
    double dGamma_dw_unnormed(double w) const;
    double dGamma_dwdctl_unnormed(double w, double ctl, double mDss) const;
    double dGamma_dwdctl_unnormed(double w, double ctl) const;

    double dGamma_dw_density(double w) const;
    double dGamma_dwdctl_density(double w, double ctl) const;
    double dGamma_dq2_density(double q2) const;

    double dGamma_dw(double w) const;
    double dGamma_dwdctl(double w, double ctl) const;

  private:
    void cleanup();

    double w(double q2) const { return w(q2, mDss_); }
    double q2(double w) const { return q2(w, mDss_); }
    double w(double q2, double mDss) const { return (mB_*mB_+mDss*mDss-q2)/(2*mB_*mDss); }
    double q2(double w, double mDss) const { return (mB_*mB_+mDss*mDss-2*mB_*mDss*w); }

  private:
    double mB_;
    double mDss_;
    double ml_;

    double norm_;

    BDss0FF *ff_;
};

inline double BDss0lnuDecayRate::dGamma_dw_unnormed(double w) const {
    return dGamma_dw_unnormed(w, mDss_);
}

inline double BDss0lnuDecayRate::dGamma_dwdctl_unnormed(double w, double ctl, double mDss) const {
  return dGamma_dw_unnormed(w, mDss) * (1-ctl*ctl);
}

inline double BDss0lnuDecayRate::dGamma_dwdctl_unnormed(double w, double ctl) const {
  return dGamma_dw_unnormed(w, mDss_) * (1-ctl*ctl);
}

inline double BDss0lnuDecayRate::dGamma_dw_density(double w) const {
  return dGamma_dw_unnormed(w) / norm_;
}

inline double BDss0lnuDecayRate::dGamma_dwdctl_density(double w, double ctl) const {
  return dGamma_dwdctl_unnormed(w, ctl) / norm_;
}

inline double BDss0lnuDecayRate::dGamma_dq2_density(double q2) const {
  return dGamma_dw_unnormed(w(q2)) / norm_;
}

inline double BDss0lnuDecayRate::dGamma_dw(double w) const {
  return GF*GF*Vcb*Vcb*pow(mB_,5)/(48*pow(PI,3)) * dGamma_dw_unnormed(w);
}

inline double BDss0lnuDecayRate::dGamma_dwdctl(double w, double ctl) const {
  return GF*GF*Vcb*Vcb*pow(mB_,5)/(64*pow(PI,3)) * dGamma_dwdctl_unnormed(w, ctl);
}

#endif
