-- sp1235

BEGIN;

CREATE MATERIALIZED VIEW ff_reweight_inputs_sp1235 AS 
SELECT 
  eid, 
  mc_n_vertices, mc_n_edges, 
  mc_from_vertices, mc_to_vertices, 
  mc_lund_id, mcmass,
  mcenergy, mcp3, mccosth, mcphi,
  mcenergycm, mcp3cm, mccosthcm, mcphicm
FROM 
  graph_sp1235
  INNER JOIN 
  (SELECT 
     eid, mcmass,
     mcenergy, mcp3, mccosth, mcphi, 
     mcenergycm, mcp3cm, mccosthcm, mcphicm
   FROM 
     framework_ntuples_sp1235
     INNER JOIN framework_ntuples_addnl_cols_sp1235 
     USING (eid)) AS Q
  USING (eid);

CREATE INDEX ON ff_reweight_inputs_sp1235 (eid);

COMMIT;

VACUUM ff_reweight_inputs_sp1235;


-- sp1237

BEGIN;

CREATE MATERIALIZED VIEW ff_reweight_inputs_sp1237 AS 
SELECT 
  eid, 
  mc_n_vertices, mc_n_edges, 
  mc_from_vertices, mc_to_vertices, 
  mc_lund_id, mcmass,
  mcenergy, mcp3, mccosth, mcphi,
  mcenergycm, mcp3cm, mccosthcm, mcphicm
FROM 
  graph_sp1237
  INNER JOIN 
  (SELECT 
     eid, mcmass,
     mcenergy, mcp3, mccosth, mcphi, 
     mcenergycm, mcp3cm, mccosthcm, mcphicm
   FROM 
     framework_ntuples_sp1237
     INNER JOIN framework_ntuples_addnl_cols_sp1237 
     USING (eid)) AS Q
  USING (eid);

CREATE INDEX ON ff_reweight_inputs_sp1237 (eid);

COMMIT;

VACUUM ff_reweight_inputs_sp1237;
