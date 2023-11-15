#ifndef CORRELATION_H
#define CORRELATION_H

int count(const long long int *tagsA, const long long int *tagsB, int sizeA, int sizeB, int tcc);

int get_cc(const long long int *tagsA, const long long int *tagsB, int sizeA, int sizeB, int tcc, long long int **inds_a, long long int  **inds_b);
#endif // CORRELATION_H