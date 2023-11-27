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

void synchronise(long long int *tags, const long long int *synctags, int sizeTags, int sizeSyncTags, long long int syncPeriod, float Precision)
{
    int i;
    int j = 0;
    for(i=0; i<sizeSyncTags-1;i++)
    {   
        while(tags[j]<synctags[i+i])
        {
            tags[j] = tags[j] - synctags[i] + (int)(i * syncPeriod / Precision);
            j++;
        }
    }
    // every tag gets remapped to where the nearest synctag should be if it really was a 
}