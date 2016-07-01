#include <ff_reweight_constants.h>

#include "LLSWReweighter.h"

LLSWReweighter::LLSWReweighter() {

  BcD0ss0enu_from_ = BDss0lnuDecayRate(mBp, mD0ss0, mE, "ISGW2");
  BcD0ss0munu_from_ = BDss0lnuDecayRate(mBp, mD0ss0, mMu, "ISGW2");
  BcD0ss0taunu_from_ = BDss0lnuDecayRate(mBp, mD0ss0, mTau, "ISGW2");
  B0D0sscenu_from_ = BDss0lnuDecayRate(mB0, mD0ssp, mE, "ISGW2");
  B0D0sscmunu_from_ = BDss0lnuDecayRate(mB0, mD0ssp, mMu, "ISGW2");
  B0D0ssctaunu_from_ = BDss0lnuDecayRate(mB0, mD0ssp, mTau, "ISGW2");
  BcD10enu_from_ = BD1lnuDecayRate(mBp, mD10, mE, "ISGW2");
  BcD10munu_from_ = BD1lnuDecayRate(mBp, mD10, mMu, "ISGW2");
  BcD10taunu_from_ = BD1lnuDecayRate(mBp, mD10, mTau, "ISGW2");
  B0D1cenu_from_ = BD1lnuDecayRate(mB0, mD1p, mE, "ISGW2");
  B0D1cmunu_from_ = BD1lnuDecayRate(mB0, mD1p, mMu, "ISGW2");
  B0D1ctaunu_from_ = BD1lnuDecayRate(mB0, mD1p, mTau, "ISGW2");
  BcD20enu_from_ = BD2lnuDecayRate(mBp, mD10, mE, "ISGW2");
  BcD20munu_from_ = BD2lnuDecayRate(mBp, mD10, mMu, "ISGW2");
  BcD20taunu_from_ = BD2lnuDecayRate(mBp, mD10, mTau, "ISGW2");
  B0D2cenu_from_ = BD2lnuDecayRate(mB0, mD1p, mE, "ISGW2");
  B0D2cmunu_from_ = BD2lnuDecayRate(mB0, mD1p, mMu, "ISGW2");
  B0D2ctaunu_from_ = BD2lnuDecayRate(mB0, mD1p, mTau, "ISGW2");
  BcD1prime0enu_from_ = BD1primelnuDecayRate(mBp, mD1prime0, mE, "ISGW2");
  BcD1prime0munu_from_ = BD1primelnuDecayRate(mBp, mD1prime0, mMu, "ISGW2");
  BcD1prime0taunu_from_ = BD1primelnuDecayRate(mBp, mD1prime0, mTau, "ISGW2");
  B0D1primecenu_from_ = BD1primelnuDecayRate(mB0, mD1primep, mE, "ISGW2");
  B0D1primecmunu_from_ = BD1primelnuDecayRate(mB0, mD1primep, mMu, "ISGW2");
  B0D1primectaunu_from_ = BD1primelnuDecayRate(mB0, mD1primep, mTau, "ISGW2");

  BcD0ss0enu_llswb1_ = BDss0lnuDecayRate(mBp, mD0ss0, mE, "LLSWB1");
  BcD0ss0munu_llswb1_ = BDss0lnuDecayRate(mBp, mD0ss0, mMu, "LLSWB1");
  BcD0ss0taunu_llswb1_ = BDss0lnuDecayRate(mBp, mD0ss0, mTau, "LLSWB1");
  B0D0sscenu_llswb1_ = BDss0lnuDecayRate(mB0, mD0ssp, mE, "LLSWB1");
  B0D0sscmunu_llswb1_ = BDss0lnuDecayRate(mB0, mD0ssp, mMu, "LLSWB1");
  B0D0ssctaunu_llswb1_ = BDss0lnuDecayRate(mB0, mD0ssp, mTau, "LLSWB1");
  BcD10enu_llswb1_ = BD1lnuDecayRate(mBp, mD10, mE, "LLSWB1");
  BcD10munu_llswb1_ = BD1lnuDecayRate(mBp, mD10, mMu, "LLSWB1");
  BcD10taunu_llswb1_ = BD1lnuDecayRate(mBp, mD10, mTau, "LLSWB1");
  B0D1cenu_llswb1_ = BD1lnuDecayRate(mB0, mD1p, mE, "LLSWB1");
  B0D1cmunu_llswb1_ = BD1lnuDecayRate(mB0, mD1p, mMu, "LLSWB1");
  B0D1ctaunu_llswb1_ = BD1lnuDecayRate(mB0, mD1p, mTau, "LLSWB1");
  BcD20enu_llswb1_ = BD2lnuDecayRate(mBp, mD10, mE, "LLSWB1");
  BcD20munu_llswb1_ = BD2lnuDecayRate(mBp, mD10, mMu, "LLSWB1");
  BcD20taunu_llswb1_ = BD2lnuDecayRate(mBp, mD10, mTau, "LLSWB1");
  B0D2cenu_llswb1_ = BD2lnuDecayRate(mB0, mD1p, mE, "LLSWB1");
  B0D2cmunu_llswb1_ = BD2lnuDecayRate(mB0, mD1p, mMu, "LLSWB1");
  B0D2ctaunu_llswb1_ = BD2lnuDecayRate(mB0, mD1p, mTau, "LLSWB1");
  BcD1prime0enu_llswb1_ = BD1primelnuDecayRate(mBp, mD1prime0, mE, "LLSWB1");
  BcD1prime0munu_llswb1_ = BD1primelnuDecayRate(mBp, mD1prime0, mMu, "LLSWB1");
  BcD1prime0taunu_llswb1_ = BD1primelnuDecayRate(mBp, mD1prime0, mTau, "LLSWB1");
  B0D1primecenu_llswb1_ = BD1primelnuDecayRate(mB0, mD1primep, mE, "LLSWB1");
  B0D1primecmunu_llswb1_ = BD1primelnuDecayRate(mB0, mD1primep, mMu, "LLSWB1");
  B0D1primectaunu_llswb1_ = BD1primelnuDecayRate(mB0, mD1primep, mTau, "LLSWB1");

  BcD0ss0enu_llswb2_ = BDss0lnuDecayRate(mBp, mD0ss0, mE, "LLSWB2");
  BcD0ss0munu_llswb2_ = BDss0lnuDecayRate(mBp, mD0ss0, mMu, "LLSWB2");
  BcD0ss0taunu_llswb2_ = BDss0lnuDecayRate(mBp, mD0ss0, mTau, "LLSWB2");
  B0D0sscenu_llswb2_ = BDss0lnuDecayRate(mB0, mD0ssp, mE, "LLSWB2");
  B0D0sscmunu_llswb2_ = BDss0lnuDecayRate(mB0, mD0ssp, mMu, "LLSWB2");
  B0D0ssctaunu_llswb2_ = BDss0lnuDecayRate(mB0, mD0ssp, mTau, "LLSWB2");
  BcD10enu_llswb2_ = BD1lnuDecayRate(mBp, mD10, mE, "LLSWB2");
  BcD10munu_llswb2_ = BD1lnuDecayRate(mBp, mD10, mMu, "LLSWB2");
  BcD10taunu_llswb2_ = BD1lnuDecayRate(mBp, mD10, mTau, "LLSWB2");
  B0D1cenu_llswb2_ = BD1lnuDecayRate(mB0, mD1p, mE, "LLSWB2");
  B0D1cmunu_llswb2_ = BD1lnuDecayRate(mB0, mD1p, mMu, "LLSWB2");
  B0D1ctaunu_llswb2_ = BD1lnuDecayRate(mB0, mD1p, mTau, "LLSWB2");
  BcD20enu_llswb2_ = BD2lnuDecayRate(mBp, mD10, mE, "LLSWB2");
  BcD20munu_llswb2_ = BD2lnuDecayRate(mBp, mD10, mMu, "LLSWB2");
  BcD20taunu_llswb2_ = BD2lnuDecayRate(mBp, mD10, mTau, "LLSWB2");
  B0D2cenu_llswb2_ = BD2lnuDecayRate(mB0, mD1p, mE, "LLSWB2");
  B0D2cmunu_llswb2_ = BD2lnuDecayRate(mB0, mD1p, mMu, "LLSWB2");
  B0D2ctaunu_llswb2_ = BD2lnuDecayRate(mB0, mD1p, mTau, "LLSWB2");
  BcD1prime0enu_llswb2_ = BD1primelnuDecayRate(mBp, mD1prime0, mE, "LLSWB2");
  BcD1prime0munu_llswb2_ = BD1primelnuDecayRate(mBp, mD1prime0, mMu, "LLSWB2");
  BcD1prime0taunu_llswb2_ = BD1primelnuDecayRate(mBp, mD1prime0, mTau, "LLSWB2");
  B0D1primecenu_llswb2_ = BD1primelnuDecayRate(mB0, mD1primep, mE, "LLSWB2");
  B0D1primecmunu_llswb2_ = BD1primelnuDecayRate(mB0, mD1primep, mMu, "LLSWB2");
  B0D1primectaunu_llswb2_ = BD1primelnuDecayRate(mB0, mD1primep, mTau, "LLSWB2");

}


