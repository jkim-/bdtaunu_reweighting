#include <cmath>
#include <ff_reweight_constants.h>

#include "CLNReweighter.h"

CLNReweighter::CLNReweighter() {

  // B -> D l nu

  BcDenu_from_ = BPlnuDecayRate(mBp, mD0, mE, "ISGW2");
  BcDmunu_from_ = BPlnuDecayRate(mBp, mD0, mMu, "ISGW2");
  BcDtaunu_from_ = BPlnuDecayRate(mBp, mD0, mTau, "ISGW2");
  B0Denu_from_ = BPlnuDecayRate(mB0, mDp, mE, "ISGW2");
  B0Dmunu_from_ = BPlnuDecayRate(mB0, mDp, mMu, "ISGW2");
  B0Dtaunu_from_ = BPlnuDecayRate(mB0, mDp, mTau, "ISGW2");

  BcDenu_to_ = BPlnuDecayRate(mBp, mD0, mE, "CLN");
  BcDmunu_to_ = BPlnuDecayRate(mBp, mD0, mMu, "CLN");
  BcDtaunu_to_ = BPlnuDecayRate(mBp, mD0, mTau, "CLN");
  B0Denu_to_ = BPlnuDecayRate(mB0, mDp, mE, "CLN");
  B0Dmunu_to_ = BPlnuDecayRate(mB0, mDp, mMu, "CLN");
  B0Dtaunu_to_ = BPlnuDecayRate(mB0, mDp, mTau, "CLN");

  // B -> D* l nu

  BcDsenu_Dpi_lm_from_ = BVlnuDecayRate(mBp, mD0, mE, false, false, "LinearQ2");
  BcDsmunu_Dpi_lm_from_ = BVlnuDecayRate(mBp, mD0, mMu, false, false, "LinearQ2");
  BcDstaunu_Dpi_lm_from_ = BVlnuDecayRate(mBp, mD0, mTau, false, false, "ISGW2");
  B0Dsenu_Dpi_lm_from_ = BVlnuDecayRate(mB0, mDp, mE, false, false, "LinearQ2");
  B0Dsmunu_Dpi_lm_from_ = BVlnuDecayRate(mB0, mDp, mMu, false, false, "LinearQ2");
  B0Dstaunu_Dpi_lm_from_ = BVlnuDecayRate(mB0, mDp, mTau, false, false, "LinearQ2");
  BcDsenu_Dgamma_lm_from_ = BVlnuDecayRate(mBp, mD0, mE, true, false, "LinearQ2");
  BcDsmunu_Dgamma_lm_from_ = BVlnuDecayRate(mBp, mD0, mMu, true, false, "LinearQ2");
  BcDstaunu_Dgamma_lm_from_ = BVlnuDecayRate(mBp, mD0, mTau, true, false, "ISGW2");
  B0Dsenu_Dgamma_lm_from_ = BVlnuDecayRate(mB0, mDp, mE, true, false, "LinearQ2");
  B0Dsmunu_Dgamma_lm_from_ = BVlnuDecayRate(mB0, mDp, mMu, true, false, "LinearQ2");
  B0Dstaunu_Dgamma_lm_from_ = BVlnuDecayRate(mB0, mDp, mTau, true, false, "LinearQ2");
  BcDsenu_Dpi_lp_from_ = BVlnuDecayRate(mBp, mD0, mE, false, true, "LinearQ2");
  BcDsmunu_Dpi_lp_from_ = BVlnuDecayRate(mBp, mD0, mMu, false, true, "LinearQ2");
  BcDstaunu_Dpi_lp_from_ = BVlnuDecayRate(mBp, mD0, mTau, false, true, "ISGW2");
  B0Dsenu_Dpi_lp_from_ = BVlnuDecayRate(mB0, mDp, mE, false, true, "LinearQ2");
  B0Dsmunu_Dpi_lp_from_ = BVlnuDecayRate(mB0, mDp, mMu, false, true, "LinearQ2");
  B0Dstaunu_Dpi_lp_from_ = BVlnuDecayRate(mB0, mDp, mTau, false, true, "LinearQ2");
  BcDsenu_Dgamma_lp_from_ = BVlnuDecayRate(mBp, mD0, mE, true, true, "LinearQ2");
  BcDsmunu_Dgamma_lp_from_ = BVlnuDecayRate(mBp, mD0, mMu, true, true, "LinearQ2");
  BcDstaunu_Dgamma_lp_from_ = BVlnuDecayRate(mBp, mD0, mTau, true, true, "ISGW2");
  B0Dsenu_Dgamma_lp_from_ = BVlnuDecayRate(mB0, mDp, mE, true, true, "LinearQ2");
  B0Dsmunu_Dgamma_lp_from_ = BVlnuDecayRate(mB0, mDp, mMu, true, true, "LinearQ2");
  B0Dstaunu_Dgamma_lp_from_ = BVlnuDecayRate(mB0, mDp, mTau, true, true, "LinearQ2");

  BcDsenu_Dpi_lm_to_ = BVlnuDecayRate(mBp, mD0, mE, false, false, "CLN");
  BcDsmunu_Dpi_lm_to_ = BVlnuDecayRate(mBp, mD0, mMu, false, false, "CLN");
  BcDstaunu_Dpi_lm_to_ = BVlnuDecayRate(mBp, mD0, mTau, false, false, "CLN");
  B0Dsenu_Dpi_lm_to_ = BVlnuDecayRate(mB0, mDp, mE, false, false, "CLN");
  B0Dsmunu_Dpi_lm_to_ = BVlnuDecayRate(mB0, mDp, mMu, false, false, "CLN");
  B0Dstaunu_Dpi_lm_to_ = BVlnuDecayRate(mB0, mDp, mTau, false, false, "CLN");
  BcDsenu_Dgamma_lm_to_ = BVlnuDecayRate(mBp, mD0, mE, true, false, "CLN");
  BcDsmunu_Dgamma_lm_to_ = BVlnuDecayRate(mBp, mD0, mMu, true, false, "CLN");
  BcDstaunu_Dgamma_lm_to_ = BVlnuDecayRate(mBp, mD0, mTau, true, false, "CLN");
  B0Dsenu_Dgamma_lm_to_ = BVlnuDecayRate(mB0, mDp, mE, true, false, "CLN");
  B0Dsmunu_Dgamma_lm_to_ = BVlnuDecayRate(mB0, mDp, mMu, true, false, "CLN");
  B0Dstaunu_Dgamma_lm_to_ = BVlnuDecayRate(mB0, mDp, mTau, true, false, "CLN");
  BcDsenu_Dpi_lp_to_ = BVlnuDecayRate(mBp, mD0, mE, false, true, "CLN");
  BcDsmunu_Dpi_lp_to_ = BVlnuDecayRate(mBp, mD0, mMu, false, true, "CLN");
  BcDstaunu_Dpi_lp_to_ = BVlnuDecayRate(mBp, mD0, mTau, false, true, "CLN");
  B0Dsenu_Dpi_lp_to_ = BVlnuDecayRate(mB0, mDp, mE, false, true, "CLN");
  B0Dsmunu_Dpi_lp_to_ = BVlnuDecayRate(mB0, mDp, mMu, false, true, "CLN");
  B0Dstaunu_Dpi_lp_to_ = BVlnuDecayRate(mB0, mDp, mTau, false, true, "CLN");
  BcDsenu_Dgamma_lp_to_ = BVlnuDecayRate(mBp, mD0, mE, true, true, "CLN");
  BcDsmunu_Dgamma_lp_to_ = BVlnuDecayRate(mBp, mD0, mMu, true, true, "CLN");
  BcDstaunu_Dgamma_lp_to_ = BVlnuDecayRate(mBp, mD0, mTau, true, true, "CLN");
  B0Dsenu_Dgamma_lp_to_ = BVlnuDecayRate(mB0, mDp, mE, true, true, "CLN");
  B0Dsmunu_Dgamma_lp_to_ = BVlnuDecayRate(mB0, mDp, mMu, true, true, "CLN");
  B0Dstaunu_Dgamma_lp_to_ = BVlnuDecayRate(mB0, mDp, mTau, true, true, "CLN");

}

