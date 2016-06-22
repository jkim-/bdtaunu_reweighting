CREATE MATERIALIZED VIEW ff_reweight_input_sigmc AS
SELECT 
  eid, 
  mc_n_vertices, mc_n_edges, 
  mc_from_vertices, mc_to_vertices, 
  mc_lund_id, 
  mcp3, mccosth, mcphi, mcenergy,
  mcmass
FROM framework_ntuples_sigmc INNER JOIN graph_sigmc USING (eid);
