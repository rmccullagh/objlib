#ifndef COMO_DOUBLE_OBJECT_H
#define COMO_DOUBLE_OBJECT_H

#include "comoobject.h"


typedef struct _como_double {
  como_object base;
  double value;
} como_double;

extern como_type como_double_type;

COMO_OBJECT_API como_object *como_doublefromdouble(double dval);

#endif