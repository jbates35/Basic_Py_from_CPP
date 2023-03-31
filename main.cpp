#include <iostream>
#include <Python.h>

using namespace std;

int main(int argc, char *argv[])
{
    //Initialize the Python Interpreter
    Py_Initialize();

    // Add the current directory to the Python module search path
    PySys_SetPath(L".");

    // Add python module expressstring
    PyObject *pModule = PyImport_ImportModule("foo");

    if(pModule == NULL) 
    {
        cout << "Error: Can't find module foo\n";
        return 1;
    }
    
    // Add python function
    PyObject *pFunc = PyObject_GetAttrString(pModule, "bar");

    // Make sure python function is callable
    if(PyErr_Occurred() || !PyCallable_Check(pFunc))
    {
        cout << "Error: Can't find function bar\n";
        return 1;
    }

    //Create empty tuple
    PyObject *pArgs = PyTuple_New(0);
    PyObject *pRetVal = PyObject_CallObject(pFunc, pArgs);

    Py_DECREF(pArgs);

    //Make sure return value is something
    if(pRetVal == NULL)
    {
        PyErr_Print();
        return 1;
    }    

    //Now parse through the return string
    char *pStr = NULL;
    if (PyArg_Parse(pRetVal, "s", &pStr))
    {
        cout << "Output string: " << pStr << "\n";
    }    
    else
    {
        PyErr_Print();
    }

    //Free memory
    Py_DECREF(pRetVal);
    Py_DECREF(pFunc);
    Py_DECREF(pModule);

    Py_Finalize();

    cout << "Hello world from cpp\n";
    return 0;
}