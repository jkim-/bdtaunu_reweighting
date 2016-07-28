-- Derive offpeak weighted counts

-- 1. Load the luminosity adjusted weights for offpeak data for each run. 
--    This was derived from the LTDA.
CREATE TEMPORARY TABLE offpeak_weights (
  run integer, 
  weight numeric
);
INSERT INTO offpeak_weights (run, weight) VALUES
(1, 7.94549858228),
(2, 8.92708552914),
(3, 13.2144568048),
(4, 9.94470441764),
(5, 9.27184067041),
(6, 10.1034378588);

-- 2. Find the number of offpeak records per run.
CREATE TEMPORARY TABLE offpeak_counts AS
SELECT run, COUNT(*) 
FROM event_labels_data 
WHERE mode_label=0 
GROUP BY (run)
ORDER BY (run);

-- 3. Computed the weighted sum over runs 
CREATE TEMPORARY VIEW offpeak_weighted_counts AS
SELECT SUM(weight*count) AS weighted_counts
FROM offpeak_weights INNER JOIN offpeak_counts USING (run);

-- Derive continuum weighted counts

-- 1. Specialize to the data imitation sample. 
CREATE TEMPORARY TABLE mc_eid AS 
SELECT eid FROM sample_assignments_generic WHERE sample_type=5;
CREATE INDEX ON mc_eid (eid);

-- 2. The imitation sample already had the luminosity weights accounted for, so just count. 
CREATE TEMPORARY VIEW continuum_weighted_counts AS
SELECT COUNT(*) AS weighted_counts
FROM mc_eid INNER JOIN event_labels_generic_augmented USING (eid)
WHERE eventlabel=5;

-- Derive the normalization weight for each continuum event. 
SELECT 
  off.weighted_counts AS offpeak_weighted_counts, 
  cont.weighted_counts AS continuum_weighted_counts,
  off.weighted_counts / cont.weighted_counts AS continuum_normalization_weight
FROM offpeak_weighted_counts AS off, continuum_weighted_counts AS cont;
