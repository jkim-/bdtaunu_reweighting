#include <iostream>
#include <cmath>
#include <algorithm>

#include <boost/property_map/property_map.hpp>

#include "ff_reweight_defs.h"
#include "McDecayGraphCrawler.h"

McDecayGraphCrawler::McDecayGraphCrawler() {}

void McDecayGraphCrawler::analyze(
    const Graph &g, McDecayGraphSummary &summary) {

  // clear the output object and initialize data structures 
  summary.clear();
  ConstMcDecayGraphIntPM lund_pm = get_lund_pm(g);

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
    if (abs(lund_pm[*vi]) == Upsilon4SLund) { s = *vi; break; } 
  }

  // create visitor
  McGraphBfsVisitor vis(summary, lund_pm);

  // crawl decay graph
  boost::breadth_first_search(g, s, visitor(vis).color_map(color_pm));

}

McGraphBfsVisitor::McGraphBfsVisitor(
    McDecayGraphSummary &result,
    ConstMcDecayGraphIntPM &lund_pm) 
  : summary_(result), lund_pm_(lund_pm) {
}

void McGraphBfsVisitor::tree_edge(Edge e, const Graph &g) {

  Vertex u = source(e, g);

  // decide whether the edge is part of a decay that is of interest
  if (is_bmeson(lund_pm_[u])) {
    (summary_.b_modes())[u].push_back(target(e, g));
    
  } else if (is_dstar(lund_pm_[u])) {
    (summary_.dstar_modes())[u].push_back(target(e, g));
  } 

}
