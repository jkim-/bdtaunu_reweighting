#ifndef __BD1PRIMEFF_H__
#define __BD1PRIMEFF_H__

// The interface assumes form factor parametrizations applicable to 
// approximation B of LLSW.

class BD1primeFF {
  public: 
    virtual ~BD1primeFF() {};
    virtual BD1primeFF* clone() = 0;
    virtual void compute_ff(double q2, 
        double &gA, double &gV1, double &gV3rgV2) const = 0;
};

class ISGW2BD1primeFF : public BD1primeFF {
  public: 
    ISGW2BD1primeFF(double mB, double mDss);
    ~ISGW2BD1primeFF();
    BD1primeFF* clone();
    void compute_ff(double q2, 
        double &gA, double &gV1, double &gV3rgV2) const;

  private:
    double mB_;
    double mDss_;
};

class LLSWBD1primeFF : public BD1primeFF {
  public: 
    LLSWBD1primeFF(double mB, double mDss, 
        bool isApproxB1=true, double tau_1=-1.5);
    ~LLSWBD1primeFF();
    BD1primeFF* clone();
    void compute_ff(double q2, 
        double &gA, double &gV1, double &gV3rgV2) const;

  private:
    double mB_;
    double mDss_;
    bool isApproxB1_;
    double tau_1_;
    double tau_1_org_;
};

#endif
