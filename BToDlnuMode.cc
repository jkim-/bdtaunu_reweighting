#include "BToDlnuMode.h"

BToDlnuMode::BToDlnuMode() {}

BToDlnuMode::BToDlnuMode(
    int Blund, int Xlund, int Leplund, 
    CLHEP::HepLorentzVector BLab, 
    CLHEP::HepLorentzVector XLab, 
    CLHEP::HepLorentzVector LepLab)
  : Blund_(Blund), 
    Xlund_(Xlund),
    Leplund_(Leplund),
    kin_(BLab, XLab, LepLab) {}
