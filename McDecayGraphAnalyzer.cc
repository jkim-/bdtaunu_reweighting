#include <iostream>
#include <cmath>
#include <algorithm>

#include <boost/property_map/property_map.hpp>

#include "ff_reweight_defs.h"
#include "McDecayGraphAnalyzer.h"

void McDecayGraphAnalyzer::clear_cache() {
  bdlnu_.clear();
}

void McDecayGraphAnalyzer::analyze(Graph g) {

  // reset and update cache
  clear_cache();
  lund_pm_ = get_lund_pm(g);
  lorentz_pm_ = get_lorentz_pm(g);
  lorentz_cm_pm_ = get_lorentz_cm_pm(g);

  // create color map for bfs
  std::map<Vertex, boost::default_color_type> color_map;
  boost::associative_property_map<
    std::map<Vertex, boost::default_color_type> > color_pm(color_map);

  VertexIter vi, vi_end;
  for (std::tie(vi, vi_end) = vertices(g); vi != vi_end; ++vi) {
    color_map[*vi] = boost::white_color;
  }

  // find source vertex to start bfs (Upsilon(4S))
  Vertex s = Vertex(); 
  for (std::tie(vi, vi_end) = vertices(g); vi != vi_end; ++vi) {
    if (abs(lund_pm_[*vi]) == Upsilon4SLund) { s = *vi; break; } 
  }

  // create visitor
  McDecayGraphSummary crawler_result;
  McGraphBfsCrawler vis(crawler_result, lund_pm_);

  // crawl decay graph
  boost::breadth_first_search(g, s, visitor(vis).color_map(color_pm));

  // extract bdlnu
  extract_bdlnu(crawler_result);

}

void McDecayGraphAnalyzer::extract_bdlnu(const McDecayGraphSummary &crawler_data) {

  for (auto it = crawler_data.b_modes().begin();
       it != crawler_data.b_modes().end(); ++it) {

    if (it->second.size() != 3) continue;

    CLHEP::HepLorentzVector BLab, BCM, XLab, XCM, LepLab, LepCM;

    Vertex u = it->first;
    BLab = lorentz_pm_[u];
    BCM = lorentz_cm_pm_[u];

    bool has_neutrino = false, has_lepton = false, has_dmeson = false;
    for (const auto & v : it->second) {
      if (is_neutrino(lund_pm_[v])) {
        has_neutrino = true;
      } else if (is_lepton(lund_pm_[v])) {
        has_lepton = true;
        LepLab = lorentz_pm_[v];
        LepCM = lorentz_cm_pm_[v];
      } else if (is_dmeson(lund_pm_[v])) {
        has_dmeson = true;
        XLab = lorentz_pm_[v];
        XCM = lorentz_cm_pm_[v];
      }
    }

    if (has_neutrino && has_lepton && has_dmeson) {
      bdlnu_.push_back({ BLab, XLab, LepLab, BCM, XCM, LepCM});
    }
  }
}

McGraphBfsCrawler::McGraphBfsCrawler(
    McDecayGraphSummary &result,
    const McDecayGraphIntPM &lund_pm) 
  : crawled_result_(result), lund_pm_(lund_pm) {
  crawled_result_.clear();
}

void McGraphBfsCrawler::tree_edge(Edge e, const Graph &g) {

  Vertex u = source(e, g);

  if (is_bmeson(lund_pm_[u])) {
    (crawled_result_.b_modes())[u].push_back(target(e, g));
    
  } else if (is_dstar(lund_pm_[u])) {
    (crawled_result_.dstar_modes())[u].push_back(target(e, g));
  } 

}
