BEGIN;

CREATE TEMPORARY TABLE sideband_weights_comb_logre (
  eid bigint,
  sideband_weight numeric
);

\copy sideband_weights_comb_logre FROM 'sideband_reweight_comb.logre.csv' WITH CSV HEADER;

CREATE INDEX ON sideband_weights_comb_logre (eid);


CREATE TABLE sideband_scaled_weights AS
SELECT 
  eid,
  sideband_weight AS comb_logre_weight
FROM 
  sideband_weights_comb_logre;

CREATE INDEX ON sideband_scaled_weights (eid);

COMMIT;

VACUUM ANALYZE sideband_scaled_weights;
