// correlation_module.c

#include <Python.h>
#include "correlation.h"
#include <numpy/arrayobject.h>

static PyObject *count_wrapper(PyObject *self, PyObject *args)
{
    PyObject *tagsA_obj, *tagsB_obj;
    int sizeA, sizeB, tcc;

    if (!PyArg_ParseTuple(args, "OOiii", &tagsA_obj, &tagsB_obj, &sizeA, &sizeB, &tcc))
        return NULL;

    long long int *tagsA = (long long int *)PyArray_DATA(tagsA_obj);
    long long int *tagsB = (long long int *)PyArray_DATA(tagsB_obj);

    int result = count(tagsA, tagsB, sizeA, sizeB, tcc);

    return PyLong_FromLong(result);
}

static PyObject *get_cc_wrapper(PyObject *self, PyObject *args)
{
    PyObject *tagsA_obj, *tagsB_obj;
    int sizeA, sizeB, tcc;

    if (!PyArg_ParseTuple(args, "OOiii", &tagsA_obj, &tagsB_obj, &sizeA, &sizeB, &tcc))
        return NULL;

    long long int *tagsA = (long long int *)PyArray_DATA(tagsA_obj);
    long long int *tagsB = (long long int *)PyArray_DATA(tagsB_obj);

    // Call the get_cc function
    long long int *inds_a = (long long int *)malloc(sizeA * sizeof(long long int));
    long long int *inds_b = (long long int *)malloc(sizeB * sizeof(long long int));
    // int count = get_cc(tagsA, tagsB, sizeA, sizeB, tcc, &inds_a, &inds_b);
    int count = get_cc(tagsA, tagsB, sizeA, sizeB, tcc, inds_a, inds_b);
    

    // Convert indices array to Python object
    PyObject *inds_obj_a = PyList_New(count);
    PyObject *inds_obj_b = PyList_New(count);
    int i = 0;
    for (i = 0; i < count; i++)
    {
        PyList_SET_ITEM(inds_obj_a, i, PyLong_FromLong(inds_a[i]));
        PyList_SET_ITEM(inds_obj_b, i, PyLong_FromLong(inds_b[i]));
    }

    // Free memory allocated for indices array
    free(inds_a);
    free(inds_b);

    // Return a tuple containing the indices array and the count
    PyObject *resultTuple = PyTuple_Pack(3, PyLong_FromLong(count), inds_obj_a, inds_obj_b);

    return resultTuple;
}

static PyObject *get_delays_wrapper(PyObject *self, PyObject *args)
{
    PyObject *tagsA_obj, *tagsB_obj;
    int sizeA, sizeB, tcc;

    if (!PyArg_ParseTuple(args, "OOiii", &tagsA_obj, &tagsB_obj, &sizeA, &sizeB, &tcc))
        return NULL;

    long long int *tagsA = (long long int *)PyArray_DATA(tagsA_obj);
    long long int *tagsB = (long long int *)PyArray_DATA(tagsB_obj);

    // Call the get_cc function
    long long int *inds_a = (long long int *)malloc(sizeA * sizeof(long long int));
    long long int *inds_b = (long long int *)malloc(sizeB * sizeof(long long int));
    // int count = get_cc(tagsA, tagsB, sizeA, sizeB, tcc, &inds_a, &inds_b);
    int count = get_cc(tagsA, tagsB, sizeA, sizeB, tcc, inds_a, inds_b);
    
    // pre-allocate delay memory
    int *delays = (int *)malloc(count * sizeof(int));

    // get delays between cc
    get_delays(tagsA, tagsB, inds_a, inds_b, delays, count,tcc);



    // Convert indices array to Python object
    PyObject *delays_obj = PyList_New(count);
    int i = 0;
    for (i = 0; i < count; i++)
    {
        
        PyList_SET_ITEM(delays_obj, i, PyLong_FromLong(delays[i]));
        
    }

    // Free memory allocated for indices array
    free(inds_a);
    free(inds_b);
    free(delays);

    return delays_obj;
}

