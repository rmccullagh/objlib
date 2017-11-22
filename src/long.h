#ifndef COMO_LONG_OBJECT
#define COMO_LONG_OBJECT

# if !(defined(COMO_BASE_INCLUDED))
#   error "Please do not include code.h directly"
#endif

typedef struct _como_long {
  como_object base;
  long value;
} como_long;

COMO_OBJECT_API como_object *como_longfromlong(long lval);

extern como_type como_long_type;

#endif
