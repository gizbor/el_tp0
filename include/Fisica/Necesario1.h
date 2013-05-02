#ifndef NECESARY_H_INCLUDED
#define NECESARY_H_INCLUDED

#ifndef __STDIO_SET_
#include <stdio.h>
#define __STDIO_SET_
#endif

#ifndef __CSTRING_SET_
#include <cstring>
#define __CSTRING_SET_
#endif

#ifndef __CSTDLIB_SET_
#include <cstdlib>
#define __CSTDLIB_SET_
#endif

#ifndef __STRING_
#include <string.h>
#define __STRING_
#endif

#ifndef __STDLIB_
#include <stdlib.h>
#define __STDLIB_
#endif

#ifndef __IOSTREAM_
#include <iostream>
#define __IOSTREAM_
#endif

#ifndef __SSTREAM_
#include <sstream>
#define __SSTREAM_
#endif

#ifndef __TYPE_DEFINITIONS_ARCHI_VAR_
enum {ERROR_DE_APERTURA, \
            ERROR_DE_CREACION, \
            ERROR_DE_LECTURA_DATOS, \
            ERROR_DE_ESCRITURA_DATOS, \
            ERROR_DE_LECTURA_INDICE, \
            ERROR_DE_ESCRITURA_INDICE};
typedef int t_num_ref;
typedef unsigned long int t_reg_var_size;
typedef long int t_index_size; // Necesito valores negativos para errores
#define __TYPE_DEFINITIONS_ARCHI_VAR_
#endif

#endif // NECESARY_H_INCLUDED
