#ifndef __BSEMILEPDICT_H__
#define __BSEMILEPDICT_H__

#include <vector>

#include <trie.h>

enum class BSemiLepCode {
  B_D_l = 1,
  B_Ds_l,
  B_Dss_l,
  null = -1,
};

class BSemiLepDict {
    
  public: 
    BSemiLepDict();
    ~BSemiLepDict();

    BSemiLepCode find(const std::vector<int> &decay_lunds, 
                      bool ignore_FSR=true);

  private:

    enum class Symbol {
      B, Dss, Ds, D, l, nu, gamma, other, null = -1,
    };

    Symbol LundToSymbol(int lund) const;
    void PopulateBSLDict();

  private:
    trie<Symbol, BSemiLepCode, Symbol::null, BSemiLepCode::null> bsl_dict_;

};

#endif
