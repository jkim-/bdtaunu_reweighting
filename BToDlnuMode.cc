#include "ff_reweight_utils.h"
#include "BToDlnuMode.h"

BToDlnuMode::BToDlnuMode() {}

BToDlnuMode::BToDlnuMode(
    double e_B, double p3mag_B, double costh_B, double phi_B, 
    double e_X, double p3mag_X, double costh_X, double phi_X, 
    double e_Lep, double p3mag_Lep, double costh_Lep, double phi_Lep, 
    double ecm_Lep) {
  BLab_ = make_lorentz_vector(e_B, p3mag_B, costh_B, phi_B);
  XLab_ = make_lorentz_vector(e_X, p3mag_X, costh_X, phi_X);
  LepLab_ = make_lorentz_vector(e_Lep, p3mag_Lep, costh_Lep, phi_Lep);
  ecmLep_ = ecm_Lep;
}
