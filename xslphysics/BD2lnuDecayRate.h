#ifndef __BD2LNUDECAYRATE_H__
#define __BD2LNUDECAYRATE_H__

#include <string>

#include <ff_reweight_constants.h>
#include "xslphysics_utils.h"
#include "BD2FF.h"

class BD2lnuDecayRate {

  friend double dGamma_dw_adapter<BD2lnuDecayRate>(double, void*);

  public:
    BD2lnuDecayRate();
    BD2lnuDecayRate(double mB, double mDss, double ml, 
                     const std::string &ff_model_name);
    BD2lnuDecayRate(const BD2lnuDecayRate&);
    BD2lnuDecayRate& operator=(const BD2lnuDecayRate&);
    ~BD2lnuDecayRate();

    double wmin() const { return w(q2max()); }
    double wmax() const { return w(q2min()); }

    double dGamma_dq2_density(double q2) const;
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

    double norm_;

    BD2FF *ff_;
};


inline double BD2lnuDecayRate::dGamma_dq2_density(double q2) const {
  return dGamma_dw_aux(w(q2)) / norm_;
}

inline double BD2lnuDecayRate::dGamma_dw_density(double w) const {
  return dGamma_dw_aux(w) / norm_;
}

inline double BD2lnuDecayRate::dGamma_dw(double w) const {
  return GF*GF*Vcb*Vcb*pow(mB_,5)/(48*pow(PI,3)) * dGamma_dw_aux(w);
}

#endif
