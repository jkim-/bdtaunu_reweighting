#ifndef __BSEMILEPDICT_H__
#define __BSEMILEPDICT_H__

#include <vector>

#include <trie.h>

enum class BSemiLepCode {
  B_D_e = 1,
  B_D_mu = 2,
  B_D_tau = 3,
  B_Ds_e = 4,
  B_Ds_mu = 5,
  B_Ds_tau = 6,
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
      B, Ds, D, e, mu, tau, nu, gamma, other, null = -1,
    };

    Symbol LundToSymbol(int lund) const;
    void PopulateBSLDict();

  private:
    trie<Symbol, BSemiLepCode, Symbol::null, BSemiLepCode::null> bsl_dict_;

};

#endif
