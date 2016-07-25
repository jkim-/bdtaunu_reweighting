#ifndef __BD2FF_H__
#define __BD2FF_H__

// The interface assumes form factor parametrizations applicable to 
// approximation B of LLSW.

class BD2FF {
  public: 
    virtual ~BD2FF() {};
    virtual BD2FF* clone() = 0;
    virtual void compute_ff(double q2, 
        double &kV, double &kA1, double &kA3rkA2) const = 0;
    virtual void compute_ff(double q2, double mDss, 
        double &kV, double &kA1, double &kA3rkA2) const = 0;
};

class ISGW2BD2FF : public BD2FF {
  public: 
    ISGW2BD2FF(double mB, double mDss);
    ~ISGW2BD2FF();
    BD2FF* clone();
    void compute_ff(double q2, 
        double &kV, double &kA1, double &kA3rkA2) const;
    void compute_ff(double q2, double mDss,
        double &kV, double &kA1, double &kA3rkA2) const;

  private:
    double mB_;
    double mDss_;
};

class LLSWBD2FF : public BD2FF {
  public: 
    LLSWBD2FF(double mB, double mDss, 
        bool isApproxB1=true, double tau_1=-1.5);
    ~LLSWBD2FF();
    BD2FF* clone();
    void compute_ff(double q2, 
        double &kV, double &kA1, double &kA3rkA2) const;
    void compute_ff(double q2, double mDss,
        double &kV, double &kA1, double &kA3rkA2) const;

  private:
    double mB_;
    double mDss_;
    bool isApproxB1_;
    double tau_1_;
    double tau_1_org_;
};

#endif
