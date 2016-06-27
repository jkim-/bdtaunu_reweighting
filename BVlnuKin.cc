#include <cmath>

#include "ff_reweight_defs.h"
#include "BVlnuKin.h"

using HepLorentzVector = CLHEP::HepLorentzVector;
using Hep3Vector = CLHEP::Hep3Vector;

void BVlnuKin::initialize_cache() {
  _ctv=-666;
  _theta_v=-666;
  _chi=-666;
}

BVlnuKin::BVlnuKin() : BXlnuKin() {
  initialize_cache();
}

BVlnuKin::BVlnuKin(
    const CLHEP::HepLorentzVector &BLab, 
    const CLHEP::HepLorentzVector &XLab, 
    const CLHEP::HepLorentzVector &LepLab, 
    const CLHEP::HepLorentzVector &XdauLab) 
  : BXlnuKin(BLab, XLab, LepLab), _XdauLab(XdauLab) {

  initialize_cache();
  initialize_boosted_vectors();
  initialize_kinematics();

}

void BVlnuKin::initialize_boosted_vectors() {

  //Daugther of the X meson in X meson's frame
  _VD_X = _XdauLab;
  _VD_X.boost(-_BLab.boostVector());
  _VD_X.boost(-_XB.boostVector());

}

void BVlnuKin::initialize_kinematics() {
  
  // ctv
  _ctv=_VD_X.vect().unit()*_XB.vect().unit();
  _theta_v=_VD_X.vect().angle(_XB.vect());
  
  // chi (by Art Snyder)
  //
  // Note that:   myHepLorentzVector.rho() = sqrt(px*px + py*py + pz*pz);
  // By contrast:       myHep3Vector.rho() = sqrt(px*px + py*py);
  Hep3Vector p3LepTrans=_LepW.vect()-_ctl*_LepW.rho()*_WB.vect().unit();
  Hep3Vector p3VDTrans=_VD_X.vect()-_ctv*_VD_X.rho()*_XB.vect().unit();
  // _chi=p3VDTrans.angle(p3LepTrans);  // Old version, with range: (0,pi).
  _chi = std::atan2(p3LepTrans.cross(p3VDTrans)*_WB.vect().unit(), p3LepTrans*p3VDTrans);
  // Note that atan2(y,x) returns chi such that tan(chi) = y/x.
  // We have chosen the orientation in which chi is measured
  // from p3LepTrans to p3VDTrans in the counter-clockwise direction, 
  // viewed in the plane in which WB.vect() is directed out of the page.  
  // y = sin(chi)*|p_l|*|p_VD| = p3LepTrans.cross(p3VDTrans)*WB.vect().unit(),
  // x = cos(chi)*|p_l|*|p_VD| = p3LepTrans*p3VDTrans

  // The return value of atan2 lies in the range (-pi, +pi), so add 2*pi to 
  // negative values to obtain the range (0,2*pi).
  if (_chi<0) { 
    _chi += twoPI;
  }
 
}
