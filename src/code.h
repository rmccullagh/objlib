#ifndef COMO_CODE_OBJECT_H
#define COMO_CODE_OBJECT_H

#include "comoobject.h"
#include "system.h"

typedef struct _como_code 
{
  como_object   base;
  como_size_t   size;
  como_size_t   capacity;
  como_uint32_t *code;
} como_code;

COMO_OBJECT_API como_object  *como_code_new();
COMO_OBJECT_API como_object  *como_code_push(como_object *, como_uint32_t);
COMO_OBJECT_API como_uint32_t como_code_get(como_object *, como_uint32_t);

#define como_get_code(x) ((como_code *)(x))

extern como_type como_code_type;

#endif
