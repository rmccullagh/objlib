#ifndef COMO_FUNCTION_H
#define COMO_FUNCTION_H

# if !(defined(COMO_BASE_INCLUDED))
#   error "Please do not include function.h directly"
#endif

#define COMO_FUNCTION_LANG    0x00000001
#define COMO_FUNCTION_NATIVE  0x00000002

typedef como_object*(*como_function_handler)(como_object *);

typedef struct _como_function 
{
  como_object base;
  como_size_t flags;
  union 
  {
    struct _como_frame *frame;
    como_function_handler handler;
  } impl;
} como_function;

COMO_OBJECT_API como_object *como_functionfromframe(como_frame *frame);
COMO_OBJECT_API como_object *como_functionfromhandler(
  como_function_handler handler);

#define como_get_function(obj) ((como_function *)((obj)))

extern como_type como_function_type;

#endif