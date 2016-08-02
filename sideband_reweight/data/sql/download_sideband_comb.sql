BEGIN; 

CREATE TEMPORARY TABLE sideband_sample_eid AS 
SELECT eid
FROM 
  (SELECT * FROM sideband_generic WHERE sideband=1) AS Q1
  INNER JOIN 
  (SELECT * FROM sample_assignments_generic WHERE sample_type=6) AS Q2 
  USING (eid);
CREATE INDEX ON sideband_sample_eid (eid);

CREATE TEMPORARY TABLE sideband_sample_comb_eid AS 
SELECT *
FROM
  sideband_sample_eid
  INNER JOIN 
  (SELECT * 
   FROM 
     event_labels_generic_augmented 
   WHERE 
     grouped_dss_evttype=3 OR 
     grouped_dss_evttype=4
  ) AS Q2 USING (eid);
CREATE INDEX ON sideband_sample_comb_eid (eid);

CREATE TEMPORARY VIEW sideband_sample_comb AS
SELECT 
  logit_logre_signal_score AS z1, 
  logit_logre_dstartau_score AS z2,
  (lumi_weight * brf_correction_weight * 
   cln_weight * llswb1_weight) AS w
FROM 
  (sideband_sample_comb_eid 
   INNER JOIN
   event_weights_generic_augmented USING(eid))
  INNER JOIN 
  candidate_optimized_events_scores_generic_t USING (eid)
WHERE 
  logit_logre_signal_score IS NOT NULL AND
  logit_logre_dstartau_score IS NOT NULL AND
  logit_gbdt300_signal_score IS NOT NULL AND
  logit_gbdt300_dstartau_score IS NOT NULL
;

\copy (SELECT * FROM sideband_sample_comb) TO '{0}' DELIMITER ' ';

COMMIT;


