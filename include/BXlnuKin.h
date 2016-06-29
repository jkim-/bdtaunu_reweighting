//*****************************************************************
// Modified on 6/25/16 by Daniel Chao. dchao@caltech.edu. 
// Original codes from David Cote and Art Snyder from BABAR. 

#ifndef _BXLNUKIN_H_
#define _BXLNUKIN_H_

#include <cmath>

#include <CLHEP/Vector/LorentzVector.h>

class BXlnuKin {

  public:

    BXlnuKin();
    BXlnuKin(const CLHEP::HepLorentzVector &BLab, 
             const CLHEP::HepLorentzVector &XLab, 
             const CLHEP::HepLorentzVector &LepLab);

    virtual ~BXlnuKin() {};

    // accessors to the 4-vectors participating in the decay. 
    const CLHEP::HepLorentzVector& BLab() const { return _BLab; };
    const CLHEP::HepLorentzVector& XLab() const { return _XLab; }
    const CLHEP::HepLorentzVector& LepLab() const { return _LepLab; }
    const CLHEP::HepLorentzVector& LepB() const { return _LepB; }

    // accessors for kinematic quantities derived from the SL decay
    double q2() const { return _q2; }
    double ctl() const { return _ctl; }
    double theta_l() const { return _theta_l; }
    double w() const { return _w; }
    double z() const ;


  protected:
    virtual void initialize_cache();
    virtual void initialize_boosted_vectors();
    virtual void initialize_kinematics();   

  protected:
    CLHEP::HepLorentzVector _BLab;
    CLHEP::HepLorentzVector _XLab;
    CLHEP::HepLorentzVector _LepLab;

    CLHEP::HepLorentzVector _XB;
    CLHEP::HepLorentzVector _WLab;
    CLHEP::HepLorentzVector _WB;
    CLHEP::HepLorentzVector _LepB;
    CLHEP::HepLorentzVector _LepW;

    double _ctl;
    double _theta_l;
    double _q2;
    double _w;
    
};

inline double BXlnuKin::z() const {
  return (std::sqrt(_w+1.)-std::sqrt(2.))/(std::sqrt(_w+1.)+std::sqrt(2.));
}

#endif

