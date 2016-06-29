#ifndef __BVLNUDECAYRATE_H__
#define __BVLNUDECAYRATE_H__

#include <string>

#include "xslphysics_utils.h"
#include "VectorFF.h"

class BVlnuDecayRate {

  friend double dGamma_dq2_adapter<BVlnuDecayRate>(double, void*);

  public:
    BVlnuDecayRate(double mB, double mDs, double ml, 
                   bool isDgamma, bool islplus,
                   const std::string &ff_model_name);
    BVlnuDecayRate(const BVlnuDecayRate&);
    BVlnuDecayRate& operator=(const BVlnuDecayRate&);
    ~BVlnuDecayRate();

    double q2min() const { return ml_*ml_; }
    double q2max() const { return (mB_-mDs_)*(mB_-mDs_); }

    double dGamma_dq2_density(double q2) const;

    double dGamma_dq2dangles_density(double q2, 
        double ctl, double ctv, double chi) const;

    // Note: the following differential decay rates are only those due to 
    // the semileptonic decay itself. the true decay rate can be obtained by 
    // multiplying the result of these functions by Br(D*->Dpi) or Br(D*->Dgamma)

    // differential decay rate in q2
    double dGamma_dq2(double q2) const;

    // differential decay rate in q2 and all decay angles
    double dGamma_dq2dangles(double q2, 
        double ctl, double ctv, double chi) const;

  private: 

    struct HelicityAmps {

      // Standard
      double h0, ht, hplus, hminus;

      // K-S
      double hu, hl, hp, hs, hsl, hti, hi, ha, hst;
    };

  private:
    void cleanup();


    void compute_pWhFF(double, double&, HelicityAmps&) const;
    double compute_non_angular(double, double) const;
    double compute_angular(double, double, double, double, 
        const HelicityAmps&) const;

    double dGamma_dq2_aux(double) const;
    double dGamma_dq2dangles_aux(double, double, double, double) const;

  private:
    double mB_;
    double mDs_;
    double ml_;
    bool isDgamma_;
    bool islplus_;

    double norm_;

    VectorFF *ff_;
};

inline double BVlnuDecayRate::compute_non_angular(double q2, double pW) const {
  return (q2-ml_*ml_)*(q2-ml_*ml_)*pW / (12.0*mB_*mB_*q2);
}

#endif
