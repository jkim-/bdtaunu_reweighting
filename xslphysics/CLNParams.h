#ifndef __CLNPARAMS_H__
#define __CLNPARAMS_H__

// default parameters based on the following:
// + HFAG 2014: arxiv hep-ex 1412.7515
// + PhysRevD 82, 034027 (2010)
// + arxiv hep-ph 1203.2654
class CLNParams {

  public: 

    CLNParams() = default;
    ~CLNParams() = default;

    void set_d_rho2(double v) { d_rho2_ = v; }
    void set_d_v11(double v) { d_v11_ = v; }
    void set_d_delta(double v) { d_delta_ = v; }
    void set_d_rho2_err(double v) { d_rho2_err_ = v; }
    void set_dstar_F1(double v) { dstar_F1_ = v; }
    void set_dstar_rho2(double v) { dstar_rho2_ = v; }
    void set_dstar_R0(double v) { dstar_R0_ = v; }
    void set_dstar_R1(double v) { dstar_R1_ = v; }
    void set_dstar_R2(double v) { dstar_R2_ = v; }
    void set_dstar_rho2_err(double v) { dstar_rho2_err_ = v; }
    void set_dstar_R1_err(double v) { dstar_R1_err_ = v; }
    void set_dstar_R2_err(double v) { dstar_R2_err_ = v; }
    void set_dstar_rho2_R1_corr(double v) { dstar_rho2_R1_corr_ = v; }
    void set_dstar_rho2_R2_corr(double v) { dstar_rho2_R2_corr_ = v; }
    void set_dstar_R1_R2_corr(double v) { dstar_R1_R2_corr_ = v; }

    double get_d_rho2() const { return d_rho2_; }
    double get_d_v11() const { return d_v11_; }
    double get_d_delta() const { return d_delta_; }
    double get_d_rho2_err() const { return d_rho2_err_; }
    double get_dstar_F1() const { return dstar_F1_; }
    double get_dstar_rho2() const { return dstar_rho2_; }
    double get_dstar_R0() const { return dstar_R0_; }
    double get_dstar_R1() const { return dstar_R1_; }
    double get_dstar_R2() const { return dstar_R2_; }
    double get_dstar_rho2_err() const { return dstar_rho2_err_; }
    double get_dstar_R1_err() const { return dstar_R1_err_; }
    double get_dstar_R2_err() const { return dstar_R2_err_; }
    double get_dstar_rho2_R1_corr() const { return dstar_rho2_R1_corr_; }
    double get_dstar_rho2_R2_corr() const { return dstar_rho2_R2_corr_; }
    double get_dstar_R1_R2_corr() const { return dstar_R1_R2_corr_; }

  private: 

    double d_rho2_ = 1.185;
    double d_v11_ = 1.0811;
    double d_delta_ = 1.0;

    double d_rho2_err_ = 0.054;


    double dstar_F1_ = 0.920;
    double dstar_rho2_ = 1.207;
    double dstar_R0_ = 1.14;
    double dstar_R1_ = 1.406;
    double dstar_R2_ = 0.853;

    double dstar_rho2_err_ = 0.026;
    double dstar_R1_err_ = 0.033;
    double dstar_R2_err_ = 0.02;

    double dstar_rho2_R1_corr_ = 0.568;
    double dstar_rho2_R2_corr_ = -0.809;
    double dstar_R1_R2_corr_ = -0.758;
};


#endif
