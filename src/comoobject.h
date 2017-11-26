#ifndef COMO_OBJECT_H
#define COMO_OBJECT_H

/* We're modeling the object system with all of C's operators */
typedef struct _como_type   como_type;
typedef struct _como_object como_object;
typedef struct _como_binary_ops como_binary_ops;
typedef struct _como_unary_ops como_unary_ops;
typedef struct _como_comparison_ops como_comparison_ops;
typedef struct _como_logical_ops como_logical_ops;

extern como_logical_ops ComoLogicalOps;

typedef long como_size_t;

struct _como_object {
  como_usize_t flags;
  struct _como_type   *type;
  struct _como_object *next;
};

#define como_object_add(self, x) \
  ((como_object *)self)->type->obj_binops->obj_add((self), (x))

struct _como_binary_ops {
  como_object *(*obj_add)(como_object *, como_object *);
  como_object *(*obj_mul)(como_object *, como_object *);
  como_object *(*obj_div)(como_object *, como_object *);
  como_object *(*obj_sub)(como_object *, como_object *);
  como_object *(*obj_rem)(como_object *, como_object *);
};

struct _como_unary_ops {
  como_object *(*obj_plus)(como_object *);
  como_object *(*obj_minus)(como_object *);
};

/* Technically, we can do this with 2 operations, 
   but let's just make it easy for now 
*/
struct _como_comparison_ops {
  como_object *(*obj_eq)(como_object *, como_object *);
  como_object *(*obj_neq)(como_object *, como_object *);
  como_object *(*obj_gt)(como_object *, como_object *);
  como_object *(*obj_lt)(como_object *, como_object *);
  como_object *(*obj_gte)(como_object *, como_object *);
  como_object *(*obj_lte)(como_object *, como_object *);
};

struct _como_logical_ops {
  como_object *(*obj_not)(como_object *);
  como_object *(*obj_and)(como_object *, como_object *);
  como_object *(*obj_or)(como_object *, como_object *);
};

struct _como_type {
  const char *obj_name;
  void(*obj_print)(como_object *);
  void(*obj_dtor)(como_object *);
  int(*obj_equals)(como_object *, como_object *);
  int(*obj_bool)(como_object *);
  como_usize_t(*obj_hash)(como_object *);
  como_object *(*obj_str)(como_object *);
  struct _como_binary_ops      *obj_binops;
  struct _como_unary_ops       *obj_unops;
  struct _como_comparison_ops  *obj_compops;
};

#define como_type_is(ob, tp) \
  (((como_object *)(ob))->type == &tp)

#define como_type_name(o) \
  (((como_object *)(o))->type->obj_name)

#define como_object_print(o) \
  (((como_object *)(o))->type->obj_print((como_object *)(o)))

#define como_object_dtor(o) \
  (((como_object *)(o))->type->obj_dtor((como_object *)(o)))

#define como_object_init(o, _type) do { \
  como_object *obj = (como_object *)(o); \
  obj->type = _type; \
  obj->flags = 0; \
  obj->next = NULL; \
} while (0)

#define COMO_OBJECT_API __attribute__((__visibility__("default")))

#endif
