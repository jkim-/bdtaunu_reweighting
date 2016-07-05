BEGIN;

CREATE TABLE brf_weights_sp1235 (
  eid bigint,
  brf_correction_weight numeric,
  b1_brf_mode brf_mode,
  b2_brf_mode brf_mode
);

\copy brf_weights_sp1235 FROM 'brf_weights_sp1235.csv' WITH CSV HEADER;

CREATE INDEX ON brf_weights_sp1235 (eid);

COMMIT;

VACUUM ANALYZE brf_weights_sp1235;
