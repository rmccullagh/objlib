#ifndef COMO_CONTAINER_H
#define COMO_CONTAINER_H

#include "comoobject.h"

/* This is an "abstract class" that holds a sequence type. It isn't 
 * supposed to be a concrete class, rather a base class that handles
 * the ever so repetive dynamic array needs
 **/
typedef struct _como_container
{
  como_object base;
  como_type  *type;
  como_size_t itemsize;
  como_size_t size;
  como_size_t capacity;
  /* child classes implement the actual data type aka the T** pointer,
   * but it just points back here */
  void        **data; 
} como_container;

#define como_get_container(o) ((como_container *)(o))
#define como_container_size(o) (((como_container *)(o))->size)
#define como_container_capacity(o) (((como_container *)(o))->capacity)

#define como_container_should_resize(self, items) do { \
  if(como_container_size(self) >= como_container_capacity(self)) { \
    como_container_resize((como_object *)self, (void ***)&items); \
  } \
} while(0)

COMO_OBJECT_API void como_container_init(como_object *obj, como_size_t size,
    como_size_t capacity, void ***itemsp);

COMO_OBJECT_API void como_container_resize(como_object *obj, void ***itemsp);
COMO_OBJECT_API void *como_container_get(como_object *obj, como_size_t idx);
COMO_OBJECT_API void *como_container_push(como_object *obj, void *value);

extern como_type como_container_type;

#endif
