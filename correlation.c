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

int minarg(long long int a, long long int b, long long int c, long long int d) {
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

long long int spread(long long int a, long long int b, long long int c, long long int d)
{
    long long int result = maxOfFour(a, b, c, d) - minOfFour(a, b, c, d);
    return result;
}

int count_fourfolds(const long long int *tagsA, const long long int *tagsB, const long long int *tagsC, const long long int *tagsD, int sizeA, int sizeB, int sizeC, int sizeD, int tcc)
{
    int counts = 0;
    int iA = 0;
    int iB = 0;
    int iC = 0;
    int iD = 0;

    while (iA < sizeA && iB < sizeB && iC < sizeC && iD < sizeD)
    {
        if (spread(tagsA[iA],tagsB[iB],tagsC[iC],tagsD[iD]) <= tcc)  // the distance between the highest and lowest is tcc (this way the bin is the same width as for 2folds)
        {
            counts++;
            iA++;
            iB++;
            iC++;
            iD++;
        }
        else  // we increase the trailing tag
        {
            int i = minarg(tagsA[iA],tagsB[iB],tagsC[iC],tagsD[iD]);
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

int get_fourfolds(const long long int *tagsA, const long long int *tagsB, const long long int *tagsC, const long long int *tagsD, int sizeA, int sizeB, int sizeC, int sizeD, int tcc, long long int *inds_a, long long int *inds_b, long long int *inds_c, long long int *inds_d)
{
    int counts = 0;
    int iA = 0;
    int iB = 0;
    int iC = 0;
    int iD = 0;

    while (iA < sizeA && iB < sizeB && iC < sizeC && iD < sizeD)
    {
        if (spread(tagsA[iA],tagsB[iB],tagsC[iC],tagsD[iD]) <= tcc)  // the distance between the highest and lowest is tcc (this way the bin is the same width as for 2folds)
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
            int i = minarg(tagsA[iA],tagsB[iB],tagsC[iC],tagsD[iD]);
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

int get_cc(const long long int *tagsA, const long long int *tagsB, int sizeA, int sizeB, int tcc, long long int *inds_a, long long int *inds_b)
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

void get_delays(const long long int *tagsA, const long long int *tagsB, long long int *inds_a, long long int *inds_b, int *delays, long long int sizeDelay, int tcc)
{
    // assume the counts are already aligned, with a large cc window e.g.
    int i;
    for (i=0;i<sizeDelay;i++){
        
        delays[i] = tagsA[inds_a[i]] - tagsB[inds_b[i]];
         
    }
    
    // the output is written into the delays variable
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


void trickle_merge(const long long int *tagsA, const long long int *tagsB, int sizeA, int sizeB, int chA, int chB, int *channels, long long int *tags){
    // create 2 arrays that represent tags and identities of the counts in each chennel ordered by tag.
    int indA = 0;
    int indB = 0;
    int i = 0;
    for (i=0;i<sizeA+sizeB;i++){
        if (indA>=sizeA){
            tags[i] = tagsB[indB];
            indB++;
        }
        else if (indB>=sizeB){
            tags[i] = tagsA[indA];
            indA++;
        }
        else if (tagsA[indA]>=tagsB[indB]){
            channels[i] = chB;
            tags[i] = tagsB[indB];
            indB++;
        }
        else{
            channels[i] = chA;
            tags[i] = tagsA[indA];
            indA++;
        }
    }
}

void findDelay(int *channels, const long long int *tags, long long int sizeTags, int chA, int chB, long long int measCorrWindow, int measResolution, long long int *doubleDecay){
    // this function requires a sorting of the time tags across both channels, 
    // so we just use what comes out of the UQD.
    // essentially we create a histogram of the delays between the two channels. (uncorrelated)
    long long int prev_a = 0;
    long long int prev_b = 0;
    long long int sizeDecay = measCorrWindow / measResolution;
    long long int CentralBin = measCorrWindow /measResolution/ 2;
    int j =0;
    for (j = 0; j<sizeDecay; j++){doubleDecay[j]=0;}

    int i = 0;
    for (i=0; i < sizeTags; i++){
        if (channels[i] == chA){
            prev_a = tags[i];
            long long int delta = tags[i] - prev_b;

            // store this delay
            if (delta <  measCorrWindow / 2){
                doubleDecay[CentralBin - delta/measResolution-1]++;
            }
        }
        else if (channels[i] == chB){
            prev_b = tags[i];
            long long int delta = tags[i] - prev_a;

            // store this delay
            if (delta <  measCorrWindow / 2){
                doubleDecay[CentralBin + delta/measResolution]++;
            }
        }

    }
    // the outcome is stored in doubleDecay
    // for (j = 0; j<sizeDecay; j++){
    //     if (doubleDecay[j]>0){
    //     printf("%lli, %i\n",doubleDecay[j], j);
    //     }
    //     }
}

void trace(const long long int *tags, long long int sizeTags, int binsize, int *trace)
{
    int counter = 0;
    long long int end_of_bin=0;
    int j = 0;
    int i = 0;
    for (i=0;i<sizeTags;i++){
        counter++;
        if (tags[i]>end_of_bin){
            trace[j] = counter;
            counter = 0;
            end_of_bin += binsize;
        }
    }
    // result in trace.
}

void synchronise(const long long int *tags, const long long int *synctags, int sizeTags, int sizeSyncTags, double syncPeriod, double Precision, long long int *syncedTags)
{
    int i;
    int j = 0;
    while(tags[j]<synctags[0]){
        syncedTags[j] = tags[j];
        j++;  // we don't know if a sync or signal will come first.
    }
    for(i=0; i<sizeSyncTags-1;i++)
    {   
        while(j<sizeTags && tags[j]<synctags[i+1])
        {
            syncedTags[j] = tags[j] - synctags[i] + (int)(i * syncPeriod / Precision);
            j++;
        }
    }
    while(j<sizeTags){
        syncedTags[j] = tags[j] - synctags[sizeSyncTags] + (int)(sizeSyncTags * syncPeriod / Precision);
        j++;  // we don't know if a sync or signal will come last.
    }
    // every tag gets remapped to where the nearest synctag should be if it really was a 
}