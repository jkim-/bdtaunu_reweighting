BEGIN;

CREATE TEMPORARY TABLE offpeak_scaled_weights_logre (
  eid bigint,
  density_weight numeric,
  normalization_weight numeric
);

\copy offpeak_scaled_weights_logre FROM 'continuum_reweight.logre.csv' WITH CSV HEADER;

CREATE INDEX ON offpeak_scaled_weights_logre (eid);

CREATE TEMPORARY TABLE offpeak_scaled_weights_gbdt300 (
  eid bigint,
  density_weight numeric,
  normalization_weight numeric
);

\copy offpeak_scaled_weights_gbdt300 FROM 'continuum_reweight.gbdt300.csv' WITH CSV HEADER;

CREATE INDEX ON offpeak_scaled_weights_gbdt300 (eid);



CREATE TABLE continuum_offpeak_scaled_weights AS
SELECT 
  eid,
  COALESCE(logre.density_weight, 1.0) AS logre_density_weight,
  COALESCE(logre.normalization_weight, 1.0) AS logre_normalization_weight,
  COALESCE(gbdt300.density_weight, 1.0) AS gbdt300_density_weight,
  COALESCE(gbdt300.normalization_weight, 1.0) AS gbdt300_normalization_weight
FROM 
  offpeak_scaled_weights_logre AS logre
  FULL OUTER JOIN 
  offpeak_scaled_weights_gbdt300 AS gbdt300
  USING (eid);

CREATE INDEX ON continuum_offpeak_scaled_weights (eid);

COMMIT;

VACUUM ANALYZE continuum_offpeak_scaled_weights;
