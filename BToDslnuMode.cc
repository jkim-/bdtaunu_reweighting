#include "BToDslnuMode.h"

BToDslnuMode::BToDslnuMode() {}

BToDslnuMode::BToDslnuMode(
    int Blund, int Xlund, int Leplund, 
    int Xdaulund, int Softdaulund,
    CLHEP::HepLorentzVector BLab, 
    CLHEP::HepLorentzVector XLab, 
    CLHEP::HepLorentzVector LepLab,
    CLHEP::HepLorentzVector XdauLab) 
  : Blund_(Blund), Xlund_(Xlund), Leplund_(Leplund), 
    Xdaulund_(Xdaulund), Softdaulund_(Softdaulund),
    kin_(BLab, XLab, LepLab, XdauLab) {}
