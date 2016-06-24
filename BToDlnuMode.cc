#include "BToDlnuMode.h"

BToDlnuMode::BToDlnuMode() {}

BToDlnuMode::BToDlnuMode(
    CLHEP::HepLorentzVector BLab, 
    CLHEP::HepLorentzVector XLab, 
    CLHEP::HepLorentzVector LepLab, 
    CLHEP::HepLorentzVector BCM, 
    CLHEP::HepLorentzVector XCM, 
    CLHEP::HepLorentzVector LepCM) 
  : BLab_(BLab), XLab_(XLab), LepLab_(LepLab), 
    BCM_(BCM), XCM_(XCM), LepCM_(LepCM) {
}
