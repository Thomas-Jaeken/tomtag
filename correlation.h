#ifndef CORRELATION_H
#define CORRELATION_H

int count(const long long int *tagsA, const long long int *tagsB, int sizeA, int sizeB, int tcc);

int get_cc(const long long int *tagsA, const long long int *tagsB, int sizeA, int sizeB, int tcc, long long int *inds_a, long long int *inds_b);

void histogram(const long long int *tagsA, const long long int *tagsB, int sizeA, int sizeB, int tcc, int *hist_data, long long int *delaysweep, long long int sizeDelay);

void trickle_merge(const long long int *tagsA, const long long int *tagsB, int sizeA, int sizeB, int chA, int chB, int *channels, long long int *tags);

void findDelay(int *channels, const long long int *tags, long long int sizeTags, int chA, int chB, long long int measCorrWindow, int measResolution, long long int *doubleDecay);

void trace(const long long int *tags, long long int sizeTags, int binsize, int *trace);

void synchronise(long long int *tags, const long long int *synctags, int sizeTags, int sizeSyncTags, long long int syncPeriod, float Precision);

#endif // CORRELATION_H