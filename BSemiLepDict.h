#ifndef __BSEMILEPDICT_H__
#define __BSEMILEPDICT_H__

#include <vector>

#include <trie.h>

enum class BSemiLepCode {
  Bc_D0_e = 1,
  Bc_D0_mu = 2,
  Bc_D0_tau = 3,
  Bc_Dstar0_e = 4,
  Bc_Dstar0_mu = 5,
  Bc_Dstar0_tau = 6,
  B0_Dc_e = 7,
  B0_Dc_mu = 8,
  B0_Dc_tau = 9,
  B0_Dstarc_e = 10,
  B0_Dstarc_mu = 11,
  B0_Dstarc_tau = 12,
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
      Bc, B0, Dstarc, Dstar0, Dc, D0, 
      e, mu, tau, nu, gamma, other, null = -1,
    };

    Symbol LundToSymbol(int lund) const;
    void PopulateBSLDict();

  private:
    trie<Symbol, BSemiLepCode, Symbol::null, BSemiLepCode::null> bsl_dict_;

};

#endif
