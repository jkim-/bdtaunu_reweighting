#!/usr/bin/env python

import numpy as np

# only deal with rho2 for now...
rho2 = 1.185

rho2_err = 0.054

central = np.array([rho2])

print '+ central values (rho2)'
print rho2
print

print '+ up/down (rho2)'
print rho2 + rho2_err
print rho2 - rho2_err
print
