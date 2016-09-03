#!/usr/bin/env python

import numpy as np

rho2 = 1.207
R1 = 1.406
R2 = 0.853

rho2_err = 0.026
R1_err = 0.033
R2_err = 0.02

rho2_R1_corr = 0.568
rho2_R2_corr = -0.809
R1_R2_corr = -0.758

rho2_var = rho2_err * rho2_err
R1_var = R1_err * R1_err
R2_var = R2_err * R2_err
rho2_R1_cov = rho2_R1_corr * rho2_err * R1_err
rho2_R2_cov = rho2_R2_corr * rho2_err * R2_err
R1_R2_cov = R1_R2_corr * R1_err * R2_err

cov = np.array([ 
      [ rho2_var, rho2_R1_cov, rho2_R2_cov],
      [ rho2_R1_cov, R1_var, R1_R2_cov],
      [ rho2_R2_cov, R1_R2_cov, R2_var] 
    ])

central = np.array([rho2, R1, R2])

print '+ central values (rho2, R1, R2)'
print central
print

print '+ covariace matrix'
print cov
print

eig_v, eig_vec = np.linalg.eig(cov)
print '+ eigenvalues'
eval0 = eig_v[0]
eval1 = eig_v[1]
eval2 = eig_v[2]
print eval0, eval1, eval2
print 

print '+ eigenvectors'
evec0 = eig_vec[:,0]
evec1 = eig_vec[:,1]
evec2 = eig_vec[:,2]
print evec0
print evec1
print evec2
print 

print '+ p0 up/down (rho2, R1, R2)'
print central + eval0*evec0
print central - eval0*evec0
print

print '+ p1 up/down (rho2, R1, R2)'
print central + eval1*evec1
print central - eval1*evec1
print

print '+ p2 up/down (rho2, R1, R2)'
print central + eval2*evec2
print central - eval2*evec2
print
