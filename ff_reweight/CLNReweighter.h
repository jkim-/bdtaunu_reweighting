#ifndef __CLNREWEIGHTER_H__
#define __CLNREWEIGHTER_H__

#include "BToDlnuMode.h"
#include "BToDslnuMode.h"

class CLNReweighter {

  public: 

    CLNReweighter();
    ~CLNReweighter() {};

    double compute_bdlnu_cln_weights(const BToDlnuMode&) const;
    double compute_bdslnu_cln_weights(const BToDslnuMode&) const;

  private:
    double ReweightBDlnu(
        const BToDlnuMode&, std::string, std::string) const; 
    double ReweightBDslnu(
        const BToDslnuMode&, bool, bool, std::string, std::string) const; 
};

#endif
