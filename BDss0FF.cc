#include <cmath> 
#include <cstdlib> 

#include "ff_reweight_defs.h"
#include "BDss0FF.h"

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


inline double get_tau_1_org_Dss0(bool isApproxB1) {
  return isApproxB1 ? 0.71 : 0.75;
}

}

ISGW2BDss0FF::ISGW2BDss0FF(double mB, double mDss) 
  : mB_(mB), mDss_(mDss) {}

ISGW2BDss0FF::~ISGW2BDss0FF() {}

BDss0FF* ISGW2BDss0FF::clone() {
  return new ISGW2BDss0FF(mB_, mDss_);
}

void ISGW2BDss0FF::compute_ff(double q2, double &gp, double &gm) const {

  double mB = mB_;
  double mD = mDss_;


  // Get R
  double mcR = 2*sqrt(mB*mD) / (mB+mD);

  // Get r
  double r = mD/mB;

  // Get FF
  double upf, umf;
  double mass=mD;
  double t=q2;

  double mtb, mbb;
  double msd, mx,mb,nf,nfp;
  double msq,bx2,mbx,mtx;
  double f5uppum,f5upmum,uppum,upmum,f5;
  double mqm,mum,mup,wt,r2,bb2,bbx2,msb,tm;

  msb=5.2;
  msd=0.33;
  bb2=0.431*0.431;
  mbb=5.31;
  nf = 4.0;

  msq=1.82;
  bx2=0.33*0.33;
  mbx=(3.0*2.49+2.40)/4.0;
  nfp = 3.0;

  mtb = msb + msd;
  mtx = msq + msd;
  mb=5.279;
  mx=mass;

  mup=1.0/(1.0/msq+1.0/msb);
  mum=1.0/(1.0/msq-1.0/msb);
  bbx2=0.5*(bb2+bx2);
  tm=(mb-mx)*(mb-mx);
  if ( t>tm ) t=0.99*tm;
  wt=1.0+(tm-t)/(2.0*mbb*mbx);

  mqm = 0.1;
  r2=3.0/(4.0*msb*msq)+3*msd*msd/(2*mbb*mbx*bbx2) + 
    (16.0/(mbb*mbx*(33.0-2.0*nfp)))*
    log(EvtGetas(mqm)/EvtGetas(msq));

  f5 = sqrt(mtx/mtb)*pow(sqrt(bx2*bb2)/bbx2,5.0/2.0) /
    (pow((1.0+r2*(tm-t)/18.0),3.0));

  f5uppum = f5*pow(( mbb / mtb ),-0.5)*pow((mbx/mtx),0.5);
  f5upmum = f5*pow(( mbb / mtb ),0.5)*pow((mbx/mtx),-0.5);

  uppum = -1.0*f5uppum*sqrt(2.0/(3.0*bb2))*msd;
  upmum = 1.0*f5upmum*sqrt(2.0/(3.0*bb2))*msd*mtb/mtx;

  upf = (uppum + upmum)/2.0;
  umf = (uppum - upmum)/2.0;

  gp = (upf + (1.0 - r)*umf/(1.0 + r))/mcR;
  gm = ((1.0 - r)*upf/(1.0 + r) + umf)/mcR;

  /*double gp = (upf + (1.0 - r)*umf/(1.0 + r))/mcR;
  double gm = ((1.0 - r)*upf/(1.0 + r) + umf)/mcR;
  double RoldFF = (1.0+r)*gp - (1.0-r)*gm;
  double oldFF = RoldFF * RoldFF;

  return oldFF;*/

}


LLSWBDss0FF::LLSWBDss0FF(double mB, double mDss, bool isApproxB1, double tau_1) 
  : mB_(mB), mDss_(mDss), isApproxB1_(isApproxB1), tau_1_(tau_1) {
  tau_1_org_ = get_tau_1_org_Dss0(isApproxB1);
}

LLSWBDss0FF::~LLSWBDss0FF() {}

BDss0FF* LLSWBDss0FF::clone() {
  return new LLSWBDss0FF(mB_, mDss_, isApproxB1_, tau_1_);
}


void LLSWBDss0FF::compute_ff(double q2, double &gp, double &gm) const {

 
  double trueW = (mB_*mB_+mDss_*mDss_-q2)/(2*mB_*mDss_);
  double tau_1_org = tau_1_org_;

  double tau_p = tau_1_;

  double m_b = 4.8;
  double m_c = 1.4;
  double e_b = 1.0/(2*m_b);
  double e_c = 1.0/(2*m_c);

  double Lambda = 0.4;
//  double Lambda_p = 0.39 + Lambda;
  double Lambda_s = 0.35 + Lambda;
  
  //double Br_BD1lnu = 0.00406;
  double Br_BD1lnu = 0.0060;
  double Br_BD1lnu_org = 0.0060;
  double tau_1 = tau_1_org*sqrt(Br_BD1lnu/Br_BD1lnu_org);

  // functions tau, zeta
//  double tau = tau_1 * (1.0 + tau_p * (trueW - 1.0));
  //double zeta = (trueW + 1.0)*tau / sqrt(3.0);
  double zeta_1 = tau_1 * 2.0 /  sqrt(3.0);
  //double zeta_1 = 1.0;
  double zeta_p = tau_p + 0.5;
  double zeta = zeta_1 * (1.0 + zeta_p * (trueW - 1.0));

  double zeta1 = 0.0;
  double zeta2 = 0.0;
    
  if (!isApproxB1_) {
    zeta1 = Lambda * zeta;
    zeta2 = -Lambda_s * zeta;
  }
  
  // form factors

  double gp_t1 
    = e_c*(2.0*(trueW-1.0)*zeta1 
	   - 3.0*(trueW*Lambda_s - Lambda)*zeta / (trueW+1.0));
  double gp_t2 
    = -e_b*(((2.0*trueW+1.0)*Lambda_s-(trueW+2.0)*Lambda)*zeta/(trueW+1.0)
	    - 2.0*(trueW-1.0)*zeta1);
  gp = gp_t1 + gp_t2;
  
  gm = zeta;

}
