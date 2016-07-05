#include <vector>
#include <algorithm>

#include <ff_reweight_constants.h>

#include "BrfReweightDict.h"

BrfReweightDict::BrfReweightDict() {
  PopulateBrfDict();
}

BrfReweightDict::~BrfReweightDict() {}

BrfReweightCode 
BrfReweightDict::find(const std::vector<int> &decay_lunds, bool ignore_fsr) {

  std::vector<Symbol> word;
  for (auto l : decay_lunds) {
    if (ignore_fsr && l == gammaLund) { continue; }
    word.push_back(LundToSymbol(l));
  }
  std::sort(word.begin(), word.end());
  word.push_back(Symbol::null);
  return brf_dict_.find(word);
}

void BrfReweightDict::PopulateBrfDict() {

  // --------------------------------------------------
  // Corrected:
  
  brf_dict_.insert({ 
      Symbol::Bp, Symbol::Dstar0, Symbol::mu, Symbol::nu,
      Symbol::null
    }, BrfReweightCode::Bp_Dstar0_mu_nu);

  brf_dict_.insert({ 
      Symbol::Bp, Symbol::Dstar0, Symbol::e, Symbol::nu,
      Symbol::null
    }, BrfReweightCode::Bp_Dstar0_e_nu);

  brf_dict_.insert({ 
      Symbol::Bp, Symbol::D0, Symbol::mu, Symbol::nu,
      Symbol::null
    }, BrfReweightCode::Bp_D0_mu_nu);

  brf_dict_.insert({ 
      Symbol::Bp, Symbol::D0, Symbol::e, Symbol::nu,
      Symbol::null
    }, BrfReweightCode::Bp_D0_e_nu);

  brf_dict_.insert({ 
      Symbol::Bp, Symbol::Dsstarp, Symbol::Dstar0,
      Symbol::null
    }, BrfReweightCode::Bp_Dsstarp_Dstar0);

  brf_dict_.insert({ 
      Symbol::Bp, Symbol::Dstar0, Symbol::tau, Symbol::nu,
      Symbol::null
    }, BrfReweightCode::Bp_Dstar0_tau_nu);

  brf_dict_.insert({ 
      Symbol::Bp, Symbol::Dsp, Symbol::D0,
      Symbol::null
    }, BrfReweightCode::Bp_Dsp_D0);

  brf_dict_.insert({ 
      Symbol::Bp, Symbol::Dsp, Symbol::Dstar0,
      Symbol::null
    }, BrfReweightCode::Bp_Dsp_Dstar0);

  brf_dict_.insert({ 
      Symbol::Bp, Symbol::D0, Symbol::tau, Symbol::nu,
      Symbol::null
    }, BrfReweightCode::Bp_D0_tau_nu);

  brf_dict_.insert({ 
      Symbol::Bp, Symbol::Dsstarp, Symbol::D0,
      Symbol::null
    }, BrfReweightCode::Bp_Dsstarp_D0);

  brf_dict_.insert({ 
      Symbol::Bp, Symbol::D0, Symbol::rhop,
      Symbol::null
    }, BrfReweightCode::Bp_D0_rhop);

  brf_dict_.insert({ 
      Symbol::Bp, Symbol::Dstar0, Symbol::a1p,
      Symbol::null
    }, BrfReweightCode::Bp_Dstar0_a1p);

  brf_dict_.insert({ 
      Symbol::Bp, Symbol::Dstarp, Symbol::pip,
      Symbol::pip, Symbol::pi0,
      Symbol::null
    }, BrfReweightCode::Bp_Dstarp_pip_pip_pi0);

  brf_dict_.insert({ 
      Symbol::Bp, Symbol::D0, Symbol::a1p,
      Symbol::null
    }, BrfReweightCode::Bp_D0_a1p);

  brf_dict_.insert({ 
      Symbol::B0, Symbol::Dstarp, Symbol::mu, Symbol::nu,
      Symbol::null
    }, BrfReweightCode::B0_Dstarp_mu_nu);

  brf_dict_.insert({ 
      Symbol::B0, Symbol::Dstarp, Symbol::e, Symbol::nu,
      Symbol::null
    }, BrfReweightCode::B0_Dstarp_e_nu);

  brf_dict_.insert({ 
      Symbol::B0, Symbol::Dp, Symbol::mu, Symbol::nu,
      Symbol::null
    }, BrfReweightCode::B0_Dp_mu_nu);

  brf_dict_.insert({ 
      Symbol::B0, Symbol::Dp, Symbol::e, Symbol::nu,
      Symbol::null
    }, BrfReweightCode::B0_Dp_e_nu);

  brf_dict_.insert({ 
      Symbol::B0, Symbol::Dsstarp, Symbol::Dstarp,
      Symbol::null
    }, BrfReweightCode::B0_Dsstarp_Dstarp);

  brf_dict_.insert({ 
      Symbol::B0, Symbol::Dstarp, Symbol::tau, Symbol::nu,
      Symbol::null
    }, BrfReweightCode::B0_Dstarp_tau_nu);

  brf_dict_.insert({ 
      Symbol::B0, Symbol::Dsp, Symbol::Dstarp,
      Symbol::null
    }, BrfReweightCode::B0_Dsp_Dstarp);

  brf_dict_.insert({ 
      Symbol::B0, Symbol::Dstarp, Symbol::Dstar0, Symbol::Kp,
      Symbol::null
    }, BrfReweightCode::B0_Dstarp_Dstar0_Kp);

  brf_dict_.insert({ 
      Symbol::B0, Symbol::Dsstarp, Symbol::Dp,
      Symbol::null
    }, BrfReweightCode::B0_Dsstarp_Dp);

  brf_dict_.insert({ 
      Symbol::B0, Symbol::Dstarp, Symbol::a1p,
      Symbol::null
    }, BrfReweightCode::B0_Dstarp_a1p);

  brf_dict_.insert({ 
      Symbol::B0, Symbol::Dp, Symbol::tau, Symbol::nu,
      Symbol::null
    }, BrfReweightCode::B0_Dp_tau_nu);

  brf_dict_.insert({ 
      Symbol::B0, Symbol::Dsp, Symbol::Dp,
      Symbol::null
    }, BrfReweightCode::B0_Dsp_Dp);

  brf_dict_.insert({ 
      Symbol::B0, Symbol::Dstar0, Symbol::Dp, Symbol::Kp,
      Symbol::null
    }, BrfReweightCode::B0_Dstar0_Dp_Kp);

  brf_dict_.insert({ 
      Symbol::B0, Symbol::Dstarp, Symbol::Dstarp, Symbol::K0,
      Symbol::null
    }, BrfReweightCode::B0_Dstarp_Dstarp_K0);

  brf_dict_.insert({ 
      Symbol::B0, Symbol::Dp, Symbol::rhop,
      Symbol::null
    }, BrfReweightCode::B0_Dp_rhop);

  brf_dict_.insert({ 
      Symbol::B0, Symbol::Ds1p, Symbol::Dstarp,
      Symbol::null
    }, BrfReweightCode::B0_Ds1p_Dstarp);

  // --------------------------------------------------
  // Fluctuated:
  
  brf_dict_.insert({ 
      Symbol::Bp, Symbol::D10, Symbol::e, Symbol::nu,
      Symbol::null
    }, BrfReweightCode::Bp_D10_e_nu);

  brf_dict_.insert({ 
      Symbol::Bp, Symbol::D0star0, Symbol::e, Symbol::nu,
      Symbol::null
    }, BrfReweightCode::Bp_D0star0_e_nu);

  brf_dict_.insert({ 
      Symbol::Bp, Symbol::D2star0, Symbol::e, Symbol::nu,
      Symbol::null
    }, BrfReweightCode::Bp_D2star0_e_nu);

  brf_dict_.insert({ 
      Symbol::Bp, Symbol::D1prime0, Symbol::e, Symbol::nu,
      Symbol::null
    }, BrfReweightCode::Bp_D1prime0_e_nu);

  brf_dict_.insert({ 
      Symbol::Bp, Symbol::Dstarp, Symbol::pip, Symbol::e, Symbol::nu,
      Symbol::null
    }, BrfReweightCode::Bp_Dstarp_pip_e_nu);

  brf_dict_.insert({ 
      Symbol::Bp, Symbol::Dp, Symbol::pip, Symbol::e, Symbol::nu,
      Symbol::null
    }, BrfReweightCode::Bp_Dp_pip_e_nu);

  brf_dict_.insert({ 
      Symbol::Bp, Symbol::Dstar0, Symbol::pi0, Symbol::e, Symbol::nu,
      Symbol::null
    }, BrfReweightCode::Bp_Dstar0_pi0_e_nu);

  brf_dict_.insert({ 
      Symbol::Bp, Symbol::D0, Symbol::pi0, Symbol::e, Symbol::nu, 
      Symbol::null
    }, BrfReweightCode::Bp_D0_pi0_e_nu);

  brf_dict_.insert({ 
      Symbol::Bp, Symbol::D10, Symbol::mu, Symbol::nu,
      Symbol::null
    }, BrfReweightCode::Bp_D10_mu_nu);

  brf_dict_.insert({ 
      Symbol::Bp, Symbol::D0star0, Symbol::mu, Symbol::nu,
      Symbol::null
    }, BrfReweightCode::Bp_D0star0_mu_nu);

  brf_dict_.insert({ 
      Symbol::Bp, Symbol::D2star0, Symbol::mu, Symbol::nu,
      Symbol::null
    }, BrfReweightCode::Bp_D2star0_mu_nu);

  brf_dict_.insert({ 
      Symbol::Bp, Symbol::D1prime0, Symbol::mu, Symbol::nu,
      Symbol::null
    }, BrfReweightCode::Bp_D1prime0_mu_nu);

  brf_dict_.insert({ 
      Symbol::Bp, Symbol::Dstarp, Symbol::pip, Symbol::mu, Symbol::nu,
      Symbol::null
    }, BrfReweightCode::Bp_Dstarp_pip_mu_nu);

  brf_dict_.insert({ 
      Symbol::Bp, Symbol::Dp, Symbol::pip, Symbol::mu, Symbol::nu, 
      Symbol::null
    }, BrfReweightCode::Bp_Dp_pip_mu_nu);

  brf_dict_.insert({ 
      Symbol::Bp, Symbol::Dstar0, Symbol::pi0, Symbol::mu, Symbol::nu, 
      Symbol::null
    }, BrfReweightCode::Bp_Dstar0_pi0_mu_nu);

  brf_dict_.insert({ 
      Symbol::Bp, Symbol::D0, Symbol::pi0, Symbol::mu, Symbol::nu,
      Symbol::null
    }, BrfReweightCode::Bp_D0_pi0_mu_nu);

  brf_dict_.insert({ 
      Symbol::Bp, Symbol::D10, Symbol::tau, Symbol::nu,
      Symbol::null
    }, BrfReweightCode::Bp_D10_tau_nu);

  brf_dict_.insert({ 
      Symbol::Bp, Symbol::D0star0, Symbol::tau, Symbol::nu,
      Symbol::null
    }, BrfReweightCode::Bp_D0star0_tau_nu);

  brf_dict_.insert({ 
      Symbol::Bp, Symbol::D2star0, Symbol::tau, Symbol::nu,
      Symbol::null
    }, BrfReweightCode::Bp_D2star0_tau_nu);

  brf_dict_.insert({ 
      Symbol::Bp, Symbol::D1prime0, Symbol::tau, Symbol::nu,
      Symbol::null
    }, BrfReweightCode::Bp_D1prime0_tau_nu);

  brf_dict_.insert({ 
      Symbol::B0, Symbol::D1p, Symbol::e, Symbol::nu,
      Symbol::null
    }, BrfReweightCode::B0_D1p_e_nu);

  brf_dict_.insert({ 
      Symbol::B0, Symbol::D0starp, Symbol::e, Symbol::nu,
      Symbol::null
    }, BrfReweightCode::B0_D0starp_e_nu);

  brf_dict_.insert({ 
      Symbol::B0, Symbol::D2starp, Symbol::e, Symbol::nu,
      Symbol::null
    }, BrfReweightCode::B0_D2starp_e_nu);

  brf_dict_.insert({ 
      Symbol::B0, Symbol::D1primep, Symbol::e, Symbol::nu,
      Symbol::null
    }, BrfReweightCode::B0_D1primep_e_nu);

  brf_dict_.insert({ 
      Symbol::B0, Symbol::Dstarp, Symbol::pi0, Symbol::e, Symbol::nu, 
      Symbol::null
    }, BrfReweightCode::B0_Dstarp_pi0_e_nu);

  brf_dict_.insert({ 
      Symbol::B0, Symbol::Dp, Symbol::pi0, Symbol::e, Symbol::nu, 
      Symbol::null
    }, BrfReweightCode::B0_Dp_pi0_e_nu);

  brf_dict_.insert({ 
      Symbol::B0, Symbol::Dstar0, Symbol::pip, Symbol::e, Symbol::nu, 
      Symbol::null
    }, BrfReweightCode::B0_Dstar0_pip_e_nu);

  brf_dict_.insert({ 
      Symbol::B0, Symbol::D0, Symbol::pip, Symbol::e, Symbol::nu, 
      Symbol::null
    }, BrfReweightCode::B0_D0_pip_e_nu);

  brf_dict_.insert({ 
      Symbol::B0, Symbol::D1p, Symbol::mu, Symbol::nu,
      Symbol::null
    }, BrfReweightCode::B0_D1p_mu_nu);

  brf_dict_.insert({ 
      Symbol::B0, Symbol::D0starp, Symbol::mu, Symbol::nu,
      Symbol::null
    }, BrfReweightCode::B0_D0starp_mu_nu);

  brf_dict_.insert({ 
      Symbol::B0, Symbol::D2starp, Symbol::mu, Symbol::nu,
      Symbol::null
    }, BrfReweightCode::B0_D2starp_mu_nu);

  brf_dict_.insert({ 
      Symbol::B0, Symbol::D1primep, Symbol::mu, Symbol::nu,
      Symbol::null
    }, BrfReweightCode::B0_D1primep_mu_nu);

  brf_dict_.insert({ 
      Symbol::B0, Symbol::Dstarp, Symbol::pi0, Symbol::mu, Symbol::nu, 
      Symbol::null
    }, BrfReweightCode::B0_Dstarp_pi0_mu_nu);

  brf_dict_.insert({ 
      Symbol::B0, Symbol::Dp, Symbol::pi0, Symbol::mu, Symbol::nu, 
      Symbol::null
    }, BrfReweightCode::B0_Dp_pi0_mu_nu);

  brf_dict_.insert({ 
      Symbol::B0, Symbol::Dstar0, Symbol::pip, Symbol::mu, Symbol::nu, 
      Symbol::null
    }, BrfReweightCode::B0_Dstar0_pip_mu_nu);

  brf_dict_.insert({ 
      Symbol::B0, Symbol::D0, Symbol::pip, Symbol::mu, Symbol::nu,
      Symbol::null
    }, BrfReweightCode::B0_D0_pip_mu_nu);

  brf_dict_.insert({ 
      Symbol::B0, Symbol::D1p, Symbol::tau, Symbol::nu,
      Symbol::null
    }, BrfReweightCode::B0_D1p_tau_nu);

  brf_dict_.insert({ 
      Symbol::B0, Symbol::D0starp, Symbol::tau, Symbol::nu,
      Symbol::null
    }, BrfReweightCode::B0_D0starp_tau_nu);

  brf_dict_.insert({ 
      Symbol::B0, Symbol::D2starp, Symbol::tau, Symbol::nu,
      Symbol::null
    }, BrfReweightCode::B0_D2starp_tau_nu);

  brf_dict_.insert({ 
      Symbol::B0, Symbol::D1primep, Symbol::tau, Symbol::nu,
      Symbol::null
    }, BrfReweightCode::B0_D1primep_tau_nu);
}


