#ifndef __FF_REWEIGHT_UTILS_H__
#define __FF_REWEIGHT_UTILS_H__

#include <vector>

#include "ff_reweight_defs.h"

HepLorentzVector make_lorentz_vector(double energy, double p3mag, double costh, double phi);

template <typename T>
std::vector<HepLorentzVector> make_lorentz_vector(
    const std::vector<T> &energy, const std::vector<T> &p3mag, 
    const std::vector<T> &costh, const std::vector<T> &phi);

#include "ff_reweight_utils_impl.h"

#endif
