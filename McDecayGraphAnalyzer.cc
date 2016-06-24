#include <iostream>
#include <cmath>
#include <algorithm>

#include <boost/property_map/property_map.hpp>

#include "McDecayGraphAnalyzer.h"

const int Upsilon4SLund = 70553;
const int B0Lund = 511;
const int BpLund = 521;
const int DstarpLund = 413;
const int Dstar0Lund = 423;
const int DpLund = 411;
const int D0Lund = 421;
const int eLund = 11;
const int muLund = 13;
const int tauLund = 15;
const int nueLund = 12;
const int numuLund = 14;
const int nutauLund = 16;

inline bool is_bmeson(int lund) {
  int abslund = abs(lund);
  return (abslund == B0Lund || abslund == BpLund) ? true : false; 
}

inline bool is_dstar(int lund) {
  int abslund = abs(lund);
  return (abslund == DstarpLund || abslund == Dstar0Lund) ? true : false; 
}

inline bool is_dmeson(int lund) {
  int abslund = abs(lund);
  return (abslund == DpLund || abslund == D0Lund) ? true : false; 
}

inline bool is_lepton(int lund) {
  int abslund = abs(lund);
  return (abslund == eLund || abslund == muLund || abslund == tauLund) ? true : false; 
}

inline bool is_neutrino(int lund) {
  int abslund = abs(lund);
  return (abslund == nueLund || abslund == numuLund || abslund == nutauLund) ? true : false; 
}

void McDecayGraphData::clear() {
  b_mesons_.clear();
  dstar_mesons_.clear();
}

void McDecayGraphAnalyzer::clear_cache() {
  bdlnu_.clear();
}

void McDecayGraphAnalyzer::analyze(Graph g) {

  // reset and update cache
  clear_cache();
  lund_pm_ = get_lund_pm(g);
  energycm_pm_ = get_energycm_pm(g);
  energy_pm_ = get_energy_pm(g);
  p3mag_pm_ = get_p3mag_pm(g);
  costh_pm_ = get_costh_pm(g);
  phi_pm_ = get_phi_pm(g);

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
  McDecayGraphData crawler_result;
  McGraphBfsCrawler vis(crawler_result, lund_pm_);

  // crawl decay graph
  boost::breadth_first_search(g, s, visitor(vis).color_map(color_pm));

  // extract bdlnu
  extract_bdlnu(crawler_result);

}

void McDecayGraphAnalyzer::extract_bdlnu(const McDecayGraphData &crawler_data) {

  for (auto it = crawler_data.b_mesons_.begin();
       it != crawler_data.b_mesons_.end(); ++it) {

    if (it->second.size() != 3) continue;

    double e_B, p3mag_B, costh_B, phi_B;
    double e_X, p3mag_X, costh_X, phi_X;
    double e_Lep, p3mag_Lep, costh_Lep, phi_Lep;
    double ecm_Lep;

    Vertex u = it->first;
    e_B = energy_pm_[u];
    p3mag_B = p3mag_pm_[u];
    costh_B = costh_pm_[u];
    phi_B = phi_pm_[u];

    bool has_neutrino = false, has_lepton = false, has_dmeson = false;
    for (const auto & v : it->second) {
      if (is_neutrino(lund_pm_[v])) {
        has_neutrino = true;
      } else if (is_lepton(lund_pm_[v])) {
        has_lepton = true;
        e_Lep = energy_pm_[v];
        p3mag_Lep = p3mag_pm_[v];
        costh_Lep = costh_pm_[v];
        phi_Lep = phi_pm_[v];

        ecm_Lep = energycm_pm_[v];
      } else if (is_dmeson(lund_pm_[v])) {
        has_dmeson = true;
        e_X = energy_pm_[v];
        p3mag_X = p3mag_pm_[v];
        costh_X = costh_pm_[v];
        phi_X = phi_pm_[v];
      }
    }

    if (has_neutrino && has_lepton && has_dmeson) {
      bdlnu_.push_back(
          { e_B, p3mag_B, costh_B, phi_B,
            e_X, p3mag_X, costh_X, phi_X,
            e_Lep, p3mag_Lep, costh_Lep, phi_Lep,
            ecm_Lep }
      );
    }
  }
}

McGraphBfsCrawler::McGraphBfsCrawler(
    McDecayGraphData &result,
    const McDecayGraphIntPM &lund_pm) 
  : crawled_result_(result), lund_pm_(lund_pm) {
  crawled_result_.clear();
}

void McGraphBfsCrawler::tree_edge(Edge e, const Graph &g) {

  Vertex u = source(e, g);

  if (is_bmeson(lund_pm_[u])) {
    crawled_result_.b_mesons_[u].push_back(target(e, g));
    
  } else if (is_dstar(lund_pm_[u])) {
    crawled_result_.dstar_mesons_[u].push_back(target(e, g));
  } 

}
