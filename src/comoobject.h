#ifndef COMO_OBJECT_H
#define COMO_OBJECT_H

#include <stddef.h>

typedef struct _como_type   como_type;
typedef struct _como_object como_object;
typedef long como_size_t;

struct _como_object {
  struct _como_type   *type;
  struct _como_object *next;
};

struct _como_type {
  const char *obj_name;
  void(*obj_print)(como_object *);
  void(*obj_dtor)(como_object *);
  int(*obj_equals)(como_object *, como_object *);
  como_size_t(*obj_hash)(como_object *);
  como_object *(*obj_str)(como_object *);
};

#define como_type_is(ob, tp) \
  (((como_object *)(ob))->type == &tp)

#define como_type_name(o) \
  (((como_object *)(o))->type->obj_name)

#define como_object_print(o) \
  (((como_object *)(o))->type->obj_print((como_object *)(o)))

#define como_object_dtor(o) \
  (((como_object *)(o))->type->obj_dtor((como_object *)(o)))

#define COMO_OBJECT_API __attribute__((__visibility__("default")))

#endif
