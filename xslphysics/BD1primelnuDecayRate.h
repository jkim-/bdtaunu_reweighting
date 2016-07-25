#ifndef __BD1PRIMELNUDECAYRATE_H__
#define __BD1PRIMELNUDECAYRATE_H__

#include <string>
#include <iostream>

#include <ff_reweight_constants.h>
#include "xslphysics_utils.h"
#include "BD1primeFF.h"

class BD1primelnuDecayRate {

  friend double dGamma_dw_adapter<BD1primelnuDecayRate>(double, void*);

  public:
    BD1primelnuDecayRate();
    BD1primelnuDecayRate(double mB, double mDss, double ml, 
                     const std::string &ff_model_name);
    BD1primelnuDecayRate(const BD1primelnuDecayRate&);
    BD1primelnuDecayRate& operator=(const BD1primelnuDecayRate&);
    ~BD1primelnuDecayRate();

    double wmin() const { return w(q2max()); }
    double wmin(double mDss) const { return w(q2max(mDss)); }
    double wmax() const { return w(q2min()); }

    double q2min() const { return ml_*ml_; }
    double q2max(double mDss) const { return (mB_-mDss)*(mB_-mDss); }
    double q2max() const { return q2max(mDss_); }

    double normalization() const { return norm_; }

    double dGamma_dw_unnormed(double w, double mDss) const;
    double dGamma_dw_unnormed(double w) const;

    double dGamma_dq2_density(double q2) const;
    double dGamma_dw_density(double w) const;

    double dGamma_dw(double w) const;

  private:
    void cleanup();

    double w(double q2, double mDss) const { return (mB_*mB_+mDss*mDss-q2)/(2*mB_*mDss); }
    double w(double q2) const { return w(q2, mDss_); }
    double q2(double w, double mDss) const { return (mB_*mB_+mDss*mDss-2*mB_*mDss*w); }
    double q2(double w) const { return q2(w, mDss_); }

  private:
    double mB_;
    double mDss_;
    double ml_;

    double norm_;

    BD1primeFF *ff_;
};

inline double BD1primelnuDecayRate::dGamma_dw_unnormed(double w) const {
  return dGamma_dw_unnormed(w, mDss_);
}

inline double BD1primelnuDecayRate::dGamma_dq2_density(double q2) const {
  return dGamma_dw_unnormed(w(q2)) / norm_;
}


inline double BD1primelnuDecayRate::dGamma_dw_density(double w) const {
  return dGamma_dw_unnormed(w) / norm_;
}

inline double BD1primelnuDecayRate::dGamma_dw(double w) const {
  return GF*GF*Vcb*Vcb*pow(mB_,5)/(48*pow(PI,3)) * dGamma_dw_unnormed(w);
}

#endif
