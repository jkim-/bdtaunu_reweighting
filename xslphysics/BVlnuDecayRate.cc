#include <cmath>
#include <string>
#include <stdexcept>

#include <ff_reweight_constants.h>
#include <gauss_legendre.h>

#include "BVlnuDecayRate.h"
#include "ISGW2VectorFF.h"
#include "CLNVectorFF.h"

namespace {

inline double compute_coupling_size() {
  return GF*GF*Vcb*Vcb/pow(twoPI, 4);
}

}

BVlnuDecayRate::BVlnuDecayRate(double mB, double mDs, double ml, 
    bool isDgamma, bool islplus, const std::string &ff_model_name)
  : mB_(mB), mDs_(mDs), ml_(ml), isDgamma_(isDgamma), islplus_(islplus) {

  if (ff_model_name == "ISGW2") {

    ff_ = new ISGW2VectorFF(mB_, mDs_);

  } else if (ff_model_name == "CLN") {

    ff_ = new CLNVectorFF(mB_, mDs_);

  } else {

    std::string s = "BVlnuDecayRate: ";
    s += ff_model_name + " form factor model not supported!. ";
    throw std::invalid_argument(s);

  }

  norm_ = gauss_legendre(256, dGamma_dq2_adapter<BVlnuDecayRate>, this, q2min(), q2max());
}

BVlnuDecayRate::BVlnuDecayRate(const BVlnuDecayRate &rhs) {
  ff_ = rhs.ff_->clone();
}

BVlnuDecayRate& BVlnuDecayRate::operator=(const BVlnuDecayRate &rhs) {
  if (this != &rhs) {
    cleanup();
    ff_ = rhs.ff_->clone();
  }
  return *this;
}

void BVlnuDecayRate::cleanup() {
  delete ff_;
}

BVlnuDecayRate::~BVlnuDecayRate() {
  cleanup();
}

void BVlnuDecayRate::compute_pWhFF(double q2, 
    double &pW, HelicityAmps &amps) const {

  double V, A0, A1, A2;
  ff_->compute_ff(q2, V, A0, A1, A2);

  pW = mB_*mB_*mB_*mB_ + mDs_*mDs_*mDs_*mDs_ + q2*q2 -
    2.*mB_*mB_*mDs_*mDs_ - 2.*mB_*mB_*q2 - 2.*mDs_*mDs_*q2;
  pW = (pW < 0) ? 0 : sqrt(pW)/(2.0*mB_);

  double h0 = 
    ((mB_*mB_-mDs_*mDs_-q2)*(mB_+mDs_)*A1 - 4*mB_*mB_*pW*pW*A2/(mB_+mDs_)) 
    / (2*mDs_*sqrt(q2));

  double ht = 2*mB_*pW*A0/sqrt(q2);
  
  // The sign in the middle is reversed from 1203.2654
  // to match Korner-Shuler (acording to Mazur)
  double hplus  = (mB_+mDs_)*A1 + 2*mB_/(mB_+mDs_)*pW*V; 
  double hminus = (mB_+mDs_)*A1 - 2*mB_/(mB_+mDs_)*pW*V; 

  amps.h0 = h0; 
  amps.ht = ht; 
  amps.hplus = hplus; 
  amps.hminus = hminus;
  amps.hu  = hplus*hplus + hminus*hminus;
  amps.hl  = h0*h0;
  amps.hp  = hplus*hplus - hminus*hminus;
  amps.hs  = 3.0 * ht*ht;
  amps.hsl = ht*h0;
  amps.hti = hplus*hminus;
  amps.hi  = 0.5 * (hplus*h0 + hminus*h0);
  amps.ha  = 0.5 * (hplus*h0 - hminus*h0);
  amps.hst = 0.5 * (hplus*ht + hminus*ht);

}

