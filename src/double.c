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

  /* check out DBL_DECIMAL_DIG */
  printf("%.17g",  dval->value);
}

static como_object *double_string(como_object *obj)
{
  como_double *self = como_get_double(obj);
  char *buffer = NULL;
  int size = 0;
  size =  snprintf(buffer, size, "%.17g", self->value);

  size++;

  buffer = malloc(size);

  snprintf(buffer, size, "%.17g", self->value);

  buffer[size - 1] = '\0';

  como_object *retval = como_stringfromstring(buffer);
  
  free(buffer);

  return retval;
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
    retval = como_doublefromdouble(self->value + 
                  ((como_double *)a)->value);

  else if(como_type_is(a, como_long_type))
      retval = como_doublefromdouble(self->value + 
                  (double)((como_long *)a)->value);
  

  return retval; 
}

static como_object *double_mul(como_object *obj, como_object *x)
{  
  como_double *self   = como_get_double(obj);
  como_object *retval = NULL;
  
  if(como_type_is(x, como_double_type))
    retval = como_doublefromdouble(self->value * ((como_double *)x)->value);
  
  else if(como_type_is(x, como_long_type))
    retval = como_doublefromdouble(self->value * 
                (double)((como_double *)x)->value);  

  return retval;
}

static como_object *double_div(como_object *obj, como_object *x)
{
  como_double *self   = como_get_double(obj);
  como_object *retval = NULL;
  
  if(como_type_is(x, como_double_type))
    retval = como_doublefromdouble(self->value / ((como_double *)x)->value);
  
  else if(como_type_is(x, como_long_type))
    retval = como_doublefromdouble(self->value / 
                (double)((como_double *)x)->value);  

  return retval;
}

static como_object *double_sub(como_object *obj, como_object *x)
{
  como_double *self   = como_get_double(obj);
  como_object *retval = NULL;
  
  if(como_type_is(x, como_double_type))
    retval = como_doublefromdouble(self->value - ((como_double *)x)->value);
  
  else if(como_type_is(x, como_long_type))
    retval = como_doublefromdouble(self->value -
                (double)((como_double *)x)->value);  

  return retval;
}

static como_object *double_rem(como_object *obj, como_object *x)
{
  como_double *self   = como_get_double(obj);
  como_object *retval = NULL;
  
  if(como_type_is(x, como_double_type)) 
  {
    double dividend = self->value;
    double divisor = ((como_double *)x)->value;
    
    retval = como_doublefromdouble(
      dividend - (divisor * ((int)dividend/(int)divisor))
    );
  } 
  else if(como_type_is(x, como_long_type))
  {
    double dividend = self->value;
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

static como_object *double_plus(como_object *obj)
{
  como_double *self = como_get_double(obj);

  return como_doublefromdouble(+self->value); 
}

static como_object *double_minus(como_object *obj)
{
  como_double *self = como_get_double(obj);

  return como_doublefromdouble(-self->value); 
}

static como_binary_ops binops = {
  .obj_add = double_add,
  .obj_mul = double_mul,
  .obj_div = double_div,
  .obj_sub = double_sub,
  .obj_rem = double_rem
};

static como_unary_ops unops = {
  .obj_plus  = double_plus,
  .obj_minus = double_minus
};

static como_comparison_ops compops = {
  .obj_eq  = NULL,
  .obj_neq = NULL,
  .obj_gt  = NULL,
  .obj_lt  = NULL,
  .obj_gte = NULL,
  .obj_lte = NULL
};

como_type como_double_type = {
  .obj_name    = "double",
  .obj_print   = double_print,
  .obj_dtor    = double_dtor,
  .obj_equals  = double_equals,
  .obj_hash    = NULL,
  .obj_str     = double_string,
  .obj_binops  = &binops,
  .obj_unops   = &unops,
  .obj_compops = &compops
};
