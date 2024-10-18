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

static PyObject *get_twofold_tags_wrapper(PyObject *self, PyObject *args)
{
    PyObject *tagsA_obj, *tagsB_obj;
    int sizeA, sizeB, tcc;

    // read in the python arguments
    if (!PyArg_ParseTuple(args, "OOiii", &tagsA_obj, &tagsB_obj, &sizeA, &sizeB, &tcc))
        return NULL;

    // format them into C types
    long long int *tagsA = (long long int *)PyArray_DATA(tagsA_obj);
    long long int *tagsB = (long long int *)PyArray_DATA(tagsB_obj);

    // pre-allocate space for the cc times
    long long int *inds_a = (long long int *)malloc(sizeA * sizeof(long long int));
    long long int *inds_b = (long long int *)malloc(sizeB * sizeof(long long int));
    
    // filter out the cc
    int count = get_twofolds(tagsA, tagsB, sizeA, sizeB, tcc, inds_a, inds_b);
    
    // Convert indices array to Python object
    PyObject *cc_obj_a = PyList_New(count);
    PyObject *cc_obj_b = PyList_New(count);
    int i = 0;
    for (i = 0; i < count; i++)
    {
        PyList_SET_ITEM(cc_obj_a, i, PyLong_FromLong(tagsA[inds_a[i]]));
        PyList_SET_ITEM(cc_obj_b, i, PyLong_FromLong(tagsB[inds_b[i]]));
    }

    // Free memory allocated for indices array
    free(inds_a);
    free(inds_b);

    // Return a tuple containing the indices array and the count
    PyObject *resultTuple = PyTuple_Pack(2,  cc_obj_a, cc_obj_b);

    return resultTuple;
}

static PyObject *get_twofold_tags_T3_wrapper(PyObject *self, PyObject *args)
{
    PyObject *tagsA_obj, *tagsB_obj, *d_tagsA_obj, *d_tagsB_obj;
    int sizeA, sizeB, tcc;

    // read in the python arguments
    if (!PyArg_ParseTuple(args, "OOOOiii", &tagsA_obj, &tagsB_obj, &d_tagsA_obj, &d_tagsB_obj, &sizeA, &sizeB, &tcc))
        return NULL;

    // format them into C types
    long long int *tagsA = (long long int *)PyArray_DATA(tagsA_obj);
    long long int *tagsB = (long long int *)PyArray_DATA(tagsB_obj);
    long long int *d_tagsA = (long long int *)PyArray_DATA(d_tagsA_obj);
    long long int *d_tagsB = (long long int *)PyArray_DATA(d_tagsB_obj);

    // pre-allocate space for the cc times
    long long int *inds_a = (long long int *)malloc(sizeA * sizeof(long long int));
    long long int *inds_b = (long long int *)malloc(sizeB * sizeof(long long int));
    
    // filter out the cc
    int count = get_twofolds(tagsA, tagsB, sizeA, sizeB, tcc, inds_a, inds_b);
    
    // Convert indices array to Python object
    PyObject *cc_obj_a = PyList_New(count);
    PyObject *cc_obj_b = PyList_New(count);
    int i = 0;
    for (i = 0; i < count; i++)
    {
        PyList_SET_ITEM(cc_obj_a, i, PyLong_FromLong(d_tagsA[inds_a[i]]));
        PyList_SET_ITEM(cc_obj_b, i, PyLong_FromLong(d_tagsB[inds_b[i]]));
    }

    // Free memory allocated for indices array
    free(inds_a);
    free(inds_b);

    // Return a tuple containing the indices array and the count
    PyObject *resultTuple = PyTuple_Pack(2,  cc_obj_a, cc_obj_b);

    return resultTuple;
}

static PyObject *get_threefold_tags_wrapper(PyObject *self, PyObject *args)
{
    PyObject *tagsA_obj, *tagsB_obj, *tagsC_obj;
    int sizeA, sizeB, sizeC, tcc;

    if (!PyArg_ParseTuple(args, "OOOiiii", &tagsA_obj, &tagsB_obj, &tagsC_obj, &sizeA, &sizeB, &sizeC, &tcc))
        return NULL;

    long long int *tagsA = (long long int *)PyArray_DATA(tagsA_obj);
    long long int *tagsB = (long long int *)PyArray_DATA(tagsB_obj);
    long long int *tagsC = (long long int *)PyArray_DATA(tagsC_obj);

    // Call the cc function
    long long int *inds_a = (long long int *)malloc(sizeA * sizeof(long long int));
    long long int *inds_b = (long long int *)malloc(sizeB * sizeof(long long int));
    long long int *inds_c = (long long int *)malloc(sizeC * sizeof(long long int));
    int count = get_threefolds(tagsA, tagsB, tagsC, sizeA, sizeB, sizeC, tcc, inds_a, inds_b, inds_c);

    // Convert indices array to Python object
    PyObject *cc_obj_a = PyList_New(count);
    PyObject *cc_obj_b = PyList_New(count);
    PyObject *cc_obj_c = PyList_New(count);
    int i = 0;
    for (i = 0; i < count; i++)
    {
        
        PyList_SET_ITEM(cc_obj_a, i, PyLong_FromLong(tagsA[inds_a[i]]));
        PyList_SET_ITEM(cc_obj_b, i, PyLong_FromLong(tagsB[inds_b[i]]));
        PyList_SET_ITEM(cc_obj_c, i, PyLong_FromLong(tagsC[inds_c[i]]));
        
    }

    // Free memory allocated for indices array
    free(inds_a);
    free(inds_b);
    free(inds_c);

    // Return a tuple containing the delays between the four channels
    PyObject *resultTuple = PyTuple_Pack(3, cc_obj_a, cc_obj_b, cc_obj_c);

    return resultTuple;
}