double CLNReweighter::compute_bdlnu_cln_weights(
    const BToDlnuMode &m, double q2) const {

  double result = 1.0;

  switch (m.bdlnu_type()) {
    case BToDlnuType::Bc_D0_e:
      result = BcDenu_to_.dGamma_dq2_density(q2) / 
               BcDenu_from_.dGamma_dq2_density(q2);
      break;
    case BToDlnuType::Bc_D0_mu:
      result = BcDmunu_to_.dGamma_dq2_density(q2) / 
               BcDmunu_from_.dGamma_dq2_density(q2);
      break;
    case BToDlnuType::Bc_D0_tau:
      result = BcDtaunu_to_.dGamma_dq2_density(q2) / 
               BcDtaunu_from_.dGamma_dq2_density(q2);
      break;
    case BToDlnuType::B0_Dc_e:
      result = B0Denu_to_.dGamma_dq2_density(q2) / 
               B0Denu_from_.dGamma_dq2_density(q2);
      break;
    case BToDlnuType::B0_Dc_mu:
      result = B0Dmunu_to_.dGamma_dq2_density(q2) / 
               B0Dmunu_from_.dGamma_dq2_density(q2);
      break;
    case BToDlnuType::B0_Dc_tau:
      result = B0Dtaunu_to_.dGamma_dq2_density(q2) / 
               B0Dtaunu_from_.dGamma_dq2_density(q2);
      break;
    default:
      ;
  }

  return result;
  
}

