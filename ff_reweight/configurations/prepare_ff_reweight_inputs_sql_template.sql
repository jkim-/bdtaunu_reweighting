BEGIN;

CREATE TEMPORARY VIEW framework_{0} AS
SELECT 
  eid, mcmass,
  mcenergy, mcp3, mccosth, mcphi, 
  mcenergycm, mcp3cm, mccosthcm, mcphicm
FROM 
  framework_ntuples_{0}
  INNER JOIN framework_ntuples_addnl_cols_{0} 
  USING (eid);

CREATE TABLE ff_reweight_inputs_{0} AS 
SELECT 
  eid, 
  mc_n_vertices, mc_n_edges, 
  mc_from_vertices, mc_to_vertices, 
  mc_lund_id, mcmass,
  mcenergy, mcp3, mccosth, mcphi,
  mcenergycm, mcp3cm, mccosthcm, mcphicm
FROM framework_{0} INNER JOIN graph_{0} USING (eid);

COMMIT;
