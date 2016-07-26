template<typename DecRateT>
inline double dGamma_dq2_adapter(double q2, void *obj) {
  return static_cast<DecRateT*>(obj)->dGamma_dq2_aux(q2);
}

template<typename DecRateT>
inline double dGamma_dw_adapter(double w, void *obj) {
  return static_cast<DecRateT*>(obj)->dGamma_dw_aux(w);
}
