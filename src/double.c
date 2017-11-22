#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include <stdio.h>
#include <float.h>

#include <como.h>

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

static como_object *double_add(como_object *xself, como_object *a)
{
  como_double *self = (como_double *)xself;
  como_object *retval = NULL;
  
  if(como_type_is(a, como_double_type))
    retval = como_doublefromdouble(self->value + ((como_double *)a)->value);
  else 
  {
    if(como_type_is(a, como_long_type))
      retval = como_doublefromdouble(self->value +
                  (double)((como_long *)a)->value);
  }

  return retval; 
}

static como_binary_ops binops = {
  .obj_add = double_add,
  .obj_mul = NULL,
  .obj_div = NULL,
  .obj_sub = NULL
};

como_type como_double_type = {
  .obj_name   = "double",
  .obj_print  = double_print,
  .obj_dtor   = double_dtor,
  .obj_equals = double_equals,
  .obj_hash   = NULL,
  .obj_str    = NULL,
  .obj_binops = &binops
};


