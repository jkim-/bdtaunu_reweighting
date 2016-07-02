#ifndef __LLSWREWEIGHTER_H__
#define __LLSWREWEIGHTER_H__

#include <BDss0lnuDecayRate.h>
#include <BD1lnuDecayRate.h>
#include <BD2lnuDecayRate.h>
#include <BD1primelnuDecayRate.h>

#include "BToDsslnuMode.h"

class LLSWReweighter {

  public: 

    LLSWReweighter();
    ~LLSWReweighter() {};

    double compute_bdsslnu_llswb1_weights(const BToDsslnuMode&, double) const;
    double compute_bdsslnu_llswb2_weights(const BToDsslnuMode&, double) const;

  private:

    BDss0lnuDecayRate BcD0ss0enu_from_, BcD0ss0enu_llswb1_, BcD0ss0enu_llswb2_; 
    BDss0lnuDecayRate BcD0ss0munu_from_, BcD0ss0munu_llswb1_, BcD0ss0munu_llswb2_; 
    BDss0lnuDecayRate BcD0ss0taunu_from_, BcD0ss0taunu_llswb1_, BcD0ss0taunu_llswb2_; 
    BDss0lnuDecayRate B0D0sscenu_from_, B0D0sscenu_llswb1_, B0D0sscenu_llswb2_; 
    BDss0lnuDecayRate B0D0sscmunu_from_, B0D0sscmunu_llswb1_, B0D0sscmunu_llswb2_; 
    BDss0lnuDecayRate B0D0ssctaunu_from_, B0D0ssctaunu_llswb1_, B0D0ssctaunu_llswb2_; 

    BD1lnuDecayRate BcD10enu_from_, BcD10enu_llswb1_, BcD10enu_llswb2_;
    BD1lnuDecayRate BcD10munu_from_, BcD10munu_llswb1_, BcD10munu_llswb2_;
    BD1lnuDecayRate BcD10taunu_from_, BcD10taunu_llswb1_, BcD10taunu_llswb2_;
    BD1lnuDecayRate B0D1cenu_from_, B0D1cenu_llswb1_, B0D1cenu_llswb2_;
    BD1lnuDecayRate B0D1cmunu_from_, B0D1cmunu_llswb1_, B0D1cmunu_llswb2_;
    BD1lnuDecayRate B0D1ctaunu_from_, B0D1ctaunu_llswb1_, B0D1ctaunu_llswb2_;

    BD2lnuDecayRate BcD20enu_from_, BcD20enu_llswb1_, BcD20enu_llswb2_;
    BD2lnuDecayRate BcD20munu_from_, BcD20munu_llswb1_, BcD20munu_llswb2_;
    BD2lnuDecayRate BcD20taunu_from_, BcD20taunu_llswb1_, BcD20taunu_llswb2_;
    BD2lnuDecayRate B0D2cenu_from_, B0D2cenu_llswb1_, B0D2cenu_llswb2_;
    BD2lnuDecayRate B0D2cmunu_from_, B0D2cmunu_llswb1_, B0D2cmunu_llswb2_;
    BD2lnuDecayRate B0D2ctaunu_from_, B0D2ctaunu_llswb1_, B0D2ctaunu_llswb2_;

    BD1primelnuDecayRate BcD1prime0enu_from_, BcD1prime0enu_llswb1_, BcD1prime0enu_llswb2_;
    BD1primelnuDecayRate BcD1prime0munu_from_, BcD1prime0munu_llswb1_, BcD1prime0munu_llswb2_;
    BD1primelnuDecayRate BcD1prime0taunu_from_, BcD1prime0taunu_llswb1_, BcD1prime0taunu_llswb2_;
    BD1primelnuDecayRate B0D1primecenu_from_, B0D1primecenu_llswb1_, B0D1primecenu_llswb2_;
    BD1primelnuDecayRate B0D1primecmunu_from_, B0D1primecmunu_llswb1_, B0D1primecmunu_llswb2_;
    BD1primelnuDecayRate B0D1primectaunu_from_, B0D1primectaunu_llswb1_, B0D1primectaunu_llswb2_;

};

#endif
