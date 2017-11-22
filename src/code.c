#include <stdio.h>
#include <stdlib.h>

#include "system.h"
#include "comoobject.h"
#include "code.h"
#include "container.h"

COMO_OBJECT_API como_object *como_code_new(void)
{
  como_code *co = malloc(sizeof(*co));

  como_container_init((como_object *)&co->base, sizeof(como_uint32_t *), 8,
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
  .obj_name   = "code",
  .obj_print  = NULL,
  .obj_dtor   = code_dtor,
  .obj_equals = NULL,
  .obj_hash   = NULL,
  .obj_str    = NULL,
  .obj_binops = NULL
};