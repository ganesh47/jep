/* -*- Mode: C; indent-tabs-mode: nil; c-basic-offset: 4 c-style: "K&R" -*- */
/* 
   jep - Java Embedded Python

   Copyright (c) 2015 JEP AUTHORS.

   This file is licenced under the the zlib/libpng License.

   This software is provided 'as-is', without any express or implied
   warranty. In no event will the authors be held liable for any
   damages arising from the use of this software.
   
   Permission is granted to anyone to use this software for any
   purpose, including commercial applications, and to alter it and
   redistribute it freely, subject to the following restrictions:

   1. The origin of this software must not be misrepresented; you
   must not claim that you wrote the original software. If you use
   this software in a product, an acknowledgment in the product
   documentation would be appreciated but is not required.

   2. Altered source versions must be plainly marked as such, and
   must not be misrepresented as being the original software.

   3. This notice may not be removed or altered from any source
   distribution.   
*/


/*
 * Contains includes and macros to enable compilation across multiple
 * platforms, with different compilers and both python 2 and 3.  This file
 * aims to be for Jep what pyport.h is for CPython.
 * 
 * TODO: Look into moving much of the python 2 vs 3 macros in util.h over
 * to this file.  Or perhaps those should get their own .h file.
 *
 */

// Python.h needs to be included first, see http://bugs.python.org/issue1045893
#include <Python.h>

#ifdef WIN32
# include "winconfig.h"
#endif

#if HAVE_CONFIG_H
# include <config.h>
#endif

#if HAVE_UNISTD_H
# include <sys/types.h>
# include <unistd.h>
#endif


#include <jni.h>

#ifndef _Included_jport
#define _Included_jport

/* Windows compatibility */
#ifdef WIN32
typedef __int64 jeplong;
#define FILE_SEP               '\\'
#else
typedef long long jeplong;
#define FILE_SEP               '/'
#endif // Windows compatibility


/* Python 3 compatibility */
#if PY_MAJOR_VERSION >= 3

// see https://mail.python.org/pipermail/python-porting/2012-April/000289.html
#define Py_TPFLAGS_HAVE_ITER 0

/* Python 3 does not support integers, only longs */
#define PyInt_AsLong(i)                   PyLong_AsLong(i)
#define PyInt_AS_LONG(i)                  PyLong_AsLong(i)
#define PyInt_Check(i)                    PyLong_Check(i)
#define PyInt_FromLong(i)                 PyLong_FromLong(i)

/* Python 3 separated Strings into PyBytes and PyUnicode */
#define PyString_FromString(str)          PyUnicode_FromString(str)
#define PyString_Check(str)               PyUnicode_Check(str)
#define PyString_FromFormat(fmt, ...)     PyUnicode_FromFormat(fmt, ##__VA_ARGS__)

/*
 * Python 3.3 drastically improved the unicode API.
 * For Python 3.2 support, see util.h.
 */
#if PY_MINOR_VERSION >= 3
  #define PyString_AsString(str)            PyUnicode_AsUTF8(str)
  #define PyString_AS_STRING(str)           PyUnicode_AsUTF8(str)
  #define PyString_Size(str)                PyUnicode_GetLength(str)
  #define PyString_GET_SIZE(str)            PyUnicode_GET_LENGTH(str)
#endif // Python 3.3+ String compatibility

#endif // Python 3 compatibility


#endif // ifndef _Included_jport
