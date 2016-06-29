#include <cmath> 
#include <cstdlib> 

#include <ff_reweight_constants.h>
#include "ISGW2VectorFF.h"

ISGW2VectorFF::ISGW2VectorFF(double mB, double mDs) 
  : mB_(mB), mDs_(mDs) {}

ISGW2VectorFF::~ISGW2VectorFF() {}

VectorFF* ISGW2VectorFF::clone() {
  return new ISGW2VectorFF(mB_, mDs_);
}

namespace {

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

double EvtGetGammaji(double z) {
  double temp;
  temp = 2+((2.0*z)/(1-z))*log(z);
  temp = -1.0*temp;
  return temp;
}

}

void ISGW2VectorFF::compute_ff(double q2, 
    double &V, double &A0, double &A1, double &A2) const {
  
  double msb=5.2;
  double msd=0.33;
  double bb2=0.431*0.431;
  double mbb=5.31;
  double nf = 4.0;
  double cf=0.989;
  double msq=1.82;
  double bx2=0.38*0.38;
  double mbx=0.75*2.01+0.25*1.87;
  double nfp = 3.0;
  double mtb=msb+msd;
  double mtx=msq+msd;
  double mup=1.0/(1.0/msq+1.0/msb);
  double mum=1.0/(1.0/msq-1.0/msb);
  double bbx2=0.5*(bb2+bx2);
  double mb=mB_;
  double mx=mDs_; 
  double tm=(mb-mx)*(mb-mx);
  double t = q2;
  if ( t > tm ) t = 0.99*tm;
  double wt=1.0+(tm-t)/(2.0*mbb*mbx);
  double mqm = 0.1;
  double r2=3.0/(4.0*msb*msq)+3*msd*msd/(2*mbb*mbx*bbx2) + 
    (16.0/(mbb*mbx*(33.0-2.0*nfp)))*
    log(EvtGetas(mqm,mqm)/EvtGetas(msq,msq));
  double ai = -1.0* ( 6.0/( 33.0 - 2.0*nf));  
  double cji = pow(( EvtGetas( msb,msb ) / EvtGetas( msq,msq ) ),ai);
  double zji = msq / msb;
  double gammaji = EvtGetGammaji( zji );
  double chiji = -1.0 - ( gammaji / ( 1- zji ));
  double betaji_g = (2.0/3.0)+gammaji;
  double betaji_f = (-2.0/3.0)+gammaji;
  double betaji_appam = -1.0-chiji+(4.0/(3.0*(1.0-zji)))+
    (2.0*(1+zji)*gammaji/(3.0*(1.0-zji)*(1.0-zji)));
  double betaji_apmam = (1.0/3.0)-chiji-(4.0/(3.0*(1.0-zji)))-
    (2.0*(1+zji)*gammaji/(3.0*(1.0-zji)*(1.0-zji)))+
    gammaji;
  double r_g = cji*(1+(betaji_g*EvtGetas( msq,sqrt(mb*msq) )/(PI)));
  double r_f = cji*(1+(betaji_f*EvtGetas( msq,sqrt(mb*msq) )/(PI)));
  double r_apmam = cji*(1+(betaji_apmam*EvtGetas( msq,sqrt(mb*msq) )/(PI)));
  double f3=sqrt(mtx/mtb)*pow(sqrt(bx2*bb2)/bbx2,1.5)/
    ((1.0+r2*(tm-t)/12.0)*(1.0+r2*(tm-t)/12.0));
  double f3f=sqrt(mbx*mbb/(mtx*mtb))*f3;
  double f3g=sqrt(mtx*mtb/(mbx*mbb))*f3;
  double f3appam=sqrt(mtb*mtb*mtb*mbx/(mbb*mbb*mbb*mtx))*f3;
  double f3apmam=sqrt(mtx*mtb/(mbx*mbb))*f3;
  double ff=cf*mtb*(1+wt+msd*(wt-1)/(2*mup))*f3f*r_f;
  double gf=0.5*(1/msq-msd*bb2/(2*mum*mtx*bbx2))*f3g*r_g;
  double appam=cji*(msd*bx2*(1-msd*bx2/(2*mtb*bbx2))/ 
		    ((1+wt)*msq*msb*bbx2)-
		    betaji_appam*EvtGetas( msq,sqrt(msq*mb) )/
		    (mtb*PI))*f3appam;
  double apmam=-1.0*(mtb/msb-msd*bx2/(2*mup*bbx2)+wt*msd*mtb*bx2*
		     (1-msd*bx2/(2*mtb*bbx2))/((wt+1)*msq*msb*bbx2))*
    f3apmam*r_apmam/mtx;
  double apf=0.5*(appam+apmam);
  double amf=0.5*(appam-apmam);
  double mass = mDs_;
  V = (gf)*(mb+mass);
  A1 = (ff)/(mb+mass);
  A2 = -1.0*(apf)*(mb+mass);
  double a3f = ((mb+mass)/(2.0*mass))*(A1) - ((mb-mass)/(2.0*mass))*(A2);
  A0 = a3f + ( (t*amf)/(2.0*mass));
}
