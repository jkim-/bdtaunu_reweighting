#ifndef __BRFREWEIGHTDICT_H__
#define __BRFREWEIGHTDICT_H__

#include <vector>
#include <string>

#include <trie.h>

enum class BrfReweightCode {
#   define X(a) a,
#   include "BrfReweightCode.def"
#   undef X
    null
};

char const* const BrfReweightCodeStr[] = {
#   define X(a) #a,
#   include "BrfReweightCode.def"
#   undef X
    0
};

inline std::string brfcode2string(BrfReweightCode c) {
  int i = static_cast<int>(c);
  int n = static_cast<int>(BrfReweightCode::null);
  return (i >= 0 && i < n) ? std::string(BrfReweightCodeStr[i]) : "null";
}

class BrfReweightDict {
    
  public: 
    BrfReweightDict();
    ~BrfReweightDict();

    BrfReweightCode find(const std::vector<int> &decay_lunds, bool ignore_fsr);

  private:

    enum class Symbol {
      Bp, B0,
      D10, D0star0, D2star0, D1prime0,
      D1p, D0starp, D2starp, D1primep,
      Dsstarp, Ds1p, Dsp, 
      Dstarp, Dstar0, 
      D0, Dp, 
      Kp, K0, 
      a1p, rhop,
      pip, pi0, 
      tau, mu, e, nu, 
      other,
      null = -1,
    };

    Symbol LundToSymbol(int lund) const;
    void PopulateBrfDict();

  private:
    trie<Symbol, BrfReweightCode, Symbol::null, BrfReweightCode::null> brf_dict_;

};

#endif
