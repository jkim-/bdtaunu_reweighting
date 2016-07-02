#include <ff_reweight_constants.h>

#include "BToDsslnuMode.h"

BToDsslnuMode::BToDsslnuMode() {}

BToDsslnuMode::BToDsslnuMode(
    int Blund, int Xlund, int Leplund, 
    CLHEP::HepLorentzVector BLab, 
    CLHEP::HepLorentzVector XLab, 
    CLHEP::HepLorentzVector LepLab)
  : Blund_(Blund), 
    Xlund_(Xlund),
    Leplund_(Leplund),
    kin_(BLab, XLab, LepLab) {

  bdsslnu_type_ = BToDsslnuType::null;

  bool is_Bc = is_chargedB(Blund_);
  bool isDss0 = is_Dss0(Xlund_);
  bool isD1 = is_D1(Xlund_);
  bool isD2 = is_D2(Xlund_);
  bool isD1prime = is_D1prime(Xlund_);

  if (is_Bc && isDss0 && Leplund_ == eLund) { bdsslnu_type_ = BToDsslnuType::Bc_D0ss0_e; }
  if (is_Bc && isDss0 && Leplund_ == muLund) { bdsslnu_type_ = BToDsslnuType::Bc_D0ss0_mu; }
  if (is_Bc && isDss0 && Leplund_ == tauLund) { bdsslnu_type_ = BToDsslnuType::Bc_D0ss0_tau; }
  if (!is_Bc && isDss0 && Leplund_ == eLund) { bdsslnu_type_ = BToDsslnuType::B0_D0ssc_e; }
  if (!is_Bc && isDss0 && Leplund_ == muLund) { bdsslnu_type_ = BToDsslnuType::B0_D0ssc_mu; }
  if (!is_Bc && isDss0 && Leplund_ == tauLund) { bdsslnu_type_ = BToDsslnuType::B0_D0ssc_tau; }

  if (is_Bc && isD1 && Leplund_ == eLund) { bdsslnu_type_ = BToDsslnuType::Bc_D10_e; }
  if (is_Bc && isD1 && Leplund_ == muLund) { bdsslnu_type_ = BToDsslnuType::Bc_D10_mu; }
  if (is_Bc && isD1 && Leplund_ == tauLund) { bdsslnu_type_ = BToDsslnuType::Bc_D10_tau; }
  if (!is_Bc && isD1 && Leplund_ == eLund) { bdsslnu_type_ = BToDsslnuType::B0_D1c_e; }
  if (!is_Bc && isD1 && Leplund_ == muLund) { bdsslnu_type_ = BToDsslnuType::B0_D1c_mu; }
  if (!is_Bc && isD1 && Leplund_ == tauLund) { bdsslnu_type_ = BToDsslnuType::B0_D1c_tau; }

  if (is_Bc && isD2 && Leplund_ == eLund) { bdsslnu_type_ = BToDsslnuType::Bc_D20_e; }
  if (is_Bc && isD2 && Leplund_ == muLund) { bdsslnu_type_ = BToDsslnuType::Bc_D20_mu; }
  if (is_Bc && isD2 && Leplund_ == tauLund) { bdsslnu_type_ = BToDsslnuType::Bc_D20_tau; }
  if (!is_Bc && isD2 && Leplund_ == eLund) { bdsslnu_type_ = BToDsslnuType::B0_D2c_e; }
  if (!is_Bc && isD2 && Leplund_ == muLund) { bdsslnu_type_ = BToDsslnuType::B0_D2c_mu; }
  if (!is_Bc && isD2 && Leplund_ == tauLund) { bdsslnu_type_ = BToDsslnuType::B0_D2c_tau; }

  if (is_Bc && isD1prime && Leplund_ == eLund) { bdsslnu_type_ = BToDsslnuType::Bc_D1prime0_e; }
  if (is_Bc && isD1prime && Leplund_ == muLund) { bdsslnu_type_ = BToDsslnuType::Bc_D1prime0_mu; }
  if (is_Bc && isD1prime && Leplund_ == tauLund) { bdsslnu_type_ = BToDsslnuType::Bc_D1prime0_tau; }
  if (!is_Bc && isD1prime && Leplund_ == eLund) { bdsslnu_type_ = BToDsslnuType::B0_D1primec_e; }
  if (!is_Bc && isD1prime && Leplund_ == muLund) { bdsslnu_type_ = BToDsslnuType::B0_D1primec_mu; }
  if (!is_Bc && isD1prime && Leplund_ == tauLund) { bdsslnu_type_ = BToDsslnuType::B0_D1primec_tau; }

}
