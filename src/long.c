#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include <stdio.h>
#include <stdint.h>
#include <limits.h>

#include "long.h"
#include "double.h"

COMO_OBJECT_API como_object *como_longfromlong(long lval)
{
  como_long *obj = malloc(sizeof(*obj));

  obj->base.type = &como_long_type;
  obj->base.next = NULL;  
  obj->value = lval;

  return (como_object *)obj;
}

static void long_print(como_object *ob)
{
  como_long *lval = (como_long *)ob;

  printf("%ld\n", lval->value);
}

static void long_dtor(como_object *ob)
{
  como_long *lval = (como_long *)ob;
  free(lval);
}

static int long_equals(como_object *base, como_object *right)
{
  int retval = 0;

  if(como_type_is(base, como_long_type) 
    && como_type_is(right, como_long_type)) {

    como_long *a = (como_long *)base;
    como_long *b = (como_long *)right;
    retval     = a->value == b->value;
  }

  return retval;
}

static como_size_t long_hash(como_object *obj)
{
  como_long *lval = (como_long *)obj;

  return lval->value;
}

#define willoverflow(a, b) \
  (((b > 0L) && (a > LONG_MAX - b)) || ((b < 0L) && (a < LONG_MIN - b)))

static como_object *long_add(como_object *xself, como_object *b)
{
  como_long *self = (como_long *)xself;
  como_object *retval = NULL;

  if(como_type_is(b, como_long_type))
  {
    long right = ((como_long *)b)->value;

    if(willoverflow(self->value, right))
    {
      retval = como_longfromlong(-1L);
    }
    else
    {
      retval = como_longfromlong(self->value + right);
    }
  }
  else 
  { 
    if(como_type_is(b, como_double_type))
    {
      double left = (double)self->value;
      double right = ((como_double *)b)->value;
    
      retval = como_doublefromdouble(left + right);
    }
  }

  return retval;
}

static como_binary_ops binops = {
  .obj_add = long_add,
  .obj_mul = NULL,
  .obj_div = NULL,
  .obj_sub = NULL
};

como_type como_long_type = {
  .obj_name   = "long",
  .obj_print  = long_print,
  .obj_dtor   = long_dtor, 
  .obj_equals = long_equals,
  .obj_hash   = long_hash,
  .obj_str    = NULL,
  .obj_binops = &binops
};

