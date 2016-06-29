#include "BXlnuKin.h"

using HepLorentzVector = CLHEP::HepLorentzVector;
using Hep3Vector = CLHEP::Hep3Vector;

void BXlnuKin::initialize_cache() {
  _ctl=-666;
  _theta_l=-666;
  _q2=-666;
  _w=-666;
}

BXlnuKin::BXlnuKin() {
  initialize_cache();
}


BXlnuKin::BXlnuKin(
    const HepLorentzVector &BLab, 
    const HepLorentzVector &XLab,
    const HepLorentzVector &LepLab) : 
    _BLab(BLab),
    _XLab(XLab),
    _LepLab(LepLab) {
  initialize_cache(); 
  initialize_boosted_vectors();
  initialize_kinematics();
}

void  BXlnuKin::initialize_boosted_vectors() {

  // X meson in the B frame
  _XB = _XLab; _XB.boost(-_BLab.boostVector());

  // W boson in the Lab frame
  _WLab = _BLab - _XLab;

  // vestige from original code. should we throw an exception? 
  // appears to be a hack that was reasonable in their use case.  
  if (_WLab.mag2() <= 0) {
      _WLab.setVectM(_WLab.vect(),0.000001);   
  }

  // W boson in the B frame
  _WB = _WLab; _WB.boost(-_BLab.boostVector());

  // Lepton in the B frame
  _LepB = _LepLab; _LepB.boost(-_BLab.boostVector());
  
  // Lepton in the W frame
  _LepW = _LepB; _LepW.boost(-_WB.boostVector());

}

void  BXlnuKin::initialize_kinematics() {

  // q2 computed as (B-X)^2 in the B frame
  _q2=_BLab.m2() + _XLab.m2() - 2*_BLab.m()*_XB.e();
  _w=(_BLab.m2()+ _XLab.m2()-_q2)/(2*_BLab.m()*_XLab.m());

  _ctl=_LepW.vect().unit()*_WB.vect().unit();
  _theta_l=_LepW.vect().angle(_WB.vect());

  return;
}
