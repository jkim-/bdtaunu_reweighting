#include "BToDlnuMode.h"

BToDlnuMode::BToDlnuMode() {}

BToDlnuMode::BToDlnuMode(
    CLHEP::HepLorentzVector BLab, 
    CLHEP::HepLorentzVector XLab, 
    CLHEP::HepLorentzVector LepLab)
  : kin_(BLab, XLab, LepLab) {}
