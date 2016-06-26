//*****************************************************************
// Modified on 6/25/16 by Daniel Chao. dchao@caltech.edu. 
// Original codes from David Cote and Art Snyder from BABAR. 

#ifndef _BVLNUKIN_H_
#define _BVLNUKIN_H_

#include <cmath>

#include <CLHEP/Vector/LorentzVector.h>

#include "BXlnuKin.h" 

class BVlnuKin : public BXlnuKin {

  public:

    BVlnuKin();
    BVlnuKin(const CLHEP::HepLorentzVector &BLab, 
             const CLHEP::HepLorentzVector &XLab, 
             const CLHEP::HepLorentzVector &LepLab, 
             const CLHEP::HepLorentzVector &XdauLab);

    ~BVlnuKin() {};

    // accessors to the 4-vectors participating in the decay. 
    CLHEP::HepLorentzVector XdauLab(){ return _XdauLab; }

    // accessors for kinematic quantities derived from the SL decay
    double ctv(){ return _ctv; }
    double theta_v(){ return _theta_v; }
    double chi(){ return _chi; }

  private:
    void clear_cache();
    void compute_kinematics();   

  private:
    CLHEP::HepLorentzVector _XdauLab;
    double _ctv;
    double _chi;
    double _theta_v;
    
};

#endif

