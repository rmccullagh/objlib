#ifndef COMO_CODE_OBJECT_H
#define COMO_CODE_OBJECT_H

# if !(defined(COMO_BASE_INCLUDED))
#   error "Please do not include code.h directly"
#endif

typedef struct _como_code 
{
  como_container base;
  como_uint32_t **code;
} como_code;

COMO_OBJECT_API como_object  *como_code_new(como_size_t cap);
COMO_OBJECT_API como_object  *como_code_push(como_object *, como_uint32_t);
COMO_OBJECT_API como_uint32_t como_code_get(como_object *, como_size_t);

#define como_get_code(x) ((como_code *)(x))

extern como_type como_code_type;

#endif
