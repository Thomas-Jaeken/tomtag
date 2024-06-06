#include <stdlib.h>
#include <stdio.h>
#include <math.h>
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

int minarg4(long long int a, long long int b, long long int c, long long int d) {
    long long int min = a;
    int result = 0;

    if (b < min) {
        min = b;
        result = 1;
    }
    if (c < min) {
        min = c;
        result = 2;
    }
    if (d < min) {
        min = d;
        result = 3;
    }

    return result;
}

long long int maxOfFour(long long int a, long long int b, long long int c, long long int d) {
    long long int max = a;

    if (b > max) {
        max = b;
    }
    if (c > max) {
        max = c;
    }
    if (d > max) {
        max = d;
    }

    return max;
}

long long int minOfFour(long long int a, long long int b, long long int c, long long int d) {
    long long int min = a;

    if (b < min) {
        min = b;
    }
    if (c < min) {
        min = c;
    }
    if (d < min) {
        min = d;
    }

    return min;
}

long long int spread4(long long int a, long long int b, long long int c, long long int d)
{
    long long int result = maxOfFour(a, b, c, d) - minOfFour(a, b, c, d);
    return result;
}
int minarg3(long long int a, long long int b, long long int c) {
    long long int min = a;
    int result = 0;

    if (b < min) {
        min = b;
        result = 1;
    }
    if (c < min) {
        min = c;
        result = 2;
    }

    return result;
}

long long int maxOfThree(long long int a, long long int b, long long int c) {
    long long int max = a;

    if (b > max) {
        max = b;
    }
    if (c > max) {
        max = c;
    }

    return max;
}

long long int minOfThree(long long int a, long long int b, long long int c) {
    long long int min = a;

    if (b < min) {
        min = b;
    }
    if (c < min) {
        min = c;
    }

    return min;
}

long long int spread3(long long int a, long long int b, long long int c)
{
    long long int result = maxOfThree(a, b, c) - minOfThree(a, b, c);
    return result;
}

int get_fourfolds(const long long int *tagsA, const long long int *tagsB, const long long int *tagsC, const long long int *tagsD, int sizeA, int sizeB, int sizeC, int sizeD, int tcc, long long int *inds_a, long long int *inds_b, long long int *inds_c, long long int *inds_d)
{
    int counts = 0;
    int iA = 0;
    int iB = 0;
    int iC = 0;
    int iD = 0;

    while (iA < sizeA && iB < sizeB && iC < sizeC && iD < sizeD)
    {
        if (spread4(tagsA[iA],tagsB[iB],tagsC[iC],tagsD[iD]) <= tcc)  // the distance between the highest and lowest is tcc (this way the bin is the same width as for 2folds)
        {
            inds_a[counts] = iA;
            inds_b[counts] = iB;
            inds_c[counts] = iC;
            inds_d[counts] = iD;
            counts++;
            iA++;
            iB++;
            iC++;
            iD++;
        }
        else  // we increase the trailing tag
        {
            int i = minarg4(tagsA[iA],tagsB[iB],tagsC[iC],tagsD[iD]);
            if(i==0){
                iA++;
            }
            else if(i==1){
                iB++;
            }
            else if(i==2){
                iC++;
            }
            else if(i==3){
                iD++;
            }
        }
    }

    return counts;
}

int get_threefolds(const long long int *tagsA, const long long int *tagsB, const long long int *tagsC, int sizeA, int sizeB, int sizeC, int tcc, long long int *inds_a, long long int *inds_b, long long int *inds_c)
{
    int counts = 0;
    int iA = 0;
    int iB = 0;
    int iC = 0;

    while (iA < sizeA && iB < sizeB && iC < sizeC)
    {
        if (spread3(tagsA[iA],tagsB[iB],tagsC[iC]) <= tcc)  // the distance between the highest and lowest is tcc (this way the bin is the same width as for 2folds)
        {
            inds_a[counts] = iA;
            inds_b[counts] = iB;
            inds_c[counts] = iC;
            counts++;
            iA++;
            iB++;
            iC++;
        }
        else  // we increase the trailing tag
        {
            int i = minarg3(tagsA[iA],tagsB[iB],tagsC[iC]);
            if(i==0){
                iA++;
            }
            else if(i==1){
                iB++;
            }
            else if(i==2){
                iC++;
            }
        }
    }

    return counts;
}

int get_twofolds(const long long int *tagsA, const long long int *tagsB, int sizeA, int sizeB, int tcc, long long int *inds_a, long long int *inds_b)
{
    int counts = 0;
    int iA = 0;
    int iB = 0;

    while (iA < sizeA && iB < sizeB)
    {
        if (llabs(tagsA[iA] - tagsB[iB]) <= tcc)
        {
            inds_a[counts] = iA;
            inds_b[counts] = iB;
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

void histogram(const long long int *tagsA, const long long int *tagsB, int sizeA, int sizeB, int tcc, int *hist_data, long long int *delaysweep, long long int sizeDelay)
{
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

void synchronise(const long long int *tags, const long long int *synctags, int sizeTags, int sizeSyncTags, int syncPeriod, long long int *syncedTags)
{
    int i;
    int j = 0;
    while(tags[j]<synctags[0]){
        syncedTags[j] = tags[j];
        j++;  // we don't know if a sync or signal will come first, in the former case, that bit cannot be synced
    }
    for(i=0; i<sizeSyncTags-1;i++)
    {   
        while(j<sizeTags && tags[j]<synctags[i+1])
        {
            syncedTags[j] = tags[j] - synctags[i] + i * syncPeriod;
            j++;
        }
    }
    while(j<sizeTags){
        syncedTags[j] = tags[j] - synctags[sizeSyncTags] + sizeSyncTags * syncPeriod ;
        j++;  // we don't know if a sync or signal will come last, in the latter case, that bit cannot be synced
    }
    // every tag gets remapped to where the nearest synctag should be if it really was a 
}
