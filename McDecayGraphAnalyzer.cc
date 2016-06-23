#include <iostream>
#include <cmath>

#include <boost/property_map/property_map.hpp>

#include "McDecayGraphAnalyzer.h"

const int Upsilon4SLund = 70553;
const int B0Lund = 511;
const int BpLund = 521;
const int DstarpLund = 413;
const int Dstar0Lund = 423;

inline bool is_bmeson(int lund) {
  int abslund = abs(lund);
  return (abslund == B0Lund || abslund == BpLund) ? true : false; 
}

inline bool is_dstar(int lund) {
  int abslund = abs(lund);
  return (abslund == DstarpLund || abslund == Dstar0Lund) ? true : false; 
}

void McDecayGraphAnalyzer::clear_cache() {
  bdlnu_.clear();
}

void McDecayGraphAnalyzer::analyze(Graph g) {

  clear_cache();

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
  IntPropertyMap lund_pm = get_lund_pm(g);
  for (std::tie(vi, vi_end) = vertices(g); vi != vi_end; ++vi) {
    if (abs(lund_pm[*vi]) == Upsilon4SLund) { s = *vi; break; } 
  }

  // create visitor
  McDecayGraphData crawler_result;
  McGraphBfsCrawler vis(crawler_result, lund_pm);

  // compute matching by bfs
  boost::breadth_first_search(g, s, visitor(vis).color_map(color_pm));

  /*for (auto it = crawler_result.b_mesons_.begin(); 
       it != crawler_result.b_mesons_.end(); ++it) {
    std::cout << lund_pm[it->first] << " -> ";
    for (const auto &v : it->second) {
      std::cout << lund_pm[v] << " ";
    }
    std::cout << std::endl;
  }

  for (auto it = crawler_result.dstar_mesons_.begin(); 
       it != crawler_result.dstar_mesons_.end(); ++it) {
    std::cout << lund_pm[it->first] << " -> ";
    for (const auto &v : it->second) {
      std::cout << lund_pm[v] << " ";
    }
    std::cout << std::endl;
  }*/

}

void McDecayGraphData::clear() {
  b_mesons_.clear();
  dstar_mesons_.clear();
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
