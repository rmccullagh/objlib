#include <stdio.h>
#include <stdlib.h>

#include <como.h>

COMO_OBJECT_API como_object *como_code_new(como_size_t cap)
{
  como_code *co = malloc(sizeof(*co));

  como_container_init((como_object *)&co->base, sizeof(como_uint32_t *), cap,
    (void ***)&co->code);

  co->base.type = &como_code_type;

  return (como_object *)co;
}

COMO_OBJECT_API como_object *como_code_push(como_object *o, como_uint32_t val)
{
  como_code *self = como_get_code(o);

  como_container_should_resize(self, self->code);

  return como_container_push(o, (void *)(unsigned long)val);  
}

COMO_OBJECT_API como_uint32_t como_code_get(como_object *o, como_size_t idx)
{
  return (como_uint32_t)(unsigned long)como_container_get(o, idx);
}

static void code_dtor(como_object *xself)
{
  free((como_code *)xself);
}

como_type como_code_type = {
  .obj_name    = "code",
  .obj_print   = NULL,
  .obj_dtor    = code_dtor,
  .obj_equals  = NULL,
  .obj_bool    = NULL,
  .obj_hash    = NULL,
  .obj_str     = NULL,
  .obj_init    = NULL,
  .obj_deinit  = NULL,
  .obj_binops  = NULL,
  .obj_unops   = NULL,
  .obj_compops = NULL,
};
