#ifndef COMO_BYTEARRAY_H
#define COMO_BYTEARRAY_H

#include "comoobject.h"

typedef struct _como_bytearray {
 	como_object   base;
 	como_size_t   size;
 	como_size_t	  capacity;
 	unsigned char *data;
 } como_bytearray;

 extern como_type como_bytearray_type;

COMO_OBJECT_API como_object *como_bytearray_new(como_size_t size);

 #endif