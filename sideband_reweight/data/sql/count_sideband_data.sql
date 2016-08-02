BEGIN;

-- count number of on/off peak data in the sideband
CREATE TEMPORARY VIEW sideband_sample_data AS
SELECT eid, sighp3_sideband, eextra_sideband
FROM 
  (SELECT * FROM sideband_data WHERE sideband=1) AS Q1
  INNER JOIN 
  candidate_optimized_events_scores_data_t USING (eid)
WHERE 
  logit_logre_signal_score IS NOT NULL AND
  logit_logre_dstartau_score IS NOT NULL AND
  logit_gbdt300_signal_score IS NOT NULL AND
  logit_gbdt300_dstartau_score IS NOT NULL
;

SELECT 
  mode_label AS data_on_peak, 
  SUM(sighp3_sideband) AS sighp3_counts, 
  SUM(eextra_sideband) AS eextra_counts
FROM 
  (SELECT * FROM sideband_sample_data) AS Q1
  INNER JOIN 
  event_labels_data USING (eid) 
GROUP BY 
  mode_label;

COMMIT;
