#include <string>
#include <cmath>
#include <ff_reweight_constants.h>

#include <BDss0lnuDecayRate.h>
#include <BD1lnuDecayRate.h>
#include <BD2lnuDecayRate.h>
#include <BD1primelnuDecayRate.h>


#include "LLSWReweighter.h"


LLSWReweighter::LLSWReweighter() {}

template <typename BDsslnuDecayRate>
double ReweightBDsslnu(const BToDsslnuMode &mode, 
                   std::string to_model,
                   std::string from_model) {
  double mB = mode.BLab().m();
  double mD = mode.XLab().m();
  double mLep = mode.LepLab().m();
  double q2 = mode.q2();
  BDsslnuDecayRate from(mB, mD, mLep, from_model);
  BDsslnuDecayRate to(mB, mD, mLep, to_model);

  // cludge for now; i suspect this happens for poorly reconstructed candidates.
  // in any case, this is very infrequent (~ 1 in 10000 records). would have 
  // been better to mark these for removal, but that's more bookkepping
  // for what the timeline will allow me to do. 
  if (q2 < from.q2min() || q2 > from.q2max() ||
      q2 < to.q2min() || q2 > to.q2max()) { 
    return 1.0;
  }

  return to.dGamma_dq2_density(q2) / from.dGamma_dq2_density(q2);
}

double LLSWReweighter::compute_bdsslnu_llswb1_weights(
    const BToDsslnuMode &m) const {

  double result = 1.0;

  switch (m.bdsslnu_type()) {

    case BToDsslnuType::Bc_D0ss0_e:
    case BToDsslnuType::Bc_D0ss0_mu:
    case BToDsslnuType::Bc_D0ss0_tau:
    case BToDsslnuType::B0_D0ssc_e:
    case BToDsslnuType::B0_D0ssc_mu:
    case BToDsslnuType::B0_D0ssc_tau:
      result = ReweightBDsslnu<BDss0lnuDecayRate>(m, "LLSWB1", "ISGW2");
      break;

    case BToDsslnuType::Bc_D10_e:
    case BToDsslnuType::Bc_D10_mu:
    case BToDsslnuType::Bc_D10_tau:
    case BToDsslnuType::B0_D1c_e:
    case BToDsslnuType::B0_D1c_mu:
    case BToDsslnuType::B0_D1c_tau:
      result = ReweightBDsslnu<BD1lnuDecayRate>(m, "LLSWB1", "ISGW2");
      break;

    case BToDsslnuType::Bc_D20_e:
    case BToDsslnuType::Bc_D20_mu:
    case BToDsslnuType::Bc_D20_tau:
    case BToDsslnuType::B0_D2c_e:
    case BToDsslnuType::B0_D2c_mu:
    case BToDsslnuType::B0_D2c_tau:
      result = ReweightBDsslnu<BD2lnuDecayRate>(m, "LLSWB1", "ISGW2");
      break;

    case BToDsslnuType::Bc_D1prime0_e:
    case BToDsslnuType::Bc_D1prime0_mu:
    case BToDsslnuType::Bc_D1prime0_tau:
    case BToDsslnuType::B0_D1primec_e:
    case BToDsslnuType::B0_D1primec_mu:
    case BToDsslnuType::B0_D1primec_tau:
      result = ReweightBDsslnu<BD1primelnuDecayRate>(m, "LLSWB1", "ISGW2");
      break;

    default:
      ;
  }


  return result;
  
}

double LLSWReweighter::compute_bdsslnu_llswb2_weights(
    const BToDsslnuMode &m) const {

  double result = 1.0;

  switch (m.bdsslnu_type()) {

    case BToDsslnuType::Bc_D0ss0_e:
    case BToDsslnuType::Bc_D0ss0_mu:
    case BToDsslnuType::Bc_D0ss0_tau:
    case BToDsslnuType::B0_D0ssc_e:
    case BToDsslnuType::B0_D0ssc_mu:
    case BToDsslnuType::B0_D0ssc_tau:
      result = ReweightBDsslnu<BDss0lnuDecayRate>(m, "LLSWB2", "ISGW2");
      break;

    case BToDsslnuType::Bc_D10_e:
    case BToDsslnuType::Bc_D10_mu:
    case BToDsslnuType::Bc_D10_tau:
    case BToDsslnuType::B0_D1c_e:
    case BToDsslnuType::B0_D1c_mu:
    case BToDsslnuType::B0_D1c_tau:
      result = ReweightBDsslnu<BD1lnuDecayRate>(m, "LLSWB2", "ISGW2");
      break;

    case BToDsslnuType::Bc_D20_e:
    case BToDsslnuType::Bc_D20_mu:
    case BToDsslnuType::Bc_D20_tau:
    case BToDsslnuType::B0_D2c_e:
    case BToDsslnuType::B0_D2c_mu:
    case BToDsslnuType::B0_D2c_tau:
      result = ReweightBDsslnu<BD2lnuDecayRate>(m, "LLSWB2", "ISGW2");
      break;

    case BToDsslnuType::Bc_D1prime0_e:
    case BToDsslnuType::Bc_D1prime0_mu:
    case BToDsslnuType::Bc_D1prime0_tau:
    case BToDsslnuType::B0_D1primec_e:
    case BToDsslnuType::B0_D1primec_mu:
    case BToDsslnuType::B0_D1primec_tau:
      result = ReweightBDsslnu<BD1primelnuDecayRate>(m, "LLSWB2", "ISGW2");
      break;

    default:
      ;
  }


  return result;
  
}



