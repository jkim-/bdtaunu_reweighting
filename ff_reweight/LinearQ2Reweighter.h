#ifndef __LINEARQ2REWEIGHTER_H__
#define __LINEARQ2REWEIGHTER_H__

#include "BToDlnuMode.h"
#include "BToDslnuMode.h"

class LinearQ2Reweighter {

  public: 

    LinearQ2Reweighter();
    ~LinearQ2Reweighter() {};

    double compute_bdlnu_linearq2_weights(const BToDlnuMode&) const;
    double compute_bdslnu_linearq2_weights(const BToDslnuMode&) const;

  private:
    double ReweightBDlnu(
        const BToDlnuMode&, std::string, std::string) const;
    double ReweightBDslnu(
        const BToDslnuMode&, bool, bool, std::string, std::string) const;
};

#endif
