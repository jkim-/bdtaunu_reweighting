#include <cmath> 
#include <cstdlib> 

#include <ff_reweight_constants.h>
#include "BD1FF.h"

namespace {

double EvtGetas( double massq, double massx ) {

  double lqcd2 = 0.04;
  double nflav = 4;
  double temp = 0.6;
  
  if ( massx > 0.6 ) {
    if ( massq < 1.85 ) {
      nflav = 3.0;}
    
    temp = 12.0*PI / ( 33.0 - 2.0*nflav) /
      log( massx*massx/lqcd2);
  }
  return temp;
  
}


inline double get_tau_1_org_D1(bool isApproxB1) {
  return isApproxB1 ? 0.71 : 0.75;
}

}

ISGW2BD1FF::ISGW2BD1FF(double mB, double mDss) 
  : mB_(mB), mDss_(mDss) {}

ISGW2BD1FF::~ISGW2BD1FF() {}

BD1FF* ISGW2BD1FF::clone() {
  return new ISGW2BD1FF(mB_, mDss_);
}

void ISGW2BD1FF::compute_ff(double q2,
    double &fA, double &fV1, double &fV3rfV2) const {
  compute_ff(q2, mDss_, fA, fV1, fV3rfV2);
}

void ISGW2BD1FF::compute_ff(double q2, double mDss,
    double &fA, double &fV1, double &fV3rfV2) const {

  double mB = mB_;
  double mD = mDss;
   
  // Get R
  double mcR = 2.0*sqrt(mB*mD) / (mB+mD);
  // Get r
  double r = mD/mB;

  // Get FF
  double t=q2;
  double mass=mD;
  double rf, vf, spf, smf;

  double mtb, mbb;
  double msd, mx,mb,nf,nfp;
  double msq,bx2,mbx,mtx;
  double f5sppsm,f5spmsm,f5;
  double f5v,f5r,mup,mum,vv,rr,spmsm,sppsm;
  double mqm,msb,bb2,bbx2,tm,wt,r2;

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
    log(EvtGetas(mqm,mqm)/EvtGetas(msq,msq));
  
  f5 = sqrt(mtx/mtb)*pow(sqrt(bx2*bb2)/bbx2,5.0/2.0) /
    (pow((1.0+r2*(tm-t)/18.0),3.0));
  
  f5v = f5*pow(( mbb / mtb ),-0.5)*pow((mbx/mtx),-0.5);
  f5r = f5*pow(( mbb / mtb ),0.5)*pow((mbx/mtx),0.5);
  f5sppsm = f5*pow(( mbb / mtb ),-1.5)*pow((mbx/mtx),0.5);
  f5spmsm = f5*pow(( mbb / mtb ),-0.5)*pow((mbx/mtx),-0.5);
  
  if (msq == msd) { 
    vv = f5v*(((mtb*sqrt(bb2))/(4.0*sqrt(2.0)*msb*msq*mtx)) +
              (((wt-1)*msd)/(6.0*sqrt(2.0*bb2)*mtx)));
    
    rr = f5r*mtb*sqrt(bb2/2)*((1.0/mup)+((msd*mtx*(wt-1)*(wt-1))/
				 (3.0*msq*bb2)));
    
    sppsm = msd*f5sppsm/(sqrt(2.0*bb2)*mtb)*(1.0-(msd/msq)+((msd*bb2)/
				    (2.0*mup*bbx2)));
    
    spmsm = msd*f5spmsm/(sqrt(2.0*bb2)*msq)*(((4-wt)/3.0)- ( (msd*msq*bb2)/
				     (2.0*mtx*mup*bbx2)));
    
  } else {
    vv = -1.0*msd*f5v/(2.0*sqrt(3.0*bb2)*mtx)*
      ((wt+1)/2.0+bb2*mtb/(2.0*msd*msq*msb));
    
    rr = -2.0*mtb*sqrt(bb2/3.0)*f5r*(1.0/msq + mtx*msd*(wt-1)/(2.0*bb2)*
		     ((wt+1)/(2.0*msq)-msd*bb2/(2.0*mum*mtx*bbx2)));
    
    sppsm = -1.0*sqrt(3.0)*msd*f5sppsm/(2.0*sqrt(bb2)*mtb)*(1 - msd/(3.0*msq) -
			    msd*bb2/(3.0*bbx2)*(1.0/(2.0*mum)-1.0/mup));
    
    spmsm = -1.0*msd*f5spmsm/(2.0*sqrt(3.0*bb2)*mtx)*((2-wt)*mtx/msq +
			   msd*bb2/bbx2*(1.0/(2.0*mum)-1.0/mup));        

  }


  vf = vv;
  rf = rr;
  spf = (sppsm + spmsm)/2.0;
  smf = (sppsm - spmsm)/2.0;

  double conv = mcR * mB * (1.0 + r);
  fA = -conv * vf;
  fV1 = 2.0 * rf / conv;
  fV3rfV2 = conv * spf;

}

