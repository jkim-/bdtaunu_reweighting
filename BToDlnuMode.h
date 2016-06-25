#ifndef __BTODLNUMODE_H__ 
#define __BTODLNUMODE_H__ 

#include <CLHEP/Vector/LorentzVector.h>

#include "DecayMode.h"

class BToDlnuMode : public DecayMode {

  public:

    BToDlnuMode();

    BToDlnuMode(
        CLHEP::HepLorentzVector BLab, 
        CLHEP::HepLorentzVector XLab, 
        CLHEP::HepLorentzVector LepLab, 
        CLHEP::HepLorentzVector BCM, 
        CLHEP::HepLorentzVector XCM, 
        CLHEP::HepLorentzVector LepCM 
    );

    CLHEP::HepLorentzVector get_BLab() const { return BLab_; }
    CLHEP::HepLorentzVector get_XLab() const { return XLab_; }
    CLHEP::HepLorentzVector get_LepLab() const { return LepLab_; }
    CLHEP::HepLorentzVector get_BCM() const { return BCM_; }
    CLHEP::HepLorentzVector get_XCM() const { return XCM_; }
    CLHEP::HepLorentzVector get_LepCM() const { return LepCM_; }

    virtual ~BToDlnuMode() {};

  private:
    CLHEP::HepLorentzVector BLab_;
    CLHEP::HepLorentzVector XLab_;
    CLHEP::HepLorentzVector LepLab_;
    CLHEP::HepLorentzVector BCM_;
    CLHEP::HepLorentzVector XCM_;
    CLHEP::HepLorentzVector LepCM_;
};

#endif
