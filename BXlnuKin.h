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
    CLHEP::HepLorentzVector BLab(){ return _BLab; };
    CLHEP::HepLorentzVector XLab(){ return _XLab; }
    CLHEP::HepLorentzVector LepLab(){ return _LepLab; }

    // accessors for kinematic quantities derived from the SL decay
    double q2(){ return _q2; }
    double ctl(){ return _ctl; }
    double theta_l(){ return _theta_l; }
    double w(){ return _w; }
    double z();


  protected:
    virtual void clear_cache();
    virtual void compute_kinematics();   

  protected:
    CLHEP::HepLorentzVector _BLab;
    CLHEP::HepLorentzVector _XLab;
    CLHEP::HepLorentzVector _LepLab;
    double _ctl;
    double _theta_l;
    double _q2;
    double _w;
    
};

inline double BXlnuKin::z(){
  return (std::sqrt(_w+1.)-std::sqrt(2.))/(std::sqrt(_w+1.)+std::sqrt(2.));
}

#endif

