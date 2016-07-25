-- sp1235

BEGIN;

CREATE MATERIALIZED VIEW ff_reweight_inputs_small_sp1235 AS
SELECT * FROM ff_reweight_inputs_sp1235 WHERE random() < 0.01;

CREATE INDEX ON ff_reweight_inputs_small_sp1235 (eid);

COMMIT;

VACUUM ANALYZE ff_reweight_inputs_small_sp1235;


-- sp1237

BEGIN;

CREATE MATERIALIZED VIEW ff_reweight_inputs_small_sp1237 AS
SELECT * FROM ff_reweight_inputs_sp1237 WHERE random() < 0.01;

CREATE INDEX ON ff_reweight_inputs_small_sp1237 (eid);

COMMIT;

VACUUM ANALYZE ff_reweight_inputs_small_sp1237;

-- union them 
CREATE VIEW ff_reweight_inputs_small AS 
SELECT * FROM ff_reweight_inputs_small_sp1235 
UNION ALL
SELECT * FROM ff_reweight_inputs_small_sp1237;

