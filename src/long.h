#ifndef COMO_LONG_OBJECT
#define COMO_LONG_OBJECT

# if !(defined(COMO_BASE_INCLUDED))
#   error "Please do not include long.h directly"
#endif

typedef struct _como_long {
  como_object base;
  long value;
} como_long;

COMO_OBJECT_API como_object *como_longfromlong(long lval);

#define como_get_long(o) (como_long *)((o))

extern como_type como_long_type;

#endif