static PyObject *histogram_wrapper(PyObject *self, PyObject *args)
{
    PyObject *tagsA_obj, *tagsB_obj, *delays_obj;
    int sizeA, sizeB, tcc, sizeDelay;

    if (!PyArg_ParseTuple(args, "OOiiiiO", &tagsA_obj, &tagsB_obj, &sizeA, &sizeB, &tcc, &sizeDelay, &delays_obj))
        return NULL;

    long long int *tagsA = (long long int *)PyArray_DATA(tagsA_obj);
    long long int *tagsB = (long long int *)PyArray_DATA(tagsB_obj);
    long long int *delaySweep = (long long int *)PyArray_DATA(delays_obj);

    // Call the histogram function
    int *hist_data = (int *)malloc(sizeDelay * sizeof(int));
    histogram(tagsA, tagsB, sizeA, sizeB, tcc, hist_data, delaySweep, sizeDelay);

    // Convert indices array to Python object
    PyObject *hist_obj = PyList_New(sizeDelay);
    int i = 0;
    for (i = 0; i < sizeDelay; i++)
    {
        PyList_SET_ITEM(hist_obj, i, PyLong_FromLong(hist_data[i]));
    }

    // Free memory allocated for indices array
    free(hist_data);

    return hist_obj;
}

static PyObject *trickle_merge_wrapper(PyObject *self, PyObject *args)
{
    PyObject *tagsA_obj, *tagsB_obj;
    int  ch_a, ch_b;
    long long int sizeA, sizeB;

    if (!PyArg_ParseTuple(args, "OOLLii", &tagsA_obj, &tagsB_obj, &sizeA, &sizeB, &ch_a, &ch_b))
        return NULL;

    long long int *tagsA = (long long int *)PyArray_DATA(tagsA_obj);
    long long int *tagsB = (long long int *)PyArray_DATA(tagsB_obj);

    // Call the histogram function
    int *channels = (int *)malloc((sizeA+sizeB) * sizeof(int));
    long long int *tags = (long long int *)malloc((sizeA+sizeB) * sizeof(long long int));
    trickle_merge(tagsA, tagsB, sizeA, sizeB, ch_a, ch_b, channels, tags);

    // Convert indices array to Python object
    PyObject *channels_obj = PyList_New(sizeA+sizeB);
    PyObject *tags_obj = PyList_New(sizeA+sizeB);
    int i = 0;
    for (i = 0; i < sizeA+sizeB; i++)
    {
        PyList_SET_ITEM(tags_obj, i, PyLong_FromLong(tags[i]));
        PyList_SET_ITEM(channels_obj, i, PyLong_FromLong(channels[i]));
    }

    // Free memory allocated for indices array
    free(channels);
    free(tags);

    PyObject *resultTuple = PyTuple_Pack(2, channels_obj, tags_obj);

    return resultTuple;
}

static PyObject *findDelay_wrapper(PyObject *self, PyObject *args)
{
    PyObject *tagsA_obj, *tagsB_obj;
    int  ch_a, ch_b, measResolution;
    long long int measCorrWindow, sizeA, sizeB;

    if (!PyArg_ParseTuple(args, "OOLLiiLi", &tagsA_obj, &tagsB_obj, &sizeA, &sizeB, &ch_a, &ch_b, &measCorrWindow, &measResolution))
        return NULL;

    long long int *tagsA = (long long int *)PyArray_DATA(tagsA_obj);
    long long int *tagsB = (long long int *)PyArray_DATA(tagsB_obj);

    

    // Call the find_delay function
    long long int sizeDecay = measCorrWindow / measResolution;
    long long int *doubleDecay = (long long int *)malloc(sizeDecay * sizeof(long long int));
    long long int *tags = (long long int *)malloc((sizeA+sizeB)*sizeof(long long int));
    int *channels = (int *)malloc((sizeA+sizeB)*sizeof(int));
    trickle_merge(tagsA, tagsB, sizeA, sizeB, ch_a, ch_b, channels, tags);
    findDelay(channels, tags, sizeA + sizeB, ch_a, ch_b, measCorrWindow, measResolution, doubleDecay);

    // Convert outcome array to Python object
    PyObject *doubleDecay_obj = PyList_New(sizeDecay);
    int i = 0;
    for (i = 0; i < sizeDecay; i++)
    {
        PyList_SET_ITEM(doubleDecay_obj, i, PyLong_FromLong(doubleDecay[i]));
    }

    // Free memory allocated for indices array
    free(channels);
    free(tags);
    free(doubleDecay);

    return doubleDecay_obj;
}

