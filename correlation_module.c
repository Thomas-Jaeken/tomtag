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
    int count = get_cc(tagsA, tagsB, sizeA, sizeB, tcc, &ind_a, &ind_b);

    // Convert indices array to Python object
    PyObject *inds_obj_a = PyList_New(count);
    PyObject *inds_obj_b = PyList_New(count);
    for (int i = 0; i < count; i++) {
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

static PyMethodDef module_methods[] = {
    {"count", count_wrapper, METH_VARARGS, "Calculate correlation"},
    {"get_cc", get_cc_wrapper, METH_VARARGS, "find correlated events"},
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
