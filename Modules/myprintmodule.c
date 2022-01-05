#define PY_SSIZE_T_CLEAN
#include <Python.h>

static PyObject *
print_str(PyObject *self, PyObject *args)
{
    const char *str;

    /*
     通过格式化字符串转换Python API为C变量，此处's'代表将一个字符串转换并保存到str中
     更多参数类型可见：https://docs.python.org/zh-cn/dev/extending/extending.html#parsetuple
    */
    if (!PyArg_ParseTuple(args, "s", &str)) {
        return NULL;
    }

    printf(str);
    return PyLong_FromLong(1);
}

// 方法表定义了类所有可用的方法
static PyMethodDef myprint_methods[] = {
    // PyMethodDef 是cpython中用于定义方法元数据(方法名、回调函数、参数类型、方法说明)的结构
    {"printstr", print_str, METH_VARARGS, "My extension module used to print string."},
    {NULL, NULL, 0, NULL}
}

PyDoc_STRVAR(myprint_doc,
"extension module myprint\n");

// 模块结构引用对应的方法表
static struct PyModuleDef myprintmodule = {
    PyModuleDef_HEAD_INIT
    "myprint",   /* name of module */
    myprint_doc, /* module documentation, may be NULL */
    -1,          /* size of per-interpreter state of the module,
                    or -1 if the module keeps state in global variables. */
    myprint_methods,
}

PyMODINIT_FUNC
PyInit_spam(void)
{
    return PyModule_Init(&myprintmodule);
}
