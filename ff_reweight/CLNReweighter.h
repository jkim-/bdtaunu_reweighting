#ifndef __CLNREWEIGHTER_H__
#define __CLNREWEIGHTER_H__

#include <CLNParams.h>

#include "BToDlnuMode.h"
#include "BToDslnuMode.h"

class CLNReweighter {

  public: 

    CLNReweighter();
    ~CLNReweighter() {};

    double compute_bdlnu_cln_weights(const BToDlnuMode &m) const {
      return compute_bdlnu_cln_weights(m, CLNParams());
    }
    double compute_bdlnu_cln_weights(const BToDlnuMode&, const CLNParams&) const;


    double compute_bdslnu_cln_weights(const BToDslnuMode &m) const {
      return compute_bdslnu_cln_weights(m, CLNParams());
    }
    double compute_bdslnu_cln_weights(const BToDslnuMode&, const CLNParams&) const;

  private:
    double ReweightBDlnu(
        const BToDlnuMode&, const CLNParams&, std::string) const; 
    double ReweightBDslnu(
        const BToDslnuMode&, bool, bool, const CLNParams&, std::string) const; 
};

#endif
