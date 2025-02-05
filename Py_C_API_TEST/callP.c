#include <Python.h>

int main() {
    // Initialize the Python interpreter
    Py_Initialize();

    // Check if the Python interpreter is initialized
    if (!Py_IsInitialized()) {
        fprintf(stderr, "Python initialization failed!\n");
        return 1;
    }

    // Load the Python module
    PyObject *pName = PyUnicode_DecodeFSDefault("hello");
    PyObject *pModule = PyImport_Import(pName);
    Py_XDECREF(pName);  // Release the reference to the module name

    if (pModule == NULL) {
        PyErr_Print();
        fprintf(stderr, "Failed to load the Python module\n");
        Py_Finalize();
        return 1;
    }

    // Get the Python function from the module
    PyObject *pFunc = PyObject_GetAttrString(pModule, "greet");

    // Check if the function is callable
    if (pFunc && PyCallable_Check(pFunc)) {
        // Prepare the argument (a Python string)
        PyObject *pArgs = PyTuple_Pack(1, PyUnicode_FromString("World"));

        // Call the Python function
        PyObject *pValue = PyObject_CallObject(pFunc, pArgs);

        // Check if the function call was successful
        if (pValue != NULL) {
            // Print the result
            printf("%s\n", PyUnicode_AsUTF8(pValue));
            Py_XDECREF(pValue);
        } else {
            PyErr_Print();
        }

        Py_XDECREF(pArgs);
    } else {
        if (PyErr_Occurred()) {
            PyErr_Print();
        }
        fprintf(stderr, "Cannot find function 'greet'\n");
    }

    // Clean up
    Py_XDECREF(pFunc);
    Py_XDECREF(pModule);

    // Finalize the Python interpreter
    Py_Finalize();
    
    return 0;
}