double CLNReweighter::compute_bdslnu_cln_weights(
    const BToDslnuMode &m, double q2) const {

  double result = 1.0;

  switch (m.bdslnu_type()) {
    case BToDslnuType::Bc_Dstar0_e_Dpi_lminus:
      result = BcDsenu_Dpi_lm_to_.dGamma_dq2_density(q2) / 
               BcDsenu_Dpi_lm_from_.dGamma_dq2_density(q2);
      break;
    case BToDslnuType::Bc_Dstar0_mu_Dpi_lminus:
      result = BcDsmunu_Dpi_lm_to_.dGamma_dq2_density(q2) / 
               BcDsmunu_Dpi_lm_from_.dGamma_dq2_density(q2);
      break;
    case BToDslnuType::Bc_Dstar0_tau_Dpi_lminus:
      result = BcDstaunu_Dpi_lm_to_.dGamma_dq2_density(q2) / 
               BcDstaunu_Dpi_lm_from_.dGamma_dq2_density(q2);
      break;
    case BToDslnuType::B0_Dstarc_e_Dpi_lminus:
      result = B0Dsenu_Dpi_lm_to_.dGamma_dq2_density(q2) / 
               B0Dsenu_Dpi_lm_from_.dGamma_dq2_density(q2);
      break;
    case BToDslnuType::B0_Dstarc_mu_Dpi_lminus:
      result = B0Dsmunu_Dpi_lm_to_.dGamma_dq2_density(q2) / 
               B0Dsmunu_Dpi_lm_from_.dGamma_dq2_density(q2);
      break;
    case BToDslnuType::B0_Dstarc_tau_Dpi_lminus:
      result = B0Dstaunu_Dpi_lm_to_.dGamma_dq2_density(q2) / 
               B0Dstaunu_Dpi_lm_from_.dGamma_dq2_density(q2);
      break;
    case BToDslnuType::Bc_Dstar0_e_Dgamma_lminus:
      result = BcDsenu_Dgamma_lm_to_.dGamma_dq2_density(q2) / 
               BcDsenu_Dgamma_lm_from_.dGamma_dq2_density(q2);
      break;
    case BToDslnuType::Bc_Dstar0_mu_Dgamma_lminus:
      result = BcDsmunu_Dgamma_lm_to_.dGamma_dq2_density(q2) / 
               BcDsmunu_Dgamma_lm_from_.dGamma_dq2_density(q2);
      break;
    case BToDslnuType::Bc_Dstar0_tau_Dgamma_lminus:
      result = BcDstaunu_Dgamma_lm_to_.dGamma_dq2_density(q2) / 
               BcDstaunu_Dgamma_lm_from_.dGamma_dq2_density(q2);
      break;
    case BToDslnuType::B0_Dstarc_e_Dgamma_lminus:
      result = B0Dsenu_Dgamma_lm_to_.dGamma_dq2_density(q2) / 
               B0Dsenu_Dgamma_lm_from_.dGamma_dq2_density(q2);
      break;
    case BToDslnuType::B0_Dstarc_mu_Dgamma_lminus:
      result = B0Dsmunu_Dgamma_lm_to_.dGamma_dq2_density(q2) / 
               B0Dsmunu_Dgamma_lm_from_.dGamma_dq2_density(q2);
      break;
    case BToDslnuType::B0_Dstarc_tau_Dgamma_lminus:
      result = B0Dstaunu_Dgamma_lm_to_.dGamma_dq2_density(q2) / 
               B0Dstaunu_Dgamma_lm_from_.dGamma_dq2_density(q2);
      break;
    case BToDslnuType::Bc_Dstar0_e_Dpi_lplus:
      result = BcDsenu_Dpi_lp_to_.dGamma_dq2_density(q2) / 
               BcDsenu_Dpi_lp_from_.dGamma_dq2_density(q2);
      break;
    case BToDslnuType::Bc_Dstar0_mu_Dpi_lplus:
      result = BcDsmunu_Dpi_lp_to_.dGamma_dq2_density(q2) / 
               BcDsmunu_Dpi_lp_from_.dGamma_dq2_density(q2);
      break;
    case BToDslnuType::Bc_Dstar0_tau_Dpi_lplus:
      result = BcDstaunu_Dpi_lp_to_.dGamma_dq2_density(q2) / 
               BcDstaunu_Dpi_lp_from_.dGamma_dq2_density(q2);
      break;
    case BToDslnuType::B0_Dstarc_e_Dpi_lplus:
      result = B0Dsenu_Dpi_lp_to_.dGamma_dq2_density(q2) / 
               B0Dsenu_Dpi_lp_from_.dGamma_dq2_density(q2);
      break;
    case BToDslnuType::B0_Dstarc_mu_Dpi_lplus:
      result = B0Dsmunu_Dpi_lp_to_.dGamma_dq2_density(q2) / 
               B0Dsmunu_Dpi_lp_from_.dGamma_dq2_density(q2);
      break;
    case BToDslnuType::B0_Dstarc_tau_Dpi_lplus:
      result = B0Dstaunu_Dpi_lp_to_.dGamma_dq2_density(q2) / 
               B0Dstaunu_Dpi_lp_from_.dGamma_dq2_density(q2);
      break;
    case BToDslnuType::Bc_Dstar0_e_Dgamma_lplus:
      result = BcDsenu_Dgamma_lp_to_.dGamma_dq2_density(q2) / 
               BcDsenu_Dgamma_lp_from_.dGamma_dq2_density(q2);
      break;
    case BToDslnuType::Bc_Dstar0_mu_Dgamma_lplus:
      result = BcDsmunu_Dgamma_lp_to_.dGamma_dq2_density(q2) / 
               BcDsmunu_Dgamma_lp_from_.dGamma_dq2_density(q2);
      break;
    case BToDslnuType::Bc_Dstar0_tau_Dgamma_lplus:
      result = BcDstaunu_Dgamma_lp_to_.dGamma_dq2_density(q2) / 
               BcDstaunu_Dgamma_lp_from_.dGamma_dq2_density(q2);
      break;
    case BToDslnuType::B0_Dstarc_e_Dgamma_lplus:
      result = B0Dsenu_Dgamma_lp_to_.dGamma_dq2_density(q2) / 
               B0Dsenu_Dgamma_lp_from_.dGamma_dq2_density(q2);
      break;
    case BToDslnuType::B0_Dstarc_mu_Dgamma_lplus:
      result = B0Dsmunu_Dgamma_lp_to_.dGamma_dq2_density(q2) / 
               B0Dsmunu_Dgamma_lp_from_.dGamma_dq2_density(q2);
      break;
    case BToDslnuType::B0_Dstarc_tau_Dgamma_lplus:
      result = B0Dstaunu_Dgamma_lp_to_.dGamma_dq2_density(q2) / 
               B0Dstaunu_Dgamma_lp_from_.dGamma_dq2_density(q2);
      break;

    default:
      ;

  }

  return result;
}

