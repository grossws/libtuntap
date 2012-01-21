/*
 * Copyright (c) 2012, Konstantin Gribov. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the documentation and/or other materials provided with the
 *    distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 * COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 * BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 * ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

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
