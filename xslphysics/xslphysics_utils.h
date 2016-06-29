#ifndef __XSLPHYSICS_UTILS_H__
#define __XSLPHYSICS_UTILS_H__

template<typename DecRateT>
double dGamma_dq2_adapter(double q2, void *obj);

template<typename DecRateT>
double dGamma_dw_adapter(double w, void *obj);

#include "xslphysics_utils_impl.h"

#endif