double CLNReweighter::compute_bdslnu_cln_weights(const BToDslnuMode &m, 
    double q2, double ctl, double ctv, double chi) const {

  double result = 1.0;

  switch (m.bdslnu_type()) {
    case BToDslnuType::Bc_Dstar0_e_Dpi_lminus:
      result = BcDsenu_Dpi_lm_to_.dGamma_dq2dangles_density(q2, ctl, ctv, chi) / 
               BcDsenu_Dpi_lm_from_.dGamma_dq2dangles_density(q2, ctl, ctv, chi);
      break;
    case BToDslnuType::Bc_Dstar0_mu_Dpi_lminus:
      result = BcDsmunu_Dpi_lm_to_.dGamma_dq2dangles_density(q2, ctl, ctv, chi) / 
               BcDsmunu_Dpi_lm_from_.dGamma_dq2dangles_density(q2, ctl, ctv, chi);
      break;
    case BToDslnuType::Bc_Dstar0_tau_Dpi_lminus:
      result = BcDstaunu_Dpi_lm_to_.dGamma_dq2dangles_density(q2, ctl, ctv, chi) / 
               BcDstaunu_Dpi_lm_from_.dGamma_dq2dangles_density(q2, ctl, ctv, chi);
      break;
    case BToDslnuType::B0_Dstarc_e_Dpi_lminus:
      result = B0Dsenu_Dpi_lm_to_.dGamma_dq2dangles_density(q2, ctl, ctv, chi) / 
               B0Dsenu_Dpi_lm_from_.dGamma_dq2dangles_density(q2, ctl, ctv, chi);
      break;
    case BToDslnuType::B0_Dstarc_mu_Dpi_lminus:
      result = B0Dsmunu_Dpi_lm_to_.dGamma_dq2dangles_density(q2, ctl, ctv, chi) / 
               B0Dsmunu_Dpi_lm_from_.dGamma_dq2dangles_density(q2, ctl, ctv, chi);
      break;
    case BToDslnuType::B0_Dstarc_tau_Dpi_lminus:
      result = B0Dstaunu_Dpi_lm_to_.dGamma_dq2dangles_density(q2, ctl, ctv, chi) / 
               B0Dstaunu_Dpi_lm_from_.dGamma_dq2dangles_density(q2, ctl, ctv, chi);
      break;
    case BToDslnuType::Bc_Dstar0_e_Dgamma_lminus:
      result = BcDsenu_Dgamma_lm_to_.dGamma_dq2dangles_density(q2, ctl, ctv, chi) / 
               BcDsenu_Dgamma_lm_from_.dGamma_dq2dangles_density(q2, ctl, ctv, chi);
      break;
    case BToDslnuType::Bc_Dstar0_mu_Dgamma_lminus:
      result = BcDsmunu_Dgamma_lm_to_.dGamma_dq2dangles_density(q2, ctl, ctv, chi) / 
               BcDsmunu_Dgamma_lm_from_.dGamma_dq2dangles_density(q2, ctl, ctv, chi);
      break;
    case BToDslnuType::Bc_Dstar0_tau_Dgamma_lminus:
      result = BcDstaunu_Dgamma_lm_to_.dGamma_dq2dangles_density(q2, ctl, ctv, chi) / 
               BcDstaunu_Dgamma_lm_from_.dGamma_dq2dangles_density(q2, ctl, ctv, chi);
      break;
    case BToDslnuType::B0_Dstarc_e_Dgamma_lminus:
      result = B0Dsenu_Dgamma_lm_to_.dGamma_dq2dangles_density(q2, ctl, ctv, chi) / 
               B0Dsenu_Dgamma_lm_from_.dGamma_dq2dangles_density(q2, ctl, ctv, chi);
      break;
    case BToDslnuType::B0_Dstarc_mu_Dgamma_lminus:
      result = B0Dsmunu_Dgamma_lm_to_.dGamma_dq2dangles_density(q2, ctl, ctv, chi) / 
               B0Dsmunu_Dgamma_lm_from_.dGamma_dq2dangles_density(q2, ctl, ctv, chi);
      break;
    case BToDslnuType::B0_Dstarc_tau_Dgamma_lminus:
      result = B0Dstaunu_Dgamma_lm_to_.dGamma_dq2dangles_density(q2, ctl, ctv, chi) / 
               B0Dstaunu_Dgamma_lm_from_.dGamma_dq2dangles_density(q2, ctl, ctv, chi);
      break;
    case BToDslnuType::Bc_Dstar0_e_Dpi_lplus:
      result = BcDsenu_Dpi_lp_to_.dGamma_dq2dangles_density(q2, ctl, ctv, chi) / 
               BcDsenu_Dpi_lp_from_.dGamma_dq2dangles_density(q2, ctl, ctv, chi);
      break;
    case BToDslnuType::Bc_Dstar0_mu_Dpi_lplus:
      result = BcDsmunu_Dpi_lp_to_.dGamma_dq2dangles_density(q2, ctl, ctv, chi) / 
               BcDsmunu_Dpi_lp_from_.dGamma_dq2dangles_density(q2, ctl, ctv, chi);
      break;
    case BToDslnuType::Bc_Dstar0_tau_Dpi_lplus:
      result = BcDstaunu_Dpi_lp_to_.dGamma_dq2dangles_density(q2, ctl, ctv, chi) / 
               BcDstaunu_Dpi_lp_from_.dGamma_dq2dangles_density(q2, ctl, ctv, chi);
      break;
    case BToDslnuType::B0_Dstarc_e_Dpi_lplus:
      result = B0Dsenu_Dpi_lp_to_.dGamma_dq2dangles_density(q2, ctl, ctv, chi) / 
               B0Dsenu_Dpi_lp_from_.dGamma_dq2dangles_density(q2, ctl, ctv, chi);
      break;
    case BToDslnuType::B0_Dstarc_mu_Dpi_lplus:
      result = B0Dsmunu_Dpi_lp_to_.dGamma_dq2dangles_density(q2, ctl, ctv, chi) / 
               B0Dsmunu_Dpi_lp_from_.dGamma_dq2dangles_density(q2, ctl, ctv, chi);
      break;
    case BToDslnuType::B0_Dstarc_tau_Dpi_lplus:
      result = B0Dstaunu_Dpi_lp_to_.dGamma_dq2dangles_density(q2, ctl, ctv, chi) / 
               B0Dstaunu_Dpi_lp_from_.dGamma_dq2dangles_density(q2, ctl, ctv, chi);
      break;
    case BToDslnuType::Bc_Dstar0_e_Dgamma_lplus:
      result = BcDsenu_Dgamma_lp_to_.dGamma_dq2dangles_density(q2, ctl, ctv, chi) / 
               BcDsenu_Dgamma_lp_from_.dGamma_dq2dangles_density(q2, ctl, ctv, chi);
      break;
    case BToDslnuType::Bc_Dstar0_mu_Dgamma_lplus:
      result = BcDsmunu_Dgamma_lp_to_.dGamma_dq2dangles_density(q2, ctl, ctv, chi) / 
               BcDsmunu_Dgamma_lp_from_.dGamma_dq2dangles_density(q2, ctl, ctv, chi);
      break;
    case BToDslnuType::Bc_Dstar0_tau_Dgamma_lplus:
      result = BcDstaunu_Dgamma_lp_to_.dGamma_dq2dangles_density(q2, ctl, ctv, chi) / 
               BcDstaunu_Dgamma_lp_from_.dGamma_dq2dangles_density(q2, ctl, ctv, chi);
      break;
    case BToDslnuType::B0_Dstarc_e_Dgamma_lplus:
      result = B0Dsenu_Dgamma_lp_to_.dGamma_dq2dangles_density(q2, ctl, ctv, chi) / 
               B0Dsenu_Dgamma_lp_from_.dGamma_dq2dangles_density(q2, ctl, ctv, chi);
      break;
    case BToDslnuType::B0_Dstarc_mu_Dgamma_lplus:
      result = B0Dsmunu_Dgamma_lp_to_.dGamma_dq2dangles_density(q2, ctl, ctv, chi) / 
               B0Dsmunu_Dgamma_lp_from_.dGamma_dq2dangles_density(q2, ctl, ctv, chi);
      break;
    case BToDslnuType::B0_Dstarc_tau_Dgamma_lplus:
      result = B0Dstaunu_Dgamma_lp_to_.dGamma_dq2dangles_density(q2, ctl, ctv, chi) / 
               B0Dstaunu_Dgamma_lp_from_.dGamma_dq2dangles_density(q2, ctl, ctv, chi);
      break;

    default:
      ;

  }

  return result;
}
