#ifndef COMO_DOUBLE_OBJECT_H
#define COMO_DOUBLE_OBJECT_H

# if !(defined(COMO_BASE_INCLUDED))
#   error "Please do not include double.h directly"
#endif

typedef struct _como_double {
  como_object base;
  double value;
} como_double;

extern como_type como_double_type;

#define como_get_double(o) ((como_double *)(o))

COMO_OBJECT_API como_object *como_doublefromdouble(double dval);

#endif
