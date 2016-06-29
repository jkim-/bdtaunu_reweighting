#ifndef __BTODLNUMODE_H__ 
#define __BTODLNUMODE_H__ 

#include <CLHEP/Vector/LorentzVector.h>

#include "DecayMode.h"
#include "BXlnuKin.h"

class BToDlnuMode : public DecayMode {

  public:

    BToDlnuMode();

    BToDlnuMode(
        CLHEP::HepLorentzVector BLab, 
        CLHEP::HepLorentzVector XLab, 
        CLHEP::HepLorentzVector LepLab
    );

    double q2() const { return kin_.q2(); }
    double ctl() const { return kin_.ctl(); }
    double theta_l() const { return kin_.theta_l(); }
    double w() const { return kin_.w(); }
    double z() const { return kin_.z(); }
    const CLHEP::HepLorentzVector &BLab() const { return kin_.BLab(); }
    const CLHEP::HepLorentzVector &XLab() const { return kin_.XLab(); }
    const CLHEP::HepLorentzVector &LepLab() const { return kin_.LepB(); }
    const CLHEP::HepLorentzVector &LepB() const { return kin_.LepB(); }

    virtual ~BToDlnuMode() {};

  private:
    BXlnuKin kin_;
};

#endif
