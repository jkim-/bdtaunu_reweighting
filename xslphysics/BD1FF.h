#ifndef __BD1FF_H__
#define __BD1FF_H__

// The interface assumes form factor parametrizations applicable to 
// approximation B of LLSW.

class BD1FF {
  public: 
    virtual ~BD1FF() {};
    virtual BD1FF* clone() = 0;
    virtual void compute_ff(double q2, 
        double &fA, double &fV1, double &fV3rfV2) const = 0;
};

class ISGW2BD1FF : public BD1FF {
  public: 
    ISGW2BD1FF(double mB, double mDss);
    ~ISGW2BD1FF();
    BD1FF* clone();
    void compute_ff(double q2, 
        double &fA, double &fV1, double &fV3rfV2) const;
    void compute_ff(double q2, double mDss,
        double &fA, double &fV1, double &fV3rfV2) const;

  private:
    double mB_;
    double mDss_;
};

class LLSWBD1FF : public BD1FF {
  public: 
    LLSWBD1FF(double mB, double mDss, 
        bool isApproxB1=true, double tau_1=-1.5);
    ~LLSWBD1FF();
    BD1FF* clone();
    void compute_ff(double q2, 
        double &fA, double &fV1, double &fV3rfV2) const;
    void compute_ff(double q2, double mDss, 
        double &fA, double &fV1, double &fV3rfV2) const;

  private:
    double mB_;
    double mDss_;
    bool isApproxB1_;
    double tau_1_;
    double tau_1_org_;
};

#endif
