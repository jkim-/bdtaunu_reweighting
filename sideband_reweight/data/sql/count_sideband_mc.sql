BEGIN;

-- count number of each event type in the sideband

CREATE TEMPORARY TABLE sideband_sample_generic AS
SELECT * 
FROM
  (SELECT * FROM sideband_generic WHERE sideband=1) AS Q1
  INNER JOIN 
  (SELECT * FROM sample_assignments_generic WHERE sample_type=5) AS Q2
  USING (eid);
CREATE INDEX ON sideband_sample_generic (eid);

CREATE TEMPORARY TABLE sideband_sample_mc AS
SELECT 
  eid, 
  sighp3_sideband,
  eextra_sideband,
  sideband,
  (brf_correction_weight * 
   cln_weight * llswb1_weight * 
   continuum_logre_density_weight * 
   continuum_logre_normalization_weight) as weight,
  grouped_dss_evttype AS evttype
FROM 
  (sideband_sample_generic 
   INNER JOIN
   event_labels_generic_augmented USING (eid))
  INNER JOIN
  event_weights_generic_augmented USING (eid);

CREATE INDEX ON sideband_sample_mc (eid);

SELECT 
  evttype,
  ROUND(SUM(sighp3_sideband*weight), 7) AS sighp3_wcounts,
  ROUND(SUM(eextra_sideband*weight), 7) AS eextra_wcounts,
  ROUND(SUM(sideband*weight), 7) AS all_wcounts,
  ROUND(  SUM(sighp3_sideband*weight) / 
          (SELECT SUM(sighp3_sideband*weight) FROM sideband_sample_mc), 
        7) AS sighp3_p,
  ROUND(  SUM(eextra_sideband*weight) / 
          (SELECT SUM(eextra_sideband*weight) FROM sideband_sample_mc), 
        7) AS eextra_p,
  ROUND(  SUM(sideband*weight) / 
          (SELECT SUM(sideband*weight) FROM sideband_sample_mc), 
        7) AS all_p
FROM
  sideband_sample_mc INNER JOIN candidate_optimized_events_scores_generic_t USING (eid)
WHERE 
  logit_logre_signal_score IS NOT NULL AND
  logit_logre_dstartau_score IS NOT NULL AND
  logit_gbdt300_signal_score IS NOT NULL AND
  logit_gbdt300_dstartau_score IS NOT NULL
GROUP BY evttype
ORDER BY evttype;

COMMIT;
