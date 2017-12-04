#include <como.h>

static como_function *create_function(int type)
{
  como_function *obj = malloc(sizeof(*obj));

  obj->base.type = &como_function_type;
  obj->base.next = NULL;  
  obj->base.flags = 0;
  obj->flags = type;

  return obj;
}

COMO_OBJECT_API como_object *como_functionfromframe(como_frame *frame)
{ 
  como_function *fn = create_function(COMO_FUNCTION_LANG);

  fn->impl.frame = frame;

  return (como_object *)fn;
}


COMO_OBJECT_API como_object *como_functionfromhandler(
  como_function_handler handler)
{
  como_function *fn = create_function(COMO_FUNCTION_NATIVE);

  fn->impl.handler = handler;

  return (como_object *)fn;
}

static void function_print(como_object *obj)
{
  como_function *self = como_get_function(obj); 

  fprintf(stdout, "<function at %p>", (void *)self);
}

static void function_dtor(como_object *obj)
{
  como_function *self = como_get_function(obj); 

  free(self);
}

static int function_equals(como_object *a, como_object *b)
{
  return a == b;
}

static int function_bool(como_object *obj)
{
  COMO_UNUSED(obj);

  return 1;
}

static como_object *function_string(como_object *obj)
{
  como_function *self = como_get_function(obj);
  char *buffer = NULL;
  int size = 0;
  size = snprintf(buffer, size, "<frame at %p>", (void *)self);

  size++;

  buffer = malloc(size);

  snprintf(buffer, size, "<function at %p>", (void *)self);

  buffer[size - 1] = '\0';

  como_object *retval = como_stringfromstring(buffer);
  
  free(buffer);

  return retval; 
}

static como_object *function_equals_wrap(como_object *obj, como_object *x)
{
  return como_boolfromint(function_equals(obj, x));
}

static como_comparison_ops compops = {
  .obj_eq  = function_equals_wrap,
  .obj_neq = NULL,
  .obj_gt  = NULL,
  .obj_lt  = NULL,
  .obj_gte = NULL,
  .obj_lte = NULL
};

como_type como_function_type = {
  .obj_name    = "function",
  .obj_print   = function_print,
  .obj_dtor    = function_dtor,
  .obj_equals  = function_equals,
  .obj_bool    = function_bool,
  .obj_hash    = NULL,
  .obj_str     = function_string,
  .obj_init    = NULL,
  .obj_deinit  = NULL,
  .obj_binops  = NULL,
  .obj_unops   = NULL,
  .obj_compops = &compops,
};