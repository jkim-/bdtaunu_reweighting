#ifndef __BTODSSLNUMODE_H__ 
#define __BTODSSLNUMODE_H__ 

#include <CLHEP/Vector/LorentzVector.h>

#include <BXlnuKin.h>

enum class BToDsslnuType {
  Bc_D0ss0_e = 1,
  Bc_D0ss0_mu,
  Bc_D0ss0_tau,
  B0_D0ssc_e,
  B0_D0ssc_mu,
  B0_D0ssc_tau,
  Bc_D10_e,
  Bc_D10_mu,
  Bc_D10_tau,
  B0_D1c_e,
  B0_D1c_mu,
  B0_D1c_tau,
  Bc_D20_e,
  Bc_D20_mu,
  Bc_D20_tau,
  B0_D2c_e,
  B0_D2c_mu,
  B0_D2c_tau,
  Bc_D1prime0_e,
  Bc_D1prime0_mu,
  Bc_D1prime0_tau,
  B0_D1primec_e,
  B0_D1primec_mu,
  B0_D1primec_tau,
  null = -1
};

class BToDsslnuMode {

  public:

    BToDsslnuMode();

    BToDsslnuMode(
        int Blund, int Xlund, int Leplund, 
        CLHEP::HepLorentzVector BLab, 
        CLHEP::HepLorentzVector XLab, 
        CLHEP::HepLorentzVector LepLab
    );

    BToDsslnuType bdsslnu_type() const { return bdsslnu_type_; }
    int Blund() const { return Blund_; }
    int Xlund() const { return Xlund_; }
    int Leplund() const { return Leplund_; }

    double q2() const { return kin_.q2(); }
    double ctl() const { return kin_.ctl(); }
    double w() const { return kin_.w(); }

    const CLHEP::HepLorentzVector &BLab() const { return kin_.BLab(); }
    const CLHEP::HepLorentzVector &XLab() const { return kin_.XLab(); }
    const CLHEP::HepLorentzVector &LepLab() const { return kin_.LepLab(); }
    const CLHEP::HepLorentzVector &LepB() const { return kin_.LepB(); }

    virtual ~BToDsslnuMode() {};

  private:
    int Blund_;
    int Xlund_;
    int Leplund_;
    BXlnuKin kin_;
    BToDsslnuType bdsslnu_type_;
};

#endif
