import tomtag as tt
import numpy as np

tagsA = np.array([12,679,1289,1487])
tagsB = np.array([20,409,1279,1887])
tcc = 15

counts = tt.count_twofolds(
    tagsA,
    tagsB,
    len(tagsA),
    len(tagsB),
    tcc
)

assert counts==2 