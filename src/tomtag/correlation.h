#ifndef CORRELATION_H
#define CORRELATION_H

int count(const long long int *tagsA, const long long int *tagsB, int sizeA, int sizeB, int tcc);

int minarg4(long long int a, long long int b, long long int c, long long int d);

long long int maxOfFour(long long int a, long long int b, long long int c, long long int d);

long long int minOfFour(long long int a, long long int b, long long int c, long long int d);

long long int spread4(long long int a, long long int b, long long int c, long long int d);

int minarg3(long long int a, long long int b, long long int c);

long long int maxOfThree(long long int a, long long int b, long long int c);

long long int minOfThree(long long int a, long long int b, long long int c);

long long int spread3(long long int a, long long int b, long long int c);

int get_fourfolds(const long long int *tagsA, const long long int *tagsB, const long long int *tagsC, const long long int *tagsD, int sizeA, int sizeB, int sizeC, int sizeD, int tcc, long long int *inds_a, long long int *inds_b, long long int *inds_c, long long int *inds_d);

int get_threefolds(const long long int *tagsA, const long long int *tagsB, const long long int *tagsC, int sizeA, int sizeB, int sizeC, int tcc, long long int *inds_a, long long int *inds_b, long long int *inds_c);

int get_twofolds(const long long int *tagsA, const long long int *tagsB, int sizeA, int sizeB, int tcc, long long int *inds_a, long long int *inds_b);

void histogram(const long long int *tagsA, const long long int *tagsB, int sizeA, int sizeB, int tcc, int *hist_data, long long int *delaysweep, long long int sizeDelay);

void synchronise(const long long int *tags, const long long int *synctags, int sizeTags, int sizeSyncTags, int syncPeriod, long long int *syncedTags);

#endif // CORRELATION_H