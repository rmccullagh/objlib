#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include <stdio.h>
#include <float.h>

#include "comoobject.h"
#include "double.h"


COMO_OBJECT_API como_object *como_doublefromdouble(double dval)
{
  como_double *obj = malloc(sizeof(*obj));

  obj->base.type = &como_double_type;
  obj->base.next = NULL;  
  obj->value = dval;

  return (como_object *)obj;
}

static void double_print(como_object *ob)
{
  como_double *dval = (como_double *)ob;

  printf("%.*G\n", DBL_DIG, dval->value);
}

static void double_dtor(como_object *ob)
{
  como_double *dval = (como_double *)ob;
  free(dval);
}

static int double_equals(como_object *a, como_object *b)
{
  int retval = 0;

  if(como_type_is(a, como_double_type) 
    && como_type_is(b, como_double_type))
  {
    retval = ((como_double *)a)->value == ((como_double *)b)->value;
  }

  return retval;
}

como_type como_double_type = {
  .obj_name   = "double",
  .obj_print  = double_print,
  .obj_dtor   = double_dtor,
  .obj_equals = double_equals,
  .obj_hash   = NULL,
  .obj_str    = NULL
};


