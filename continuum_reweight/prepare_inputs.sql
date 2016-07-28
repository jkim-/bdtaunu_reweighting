-- prepare the inputs that continuum_reweight requires. 
-- this materialized view can be dropped after the reweighting
-- is complete.

BEGIN;

CREATE MATERIALIZED VIEW continuum_reweight_inputs AS
SELECT 
  eid,
  logit_gbdt300_signal_score, 
  logit_gbdt300_dstartau_score, 
  logit_logre_signal_score, 
  logit_logre_dstartau_score
FROM 
  candidate_optimized_events_scores_generic_t 
  INNER JOIN 
  (SELECT eid FROM event_labels_generic WHERE eventlabel=5) AS Q
  USING (eid)
WHERE
  logit_gbdt300_signal_score IS NOT NULL AND
  logit_gbdt300_dstartau_score IS NOT NULL AND
  logit_logre_signal_score IS NOT NULL AND
  logit_logre_dstartau_score IS NOT NULL
;

COMMIT;
