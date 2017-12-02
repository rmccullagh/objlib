#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include <stdio.h>
#include <stdint.h>
#include <limits.h>
#include <assert.h>

#include <como.h>

COMO_OBJECT_API como_object *como_longfromlong(long lval)
{
  como_long *obj = malloc(sizeof(*obj));

  obj->base.type = &como_long_type;
  obj->base.next = NULL;  
  obj->base.flags = 0;
  obj->value = lval;

  return (como_object *)obj;
}

static void long_print(como_object *ob)
{
  como_long *lval = (como_long *)ob;

  printf("%ld", lval->value);
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

static como_usize_t long_hash(como_object *obj)
{
  como_long *lval = (como_long *)obj;

  return lval->value & 0x7fffffffffffffffL;
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

  assert((void *)retval != (void *)b);

  return retval;
}

static como_object *long_mul(como_object *xself, como_object *b)
{
  como_long *self = como_get_long(xself);
  como_object *retval = NULL;

  if(como_type_is(b, como_long_type))
  {
    long right = ((como_long *)b)->value;

    if(0 /*willoverflow */)
    {
      retval = como_longfromlong(-1L);
    }
    else
    {
      retval = como_longfromlong(self->value * right);
    }
  }
  else 
  { 
    if(como_type_is(b, como_double_type))
    {
      double left = (double)self->value;
      double right = ((como_double *)b)->value;
    
      retval = como_doublefromdouble(left * right);
    }
  }

  return retval;
}

static como_object *long_div(como_object *xself, como_object *b)
{
  como_long *self = como_get_long(xself);
  como_object *retval = NULL;

  if(como_type_is(b, como_long_type))
  {
    long right = ((como_long *)b)->value;

    if(0 /*willoverflow */)
    {
      retval = como_longfromlong(-1L);
    }
    else
    {
      /* TODO divide by zero and overflow */
      retval = como_longfromlong(self->value / right);
    }
  }
  else 
  { 
    if(como_type_is(b, como_double_type))
    {
      double left = (double)self->value;
      double right = ((como_double *)b)->value;
    
      retval = como_doublefromdouble(left / right);
    }
  }

  return retval;
}

static como_object *long_sub(como_object *xself, como_object *b)
{
  como_long *self = como_get_long(xself);
  como_object *retval = NULL;

  if(como_type_is(b, como_long_type))
  {
    long right = ((como_long *)b)->value;

    if(0 /*willoverflow */)
    {
      retval = como_longfromlong(-1L);
    }
    else
    {
      /* TODO divide by zero and overflow */
      retval = como_longfromlong(self->value - right);
    }
  }
  else 
  { 
    if(como_type_is(b, como_double_type))
    {
      double left = (double)self->value;
      double right = ((como_double *)b)->value;
    
      retval = como_doublefromdouble(left - right);
    }
  }

  return retval;
}

static como_object *long_rem(como_object *xself, como_object *x)
{
  como_long *self = como_get_long(xself);
  como_object *retval = NULL;
  
  if(como_type_is(x, como_double_type)) 
  {
    double dividend = (double)self->value;
    double divisor = ((como_double *)x)->value;
    
    retval = como_doublefromdouble(
      dividend - (divisor * ((int)dividend/(int)divisor))
    );
  } 
  else if(como_type_is(x, como_long_type))
  {
    double dividend = (double)self->value;
    double divisor = (double)(((como_long *)x)->value);

    /* 269.86 % 100 = 269.86 - (100 * int(269.86/100)) */
    /* http://www2.nkfust.edu.tw/~mhchen/papers/Psychologica\
     * l%20Barriers%20Effects%20on%20Futures%20Markets/mod.pdf */
    retval = como_doublefromdouble(
        dividend - (divisor * ((int)dividend/(int)divisor))
    );
  } 

  return retval;
}

static como_object *long_plus(como_object *obj)
{
  como_long *self = como_get_long(obj);

  return como_longfromlong(+self->value); 
}

static como_object *long_minus(como_object *obj)
{
  como_long *self = como_get_long(obj);

  return como_longfromlong(-self->value); 
}

static como_object *long_string(como_object *obj)
{
  como_long *self = como_get_long(obj);
  char *buffer = NULL;
  int size = 0;
  size =  snprintf(buffer, size, "%ld", self->value);

  size++;

  buffer = malloc(size);

  snprintf(buffer, size, "%ld", self->value);

  buffer[size - 1] = '\0';

  como_object *retval = como_stringfromstring(buffer);
  
  free(buffer);

  return retval;
}

static como_binary_ops binops = {
  .obj_add = long_add,
  .obj_mul = long_mul,
  .obj_div = long_div,
  .obj_sub = long_sub,
  .obj_rem = long_rem
};

static como_unary_ops unops = { 
  .obj_plus  = long_plus,
  .obj_minus = long_minus
};

static como_object *long_equals_wrap(como_object *a, como_object *b)
{
  return como_boolfromint(long_equals(a, b));
}

static como_object *long_neq(como_object *a, como_object *b)
{
  return como_boolfromint(!long_equals(a, b));
}

static como_object *long_gt(como_object *a, como_object *b)
{
  como_long *self = como_get_long(a);

  if(como_type_is(b, como_long_type))
    return como_false;
  else
    return como_boolfromint(self->value > ((como_long *)b)->value);
}

static como_object *long_lt(como_object *a, como_object *b)
{
  como_long *self = como_get_long(a);

  if(como_type_is(b, como_long_type))
    return como_false;
  else
    return como_boolfromint(self->value < ((como_long *)b)->value);
}

static como_object *long_gte(como_object *a, como_object *b)
{
  como_long *self = como_get_long(a);

  if(como_type_is(b, como_long_type))
    return como_false;
  else
  {
    como_long *right = (como_long *)b;

    if(self->value > right->value)
      return como_true;
    else if(self->value == right->value)
      return como_true;
    else
      return como_false;
  }
}

static como_object *long_lte(como_object *a, como_object *b)
{
  como_long *self = como_get_long(a);

  if(como_type_is(b, como_long_type))
    return como_false;
  else
  {
    como_long *right = (como_long *)b;

    if(self->value < right->value)
      return como_true;
    else if(self->value == right->value)
      return como_true;
    else
      return como_false;
  }
}

static int long_bool(como_object *x)
{
  return ((como_long *)x)->value != 0L;
}

static como_comparison_ops compops = {
  .obj_eq  = long_equals_wrap,
  .obj_neq = long_neq,
  .obj_gt  = long_gt,
  .obj_lt  = long_lt,
  .obj_gte = long_gte,
  .obj_lte = long_lte
};

como_type como_long_type = {
  .obj_name    = "long",
  .obj_print   = long_print,
  .obj_dtor    = long_dtor, 
  .obj_equals  = long_equals,
  .obj_bool    = long_bool,
  .obj_hash    = long_hash,
  .obj_str     = long_string,
  .obj_init    = NULL,
  .obj_deinit  = NULL,
  .obj_binops  = &binops,
  .obj_unops   = &unops,
  .obj_compops = &compops
};

