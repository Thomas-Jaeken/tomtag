#include <stdlib.h>
#include <stdio.h>
#include "correlation.h"

int count(const long long int *tagsA, const long long int *tagsB, int sizeA, int sizeB, int tcc)
{
    int counts = 0;
    int iA = 0;
    int iB = 0;

    while (iA < sizeA && iB < sizeB)
    {
        if (llabs(tagsA[iA] - tagsB[iB]) <= tcc)
        {
            counts++;
            iA++;
            iB++;
        }
        else if (tagsA[iA] < tagsB[iB])
        {
            iA++;
        }
        else
        {
            iB++;
        }
    }

    return counts;
}

int get_cc(const long long int *tagsA, const long long int *tagsB, int sizeA, int sizeB, int tcc, long long int **inds_a, long long int **inds_b)
{
    int counts = 0;
    int iA = 0;
    int iB = 0;

    // Assume a maximum count (worst-case scenario, all elements match)
    *inds_a = malloc((sizeA) * sizeof(long long int));
    *inds_b = malloc((sizeB) * sizeof(long long int));

    while (iA < sizeA && iB < sizeB)
    {
        if (llabs(tagsA[iA] - tagsB[iB]) <= tcc)
        {
            *inds_a[counts] = iA;
            *inds_b[counts] = iB;
            counts++;
            iA++;
            iB++;
        }
        else if (tagsA[iA] < tagsB[iB])
        {
            iA++;
        }
        else
        {
            iB++;
        }
    }

    // Resize the array to the actual count
    *inds_a = realloc(*inds_a, counts * sizeof(long long int));
    *inds_b = realloc(*inds_b, counts * sizeof(long long int));

    return counts;
}

void histogram(const long long int *tagsA, const long long int *tagsB, int sizeA, int sizeB, int tcc, int *hist_data, long long int *delaysweep, long long int sizeDelay)
{
    //*hist_data = malloc((sizeDelay) * sizeof(int));

    int i = 0;
    for (i = 0; i < sizeDelay; i++)
    {
        long long int *temp_B_shifted = malloc((sizeB) * sizeof(long long int));
        int j = 0;
        for (j = 0; j < sizeB; j++)
        {
            temp_B_shifted[j] = tagsB[j] + delaysweep[i];
        }
        hist_data[i] = count(tagsA, temp_B_shifted, sizeA, sizeB, tcc);
        free(temp_B_shifted);
    }

    // the output is written into the hist_data variable
}