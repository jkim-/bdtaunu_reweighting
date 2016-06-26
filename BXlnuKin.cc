#include "BXlnuKin.h"

using HepLorentzVector = CLHEP::HepLorentzVector;
using Hep3Vector = CLHEP::Hep3Vector;

void BXlnuKin::clear_cache() {
  _ctl=-666;
  _theta_l=-666;
  _q2=-666;
  _w=-666;
}

BXlnuKin::BXlnuKin() {
  clear_cache();
}


BXlnuKin::BXlnuKin(
    const HepLorentzVector &BLab, 
    const HepLorentzVector &XLab,
    const HepLorentzVector &LepLab) : 
    _BLab(BLab),
    _XLab(XLab),
    _LepLab(LepLab) {
  clear_cache(); 
  compute_kinematics();
}

void  BXlnuKin::compute_kinematics() {

  // X meson in the B frame
  HepLorentzVector XB = _XLab;
  XB.boost(-_BLab.boostVector());

  // q2 computed as (B-X)^2 in the B frame
  _q2=_BLab.m2() + _XLab.m2() - 2*_BLab.m()*XB.e();
  _w=(_BLab.m2()+ _XLab.m2()-_q2)/(2*_BLab.m()*_XLab.m());

  // W boson in the Lab frame
  HepLorentzVector WLab = _BLab - _XLab;

  // vestige from original code. should we throw an exception? 
  // appears to be a hack that was reasonable in their use case.  
  if (WLab.mag2() <= 0) {
      WLab.setVectM(WLab.vect(),0.000001);   
  }
  HepLorentzVector W_B = WLab;
  W_B.boost(-_BLab.boostVector());

  //Lepton in the W frame
  HepLorentzVector LepW = _LepLab;
  LepW.boost(-_BLab.boostVector());
  LepW.boost(-W_B.boostVector());

  _ctl=LepW.vect().unit()*W_B.vect().unit();
  _theta_l=LepW.vect().angle(W_B.vect());

  return;
}
