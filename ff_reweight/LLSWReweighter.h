#ifndef __LLSWREWEIGHTER_H__
#define __LLSWREWEIGHTER_H__

#include "BToDsslnuMode.h"

class LLSWReweighter {

  public: 

    LLSWReweighter();
    ~LLSWReweighter() {};

    double compute_bdsslnu_llswb1_weights(const BToDsslnuMode&) const;
    double compute_bdsslnu_llswb2_weights(const BToDsslnuMode&) const;

};

#endif
