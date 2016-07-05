BEGIN;

CREATE TABLE brf_weights_{0} (
  eid bigint,
  brf_correction_weight numeric,
  b1_brf_mode brf_mode,
  b2_brf_mode brf_mode
);

\copy brf_weights_{0} FROM 'brf_weights_{0}.csv' WITH CSV HEADER;

CREATE INDEX ON brf_weights_{0} (eid);

COMMIT;

VACUUM ANALYZE brf_weights_{0};
