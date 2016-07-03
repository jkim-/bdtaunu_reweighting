BEGIN;

CREATE TEMPORARY VIEW framework_sp1235 AS
SELECT 
  eid, mcmass,
  mcenergy, mcp3, mccosth, mcphi, 
  mcenergycm, mcp3cm, mccosthcm, mcphicm
FROM 
  (SELECT * FROM framework_ntuples_sp1235 LIMIT 5000) AS q
  --framework_ntuples_sp1235
  INNER JOIN framework_ntuples_addnl_cols_sp1235 
  USING (eid);

CREATE TABLE ff_reweight_inputs_sp1235 AS 
SELECT 
  eid, 
  mc_n_vertices, mc_n_edges, 
  mc_from_vertices, mc_to_vertices, 
  mc_lund_id, mcmass,
  mcenergy, mcp3, mccosth, mcphi,
  mcenergycm, mcp3cm, mccosthcm, mcphicm
FROM framework_sp1235 INNER JOIN graph_sp1235 USING (eid);

COMMIT;
