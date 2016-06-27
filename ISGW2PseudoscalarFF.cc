#include <cmath> 
#include <cstdlib> 

#include "ff_reweight_defs.h"
#include "ISGW2PseudoscalarFF.h"

ISGW2PseudoscalarFF::ISGW2PseudoscalarFF(double mB, double mD) 
  : mB_(mB), mD_(mD) {}

ISGW2PseudoscalarFF::~ISGW2PseudoscalarFF() {}

double EvtGetas(double massq, double massx) {
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

double EvtGetGammaji(double z) {
  double temp;
  temp = 2+((2.0*z)/(1-z))*log(z);
  temp = -1.0*temp;
  return temp;
}

void ISGW2PseudoscalarFF::compute_ff(
    double q2, double &fplus, double &fminus) const {

  double msb=5.2;
  double msd=0.33;
  double bb2=0.431*0.431;
  double mbb=5.31;
  double nf = 4.0;
  double msq=1.82;
  double bx2=0.45*0.45;
  double mbx=0.75*2.01+0.25*1.87;
  double nfp = 3.0;
  double mtb = msb + msd;
  double mtx = msq + msd;
  double mb = mB_;
  double mx = mD_;
  double mup=1.0/(1.0/msq+1.0/msb);
  double bbx2=0.5*(bb2+bx2);
  double tm=(mb-mx)*(mb-mx);
  double t = q2;
  if (t > tm) t=0.99*tm;
  double mqm = 0.1;
  double r2=3.0/(4.0*msb*msq)+3*msd*msd/(2*mbb*mbx*bbx2) + 
    (16.0/(mbb*mbx*(33.0-2.0*nfp)))*
    log(EvtGetas(mqm,mqm)/EvtGetas(msq,msq));
  double f3 = sqrt(mtx/mtb)*pow(sqrt(bx2*bb2)/bbx2,1.5) /
    ((1.0+r2*(tm-t)/12.0)*(1.0+r2*(tm-t)/12.0));
  double ai = -1.0* ( 6.0/( 33.0 - 2.0*nf));  
  double cji = pow(( EvtGetas( msb,msb ) / EvtGetas( msq,msq ) ),ai);
  double zji = msq / msb;
  double gammaji = EvtGetGammaji( zji );
  double chiji = -1.0 - ( gammaji / ( 1- zji ));
  double betaji_fppfm = gammaji - (2.0/3.0)*chiji;
  double betaji_fpmfm = gammaji + (2.0/3.0)*chiji;
  double rfppfm = cji *(1.0 + betaji_fppfm*EvtGetas( msq,sqrt(msb*msq) )/PI);
  double rfpmfm = cji *(1.0 + betaji_fpmfm*EvtGetas( msq,sqrt(msb*msq) )/PI);
  double f3fppfm = f3*pow(( mbb / mtb ),-0.5)*pow((mbx/mtx),0.5);
  double f3fpmfm = f3*pow(( mbb / mtb ),0.5)*pow((mbx/mtx),-0.5);
  double fppfm = f3fppfm* rfppfm * ( 2.0 - ( ( mtx/msq)*(1- ( (msd*msq*bb2)
							      /(2.0*mup*mtx*bbx2)))));
  double fpmfm = f3fpmfm* rfpmfm * ( mtb/msq) * ( 1 - ( ( msd*msq*bb2)/
							( 2.0*mup*mtx*bbx2)));

  fplus = (fppfm + fpmfm)/2.0;
  fminus = (fppfm - fpmfm)/2.0;

}
