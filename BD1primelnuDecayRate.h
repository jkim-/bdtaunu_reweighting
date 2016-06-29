#ifndef __BD1PRIMELNUDECAYRATE_H__
#define __BD1PRIMELNUDECAYRATE_H__

#include <string>

#include "ff_reweight_defs.h"
#include "ff_reweight_utils.h"
#include "BD1primeFF.h"

class BD1primelnuDecayRate {

  friend double dGamma_dw_adapter<BD1primelnuDecayRate>(double, void*);

  public:
    BD1primelnuDecayRate(double mB, double mDss, double ml, 
                     const std::string &ff_model_name);
    BD1primelnuDecayRate(const BD1primelnuDecayRate&);
    BD1primelnuDecayRate& operator=(const BD1primelnuDecayRate&);
    ~BD1primelnuDecayRate();

    double wmin() const { return w(q2max()); }
    double wmax() const { return w(q2min()); }

    double dGamma_dw(double w) const;
    double dGamma_dw_density(double w) const;

  private:
    void cleanup();

    double q2min() const { return ml_*ml_; }
    double q2max() const { return (mB_-mDss_)*(mB_-mDss_); }
    double w(double q2) const { return (mB_*mB_+mDss_*mDss_-q2)/(2*mB_*mDss_); }
    double q2(double w) const { return (mB_*mB_+mDss_*mDss_-2*mB_*mDss_*w); }

    double dGamma_dw_aux(double w) const;

  private:
    double mB_;
    double mDss_;
    double ml_;

    BD1primeFF *ff_;
    double norm_;
};


inline double BD1primelnuDecayRate::dGamma_dw_density(double w) const {
  return dGamma_dw_aux(w) / norm_;
}

inline double BD1primelnuDecayRate::dGamma_dw(double w) const {
  return GF*GF*Vcb*Vcb*pow(mB_,5)/(48*pow(PI,3)) * dGamma_dw_aux(w);
}

#endif
