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
      Symbol::B, Symbol::D, Symbol::e, Symbol::nu,
      Symbol::null
    }, BSemiLepCode::B_D_e);

  bsl_dict_.insert({
      Symbol::B, Symbol::D, Symbol::mu, Symbol::nu,
      Symbol::null
    }, BSemiLepCode::B_D_mu);

  bsl_dict_.insert({
      Symbol::B, Symbol::D, Symbol::tau, Symbol::nu,
      Symbol::null
    }, BSemiLepCode::B_D_tau);

  bsl_dict_.insert({
      Symbol::B, Symbol::Ds, Symbol::e, Symbol::nu,
      Symbol::null
    }, BSemiLepCode::B_Ds_e);

  bsl_dict_.insert({
      Symbol::B, Symbol::Ds, Symbol::mu, Symbol::nu,
      Symbol::null
    }, BSemiLepCode::B_Ds_mu);

  bsl_dict_.insert({
      Symbol::B, Symbol::Ds, Symbol::tau, Symbol::nu,
      Symbol::null
    }, BSemiLepCode::B_Ds_tau);

}

// function mapping a lund id to an element in Symbol. 
BSemiLepDict::Symbol 
BSemiLepDict::LundToSymbol(int lund) const {
  switch (abs(lund)) {
    case BpLund:
    case B0Lund:
      return Symbol::B;
    case DstarpLund:
    case Dstar0Lund:
      return Symbol::Ds;
    case DpLund:
    case D0Lund:
      return Symbol::D;
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

