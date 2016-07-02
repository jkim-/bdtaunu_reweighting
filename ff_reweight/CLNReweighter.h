#ifndef __CLNREWEIGHTER_H__
#define __CLNREWEIGHTER_H__

#include <BPlnuDecayRate.h>
#include <BVlnuDecayRate.h>
#include "BToDlnuMode.h"
#include "BToDslnuMode.h"

class CLNReweighter {

  public: 

    CLNReweighter();
    ~CLNReweighter() {};

    double compute_bdlnu_cln_weights(const BToDlnuMode&, double) const ;
    double compute_bdslnu_cln_weights(const BToDslnuMode&, double) const ;
    double compute_bdslnu_cln_weights(const BToDslnuMode&, 
        double, double, double, double) const;

  private:

    BPlnuDecayRate BcDenu_from_, BcDenu_to_;
    BPlnuDecayRate BcDmunu_from_, BcDmunu_to_;
    BPlnuDecayRate BcDtaunu_from_, BcDtaunu_to_;
    BPlnuDecayRate B0Denu_from_, B0Denu_to_;
    BPlnuDecayRate B0Dmunu_from_, B0Dmunu_to_;
    BPlnuDecayRate B0Dtaunu_from_, B0Dtaunu_to_;

    BVlnuDecayRate BcDsenu_Dpi_lm_from_, BcDsenu_Dpi_lm_to_;
    BVlnuDecayRate BcDsmunu_Dpi_lm_from_, BcDsmunu_Dpi_lm_to_;
    BVlnuDecayRate BcDstaunu_Dpi_lm_from_, BcDstaunu_Dpi_lm_to_;
    BVlnuDecayRate B0Dsenu_Dpi_lm_from_, B0Dsenu_Dpi_lm_to_;
    BVlnuDecayRate B0Dsmunu_Dpi_lm_from_, B0Dsmunu_Dpi_lm_to_;
    BVlnuDecayRate B0Dstaunu_Dpi_lm_from_, B0Dstaunu_Dpi_lm_to_;

    BVlnuDecayRate BcDsenu_Dgamma_lm_from_, BcDsenu_Dgamma_lm_to_;
    BVlnuDecayRate BcDsmunu_Dgamma_lm_from_, BcDsmunu_Dgamma_lm_to_;
    BVlnuDecayRate BcDstaunu_Dgamma_lm_from_, BcDstaunu_Dgamma_lm_to_;
    BVlnuDecayRate B0Dsenu_Dgamma_lm_from_, B0Dsenu_Dgamma_lm_to_;
    BVlnuDecayRate B0Dsmunu_Dgamma_lm_from_, B0Dsmunu_Dgamma_lm_to_;
    BVlnuDecayRate B0Dstaunu_Dgamma_lm_from_, B0Dstaunu_Dgamma_lm_to_;

    BVlnuDecayRate BcDsenu_Dpi_lp_from_, BcDsenu_Dpi_lp_to_;
    BVlnuDecayRate BcDsmunu_Dpi_lp_from_, BcDsmunu_Dpi_lp_to_;
    BVlnuDecayRate BcDstaunu_Dpi_lp_from_, BcDstaunu_Dpi_lp_to_;
    BVlnuDecayRate B0Dsenu_Dpi_lp_from_, B0Dsenu_Dpi_lp_to_;
    BVlnuDecayRate B0Dsmunu_Dpi_lp_from_, B0Dsmunu_Dpi_lp_to_;
    BVlnuDecayRate B0Dstaunu_Dpi_lp_from_, B0Dstaunu_Dpi_lp_to_;

    BVlnuDecayRate BcDsenu_Dgamma_lp_from_, BcDsenu_Dgamma_lp_to_;
    BVlnuDecayRate BcDsmunu_Dgamma_lp_from_, BcDsmunu_Dgamma_lp_to_;
    BVlnuDecayRate BcDstaunu_Dgamma_lp_from_, BcDstaunu_Dgamma_lp_to_;
    BVlnuDecayRate B0Dsenu_Dgamma_lp_from_, B0Dsenu_Dgamma_lp_to_;
    BVlnuDecayRate B0Dsmunu_Dgamma_lp_from_, B0Dsmunu_Dgamma_lp_to_;
    BVlnuDecayRate B0Dstaunu_Dgamma_lp_from_, B0Dstaunu_Dgamma_lp_to_;
};

#endif
