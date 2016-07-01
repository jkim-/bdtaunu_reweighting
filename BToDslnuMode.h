#ifndef __BTODSLNUMODE_H__ 
#define __BTODSLNUMODE_H__ 

#include <CLHEP/Vector/LorentzVector.h>

#include <BVlnuKin.h>

enum class BToDslnuType {

  Bc_Dstar0_e_Dpi_lminus = 1,
  Bc_Dstar0_mu_Dpi_lminus,
  Bc_Dstar0_tau_Dpi_lminus,
  B0_Dstarc_e_Dpi_lminus,
  B0_Dstarc_mu_Dpi_lminus,
  B0_Dstarc_tau_Dpi_lminus,

  Bc_Dstar0_e_Dgamma_lminus,
  Bc_Dstar0_mu_Dgamma_lminus,
  Bc_Dstar0_tau_Dgamma_lminus,
  B0_Dstarc_e_Dgamma_lminus,
  B0_Dstarc_mu_Dgamma_lminus,
  B0_Dstarc_tau_Dgamma_lminus,

  Bc_Dstar0_e_Dpi_lplus,
  Bc_Dstar0_mu_Dpi_lplus,
  Bc_Dstar0_tau_Dpi_lplus,
  B0_Dstarc_e_Dpi_lplus,
  B0_Dstarc_mu_Dpi_lplus,
  B0_Dstarc_tau_Dpi_lplus,

  Bc_Dstar0_e_Dgamma_lplus,
  Bc_Dstar0_mu_Dgamma_lplus,
  Bc_Dstar0_tau_Dgamma_lplus,
  B0_Dstarc_e_Dgamma_lplus,
  B0_Dstarc_mu_Dgamma_lplus,
  B0_Dstarc_tau_Dgamma_lplus,

  null = -1
};

class BToDslnuMode {

  public:

    BToDslnuMode();

    BToDslnuMode(
        int Blund, int Xlund, int Leplund, 
        int Xdaulund, int Softdaulund,
        CLHEP::HepLorentzVector BLab, 
        CLHEP::HepLorentzVector XLab, 
        CLHEP::HepLorentzVector LepLab,
        CLHEP::HepLorentzVector XdauLab
    );

    BToDslnuType bdslnu_type() const { return bdslnu_type_; }
    int Blund() const { return Blund_; }
    int Xlund() const { return Xlund_; }
    int Leplund() const { return Leplund_; }
    int Xdaulund() const { return Xdaulund_; }
    int Softdaulund() const { return Softdaulund_; }

    double q2() const { return kin_.q2(); }
    double ctl() const { return kin_.ctl(); }
    double w() const { return kin_.w(); }
    double ctv() const { return kin_.ctv(); }
    double chi() const { return kin_.chi(); }

    const CLHEP::HepLorentzVector &BLab() const { return kin_.BLab(); }
    const CLHEP::HepLorentzVector &XLab() const { return kin_.XLab(); }
    const CLHEP::HepLorentzVector &LepLab() const { return kin_.LepB(); }
    const CLHEP::HepLorentzVector &LepB() const { return kin_.LepB(); }
    const CLHEP::HepLorentzVector &XdauLab() const { return kin_.XdauLab(); }

    virtual ~BToDslnuMode() {};

  private:
    int Blund_;
    int Xlund_;
    int Leplund_;
    int Xdaulund_;
    int Softdaulund_;
    BVlnuKin kin_;
    BToDslnuType bdslnu_type_;
};

#endif
