#include <stdlib.h>
#include "comoobject.h"
#include "container.h"

COMO_OBJECT_API void como_container_init(como_object *obj, 
    como_size_t sizeofitem,
    como_size_t capacity,
    void ***itemsp)
{
  /* Initialize the parent */
  obj->type = &como_container_type;
 
  /* Initialize self */ 
  como_container *self = como_get_container(obj);
 
  self->size = 0;
  self->itemsize = sizeofitem;
  self->capacity = capacity;

  self->data = malloc(sizeofitem * capacity);

  *itemsp = self->data;
}

COMO_OBJECT_API void como_container_resize(como_object *obj, void ***itemsp)
{
  como_container *self = como_get_container(obj);
  como_size_t newcap = self->capacity * 2;
  self->data = realloc(self->data, self->itemsize * newcap);

  *itemsp = self->data;
  self->capacity = newcap;
}

COMO_OBJECT_API void *como_container_get(como_object *obj, como_size_t idx)
{
  como_container *self = como_get_container(obj);
  void *retval = NULL;

  if(idx >= 0 && idx < self->size) 
    retval = self->data[idx];

  return retval;
}

COMO_OBJECT_API void *como_container_push(como_object *obj, void *value)
{
  como_container *self = como_get_container(obj);
 
  self->data[self->size++] = value;

  return value;
}

static void container_dtor(como_object *x)
{
  como_container *self = como_get_container(x);
  free(self->data);
  
  /* This object (container)
   * wasn't allocated on the heap, it is simply a stack pointer */
  /* We should call the child dtor because it won't get called otherwise */
  /* The child class is actually the one allocated on the heap */
  self->type->obj_dtor(x); 
}

como_type como_container_type = {
  .obj_name   = "container",
  .obj_print  = NULL,
  .obj_dtor   = container_dtor,
  .obj_equals = NULL,
  .obj_hash   = NULL,
  .obj_str    = NULL,
  .obj_binops = NULL
};
























