#include <Python.h>

#include "tuntap.h"

static PyObject *
wrap_tuntap_open(PyObject *self, PyObject *args, int isTap) {
  char *dev;

  int ok = PyArg_ParseTuple(args, "s", &dev);
  if(!ok)
    return NULL;

  int fd;
  if(isTap) {
    fd = tap_open(dev);
  } else {
    fd = tun_open(dev);
  }

  if(fd < 0)
    return NULL;

  PyObject *io, *f;

  io = PyImport_ImportModule("io");
  if (io == NULL)
    return NULL;

  f = PyObject_CallMethod(io, "open", "isi", fd, "r+b", 0);
  Py_DECREF(io);

  if (f == NULL)
    return NULL;

  return f;
}

static PyObject *
wrap_tap_open(PyObject *self, PyObject *args) {
  return wrap_tuntap_open(self, args, 1);
}

static PyObject *
wrap_tun_open(PyObject *self, PyObject *args) {
  return wrap_tuntap_open(self, args, 0);
}

static PyMethodDef methods[] = {
  {"tap_open", wrap_tap_open, METH_VARARGS, "Open TAP adapter file for 'r+b'"},
  {"tun_open", wrap_tun_open, METH_VARARGS, "Open TUN adapter file for 'r+b'"},
  {NULL, NULL, 0, NULL}
};

PyMODINIT_FUNC
inittuntap() {
  Py_InitModule("tuntap", methods);
}
