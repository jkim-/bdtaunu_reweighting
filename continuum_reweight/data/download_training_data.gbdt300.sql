-- download offpeak
BEGIN;

CREATE TEMPORARY TABLE offpeak_eid AS
SELECT eid FROM event_labels_data WHERE mode_label=0;
CREATE INDEX ON offpeak_eid (eid);

CREATE TEMPORARY VIEW offpeak AS
SELECT 
  logit_gbdt300_signal_score AS z1, 
  logit_gbdt300_dstartau_score AS z2,
  1.0 AS w
FROM 
  offpeak_eid INNER JOIN candidate_optimized_events_scores_data_t USING (eid)
WHERE
  logit_gbdt300_signal_score IS NOT NULL AND 
  logit_gbdt300_dstartau_score IS NOT NULL
;

\copy (SELECT * FROM offpeak) TO 'offpeak.gbdt300.csv' DELIMITER ' ';

COMMIT;


-- download default continuum
BEGIN;

CREATE TEMPORARY TABLE continuum_eid AS
SELECT eid FROM event_labels_generic 
WHERE eventlabel=5 AND random() < 0.03;
CREATE INDEX ON continuum_eid (eid);

CREATE TEMPORARY TABLE continuum_meta AS 
SELECT eid, weight AS lumi_weight FROM 
continuum_eid INNER JOIN event_weights_generic USING (eid);
CREATE INDEX ON continuum_meta (eid);

CREATE TEMPORARY VIEW continuum AS
SELECT 
  logit_gbdt300_signal_score AS z1, 
  logit_gbdt300_dstartau_score AS z2,
  lumi_weight AS w
FROM 
  continuum_meta INNER JOIN candidate_optimized_events_scores_generic_t USING (eid)
WHERE
  logit_gbdt300_signal_score IS NOT NULL AND 
  logit_gbdt300_dstartau_score IS NOT NULL
;

\copy (SELECT * FROM continuum) TO 'continuum.gbdt300.csv' DELIMITER ' ';

COMMIT;
