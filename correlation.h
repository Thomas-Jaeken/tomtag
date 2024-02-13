#ifndef CORRELATION_H
#define CORRELATION_H

int count(const long long int *tagsA, const long long int *tagsB, int sizeA, int sizeB, int tcc);

int minarg(long long int a, long long int b, long long int c, long long int d);

long long int maxOfFour(long long int a, long long int b, long long int c, long long int d);

long long int minOfFour(long long int a, long long int b, long long int c, long long int d);

long long int spread(long long int a, long long int b, long long int c, long long int d);

int count_fourfolds(const long long int *tagsA, const long long int *tagsB, const long long int *tagsC, const long long int *tagsD, int sizeA, int sizeB, int sizeC, int sizeD, int tcc);

int get_fourfolds(const long long int *tagsA, const long long int *tagsB, const long long int *tagsC, const long long int *tagsD, int sizeA, int sizeB, int sizeC, int sizeD, int tcc, long long int *inds_a, long long int *inds_b, long long int *inds_c, long long int *inds_d);

int get_cc(const long long int *tagsA, const long long int *tagsB, int sizeA, int sizeB, int tcc, long long int *inds_a, long long int *inds_b);

void get_delays(const long long int *tagsA, const long long int *tagsB, long long int *inds_a, long long int *inds_b, int *delays, long long int sizeDelay, int tcc);

void histogram(const long long int *tagsA, const long long int *tagsB, int sizeA, int sizeB, int tcc, int *hist_data, long long int *delaysweep, long long int sizeDelay);

void trickle_merge(const long long int *tagsA, const long long int *tagsB, int sizeA, int sizeB, int chA, int chB, int *channels, long long int *tags);

void findDelay(int *channels, const long long int *tags, long long int sizeTags, int chA, int chB, long long int measCorrWindow, int measResolution, long long int *doubleDecay);

void trace(const long long int *tags, long long int sizeTags, int binsize, int *trace);

void synchronise(const long long int *tags, const long long int *synctags, int sizeTags, int sizeSyncTags, double syncPeriod, double Precision, long long int *syncedTags);

#endif // CORRELATION_H