static PyObject *trace_wrapper(PyObject *self, PyObject *args)
{
    PyObject *tags_obj;
    int binsize;
    long long int sizeTags;

    if (!PyArg_ParseTuple(args, "OLi", &tags_obj, &sizeTags, &binsize))
        return NULL;

    long long int *tags = (long long int *)PyArray_DATA(tags_obj);

    // Call the trace function
    long long int sizetrace = tags[sizeTags-1] / binsize;
    int* trace_result= (int*)malloc(sizeof(int)*sizetrace);
    int k = 0;
    for (k=0;k<sizetrace;k++){trace_result[k]=0;}
    trace(tags, sizeTags, binsize, trace_result);

    // Convert outcome array to Python object
    PyObject *trace_obj = PyList_New(sizetrace);
    int i = 0;
    for (i = 0; i < sizetrace; i++)
    {
        PyList_SET_ITEM(trace_obj, i, PyLong_FromLong(trace_result[i]));
    }

    // Free memory allocated for indices array
    free(trace_result);

    return trace_obj;
}

static PyObject *sync_wrapper(PyObject *self, PyObject *args)
{
    PyObject *tags_obj, *synctags_obj;
    long long int sizeTags, sizeSyncTags;
    double syncPeriod, Precision;

    if (!PyArg_ParseTuple(args, "OOLLdd", &tags_obj, &synctags_obj, &sizeTags, &sizeSyncTags, &syncPeriod, &Precision))
        return NULL;

    long long int *tags = (long long int *)PyArray_DATA(tags_obj);
    long long int *syncTags = (long long int *)PyArray_DATA(synctags_obj);

    // Call the function
    long long int *syncedTags = (long long int *)malloc(sizeTags * sizeof(long long int));
    synchronise(tags, syncTags, sizeTags, sizeSyncTags, syncPeriod, Precision, syncedTags);

    // Convert outcome array to Python object
    PyObject *tags_synced_obj = PyList_New(sizeTags);
    int i = 0;
    for (i = 0; i < sizeTags; i++)
    {
        PyList_SET_ITEM(tags_synced_obj, i, PyLong_FromLong(syncedTags[i]));
    }

    // Free memory allocated for indices array
    free(syncedTags);

    return tags_synced_obj;
}

static PyMethodDef module_methods[] = {
    {"count", count_wrapper, METH_VARARGS, "Calculate correlation"},
    {"get_cc", get_cc_wrapper, METH_VARARGS, "find correlated events"},
    {"get_delays", get_delays_wrapper, METH_VARARGS, "find delays between correlated events"},
    {"histogram", histogram_wrapper, METH_VARARGS, "construct histogram"},
    {"double_decay", findDelay_wrapper, METH_VARARGS, "create double decay"},
    {"trickle", trickle_merge_wrapper, METH_VARARGS, "merge two arrays"},
    {"trace", trace_wrapper, METH_VARARGS, "bin counts into binsize sized bins"},
    {"sync", sync_wrapper, METH_VARARGS, "use a periodic signal to sync a random signal."},
    {NULL, NULL, 0, NULL}};

static struct PyModuleDef module_definition = {
    PyModuleDef_HEAD_INIT,
    "tomtag",
    NULL,
    -1,
    module_methods};

PyMODINIT_FUNC PyInit_tomtag(void)
{
    return PyModule_Create(&module_definition);
}