double BVlnuDecayRate::compute_angular(double q2, 
    double ctl, double ctv, double chi, 
    const HelicityAmps &amps) const {

  // flip represents the spin flip term in Eq 24
  double flip  = ml_*ml_ / (2.0 * q2);

  double sin2tl = 2.*ctl*sqrt(1.-ctl*ctl);
  double sin2tv = 2.*ctv*sqrt(1.-ctv*ctv);

  // the 13 angular terms of Eq 22, listed in the same order
  double ang1  = (3./8.)*(1.+ctl*ctl)*(3./4.)*(1.-ctv*ctv);
  double ang2  = (3./4.)*(1.-ctl*ctl)*(3./2.)*(ctv*ctv);
  double ang3  = (-3./4.)*(1.-ctl*ctl)*cos(2.*chi)*(3./4.)*(1.-ctv*ctv);
  double ang4  = (-9./16.)*sin2tl*cos(chi)*sin2tv;
  double ang5  = (3./4.)*ctl*(3./4.)*(1.-ctv*ctv);
  double ang6  = (-9./8.)*sqrt(1.-ctl*ctl)*cos(chi)*sin2tv;
  double ang7  = (3./4.)*(1.-ctl*ctl)*(3./4.)*(1.-ctv*ctv);
  double ang8  = (3./2.)*ctl*ctl*(3./2.)*ctv*ctv;
  double ang9  = (3./4.)*(1.-ctl*ctl)*cos(2.*chi)*(3./4.)*(1.-ctv*ctv)*2.0;
  double ang10 = (9./8.)*sin2tl*cos(chi)*sin2tv;
  double ang11 = (3./2.)*ctv*ctv*(1./2.);
  double ang12 = (3.)*ctl*(3./2.)*ctv*ctv;
  double ang13 = (9./4.)*sqrt(1.-ctl*ctl)*cos(chi)*sin2tv;

  if (isDgamma_) {
    ang1  = (3./8.)*(1.+ctl*ctl)*(3./4.)*(1.+ctv*ctv);
    ang2  = (3./4.)*(1.-ctl*ctl)*(3./2.)*(1.-ctv*ctv);
    ang3  = (3./4.)*(1.-ctl*ctl)*cos(2.*chi)*(3./4.)*(1.-ctv*ctv);
    ang4  = (9./16.)*sin2tl*cos(chi)*sin2tv;
    ang5  = (3./4.)*ctl*(3./4.)*(1.+ctv*ctv);
    ang6  = (9./8.)*sqrt(1.-ctl*ctl)*cos(chi)*sin2tv;
    ang7  = (3./4.)*(1.-ctl*ctl)*(3./4.)*(1.+ctv*ctv);
    ang8  = (3./2.)*ctl*ctl*(3./2.)*(1.-ctv*ctv);
    ang9  = (-3./4.)*(1.-ctl*ctl)*cos(2.*chi)*(3./4.)*(1.-ctv*ctv)*2.0;
    ang10 = (-9./8.)*sin2tl*cos(chi)*sin2tv;
    ang11 = (3./2.)*(1.-ctv*ctv)*(1./2.);
    ang12 = (3.)*ctl*(3./2.)*(1.-ctv*ctv);
    ang13 = (-9./4.)*sqrt(1.-ctl*ctl)*cos(chi)*sin2tv;
  }

  // tau+ parity flip
  if (islplus_) {
    ang5 *= -1.0;
    ang6 *= -1.0;
  }

  double result = 
    ang1*amps.hu +
    ang2*amps.hl +
    ang3*amps.hti +
    ang4*amps.hi +
    ang5*amps.hp +
    ang6*amps.ha +
    ang7*flip*amps.hu +
    ang8*flip*amps.hl +
    ang9*flip*amps.hti +
    ang10*flip*amps.hi +
    ang11*flip*amps.hs +
    ang12*flip*amps.hsl +
    ang13*flip*amps.hst;

  return result;

}

double BVlnuDecayRate::dGamma_dq2dangles_aux(
    double q2, double ctl, double ctv, double chi) const {

  double pW; HelicityAmps amps;
  compute_pWhFF(q2, pW, amps);

  double result = compute_non_angular(q2, pW);
  result *= compute_angular(q2, ctl, ctv, chi, amps);

  return result;
}


double BVlnuDecayRate::dGamma_dq2_aux(double q2) const {

  double pW; HelicityAmps amps;
  compute_pWhFF(q2, pW, amps);

  double result = compute_non_angular(q2, pW);
  result *= (amps.hu+amps.hl) + (ml_*ml_)/(2.0*q2)*(amps.hu+amps.hl+amps.hs);
  result *= twoPI;
  return result;

}

double BVlnuDecayRate::dGamma_dq2(double q2) const {
  return compute_coupling_size() * dGamma_dq2_aux(q2);
}

double BVlnuDecayRate::dGamma_dq2dangles(
    double q2, double ctl, double ctv, double chi) const {
  return compute_coupling_size() * dGamma_dq2dangles_aux(q2, ctl, ctv, chi);
}

double BVlnuDecayRate::dGamma_dq2_density(double q2) const {
  return dGamma_dq2_aux(q2) / norm_;
}

double BVlnuDecayRate::dGamma_dq2dangles_density(double q2, 
    double ctl, double ctv, double chi) const {
  return dGamma_dq2dangles_aux(q2, ctl, ctv, chi) / norm_;
}

