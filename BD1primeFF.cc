#include <cmath> 
#include <cstdlib> 

#include "ff_reweight_defs.h"
#include "BD1primeFF.h"

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


inline double get_tau_1_org_D1prime(bool isApproxB1) {
  return isApproxB1 ? 0.71 : 0.75;
}

}

ISGW2BD1primeFF::ISGW2BD1primeFF(double mB, double mDss) 
  : mB_(mB), mDss_(mDss) {}

ISGW2BD1primeFF::~ISGW2BD1primeFF() {}

BD1primeFF* ISGW2BD1primeFF::clone() {
  return new ISGW2BD1primeFF(mB_, mDss_);
}

void ISGW2BD1primeFF::compute_ff(double q2, 
    double &gA, double &gV1, double &gV3rgV2) const {
  
  double mB = mB_;
  double mD = mDss_;

  // Get R
  double mcR = 2.0*sqrt(mB*mD) / (mB+mD);
  // Get r
  double r = mD/mB;

  // Get FF
  double t=q2;
  double mass=mD;
  double lf, qf, cpf, cmf;

  double mtb, mbb;
  double msd, mx,mb,nf,nfp;
  double msq,bx2,mbx,mtx;
  double f5cppcm,f5cpmcm,f5,ql,ll,cppcm,cpmcm,f5q,f5l;
  double mqm,msb,bb2,mup,mum,bbx2,tm,wt,r2;

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
  mb=mB;
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

  f5q = f5*pow(( mbb / mtb ),-0.5)*pow((mbx/mtx),-0.5);
  f5l = f5*pow(( mbb / mtb ),0.5)*pow((mbx/mtx),0.5);
  f5cppcm = f5*pow(( mbb / mtb ),-1.5)*pow((mbx/mtx),0.5);
  f5cpmcm = f5*pow(( mbb / mtb ),-0.5)*pow((mbx/mtx),-0.5);
  
  if (msq == msd) { 
    
    ql = -1.0*(msd*(5.0+wt)*f5q/(2.0*mtx*sqrt(bb2)*6.0));
    
    ll = -1.0*mtb*sqrt(bb2)*f5l*(1/mum+ ( (msd*mtx*(wt-1)/bb2)*
					  ( (5.0+wt)/(6.0*msq)-(msd*bb2)/(2.0*mum*mtx*bbx2))));
    
    cppcm = (-1.0*(msd*mtx*f5cppcm/(2.0*msq*mtb*sqrt(bb2)))*
	     (1-(msd*msq*bb2)/(2.0*mtx*mum*bbx2)));
    
    cpmcm = 1.0*(msd*mtx*f5cpmcm/(2.0*msq*mtb*sqrt(bb2)))*
      (((wt+2.0)/3.0)-(msd*msq*bb2)/(2.0*mtx*mum*bbx2))
      *(mtb/mtx);
  } else {

    ql = f5q*sqrt(1.0/6.0)*msd/(sqrt(bb2)*mtx)*
      (1.0-bb2*mtb/(4.0*msd*msq*msb));
    ll = f5l*sqrt(2.0/3.0)*mtb*sqrt(bb2)*(1.0/(2.0*msq) - 3.0/(2.0*msb) +
					  msd*mtx*(wt-1)/bb2*(1.0/msq-msd*bb2/(2.0*mum*mtx*bbx2)));  
    cppcm = msd*msd*bx2*f5cppcm/(sqrt(6.0)*mtb*msq*sqrt(bb2)*bbx2);
    cpmcm = -sqrt(2.0/3.0)*msd*f5cpmcm/(sqrt(bb2)*mtx)*
      (1+msd*bx2/(2.0*msq*bbx2));
  }

  qf = ql;
  lf = ll;
  cpf = (cppcm + cpmcm)/2.0;
  cmf = (cppcm - cpmcm)/2.0;

  double conv = mcR * mB * (1.0 + r);
  gA = -conv * qf;
  gV1 = 2.0 * lf / conv;
  gV3rgV2 = conv * cpf;

}

LLSWBD1primeFF::LLSWBD1primeFF(double mB, double mDss, bool isApproxB1, double tau_1)
  : mB_(mB), mDss_(mDss), isApproxB1_(isApproxB1), tau_1_(tau_1) {
  tau_1_org_ = get_tau_1_org_D1prime(isApproxB1);
}

LLSWBD1primeFF::~LLSWBD1primeFF() {}

BD1primeFF* LLSWBD1primeFF::clone() {
  return new LLSWBD1primeFF(mB_, mDss_, isApproxB1_, tau_1_);
}


void LLSWBD1primeFF::compute_ff(double q2, 
    double &gA, double &gV1, double &gV3rgV2) const {
 
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

  double gA_t1 = zeta;
  double gA_t2 = e_c*(trueW*Lambda_s - Lambda)*zeta / (trueW+1.0);
  double gA_t3 
    = -e_b*(((2.0*trueW+1.0)*Lambda_s-(trueW+2.0)*Lambda)*zeta/(trueW+1.0)
	    - 2.0*(trueW-1.0)*zeta1);
  gA = gA_t1 + gA_t2 + gA_t3;
  
  double gV1_t1 = (trueW-1.0)*zeta;
  double gV1_t2 = e_c*(trueW*Lambda_s - Lambda)*zeta; 
  double gV1_t3 
    = -e_b*(((2.0*trueW+1.0)*Lambda_s-(trueW+2.0)*Lambda)*zeta 
	    - 2.0*(trueW*trueW-1.0)*zeta1);
  gV1 = gV1_t1 + gV1_t2 + gV1_t3;
  
  double gV2 = 2.0*e_c*zeta1;
  
  double gV3_t1 = -zeta;
  double gV3_t2  
    = -e_c*((trueW*Lambda_s - Lambda)*zeta / (trueW+1.0) + 2.0*zeta1);
  double gV3_t3 
    = e_b*(((2.0*trueW+1.0)*Lambda_s-(trueW+2.0)*Lambda)*zeta/(trueW+1.0) 
	   - 2.0*(trueW-1.0)*zeta1);
  double gV3 = gV3_t1 + gV3_t2 + gV3_t3;
    
  // calculate FF
  gV3rgV2 = gV3 + r*gV2;

}

