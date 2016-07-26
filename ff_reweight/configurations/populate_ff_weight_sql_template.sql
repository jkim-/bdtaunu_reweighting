BEGIN;

CREATE TABLE formfactor_weights_{0} (
  eid bigint,
  cln_weight numeric,
  linearq2_weight numeric,
  llswb1_weight numeric,
  llswb2_weight numeric
);

\copy formfactor_weights_{0} FROM 'formfactor_weights_{0}.csv' WITH CSV HEADER;

CREATE INDEX ON formfactor_weights_{0} (eid);

COMMIT;

VACUUM ANALYZE formfactor_weights_{0};