static PyObject *get_fourfold_tags_wrapper(PyObject *self, PyObject *args)
{
    PyObject *tagsA_obj, *tagsB_obj, *tagsC_obj, *tagsD_obj;
    int sizeA, sizeB, sizeC, sizeD, tcc;

    // read in the python arguments
    if (!PyArg_ParseTuple(args, "OOOOiiiii", &tagsA_obj, &tagsB_obj, &tagsC_obj, &tagsD_obj, &sizeA, &sizeB, &sizeC, &sizeD, &tcc))
        return NULL;

    // format them into C types
    long long int *tagsA = (long long int *)PyArray_DATA(tagsA_obj);
    long long int *tagsB = (long long int *)PyArray_DATA(tagsB_obj);
    long long int *tagsC = (long long int *)PyArray_DATA(tagsC_obj);
    long long int *tagsD = (long long int *)PyArray_DATA(tagsD_obj);

    // pre-allocate space for the cc times
    long long int *inds_a = (long long int *)malloc(sizeA * sizeof(long long int));
    long long int *inds_b = (long long int *)malloc(sizeB * sizeof(long long int));
    long long int *inds_c = (long long int *)malloc(sizeC * sizeof(long long int));
    long long int *inds_d = (long long int *)malloc(sizeD * sizeof(long long int));

    // filter out the cc
    int count = get_fourfolds(tagsA, tagsB, tagsC, tagsD, sizeA, sizeB, sizeC, sizeD, tcc, inds_a, inds_b, inds_c, inds_d);
    
    // Convert indices array to Python object
    PyObject *cc_obj_a = PyList_New(count);
    PyObject *cc_obj_b = PyList_New(count);
    PyObject *cc_obj_c = PyList_New(count);
    PyObject *cc_obj_d = PyList_New(count);
    int i = 0;
    for (i = 0; i < count; i++)
    {
        PyList_SET_ITEM(cc_obj_a, i, PyLong_FromLong(tagsA[inds_a[i]]));
        PyList_SET_ITEM(cc_obj_b, i, PyLong_FromLong(tagsB[inds_b[i]]));
        PyList_SET_ITEM(cc_obj_c, i, PyLong_FromLong(tagsC[inds_c[i]]));
        PyList_SET_ITEM(cc_obj_d, i, PyLong_FromLong(tagsD[inds_d[i]]));
    }

    // Free memory allocated for indices array
    free(inds_a);
    free(inds_b);
    free(inds_c);
    free(inds_d);

    // Return a tuple containing the delays between the four channels
    PyObject *resultTuple = PyTuple_Pack(4, cc_obj_a, cc_obj_b, cc_obj_c, cc_obj_d);

    return resultTuple;
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

static PyObject *sync_wrapper(PyObject *self, PyObject *args)
{
    PyObject *tags_obj, *synctags_obj;
    long long int sizeTags, sizeSyncTags;
    int syncPeriod;

    if (!PyArg_ParseTuple(args, "OOLLdd", &tags_obj, &synctags_obj, &sizeTags, &sizeSyncTags, &syncPeriod))
        return NULL;

    long long int *tags = (long long int *)PyArray_DATA(tags_obj);
    long long int *syncTags = (long long int *)PyArray_DATA(synctags_obj);

    // Call the function
    long long int *syncedTags = (long long int *)malloc(sizeTags * sizeof(long long int));
    synchronise(tags, syncTags, sizeTags, sizeSyncTags, syncPeriod, syncedTags);

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
    {"count_twofolds", count_wrapper, METH_VARARGS, "Calculate number of twofolds"},
    {"get_twofold_tags", get_twofold_tags_wrapper, METH_VARARGS, "find correlated timetags between 2 channels"},
    {"get_twofold_tags_T3", get_twofold_tags_T3_wrapper, METH_VARARGS, "find sync offset of coincidences between 2 channels"},
    {"get_threefold_tags", get_threefold_tags_wrapper, METH_VARARGS, "find correlated timetags between 3 channels"},
    {"get_fourfold_tags", get_fourfold_tags_wrapper, METH_VARARGS, "find correlated timetags between 4 channels"},
    {"histogram", histogram_wrapper, METH_VARARGS, "construct histogram"},
    {"sync_to_clock", sync_wrapper, METH_VARARGS, "use tags sampled from a known periodic signal to sync signaltags, mitigating the effect of a poor tagging oscillator."},
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
