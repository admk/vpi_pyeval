#include <Python.h>
#include <vpi_user.h>
#include <veriuser.h>

PyObject *globals = NULL;

int pyeval(const char *stmt)
{
    if (!globals)
    {
        // initialise python
        Py_Initialize();
        globals = PyModule_GetDict(PyImport_AddModule("__main__"));
    }
    // run as eval
    PyObject *py_result = PyRun_String(
            stmt, Py_eval_input, globals, globals);
    if (!PyErr_Occurred())
        return PyLong_AsLong(py_result);
    // run as exec
    PyErr_Clear();
    return PyRun_SimpleString(stmt);
}

static int pyeval_calltf(char *user_data)
{
    if (tf_typep(1) != TF_STRING)
        tf_error("$pyeval argument must be a literal string\n");

    tf_putp(0, pyeval(tf_getcstringp(1)));
    return 0;
}

void pyeval_register()
{
    // register pyeval callback function
    s_vpi_systf_data tf_data;
    tf_data.type = vpiSysFunc;
    tf_data.tfname = "$pyeval";
    tf_data.calltf = pyeval_calltf;
    tf_data.compiletf = NULL;
    tf_data.sizetf = 0;
    tf_data.user_data = 0;
    vpi_register_systf(&tf_data);
}

void (*vlog_startup_routines[])() =
{
    pyeval_register,
    0
};
