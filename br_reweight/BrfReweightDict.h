#ifndef __BRFREWEIGHTDICT_H__
#define __BRFREWEIGHTDICT_H__

#include <vector>

#include <trie.h>

enum class BrfReweightCode {
  // Decay modes to be corrected
  // Bc:
  Bp_Dstar0_mu_nu = 1,
  Bp_Dstar0_e_nu = 2,
  Bp_D0_mu_nu = 3,
  Bp_D0_e_nu = 4,
  Bp_Dsstarp_Dstar0 = 5,
  Bp_Dstar0_tau_nu = 6,
  Bp_Dsp_D0 = 7,
  Bp_Dsp_Dstar0 = 8,
  Bp_D0_tau_nu = 9,
  Bp_Dsstarp_D0 = 10,
  Bp_D0_rhop = 11,
  Bp_Dstar0_a1p = 12,
  Bp_Dstarp_pip_pip_pi0 = 13,
  Bp_D0_a1p = 14,
  // B0:
  B0_Dstarp_mu_nu = 15,
  B0_Dstarp_e_nu = 16,
  B0_Dp_mu_nu = 17,
  B0_Dp_e_nu = 18,
  B0_Dsstarp_Dstarp = 19,
  B0_Dstarp_tau_nu = 20,
  B0_Dsp_Dstarp = 21,
  B0_Dstarp_Dstar0_Kp = 22,
  B0_Dsstarp_Dp = 23,
  B0_Dstarp_a1p = 24,
  B0_Dp_tau_nu = 25,
  B0_Dsp_Dp = 26,
  B0_Dstar0_Dp_Kp = 27,
  B0_Dstarp_Dstarp_K0 = 28,
  B0_Dp_rhop = 29,
  B0_Ds1p_Dstarp = 30,

  // Decay modes to be fluctuated
  // Bc:
  Bp_D10_e_nu = 31,
  Bp_D0star0_e_nu = 32,
  Bp_D2star0_e_nu = 33,
  Bp_D1prime0_e_nu = 34,
  Bp_Dstarp_pip_e_nu = 35,
  Bp_Dp_pip_e_nu = 36,
  Bp_Dstar0_pi0_e_nu = 37,
  Bp_D0_pi0_e_nu = 38,
  Bp_D10_mu_nu = 39,
  Bp_D0star0_mu_nu = 40,
  Bp_D2star0_mu_nu = 41,
  Bp_D1prime0_mu_nu = 42,
  Bp_Dstarp_pip_mu_nu = 43,
  Bp_Dp_pip_mu_nu = 44,
  Bp_Dstar0_pi0_mu_nu = 45,
  Bp_D0_pi0_mu_nu = 46,
  Bp_D10_tau_nu = 47,
  Bp_D0star0_tau_nu = 48,
  Bp_D2star0_tau_nu = 49,
  Bp_D1prime0_tau_nu = 50,
  // B0:
  B0_D1p_e_nu = 51,
  B0_D0starp_e_nu = 52,
  B0_D2starp_e_nu = 53,
  B0_D1primep_e_nu = 54,
  B0_Dstarp_pi0_e_nu = 55,
  B0_Dp_pi0_e_nu = 56,
  B0_Dstar0_pip_e_nu = 57,
  B0_D0_pip_e_nu = 58,
  B0_D1p_mu_nu = 59,
  B0_D0starp_mu_nu = 60,
  B0_D2starp_mu_nu = 61,
  B0_D1primep_mu_nu = 62,
  B0_Dstarp_pi0_mu_nu = 63,
  B0_Dp_pi0_mu_nu = 64,
  B0_Dstar0_pip_mu_nu = 65,
  B0_D0_pip_mu_nu = 66,
  B0_D1p_tau_nu = 67,
  B0_D0starp_tau_nu = 68,
  B0_D2starp_tau_nu = 69,
  B0_D1primep_tau_nu = 70,
  null = -1
};

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
