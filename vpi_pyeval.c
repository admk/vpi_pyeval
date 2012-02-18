#include <Python.h>
#include <vpi_user.h>
#include <veriuser.h>

#define kPyStmtLength 256

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
    char py_stmt[kPyStmtLength];
    strcpy(py_stmt, tf_getcstringp(1));
    int i = 2;
    while (true)
    {
        int tf_type = tf_typep(i);
        if (tf_type == TF_NULLPARAM)
            break;
        // convert argument to string and append
        char py_arg[kPyStmtLength];
        switch (tf_type)
        {
        case TF_STRING:
            strcpy(py_arg, tf_getcstringp(i));
            break;
        case TF_READONLY:
        case TF_READWRITE:
            sprintf(py_arg, "%d", tf_getp(i));
            break;
        case TF_READONLYREAL:
        case TF_READWRITEREAL:
            sprintf(py_arg, "%f", tf_getrealp(i));
            break;
        default:
            strcpy(py_arg, "XXXX");
        }
        strcat(py_stmt, py_arg);
        i++;
    }
    
    // return value
    tf_putp(0, pyeval(py_stmt));
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
