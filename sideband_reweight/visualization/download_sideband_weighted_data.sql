CREATE TEMPORARY VIEW sample_eid AS
SELECT eid FROM sample_assignments_generic WHERE sample_type=5;

CREATE TEMPORARY TABLE sample_meta AS
SELECT * FROM 
sample_eid INNER JOIN event_labels_generic_augmented USING (eid);
CREATE INDEX ON sample_meta (eid);

CREATE TEMPORARY VIEW M AS 
SELECT 
  grouped_dss_evttype AS evttype,
  logit_logre_signal_score AS z1,
  logit_logre_dstartau_score AS z2,
  (cln_weight * brf_correction_weight * llswb1_weight) AS w,
  sideband_comb_logre_weight AS sideband_w
FROM
  (sample_meta INNER JOIN event_weights_generic_augmented USING (eid))
  INNER JOIN candidate_optimized_events_scores_generic_t USING (eid)
WHERE 
  (grouped_dss_evttype = 3 OR grouped_dss_evttype = 4) AND
  logit_logre_signal_score IS NOT NULL AND 
  logit_logre_dstartau_score IS NOT NULL AND 
  logit_gbdt300_signal_score IS NOT NULL AND 
  logit_gbdt300_dstartau_score IS NOT NULL
;

\copy (SELECT * FROM M) TO 'weight_visual.csv' CSV HEADER DELIMITER ' ';
