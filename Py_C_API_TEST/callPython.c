#include <Python.h>
#include <stdio.h>

int main() {
    // Initialize the Python Interpreter
    Py_Initialize();

    PyRun_SimpleString("import sys");
    PyRun_SimpleString("sys.path.append(\"/home/rcraig8/Research/Research/Py_C_API_TEST\")");

    // Import the Python script (module)
    PyObject *pName = PyUnicode_DecodeFSDefault("ollamatest"); // "ollamatest" is the name of the Python script (without .py)
    PyObject *pModule = PyImport_Import(pName);
    

    if (pModule != NULL) {
        // Get the function "greet" from the module
        PyObject *pFunc = PyObject_GetAttrString(pModule, "comment");
	const char *text = "You are tasked to generate comprehensive Doxygen-style comments for a given C++ function. The generated comments should include sections for the function's @fn followed by fully qualified function signature, a brief description as a short, one-sentence summary or tagline that concisely describes the purpose of the function or entity, detailed description for background context, implementation details including algorithms used if applicable, parameters, return value, warnings, preconditions, postconditions, any relevant notes. Make sure your generated comments are clear and follow Doxygen formatting conventions. The comments should be suitable to be directly saved into a separated dox file later. Please use @tag_name instead of \\tag_name in the comments. The comments must start with a line including @fn full_qualified_function_signature, without its function body. Please do not use markdown syntax, use plain text instead. Please do not output anything other than the requested Doxygen-style comments, even when reporting errors. Please follow the example below: /** @fn long long calculateFactorial(int n) @brief Calculates the factorial of a non-negative integer. This function computes the factorial of a given non-negative integer using a recursive algorithm. The factorial of a number n is defined as the product of all positive integers less than or equal to n. @param n The non-negative integer for which the factorial is to be calculated. Must be greater than or equal to 0. If n is greater than 20, the result may overflow a 64-bit integer. @return The factorial of the input integer n. Returns 1 if n is 0, as 0! is defined as 1. ... other details are omitted here */ Below is the full C++ function definition: ```cpp \"int add(int a, int b) {return a + b;}\" ``` If the function definition is empty or ill-formed, output the following Doxygen-style comments as your error message:";
        if (pFunc && PyCallable_Check(pFunc)) {
            // Call the Python function with arguments
            PyObject *pArgs = PyTuple_Pack(1, PyUnicode_FromString(text));
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