double LLSWReweighter::compute_bdsslnu_llswb1_weights(
    const BToDsslnuMode &m, double q2) const {

  double result = 1.0;

  switch (m.bdsslnu_type()) {

    case BToDsslnuType::Bc_D0ss0_e:
      result = BcD0ss0enu_llswb1_.dGamma_dq2_density(q2) / 
               BcD0ss0enu_from_.dGamma_dq2_density(q2);
      break;
    case BToDsslnuType::Bc_D0ss0_mu:
      result = BcD0ss0munu_llswb1_.dGamma_dq2_density(q2) / 
               BcD0ss0munu_from_.dGamma_dq2_density(q2);
      break;
    case BToDsslnuType::Bc_D0ss0_tau:
      result = BcD0ss0taunu_llswb1_.dGamma_dq2_density(q2) / 
               BcD0ss0taunu_from_.dGamma_dq2_density(q2);
      break;
    case BToDsslnuType::B0_D0ssc_e:
      result = B0D0sscenu_llswb1_.dGamma_dq2_density(q2) / 
               B0D0sscenu_from_.dGamma_dq2_density(q2);
      break;
    case BToDsslnuType::B0_D0ssc_mu:
      result = B0D0sscmunu_llswb1_.dGamma_dq2_density(q2) / 
               B0D0sscmunu_from_.dGamma_dq2_density(q2);
      break;
    case BToDsslnuType::B0_D0ssc_tau:
      result = B0D0ssctaunu_llswb1_.dGamma_dq2_density(q2) / 
               B0D0ssctaunu_from_.dGamma_dq2_density(q2);
      break;

    case BToDsslnuType::Bc_D10_e:
      result = BcD10enu_llswb1_.dGamma_dq2_density(q2) / 
               BcD10enu_from_.dGamma_dq2_density(q2);
      break;
    case BToDsslnuType::Bc_D10_mu:
      result = BcD10munu_llswb1_.dGamma_dq2_density(q2) / 
               BcD10munu_from_.dGamma_dq2_density(q2);
      break;
    case BToDsslnuType::Bc_D10_tau:
      result = BcD10taunu_llswb1_.dGamma_dq2_density(q2) / 
               BcD10taunu_from_.dGamma_dq2_density(q2);
      break;
    case BToDsslnuType::B0_D1c_e:
      result = B0D1cenu_llswb1_.dGamma_dq2_density(q2) / 
               B0D1cenu_from_.dGamma_dq2_density(q2);
      break;
    case BToDsslnuType::B0_D1c_mu:
      result = B0D1cmunu_llswb1_.dGamma_dq2_density(q2) / 
               B0D1cmunu_from_.dGamma_dq2_density(q2);
      break;
    case BToDsslnuType::B0_D1c_tau:
      result = B0D1ctaunu_llswb1_.dGamma_dq2_density(q2) / 
               B0D1ctaunu_from_.dGamma_dq2_density(q2);
      break;

    case BToDsslnuType::Bc_D20_e:
      result = BcD20enu_llswb1_.dGamma_dq2_density(q2) / 
               BcD20enu_from_.dGamma_dq2_density(q2);
      break;
    case BToDsslnuType::Bc_D20_mu:
      result = BcD20munu_llswb1_.dGamma_dq2_density(q2) / 
               BcD20munu_from_.dGamma_dq2_density(q2);
      break;
    case BToDsslnuType::Bc_D20_tau:
      result = BcD20taunu_llswb1_.dGamma_dq2_density(q2) / 
               BcD20taunu_from_.dGamma_dq2_density(q2);
      break;
    case BToDsslnuType::B0_D2c_e:
      result = B0D2cenu_llswb1_.dGamma_dq2_density(q2) / 
               B0D2cenu_from_.dGamma_dq2_density(q2);
      break;
    case BToDsslnuType::B0_D2c_mu:
      result = B0D2cmunu_llswb1_.dGamma_dq2_density(q2) / 
               B0D2cmunu_from_.dGamma_dq2_density(q2);
      break;
    case BToDsslnuType::B0_D2c_tau:
      result = B0D2ctaunu_llswb1_.dGamma_dq2_density(q2) / 
               B0D2ctaunu_from_.dGamma_dq2_density(q2);
      break;

    case BToDsslnuType::Bc_D1prime0_e:
      result = BcD1prime0enu_llswb1_.dGamma_dq2_density(q2) / 
               BcD1prime0enu_from_.dGamma_dq2_density(q2);
      break;
    case BToDsslnuType::Bc_D1prime0_mu:
      result = BcD1prime0munu_llswb1_.dGamma_dq2_density(q2) / 
               BcD1prime0munu_from_.dGamma_dq2_density(q2);
      break;
    case BToDsslnuType::Bc_D1prime0_tau:
      result = BcD1prime0taunu_llswb1_.dGamma_dq2_density(q2) / 
               BcD1prime0taunu_from_.dGamma_dq2_density(q2);
      break;
    case BToDsslnuType::B0_D1primec_e:
      result = B0D1primecenu_llswb1_.dGamma_dq2_density(q2) / 
               B0D1primecenu_from_.dGamma_dq2_density(q2);
      break;
    case BToDsslnuType::B0_D1primec_mu:
      result = B0D1primecmunu_llswb1_.dGamma_dq2_density(q2) / 
               B0D1primecmunu_from_.dGamma_dq2_density(q2);
      break;
    case BToDsslnuType::B0_D1primec_tau:
      result = B0D1primectaunu_llswb1_.dGamma_dq2_density(q2) / 
               B0D1primectaunu_from_.dGamma_dq2_density(q2);
      break;

    default:
      ;
  }

  return result;
  
}


