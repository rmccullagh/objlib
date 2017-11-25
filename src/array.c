#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

#include <como.h>

COMO_OBJECT_API como_object *como_array_new(como_size_t size)
{
  como_array *ar = malloc(sizeof(*ar));

  /* call the "base" constructor */
  como_container_init((como_object *)&ar->base, sizeof(como_object *), size, 
      (void ***)&ar->items); 

  ar->base.type = &como_array_type;

  return (como_object *)ar;
}

COMO_OBJECT_API como_object *como_array_push(como_object *xself, 
    como_object *value)
{
  como_array *self = como_get_array(xself);
  
  como_container_should_resize(self, self->items);

  return (como_object *)como_container_push(xself, value);
}

COMO_OBJECT_API como_object *como_array_get(como_object *xself,
    como_size_t index)
{
  return (como_object *)como_container_get(xself, index);
}

/* We can use this as a sparse array, this is primary used for a stack */
COMO_OBJECT_API como_object *como_array_push_index(como_object *xself,
  como_size_t i, 
  como_object *value)
{
  if(i < 0)
    assert(!(i < 0));

  if(i >= como_container_capacity(xself))
    assert(!(i >= como_container_capacity(xself)));
  
  como_get_array(xself)->items[i] = value;
  return value;
}

static void array_dtor(como_object *xself)
{
  como_array *self = como_get_array(xself);
  free(self);
}

como_type como_array_type = {
  .obj_name   = "array",
  .obj_print  = NULL,
  .obj_dtor   = array_dtor,
  .obj_equals = NULL,
  .obj_hash   = NULL,
  .obj_str    = NULL,
  .obj_binops = NULL,
};
