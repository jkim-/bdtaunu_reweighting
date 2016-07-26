#ifndef __BDSS0FF_H__
#define __BDSS0FF_H__

// The interface assumes form factor parametrizations applicable to 
// approximation B of LLSW.

class BDss0FF {
  public: 
    virtual ~BDss0FF() {};
    virtual BDss0FF* clone() = 0;
    virtual void compute_ff(double q2, double &gp, double &gm) const = 0;
};

class ISGW2BDss0FF : public BDss0FF {
  public: 
    ISGW2BDss0FF(double mB, double mDss);
    ~ISGW2BDss0FF();
    BDss0FF* clone();
    void compute_ff(double q2, double &gp, double &gm) const;

  private:
    double mB_;
    double mDss_;
};

class LLSWBDss0FF : public BDss0FF {
  public: 
    LLSWBDss0FF(double mB, double mDss, bool isApproxB1=true, double tau_1=-1.5);
    ~LLSWBDss0FF();
    BDss0FF* clone();
    void compute_ff(double q2, double &gp, double &gm) const;

  private:
    double mB_;
    double mDss_;
    bool isApproxB1_;
    double tau_1_;
    double tau_1_org_;
};

#endif
