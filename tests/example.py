import tomtag as tt 
import numpy as np

tcc = 3
data_a = np.array([1,50,55,164])
data_b = np.array([2,56,15,194])

counts, inds_a, inds_b = tt.get_cc(data_a,data_b,len(data_a),len(data_b),tcc)

assert counts == tt.count(data_a,data_b,len(data_a),len(data_b),tcc)