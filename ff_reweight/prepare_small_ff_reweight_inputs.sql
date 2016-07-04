BEGIN;

CREATE TEMPORARY VIEW temp_framework AS
SELECT 
  eid, mcmass,
  mcenergy, mcp3, mccosth, mcphi, 
  mcenergycm, mcp3cm, mccosthcm, mcphicm
FROM 
  (SELECT * FROM framework_ntuples_sp1005 LIMIT 5000) AS q
  --framework_ntuples_sp1005
  INNER JOIN framework_ntuples_addnl_cols_sp1005 
  USING (eid);

CREATE TABLE ff_reweight_inputs_small AS 
SELECT 
  eid, 
  mc_n_vertices, mc_n_edges, 
  mc_from_vertices, mc_to_vertices, 
  mc_lund_id, mcmass,
  mcenergy, mcp3, mccosth, mcphi,
  mcenergycm, mcp3cm, mccosthcm, mcphicm
FROM temp_framework INNER JOIN graph_sp1005 USING (eid);

COMMIT;
