#include <como.h>


static como_bool *create_bool(int value)
{
  como_bool *obj = malloc(sizeof(*obj));

  obj->base.type = &como_bool_type;
  obj->base.next = NULL;  
  obj->value = value;

  return obj;
}

static void bool_print(como_object *x)
{
  como_bool *self = como_get_bool(x);

  fprintf(stdout, "%s", self->value == 1 ? "true" : "false");
}

static void bool_dtor(como_object *x)
{
  como_bool *self = como_get_bool(x);

  free(self);
}

static int bool_equals(como_object *obj, como_object *x)
{
  como_bool *self = como_get_bool(obj);

  if(!como_type_is(x, como_bool_type))
    return 0;
  else
    return self->value == como_get_bool(x)->value;
}

static como_object *bool_string(como_object *obj)
{
  como_bool *self = como_get_bool(obj);

  if(self->value == 1)
    return como_stringfromstring("true");
  else
    return como_stringfromstring("false");
}

COMO_OBJECT_API como_object *como_boolfromint(int value)
{
  return (como_object *)create_bool(value == 1 ? value : 0);
}

COMO_OBJECT_API como_object *como_boolfromcomoobject(como_object *obj)
{
  return obj;
}

static como_object *bool_equals_wrap(como_object *obj, como_object *x)
{
  return como_boolfromint(bool_equals(obj, x));
}

static como_object *bool_neq(como_object *obj, como_object *x)
{
  como_bool *self = como_get_bool(obj);

  if(!como_type_is(x, como_bool_type))
    return como_false;
  else
    return como_boolfromint(self->value != como_get_bool(x)->value);
}

static como_object *bool_gt(como_object *obj, como_object *x)
{
  COMO_UNUSED(obj);
  COMO_UNUSED(x);

  return como_false;
}

static como_object *bool_lt(como_object *obj, como_object *x)
{
  COMO_UNUSED(obj);
  COMO_UNUSED(x);

  return como_false;
}

static como_object *bool_gte(como_object *obj, como_object *x)
{
  COMO_UNUSED(obj);
  COMO_UNUSED(x);

  return como_false;
}

static como_object *bool_lte(como_object *obj, como_object *x)
{
  COMO_UNUSED(obj);
  COMO_UNUSED(x);

  return como_false;
}
  
static int bool_bool(como_object *x)
{
  return ((como_bool *)x)->value != 0;
}

static como_comparison_ops compops = {
  .obj_eq  = bool_equals_wrap,
  .obj_neq = bool_neq,
  .obj_gt  = bool_gt,
  .obj_lt  = bool_lt,
  .obj_gte = bool_gte,
  .obj_lte = bool_lte
};

como_type como_bool_type = {
  .obj_name    = "bool",
  .obj_print   = bool_print,
  .obj_dtor    = bool_dtor,
  .obj_equals  = bool_equals,
  .obj_bool    = bool_bool,
  .obj_hash    = NULL,
  .obj_str     = bool_string,
  .obj_init    = NULL,
  .obj_deinit  = NULL,
  .obj_binops  = NULL,
  .obj_unops   = NULL,
  .obj_compops = &compops,
};