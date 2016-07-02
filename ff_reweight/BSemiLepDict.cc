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
      Symbol::B, Symbol::D, Symbol::l, Symbol::nu,
      Symbol::null
    }, BSemiLepCode::B_D_l);

  bsl_dict_.insert({
      Symbol::B, Symbol::Ds, Symbol::l, Symbol::nu,
      Symbol::null
    }, BSemiLepCode::B_Ds_l);

  bsl_dict_.insert({
      Symbol::B, Symbol::Dss, Symbol::l, Symbol::nu,
      Symbol::null
    }, BSemiLepCode::B_Dss_l);

}

// function mapping a lund id to an element in Symbol. 
BSemiLepDict::Symbol 
BSemiLepDict::LundToSymbol(int lund) const {
  switch (abs(lund)) {
    case BpLund:
    case B0Lund:
      return Symbol::B;
    case D1pLund:
    case D10Lund:
    case D2pLund:
    case D20Lund:
    case D1primepLund:
    case D1prime0Lund:
    case D0sspLund:
    case D0ss0Lund:
      return Symbol::Dss;
    case DstarpLund:
    case Dstar0Lund:
      return Symbol::Ds;
    case DpLund:
    case D0Lund:
      return Symbol::D;
    case eLund:
    case muLund:
    case tauLund:
      return Symbol::l;
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

