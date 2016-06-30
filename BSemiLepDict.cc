#include <vector>
#include <algorithm>

#include <ff_reweight_constants.h>

#include "BSemiLepDict.h"

BSemiLepDict::BSemiLepDict() {
  PopulateBSLDict();
}

BSemiLepDict::~BSemiLepDict() {}

BSemiLepCode BSemiLepDict::find(
    const std::vector<int> &decay_lunds, 
    bool ignore_FSR) {

  std::vector<Symbol> word;
  for (auto l : decay_lunds) {
    if (ignore_FSR && l == gammaLund) { continue; }
    word.push_back(LundToSymbol(l));
  }
  std::sort(word.begin(), word.end());
  word.push_back(Symbol::null);
  return bsl_dict_.find(word);
}

void BSemiLepDict::PopulateBSLDict() {

  bsl_dict_.insert({
      Symbol::Bc, Symbol::D0, Symbol::e, Symbol::nu,
      Symbol::null
    }, BSemiLepCode::Bc_D0_e);

  bsl_dict_.insert({
      Symbol::Bc, Symbol::D0, Symbol::mu, Symbol::nu,
      Symbol::null
    }, BSemiLepCode::Bc_D0_mu);

  bsl_dict_.insert({
      Symbol::Bc, Symbol::D0, Symbol::tau, Symbol::nu,
      Symbol::null
    }, BSemiLepCode::Bc_D0_tau);

  bsl_dict_.insert({
      Symbol::Bc, Symbol::Dstar0, Symbol::e, Symbol::nu,
      Symbol::null
    }, BSemiLepCode::Bc_Dstar0_e);

  bsl_dict_.insert({
      Symbol::Bc, Symbol::Dstar0, Symbol::mu, Symbol::nu,
      Symbol::null
    }, BSemiLepCode::Bc_Dstar0_mu);

  bsl_dict_.insert({
      Symbol::Bc, Symbol::Dstar0, Symbol::tau, Symbol::nu,
      Symbol::null
    }, BSemiLepCode::Bc_Dstar0_tau);

  bsl_dict_.insert({
      Symbol::B0, Symbol::Dc, Symbol::e, Symbol::nu,
      Symbol::null
    }, BSemiLepCode::B0_Dc_e);

  bsl_dict_.insert({
      Symbol::B0, Symbol::Dc, Symbol::mu, Symbol::nu,
      Symbol::null
    }, BSemiLepCode::B0_Dc_mu);

  bsl_dict_.insert({
      Symbol::B0, Symbol::Dc, Symbol::tau, Symbol::nu,
      Symbol::null
    }, BSemiLepCode::B0_Dc_tau);

  bsl_dict_.insert({
      Symbol::B0, Symbol::Dstarc, Symbol::e, Symbol::nu,
      Symbol::null
    }, BSemiLepCode::B0_Dstarc_e);

  bsl_dict_.insert({
      Symbol::B0, Symbol::Dstarc, Symbol::mu, Symbol::nu,
      Symbol::null
    }, BSemiLepCode::B0_Dstarc_mu);

  bsl_dict_.insert({
      Symbol::B0, Symbol::Dstarc, Symbol::tau, Symbol::nu,
      Symbol::null
    }, BSemiLepCode::B0_Dstarc_tau);

}

// function mapping a lund id to an element in Symbol. 
BSemiLepDict::Symbol 
BSemiLepDict::LundToSymbol(int lund) const {
  switch (abs(lund)) {
    case BpLund:
      return Symbol::Bc;
    case B0Lund:
      return Symbol::B0;
    case DstarpLund:
      return Symbol::Dstarc;
    case Dstar0Lund:
      return Symbol::Dstar0;
    case DpLund:
      return Symbol::Dc;
    case D0Lund:
      return Symbol::D0;
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
    case gammaLund:
      return Symbol::gamma;
    default:
      return Symbol::other;
  }
}

