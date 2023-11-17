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
    long long int *ind_a;
    long long int *ind_b;
    // int count = get_cc(tagsA, tagsB, sizeA, sizeB, tcc, &ind_a, &ind_b);
    int count = get_cc(tagsA, tagsB, sizeA, sizeB, tcc, &ind_a, &ind_b);

    // Convert indices array to Python object
    PyObject *inds_obj_a = PyList_New(count);
    PyObject *inds_obj_b = PyList_New(count);
    int i = 0;
    for (i = 0; i < count; i++)
    {
        PyList_SET_ITEM(inds_obj_a, i, PyLong_FromLong(ind_a[i]));
        PyList_SET_ITEM(inds_obj_b, i, PyLong_FromLong(ind_b[i]));
    }

    // Free memory allocated for indices array
    free(ind_a);
    free(ind_b);

    // Return a tuple containing the indices array and the count
    PyObject *resultTuple = PyTuple_Pack(3, PyLong_FromLong(count), inds_obj_a, inds_obj_b);

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

static PyMethodDef module_methods[] = {
    {"count", count_wrapper, METH_VARARGS, "Calculate correlation"},
    {"get_cc", get_cc_wrapper, METH_VARARGS, "find correlated events"},
    {"histogram", histogram_wrapper, METH_VARARGS, "construct histogram"},
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
