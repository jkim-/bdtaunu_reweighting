#include <ff_reweight_constants.h>

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
    kin_(BLab, XLab, LepLab) {

  bdlnu_type_ = BToDlnuType::null;

  bool is_Bc = is_chargedB(Blund_), is_D0 = is_neutralD(Xlund_);
  if (is_Bc && is_D0 && Leplund_ == eLund) { bdlnu_type_ = BToDlnuType::Bc_D0_e; }
  if (is_Bc && is_D0 && Leplund_ == muLund) { bdlnu_type_ = BToDlnuType::Bc_D0_mu; }
  if (is_Bc && is_D0 && Leplund_ == tauLund) { bdlnu_type_ = BToDlnuType::Bc_D0_tau; }
  if (!is_Bc && !is_D0 && Leplund_ == eLund) { bdlnu_type_ = BToDlnuType::B0_Dc_e; }
  if (!is_Bc && !is_D0 && Leplund_ == muLund) { bdlnu_type_ = BToDlnuType::B0_Dc_mu; }
  if (!is_Bc && !is_D0 && Leplund_ == tauLund) { bdlnu_type_ = BToDlnuType::B0_Dc_tau; }

}
