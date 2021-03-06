BEGIN;

CREATE TABLE formfactor_weights_sp1235 (
  eid bigint,
  cln_weight numeric,
  linearq2_weight numeric,
  llswb1_weight numeric,
  llswb2_weight numeric
);

\copy formfactor_weights_sp1235 FROM 'formfactor_weights_sp1235.csv' WITH CSV HEADER;

CREATE INDEX ON formfactor_weights_sp1235 (eid);

COMMIT;

VACUUM ANALYZE formfactor_weights_sp1235;
