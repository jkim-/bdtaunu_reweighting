#include <ff_reweight_constants.h>

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
    kin_(BLab, XLab, LepLab, XdauLab) {

  bdslnu_type_ = BToDslnuType::null;

  bool is_Bc = is_chargedB(Blund_), is_Dstar0 = is_neutralDstar(Xlund_);
  bool is_softpi = is_pion(Softdaulund_), is_lminus = !is_positive_lepton(Leplund_);

  if (is_Bc && is_Dstar0 && Leplund_ == eLund && is_softpi && is_lminus) {
    bdslnu_type_ = BToDslnuType::Bc_Dstar0_e_Dpi_lminus;
  }

  if (is_Bc && is_Dstar0 && Leplund_ == muLund && is_softpi && is_lminus) {
    bdslnu_type_ = BToDslnuType::Bc_Dstar0_mu_Dpi_lminus;
  }
      
  if (is_Bc && is_Dstar0 && Leplund_ == tauLund && is_softpi && is_lminus) {
    bdslnu_type_ = BToDslnuType::Bc_Dstar0_tau_Dpi_lminus;
  }
      
  if (!is_Bc && !is_Dstar0 && Leplund_ == eLund && is_softpi && is_lminus) {
    bdslnu_type_ = BToDslnuType::Bc_Dstar0_e_Dpi_lminus;
  }

  if (!is_Bc && !is_Dstar0 && Leplund_ == muLund && is_softpi && is_lminus) {
    bdslnu_type_ = BToDslnuType::Bc_Dstar0_mu_Dpi_lminus;
  }
      
  if (!is_Bc && !is_Dstar0 && Leplund_ == tauLund && is_softpi && is_lminus) {
    bdslnu_type_ = BToDslnuType::Bc_Dstar0_tau_Dpi_lminus;
  }
      
  if (is_Bc && is_Dstar0 && Leplund_ == eLund && !is_softpi && is_lminus) {
    bdslnu_type_ = BToDslnuType::Bc_Dstar0_e_Dpi_lminus;
  }

  if (is_Bc && is_Dstar0 && Leplund_ == muLund && !is_softpi && is_lminus) {
    bdslnu_type_ = BToDslnuType::Bc_Dstar0_mu_Dpi_lminus;
  }
      
  if (is_Bc && is_Dstar0 && Leplund_ == tauLund && !is_softpi && is_lminus) {
    bdslnu_type_ = BToDslnuType::Bc_Dstar0_tau_Dpi_lminus;
  }
      
  if (!is_Bc && !is_Dstar0 && Leplund_ == eLund && !is_softpi && is_lminus) {
    bdslnu_type_ = BToDslnuType::Bc_Dstar0_e_Dpi_lminus;
  }

  if (!is_Bc && !is_Dstar0 && Leplund_ == muLund && !is_softpi && is_lminus) {
    bdslnu_type_ = BToDslnuType::Bc_Dstar0_mu_Dpi_lminus;
  }
      
  if (!is_Bc && !is_Dstar0 && Leplund_ == tauLund && !is_softpi && is_lminus) {
    bdslnu_type_ = BToDslnuType::Bc_Dstar0_tau_Dpi_lminus;
  }
      
  // ----

  if (is_Bc && is_Dstar0 && Leplund_ == eLund && is_softpi && !is_lminus) {
    bdslnu_type_ = BToDslnuType::Bc_Dstar0_e_Dpi_lminus;
  }

  if (is_Bc && is_Dstar0 && Leplund_ == muLund && is_softpi && !is_lminus) {
    bdslnu_type_ = BToDslnuType::Bc_Dstar0_mu_Dpi_lminus;
  }
      
  if (is_Bc && is_Dstar0 && Leplund_ == tauLund && is_softpi && !is_lminus) {
    bdslnu_type_ = BToDslnuType::Bc_Dstar0_tau_Dpi_lminus;
  }
      
  if (!is_Bc && !is_Dstar0 && Leplund_ == eLund && is_softpi && !is_lminus) {
    bdslnu_type_ = BToDslnuType::Bc_Dstar0_e_Dpi_lminus;
  }

  if (!is_Bc && !is_Dstar0 && Leplund_ == muLund && is_softpi && !is_lminus) {
    bdslnu_type_ = BToDslnuType::Bc_Dstar0_mu_Dpi_lminus;
  }
      
  if (!is_Bc && !is_Dstar0 && Leplund_ == tauLund && is_softpi && !is_lminus) {
    bdslnu_type_ = BToDslnuType::Bc_Dstar0_tau_Dpi_lminus;
  }
      
  if (is_Bc && is_Dstar0 && Leplund_ == eLund && !is_softpi && !is_lminus) {
    bdslnu_type_ = BToDslnuType::Bc_Dstar0_e_Dpi_lminus;
  }

  if (is_Bc && is_Dstar0 && Leplund_ == muLund && !is_softpi && !is_lminus) {
    bdslnu_type_ = BToDslnuType::Bc_Dstar0_mu_Dpi_lminus;
  }
      
  if (is_Bc && is_Dstar0 && Leplund_ == tauLund && !is_softpi && !is_lminus) {
    bdslnu_type_ = BToDslnuType::Bc_Dstar0_tau_Dpi_lminus;
  }
      
  if (!is_Bc && !is_Dstar0 && Leplund_ == eLund && !is_softpi && !is_lminus) {
    bdslnu_type_ = BToDslnuType::Bc_Dstar0_e_Dpi_lminus;
  }

  if (!is_Bc && !is_Dstar0 && Leplund_ == muLund && !is_softpi && !is_lminus) {
    bdslnu_type_ = BToDslnuType::Bc_Dstar0_mu_Dpi_lminus;
  }
      
  if (!is_Bc && !is_Dstar0 && Leplund_ == tauLund && !is_softpi && !is_lminus) {
    bdslnu_type_ = BToDslnuType::Bc_Dstar0_tau_Dpi_lminus;
  }

    
}