double LLSWReweighter::compute_bdsslnu_llswb2_weights(
    const BToDsslnuMode &m, double q2) const {

  double result = 1.0;

  switch (m.bdsslnu_type()) {

    case BToDsslnuType::Bc_D0ss0_e:
      result = BcD0ss0enu_llswb2_.dGamma_dq2_density(q2) / 
               BcD0ss0enu_from_.dGamma_dq2_density(q2);
      break;
    case BToDsslnuType::Bc_D0ss0_mu:
      result = BcD0ss0munu_llswb2_.dGamma_dq2_density(q2) / 
               BcD0ss0munu_from_.dGamma_dq2_density(q2);
      break;
    case BToDsslnuType::Bc_D0ss0_tau:
      result = BcD0ss0taunu_llswb2_.dGamma_dq2_density(q2) / 
               BcD0ss0taunu_from_.dGamma_dq2_density(q2);
      break;
    case BToDsslnuType::B0_D0ssc_e:
      result = B0D0sscenu_llswb2_.dGamma_dq2_density(q2) / 
               B0D0sscenu_from_.dGamma_dq2_density(q2);
      break;
    case BToDsslnuType::B0_D0ssc_mu:
      result = B0D0sscmunu_llswb2_.dGamma_dq2_density(q2) / 
               B0D0sscmunu_from_.dGamma_dq2_density(q2);
      break;
    case BToDsslnuType::B0_D0ssc_tau:
      result = B0D0ssctaunu_llswb2_.dGamma_dq2_density(q2) / 
               B0D0ssctaunu_from_.dGamma_dq2_density(q2);
      break;

    case BToDsslnuType::Bc_D10_e:
      result = BcD10enu_llswb2_.dGamma_dq2_density(q2) / 
               BcD10enu_from_.dGamma_dq2_density(q2);
      break;
    case BToDsslnuType::Bc_D10_mu:
      result = BcD10munu_llswb2_.dGamma_dq2_density(q2) / 
               BcD10munu_from_.dGamma_dq2_density(q2);
      break;
    case BToDsslnuType::Bc_D10_tau:
      result = BcD10taunu_llswb2_.dGamma_dq2_density(q2) / 
               BcD10taunu_from_.dGamma_dq2_density(q2);
      break;
    case BToDsslnuType::B0_D1c_e:
      result = B0D1cenu_llswb2_.dGamma_dq2_density(q2) / 
               B0D1cenu_from_.dGamma_dq2_density(q2);
      break;
    case BToDsslnuType::B0_D1c_mu:
      result = B0D1cmunu_llswb2_.dGamma_dq2_density(q2) / 
               B0D1cmunu_from_.dGamma_dq2_density(q2);
      break;
    case BToDsslnuType::B0_D1c_tau:
      result = B0D1ctaunu_llswb2_.dGamma_dq2_density(q2) / 
               B0D1ctaunu_from_.dGamma_dq2_density(q2);
      break;

    case BToDsslnuType::Bc_D20_e:
      result = BcD20enu_llswb2_.dGamma_dq2_density(q2) / 
               BcD20enu_from_.dGamma_dq2_density(q2);
      break;
    case BToDsslnuType::Bc_D20_mu:
      result = BcD20munu_llswb2_.dGamma_dq2_density(q2) / 
               BcD20munu_from_.dGamma_dq2_density(q2);
      break;
    case BToDsslnuType::Bc_D20_tau:
      result = BcD20taunu_llswb2_.dGamma_dq2_density(q2) / 
               BcD20taunu_from_.dGamma_dq2_density(q2);
      break;
    case BToDsslnuType::B0_D2c_e:
      result = B0D2cenu_llswb2_.dGamma_dq2_density(q2) / 
               B0D2cenu_from_.dGamma_dq2_density(q2);
      break;
    case BToDsslnuType::B0_D2c_mu:
      result = B0D2cmunu_llswb2_.dGamma_dq2_density(q2) / 
               B0D2cmunu_from_.dGamma_dq2_density(q2);
      break;
    case BToDsslnuType::B0_D2c_tau:
      result = B0D2ctaunu_llswb2_.dGamma_dq2_density(q2) / 
               B0D2ctaunu_from_.dGamma_dq2_density(q2);
      break;

    case BToDsslnuType::Bc_D1prime0_e:
      result = BcD1prime0enu_llswb2_.dGamma_dq2_density(q2) / 
               BcD1prime0enu_from_.dGamma_dq2_density(q2);
      break;
    case BToDsslnuType::Bc_D1prime0_mu:
      result = BcD1prime0munu_llswb2_.dGamma_dq2_density(q2) / 
               BcD1prime0munu_from_.dGamma_dq2_density(q2);
      break;
    case BToDsslnuType::Bc_D1prime0_tau:
      result = BcD1prime0taunu_llswb2_.dGamma_dq2_density(q2) / 
               BcD1prime0taunu_from_.dGamma_dq2_density(q2);
      break;
    case BToDsslnuType::B0_D1primec_e:
      result = B0D1primecenu_llswb2_.dGamma_dq2_density(q2) / 
               B0D1primecenu_from_.dGamma_dq2_density(q2);
      break;
    case BToDsslnuType::B0_D1primec_mu:
      result = B0D1primecmunu_llswb2_.dGamma_dq2_density(q2) / 
               B0D1primecmunu_from_.dGamma_dq2_density(q2);
      break;
    case BToDsslnuType::B0_D1primec_tau:
      result = B0D1primectaunu_llswb2_.dGamma_dq2_density(q2) / 
               B0D1primectaunu_from_.dGamma_dq2_density(q2);
      break;

    default:
      ;
  }

  return result;
  
}

