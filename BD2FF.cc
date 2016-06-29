#include <cmath> 
#include <cstdlib> 

#include "ff_reweight_defs.h"
#include "BD2FF.h"

namespace {

double EvtGetas(double mass) {

  double lqcd2 = 0.04;
  double nflav = 4;
  double temp = 0.6;

  if ( mass > 0.6 ) {
    if ( mass < 1.85 ) {
      nflav = 3.0;}

    temp = 12.0*PI / ( 33.0 - 2.0*nflav) /
      log( mass*mass/lqcd2);
  }
  return temp;
} 


inline double get_tau_1_org_D2(bool isApproxB1) {
  return isApproxB1 ? 0.71 : 0.75;
}

}

ISGW2BD2FF::ISGW2BD2FF(double mB, double mDss) 
  : mB_(mB), mDss_(mDss) {}

ISGW2BD2FF::~ISGW2BD2FF() {}

BD2FF* ISGW2BD2FF::clone() {
  return new ISGW2BD2FF(mB_, mDss_);
}

void ISGW2BD2FF::compute_ff(double q2, 
    double &kV, double &kA1, double &kA3rkA2) const {

  double mB = mB_;
  double mD = mDss_;

  // Get R
  double mcR = 2.0*sqrt(mB*mD) / (mB+mD);
  // Get r
  double r = mD/mB;

  // Get FF
  double t=q2;
  double mass=mD;
  double hf, kf, bpf, bmf;

  double mtb, mbb;
  double msd, mx,mb,nf,nfp; 
  double msq,bx2,mbx,mtx,f5;
  double f5h,f5k,f5bppbm,f5bpmbm,bppbm,bpmbm;
  double mqm,mum,mup,tm,wt,r2,bb2,bbx2;
  double msb;

  msb=5.2;
  msd=0.33;
  bb2=0.431*0.431;
  mbb=5.31;
  nf = 4.0;

  msq=1.82;
  bx2=0.33*0.33;
  mbx=(5.0*2.46+3.0*2.42)/8.0;
  nfp = 3.0;

  mtb = msb + msd;
  mtx = msq + msd;
  mb=mB;
  mx=mass;

  mup=1.0/(1.0/msq+1.0/msb);
  mum=1.0/(1.0/msq-1.0/msb);
  bbx2=0.5*(bb2+bx2);
  tm=(mb-mx)*(mb-mx);
  if ( t>tm ) t=0.99*tm;
  wt=1.0+(tm-t)/(2.0*mbb*mbx);

  mqm = 0.1;
  r2=3.0/(4.0*msb*msq)+3*msd*msd/(2*mbb*mbx*bbx2)+
    (16.0/(mbb*mbx*(33.0-2.0*nfp)))*
    log(EvtGetas(mqm)/EvtGetas(msq));

  f5 = sqrt(mtx/mtb)*pow(sqrt(bx2*bb2)/bbx2,5.0/2.0) /
       (pow((1.0+r2*(tm-t)/18.0),3.0));
  
  f5h = f5*pow(( mbb / mtb ),-1.5)*pow((mbx/mtx),-0.5);
  f5k = f5*pow(( mbb / mtb ),-0.5)*pow((mbx/mtx),0.5);
  f5bppbm = f5*pow(( mbb / mtb ),-2.5)*pow((mbx/mtx),0.5);
  f5bpmbm = f5*pow(( mbb / mtb ),-1.5)*pow((mbx/mtx),-0.5);
  
  hf = f5h*(msd/(sqrt(8.0*bb2)*mtb))*((1.0/msq)-(msd*bb2/(2.0*mum*
        mtx*bbx2)));
  
  kf = f5k*(msd/(sqrt(2.0*bb2)))*(1.0+wt);
  
  bppbm = ((msd*msd*f5bppbm*bx2)/(sqrt(32.0*bb2)*msq*msb*mtb*bbx2))*
          (1.0-(msd*bx2/(2.0*mtb*bbx2)));

  bpmbm = -1.0*(msd*f5bpmbm/(sqrt(2.0*bb2)*msb*mtx))*(1.0-
          ((msd*msb*bx2)/(2.0*mup*mtb*bbx2))+((msd*bx2*(1.0-
          ((msd*bx2)/(2.0*mtb*bbx2))))/(4.0*msq*bbx2)));

  bpf = (bppbm + bpmbm)/2.0;
  bmf = (bppbm - bpmbm)/2.0;

  double conv = mcR * mB * (1+r);
  kV = -conv * mB * hf;
  kA1 = 2.0 * mB * kf / conv;
  kA3rkA2 = conv * mB * bpf;

}

LLSWBD2FF::LLSWBD2FF(double mB, double mDss, bool isApproxB1, double tau_1)
  : mB_(mB), mDss_(mDss), isApproxB1_(isApproxB1), tau_1_(tau_1) {
  tau_1_org_ = get_tau_1_org_D2(isApproxB1);
}

LLSWBD2FF::~LLSWBD2FF() {}

BD2FF* LLSWBD2FF::clone() {
  return new LLSWBD2FF(mB_, mDss_, isApproxB1_, tau_1_);
}


void LLSWBD2FF::compute_ff(double q2, 
    double &kV, double &kA1, double &kA3rkA2) const {
 
  double trueW = (mB_*mB_+mDss_*mDss_-q2)/(2*mB_*mDss_);
  double tau_1_org = tau_1_org_;
  double mB = mB_;
  double mD = mDss_;

  double tau_p = tau_1_;

  double r = mD/mB;

  double m_b = 4.8;
  double m_c = 1.4;
  double e_b = 1.0/(2*m_b);
  double e_c = 1.0/(2*m_c);

  double Lambda = 0.4;
  double Lambda_p = 0.39 + Lambda;
//  double Lambda_s = 0.35 + Lambda;
  
  //double Br_BD1lnu = 0.00406;
  double Br_BD1lnu = 0.0060;
  double Br_BD1lnu_org = 0.0060;
  double tau_1 = tau_1_org*sqrt(Br_BD1lnu/Br_BD1lnu_org);
  

  // functions tau, tau1 and tau2
  double tau = tau_1 * (1.0 + tau_p * (trueW - 1.0));

  double tau1 = 0.0;
  double tau2 = 0.0;
    
  if (!isApproxB1_) {
    tau1 = Lambda * tau;
    tau2 = -Lambda_p * tau;
  }
  
  // form factors
  double kV_t1 = -tau;
  double kV_t2  
    = -e_b*((Lambda_p+Lambda)*tau - (2.0*trueW+1.0)*tau1 - tau2);
  double kV_t3 = -e_c*(tau1-tau2);
  kV = kV_t1 + kV_t2 + kV_t3;
  
  double kA1_t1 = -(1.0+trueW)*tau;
  double kA1_t2  
    = -e_b*(trueW-1.0)*((Lambda_p+Lambda)*tau 
			      - (2.0*trueW+1.0)*tau1 - tau2);
  double kA1_t3 = -e_c*(trueW-1.0)*(tau1-tau2);
  kA1 = kA1_t1 + kA1_t2 + kA1_t3;
  
  double kA2 = -2.0*e_c*tau1; 
  
  double kA3_t1 = tau;
  double kA3_t2  
    = e_b*((Lambda_p+Lambda)*tau - (2.0*trueW+1.0)*tau1 - tau2);
  double kA3_t3 = -e_c*(tau1+tau2); 
  double kA3 = kA3_t1 + kA3_t2 + kA3_t3;
    
  // calculate FF
  kA3rkA2 = kA3 + r*kA2;

}

