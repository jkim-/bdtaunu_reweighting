#ifndef __BTODLNUMODE_H__ 
#define __BTODLNUMODE_H__ 

#include "ff_reweight_defs.h"
#include "DecayMode.h"

class BToDlnuMode : public DecayMode {

  public:

    BToDlnuMode();

    BToDlnuMode(
        double e_B, double p3mag_B, double costh_B, double phi_B, 
        double e_X, double p3mag_X, double costh_X, double phi_X, 
        double e_Lep, double p3mag_Lep, double costh_Lep, double phi_Lep,
        double ecm_Lep
    );

    HepLorentzVector get_BLab() { return BLab_; }
    HepLorentzVector get_XLab() { return XLab_; }
    HepLorentzVector get_LepLab() { return LepLab_; }
    double get_ecmLep() { return ecmLep_; }

    virtual ~BToDlnuMode() {};

  private:
    HepLorentzVector BLab_;
    HepLorentzVector XLab_;
    HepLorentzVector LepLab_;

    double ecmLep_;
};

#endif
