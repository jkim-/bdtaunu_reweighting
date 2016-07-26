#include <cmath>
#include <ff_reweight_constants.h>

#include <BPlnuDecayRate.h>
#include <BVlnuDecayRate.h>

#include "CLNReweighter.h"

CLNReweighter::CLNReweighter() {}

double ReweightBDlnu(const BToDlnuMode &mode, 
                   std::string to_model,
                   std::string from_model) {
  double mB = mode.BLab().m();
  double mD = mode.XLab().m();
  double mLep = mode.LepLab().m();
  double q2 = mode.q2();
  BPlnuDecayRate from(mB, mD, mLep, from_model);
  BPlnuDecayRate to(mB, mD, mLep, to_model);
  return to.dGamma_dq2_density(q2) / from.dGamma_dq2_density(q2);
}

double ReweightBDslnu(const BToDslnuMode &mode, 
                      bool isDgamma, bool islplus,
                      std::string to_model,
                      std::string from_model) {
  double mB = mode.BLab().m();
  double mD = mode.XLab().m();
  double mLep = mode.LepLab().m();
  double q2 = mode.q2();
  double ctl = mode.ctl();
  double ctv = mode.ctv(); 
  double chi = mode.chi();
  BVlnuDecayRate from(mB, mD, mLep, isDgamma, islplus, from_model);
  BVlnuDecayRate to(mB, mD, mLep, isDgamma, islplus, to_model);
  return to.dGamma_dq2dangles_density(q2, ctl, ctv, chi) / 
         from.dGamma_dq2dangles_density(q2, ctl, ctv, chi);
}


double CLNReweighter::compute_bdlnu_cln_weights(const BToDlnuMode &m) const {

  double result = 1.0;

  switch (m.bdlnu_type()) {
    case BToDlnuType::Bc_D0_e:
    case BToDlnuType::Bc_D0_mu:
    case BToDlnuType::Bc_D0_tau:
    case BToDlnuType::B0_Dc_e:
    case BToDlnuType::B0_Dc_mu:
    case BToDlnuType::B0_Dc_tau:
      result = ReweightBDlnu(m, "CLN", "ISGW2");
      break;
    default:
      ;
  }

  return result;
  
}

double CLNReweighter::compute_bdslnu_cln_weights(const BToDslnuMode &m) const {

  double result = 1.0;

  switch (m.bdslnu_type()) {

    case BToDslnuType::Bc_Dstar0_e_Dpi_lminus:
    case BToDslnuType::Bc_Dstar0_mu_Dpi_lminus:
    case BToDslnuType::B0_Dstarc_e_Dpi_lminus:
    case BToDslnuType::B0_Dstarc_mu_Dpi_lminus:
      result = ReweightBDslnu(m, false, false, "CLN", "LinearQ2");
      break;
    case BToDslnuType::Bc_Dstar0_tau_Dpi_lminus:
    case BToDslnuType::B0_Dstarc_tau_Dpi_lminus:
      result = ReweightBDslnu(m, false, false, "CLN", "ISGW2");
      break;

    case BToDslnuType::Bc_Dstar0_e_Dgamma_lminus:
    case BToDslnuType::Bc_Dstar0_mu_Dgamma_lminus:
    case BToDslnuType::B0_Dstarc_e_Dgamma_lminus:
    case BToDslnuType::B0_Dstarc_mu_Dgamma_lminus:
      result = ReweightBDslnu(m, true, false, "CLN", "LinearQ2");
      break;
    case BToDslnuType::Bc_Dstar0_tau_Dgamma_lminus:
    case BToDslnuType::B0_Dstarc_tau_Dgamma_lminus:
      result = ReweightBDslnu(m, true, false, "CLN", "ISGW2");
      break;

    case BToDslnuType::Bc_Dstar0_e_Dpi_lplus:
    case BToDslnuType::Bc_Dstar0_mu_Dpi_lplus:
    case BToDslnuType::B0_Dstarc_e_Dpi_lplus:
    case BToDslnuType::B0_Dstarc_mu_Dpi_lplus:
      result = ReweightBDslnu(m, false, true, "CLN", "LinearQ2");
      break;
    case BToDslnuType::Bc_Dstar0_tau_Dpi_lplus:
    case BToDslnuType::B0_Dstarc_tau_Dpi_lplus:
      result = ReweightBDslnu(m, false, true, "CLN", "ISGW2");
      break;

    case BToDslnuType::Bc_Dstar0_e_Dgamma_lplus:
    case BToDslnuType::Bc_Dstar0_mu_Dgamma_lplus:
    case BToDslnuType::B0_Dstarc_e_Dgamma_lplus:
    case BToDslnuType::B0_Dstarc_mu_Dgamma_lplus:
      result = ReweightBDslnu(m, true, true, "CLN", "LinearQ2");
      break;
    case BToDslnuType::Bc_Dstar0_tau_Dgamma_lplus:
    case BToDslnuType::B0_Dstarc_tau_Dgamma_lplus:
      result = ReweightBDslnu(m, true, true, "CLN", "ISGW2");
      break;

    default:
      ;

  }

  return result;
}


