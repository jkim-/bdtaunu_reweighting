BEGIN; 

CREATE TEMPORARY VIEW sideband_sample_data AS
SELECT 
  logit_logre_signal_score AS z1, 
  logit_logre_dstartau_score AS z2,
  1.0 AS w
FROM 
  (
    (SELECT * FROM sideband_data WHERE sideband=1) AS Q1
    INNER JOIN 
    (SELECT * FROM event_labels_data WHERE mode_label=:mode_label) AS Q2 USING (eid)
  )
  INNER JOIN 
  candidate_optimized_events_scores_data_t USING (eid)
WHERE 
  logit_logre_signal_score IS NOT NULL AND
  logit_logre_dstartau_score IS NOT NULL
;

\copy (SELECT * FROM sideband_sample_data) TO '{0}' DELIMITER ' ';

COMMIT;


