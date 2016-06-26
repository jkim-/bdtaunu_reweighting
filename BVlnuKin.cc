#include <cmath>

#include "ff_reweight_defs.h"
#include "BVlnuKin.h"

using HepLorentzVector = CLHEP::HepLorentzVector;
using Hep3Vector = CLHEP::Hep3Vector;

void BVlnuKin::clear_cache() {
  BXlnuKin::clear_cache();
  _ctv=-666;
  _theta_v=-666;
  _chi=-666;
}

BVlnuKin::BVlnuKin() {
  clear_cache();
}

BVlnuKin::BVlnuKin(
    const CLHEP::HepLorentzVector &BLab, 
    const CLHEP::HepLorentzVector &XLab, 
    const CLHEP::HepLorentzVector &LepLab, 
    const CLHEP::HepLorentzVector &XdauLab) 
  : BXlnuKin(BLab, XLab, LepLab), _XdauLab(XdauLab) {

  clear_cache();
  compute_kinematics();

}

void BVlnuKin::compute_kinematics() {

  BXlnuKin::compute_kinematics();

  //X meson in the B frame
  HepLorentzVector XB = _XLab; XB.boost(-_BLab.boostVector());

  //W boson in the Lab frame
  HepLorentzVector WLab = _BLab - _XLab;
  if (WLab.mag2()<=0) {
      WLab.setVectM(WLab.vect(),0.000001);   
  }
  HepLorentzVector W_B = WLab;
  W_B.boost(-_BLab.boostVector());

  //Lepton in the W frame
  HepLorentzVector LepW = _LepLab;
  LepW.boost(-_BLab.boostVector());
  LepW.boost(-W_B.boostVector());

  //Daugther of the X meson in X meson's frame
  HepLorentzVector VD_X(_XdauLab);
  VD_X.boost(-_BLab.boostVector());
  VD_X.boost(-XB.boostVector());
  
  // ctv
  _ctv=VD_X.vect().unit()*XB.vect().unit();
  _theta_v=VD_X.vect().angle(XB.vect());
  
  // chi (by Art Snyder)
  //
  // Note that:   myHepLorentzVector.rho() = sqrt(px*px + py*py + pz*pz);
  // By contrast:       myHep3Vector.rho() = sqrt(px*px + py*py);
  Hep3Vector p3LepTrans=LepW.vect()-_ctl*LepW.rho()*W_B.vect().unit();
  Hep3Vector p3VDTrans=VD_X.vect()-_ctv*VD_X.rho()*XB.vect().unit();
  // _chi=p3VDTrans.angle(p3LepTrans);  // Old version, with range: (0,pi).
  _chi = std::atan2(p3LepTrans.cross(p3VDTrans)*W_B.vect().unit(), p3LepTrans*p3VDTrans);
  // Note that atan2(y,x) returns chi such that tan(chi) = y/x.
  // We have chosen the orientation in which chi is measured
  // from p3LepTrans to p3VDTrans in the counter-clockwise direction, 
  // viewed in the plane in which W_B.vect() is directed out of the page.  
  // y = sin(chi)*|p_l|*|p_VD| = p3LepTrans.cross(p3VDTrans)*W_B.vect().unit(),
  // x = cos(chi)*|p_l|*|p_VD| = p3LepTrans*p3VDTrans

  // The return value of atan2 lies in the range (-pi, +pi), so add 2*pi to 
  // negative values to obtain the range (0,2*pi).
  if (_chi<0) { 
    _chi += twoPi;
  }
 
}
