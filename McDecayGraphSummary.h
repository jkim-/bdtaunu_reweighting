#ifndef __MCDECAYGRAPHSUMMARY_H__
#define __MCDECAYGRAPHSUMMARY_H__

#include "McDecayGraph.h"

class McDecayGraphSummary {

  public:
    using Vertex = McDecayGraphTraits::vertex_descriptor;

  public:

    McDecayGraphSummary();
    ~McDecayGraphSummary() {};

    void insert_b_mode(const Vertex&, const std::vector<Vertex>&);
    void insert_dstar_mode(const Vertex&, const std::vector<Vertex>&);
    void insert_d_mode(const Vertex&, const std::vector<Vertex>&);

    const std::unordered_map<Vertex, std::vector<Vertex>>& b_modes() const;
    std::unordered_map<Vertex, std::vector<Vertex>>& b_modes();

    const std::unordered_map<Vertex, std::vector<Vertex>>& dstar_modes() const;
    std::unordered_map<Vertex, std::vector<Vertex>>& dstar_modes();

    const std::unordered_map<Vertex, std::vector<Vertex>>& d_modes() const;
    std::unordered_map<Vertex, std::vector<Vertex>>& d_modes();

    void clear();

  private:

    std::unordered_map<Vertex, std::vector<Vertex>> b_modes_;
    std::unordered_map<Vertex, std::vector<Vertex>> dstar_modes_;
    std::unordered_map<Vertex, std::vector<Vertex>> d_modes_;
};

inline std::unordered_map<McDecayGraphSummary::Vertex, 
                          std::vector<McDecayGraphSummary::Vertex>>& 
McDecayGraphSummary::b_modes() {
  return const_cast<std::unordered_map<Vertex, std::vector<Vertex>>&>(
           static_cast<const McDecayGraphSummary&>(*this).b_modes());
}

inline const std::unordered_map<McDecayGraphSummary::Vertex, 
                                std::vector<McDecayGraphSummary::Vertex>>& 
McDecayGraphSummary::b_modes() const {
  return b_modes_;
}

inline std::unordered_map<McDecayGraphSummary::Vertex, 
                          std::vector<McDecayGraphSummary::Vertex>>& 
McDecayGraphSummary::dstar_modes() {
  return const_cast<std::unordered_map<Vertex, std::vector<Vertex>>&>(
           static_cast<const McDecayGraphSummary&>(*this).dstar_modes());
}

inline const std::unordered_map<McDecayGraphSummary::Vertex, 
                          std::vector<McDecayGraphSummary::Vertex>>&
McDecayGraphSummary::dstar_modes() const {
  return dstar_modes_;
}

inline std::unordered_map<McDecayGraphSummary::Vertex, 
                          std::vector<McDecayGraphSummary::Vertex>>& 
McDecayGraphSummary::d_modes() {
  return const_cast<std::unordered_map<Vertex, std::vector<Vertex>>&>(
           static_cast<const McDecayGraphSummary&>(*this).d_modes());
}

inline const std::unordered_map<McDecayGraphSummary::Vertex, 
                          std::vector<McDecayGraphSummary::Vertex>>& 
McDecayGraphSummary::d_modes() const {
  return d_modes_;
}

inline void 
McDecayGraphSummary::insert_b_mode(
    const Vertex &u, const std::vector<Vertex> &daughters) {
  b_modes_[u] = daughters;
}

inline void 
McDecayGraphSummary::insert_dstar_mode(
    const Vertex &u, const std::vector<Vertex> &daughters) {
  dstar_modes_[u] = daughters;
}

inline void 
McDecayGraphSummary::insert_d_mode(
    const Vertex &u, const std::vector<Vertex> &daughters) {
  d_modes_[u] = daughters;
}

#endif