// function mapping a lund id to an element in Symbol. 
BrfReweightDict::Symbol 
BrfReweightDict::LundToSymbol(int lund) const {
  switch (abs(lund)) {
    case B0Lund:
      return Symbol::B0;
    case BpLund:
      return Symbol::Bp;

    case D10Lund:
      return Symbol::D10;
    case D0ss0Lund:
      return Symbol::D0star0;
    case D20Lund:
      return Symbol::D2star0;
    case D1prime0Lund:
      return Symbol::D1prime0;

    case D1pLund:
      return Symbol::D1p;
    case D0sspLund:
      return Symbol::D0starp;
    case D2pLund:
      return Symbol::D2starp;
    case D1primepLund:
      return Symbol::D1primep;

    case DsstarpLund:
      return Symbol::Dsstarp;
    case DspLund:
      return Symbol::Dsp;
    case Ds1pLund:
      return Symbol::Ds1p;

    case DstarpLund:
      return Symbol::Dstarp;
    case Dstar0Lund:
      return Symbol::Dstar0;

    case DpLund:
      return Symbol::Dp;
    case D0Lund:
      return Symbol::D0;

    case KpLund:
      return Symbol::Kp;
    case K0Lund:
      return Symbol::K0;

    case a1pLund:
      return Symbol::a1p;
    case rhopLund:
      return Symbol::rhop;

    case pipLund:
      return Symbol::pip;
    case pi0Lund:
      return Symbol::pi0;

    case eLund:
      return Symbol::e;
    case muLund:
      return Symbol::mu;
    case tauLund:
      return Symbol::tau;
    case nueLund:
    case numuLund:
    case nutauLund:
      return Symbol::nu;

    default:
      return Symbol::other;
  }
}

