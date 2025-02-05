#include <Python.h>
#include <stdio.h>

int main() {
    // Initialize the Python Interpreter
    Py_Initialize();

    // Import the Python script (module)
    PyObject *pName = PyUnicode_DecodeFSDefault("hello"); // "hello" is the name of the Python script (without .py)
    PyObject *pModule = PyImport_Import(pName);

    if (pModule != NULL) {
        // Get the function "greet" from the module
        PyObject *pFunc = PyObject_GetAttrString(pModule, "greet");

        if (pFunc && PyCallable_Check(pFunc)) {
            // Call the Python function with arguments
            PyObject *pArgs = PyTuple_Pack(1, PyUnicode_FromString("World"));
            PyObject *pValue = PyObject_CallObject(pFunc, pArgs);

            if (pValue != NULL) {
                // Print the result returned by Python
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
            printf("Function 'greet' not found or is not callable.\n");
        }
        Py_XDECREF(pFunc);
        Py_XDECREF(pModule);
    } else {
        PyErr_Print();
        printf("Failed to load Python module.\n");
    }

    // Finalize the Python Interpreter
    Py_Finalize();

    return 0;
}

