#ifndef COMO_MAP_OBJECT_H
#define COMO_MAP_OBJECT_H

#include "comoobject.h"

typedef struct _como_map_bucket {
  como_object             *key;
  como_object             *value;
  struct _como_map_bucket *next;
} como_map_bucket;

typedef struct _como_map {
  como_object       base;
  como_map_bucket **buckets;
  como_size_t       size;
  como_size_t       capacity;
} como_map;

COMO_OBJECT_API como_object *como_map_new(como_size_t size);
COMO_OBJECT_API como_object *como_map_put(como_object *obj, como_object *key, 
  como_object *value);
COMO_OBJECT_API como_object *como_map_get(como_object *obj, como_object *key);
COMO_OBJECT_API como_object *como_map_delete(como_object *obj, 
  como_object *key);

#define como_map_size(o) (((como_map *)(o))->size)
#define como_map_capacity(o) (((como_map *)(o))->capacity)

extern como_type como_map_type;

#endif
