BEGIN;

CREATE TABLE cln_weight_variations_{0} (
  eid bigint,
  cln_D_rho2_up numeric, 
  cln_D_rho2_down numeric,
  cln_Dstar_p0_up numeric, 
  cln_Dstar_p0_down numeric,
  cln_Dstar_p1_up numeric, 
  cln_Dstar_p1_down numeric,
  cln_Dstar_p2_up numeric, 
  cln_Dstar_p2_down numeric
);


\copy cln_weight_variations_{0} FROM 'cln_weight_variations_{0}.csv' WITH CSV HEADER;

CREATE INDEX ON cln_weight_variations_{0} (eid);

COMMIT;

VACUUM ANALYZE cln_weight_variations_{0};
