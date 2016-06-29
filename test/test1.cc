#include <iostream>
#include <cmath>
#include <CLHEP/Vector/LorentzVector.h>

CLHEP::HepLorentzVector make_HepLorentzVector(
  double energy, double p3mag, double costh, double phi) {
  double th = acos(costh);
  double x = p3mag*sin(th)*cos(phi); 
  double y = p3mag*sin(th)*sin(phi); 
  double z = p3mag*costh;
  return CLHEP::HepLorentzVector(energy, CLHEP::Hep3Vector(x, y, z));
}

int main() {

  CLHEP::HepLorentzVector v = make_HepLorentzVector(12.1007, 5.85557, 0.999825, 3.13608);
  std::cout << v.m() << std::endl;

  return 0;
}
