#ifndef __BTODLNUMODE_H__ 
#define __BTODLNUMODE_H__ 

#include <CLHEP/Vector/LorentzVector.h>

#include <BXlnuKin.h>

class BToDlnuMode {

  public:

    BToDlnuMode();

    BToDlnuMode(
        int Blund, int Xlund, int Leplund,
        CLHEP::HepLorentzVector BLab, 
        CLHEP::HepLorentzVector XLab, 
        CLHEP::HepLorentzVector LepLab
    );

    int Blund() const { return Blund_; }
    int Xlund() const { return Xlund_; }
    int Leplund() const { return Leplund_; }
    double q2() const { return kin_.q2(); }
    double ctl() const { return kin_.ctl(); }
    double w() const { return kin_.w(); }
    const CLHEP::HepLorentzVector &BLab() const { return kin_.BLab(); }
    const CLHEP::HepLorentzVector &XLab() const { return kin_.XLab(); }
    const CLHEP::HepLorentzVector &LepLab() const { return kin_.LepB(); }
    const CLHEP::HepLorentzVector &LepB() const { return kin_.LepB(); }

    virtual ~BToDlnuMode() {};

  private:
    int Blund_;
    int Xlund_;
    int Leplund_;
    BXlnuKin kin_;
};

#endif
