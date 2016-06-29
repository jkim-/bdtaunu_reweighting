#ifndef __MCDECAYGRAPHSUMMARY_H__
#define __MCDECAYGRAPHSUMMARY_H__

#include "McDecayGraph.h"

// class encapsulating the data curated from a McDecayGraph 
class McDecayGraphSummary {

  public:
    using Vertex = McDecayGraphTraits::vertex_descriptor;

  public:

    McDecayGraphSummary();
    ~McDecayGraphSummary() {};

    // returns reference to a map associating mother vertices to 
    // their daughter vertices
    const std::unordered_map<Vertex, std::vector<Vertex>>& b_modes() const;
    std::unordered_map<Vertex, std::vector<Vertex>>& b_modes();

    const std::unordered_map<Vertex,std::vector<Vertex>>& dstar_modes() const;
    std::unordered_map<Vertex, std::vector<Vertex>>& dstar_modes();

    const std::unordered_map<Vertex, std::vector<Vertex>>& d_modes() const;
    std::unordered_map<Vertex, std::vector<Vertex>>& d_modes();

    // clears cached information 
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

#endif