LLSWBD1FF::LLSWBD1FF(double mB, double mDss, bool isApproxB1, double tau_1)
  : mB_(mB), mDss_(mDss), isApproxB1_(isApproxB1), tau_1_(tau_1) {
  tau_1_org_ = get_tau_1_org_D1(isApproxB1);
}

LLSWBD1FF::~LLSWBD1FF() {}

BD1FF* LLSWBD1FF::clone() {
  return new LLSWBD1FF(mB_, mDss_, isApproxB1_, tau_1_);
}


void LLSWBD1FF::compute_ff(double q2, 
    double &fA, double &fV1, double &fV3rfV2) const {
  compute_ff(q2, mDss_, fA, fV1, fV3rfV2);
}


void LLSWBD1FF::compute_ff(double q2, double mDss,
    double &fA, double &fV1, double &fV3rfV2) const {
 
  double trueW = (mB_*mB_+mDss*mDss-q2)/(2*mB_*mDss);
  double tau_1_org = tau_1_org_;
  double mB = mB_;
  double mD = mDss;

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
  double r6 = sqrt(6.0);
  //cout << "r6 = " << r6 << endl;
  
  double r6fA_t1 = -(trueW+1.0)*tau;
  double r6fA_t2  
    = -e_b*(trueW-1.0)*((Lambda_p+Lambda)*tau - (2.0*trueW+1.0)*tau1 - tau2);
  double r6fA_t3 
    = -e_c*(4.0*(trueW*Lambda_p-Lambda)*tau - 3.0*(trueW-1.0)*(tau1-tau2));
  double r6fA = r6fA_t1 + r6fA_t2 + r6fA_t3;
  fA = r6fA/r6;
  //cout << "fA = " << fA << endl;
  
  double r6fV1_t1 = (1.0-trueW*trueW)*tau;
  double r6fV1_t2  
    = -e_b*(trueW*trueW-1.0)*((Lambda_p+Lambda)*tau 
			      - (2.0*trueW+1.0)*tau1 - tau2);
  double r6fV1_t3 
    = -e_c*(4.0*(trueW+1.0)*(trueW*Lambda_p-Lambda)*tau 
	    - 3.0*(trueW*trueW-1.0)*(tau1-tau2));
  double r6fV1 = r6fV1_t1 + r6fV1_t2 + r6fV1_t3;
  fV1 = r6fV1/r6;
  
  double r6fV2_t1 = -3.0*tau;
  double r6fV2_t2 
    = -3.0*e_b*((Lambda_p+Lambda)*tau - (2.0*trueW+1.0)*tau1 - tau2);
  double r6fV2_t3 = -e_c*((4.0*trueW-1.0)*tau1 + 5.0*tau2);
  double r6fV2 = r6fV2_t1 + r6fV2_t2 + r6fV2_t3;
  double fV2 = r6fV2/r6;
  
  double r6fV3_t1 = (trueW-2.0)*tau;
  double r6fV3_t2  
    = e_b*(trueW+2.0)*((Lambda_p+Lambda)*tau - (2.0*trueW+1.0)*tau1 - tau2);
  double r6fV3_t3 
    = e_c*(4.0*(trueW*Lambda_p-Lambda)*tau 
	   + (trueW+2.0)*tau1 + (3.0*trueW+2.0)*tau2);
  double r6fV3 = r6fV3_t1 + r6fV3_t2 + r6fV3_t3;
  double fV3 = r6fV3/r6;
  //cout << "fV3 = " << fV3 << endl;
    
  // calculate FF
  fV3rfV2 = fV3 + r * fV2;

}

