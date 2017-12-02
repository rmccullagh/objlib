#include <como.h>

COMO_OBJECT_API como_object *como_frame_new(char *name, 
  como_object *callingframe)
{
  como_frame *obj = malloc(sizeof(*obj));
  como_size_t i;

  obj->base.type = &como_frame_type;
  obj->base.next = NULL;  

  obj->name      = como_stringfromstring(name);
  obj->code      = como_code_new(COMO_CODE_SIZE);
  obj->constants = como_array_new(COMO_FRAME_CONSTANTS_SIZE);
  obj->locals    = NULL,
  obj->stack     = malloc(sizeof(como_object *) * COMO_FRAME_STACK_SIZE); 
  obj->root      = NULL;
  obj->pc        = 0;
  obj->sz        = COMO_FRAME_STACK_SIZE;
  obj->sp        = 0;
  obj->nobjs     = 0;
  obj->nobjslt   = 0;
  obj->mxobjs    = COMO_FRAME_MAX_OBJECTS;
  obj->parent    = callingframe;

  for(i = 0; i < obj->sz; i++)
    obj->stack[i] = NULL;

  return (como_object *)obj;
}

COMO_OBJECT_API void como_frame_growstack(como_object *obj)
{
  como_frame *self = como_get_frame(obj);

  if(self->sp >= self->sz)
  {
    self->sz = self->sz * 2;
    self->stack = realloc(self->stack, sizeof(como_object *) * self->sz);
  }
}

static void frame_init(como_object *obj)
{
  como_frame *self = como_get_frame(obj);

  self->locals    = como_map_new(COMO_FRAME_LOCALS_SIZE);
  self->pc = 0;
  self->sp = 0;
}

static void frame_deinit(como_object *obj)
{
  como_frame *self = como_get_frame(obj);
  como_map *map = (como_map *)self->locals;
  como_size_t i;

  for(i = 0; i < map->capacity; i++)
  {
    como_map_bucket *bucket = map->buckets[i];

    while(bucket) 
    {      
      bucket->key->flags--;
      
      bucket->value->flags--;

      bucket = bucket->next;
    }
  }

  como_object_dtor(self->locals);
}

static void frame_dtor(como_object *obj)
{
  como_frame *self = como_get_frame(obj);
  
  como_object_dtor(self->name);
  como_object_dtor(self->code);
  como_object_dtor(self->constants);

  free(self->stack);
  free(self);
}

static void frame_print(como_object *obj)
{
  como_frame *self = como_get_frame(obj);

  fprintf(stdout, "<frame %s at %p>", 
    ((como_string*)self->name)->value, (void *)obj);
}

static como_object *frame_string(como_object *obj)
{
  como_frame *self = como_get_frame(obj);
  char *buffer = NULL;
  int size = 0;
  size = snprintf(buffer, size, "<frame %s at %p>", 
    ((como_string*)self->name)->value, (void *)obj);

  size++;

  buffer = malloc(size);

  snprintf(buffer, size, "<frame %s at %p>", ((como_string*)self->name)->value, 
            (void *)obj);

  buffer[size - 1] = '\0';

  como_object *retval = como_stringfromstring(buffer);
  
  free(buffer);

  return retval; 
}

static int frame_equals(como_object *obj, como_object *b)
{
  return obj == b;
}

static int frame_bool(como_object *obj)
{
  COMO_UNUSED(obj);

  return 1;
}

static como_object *frame_equals_wrap(como_object *obj, como_object *x)
{
  return como_boolfromint(frame_equals(obj, x));
}

static como_comparison_ops compops = {
  .obj_eq  = frame_equals_wrap,
  .obj_neq = NULL,
  .obj_gt  = NULL,
  .obj_lt  = NULL,
  .obj_gte = NULL,
  .obj_lte = NULL
};

como_type como_frame_type = {
  .obj_name    = "frame",
  .obj_print   = frame_print,
  .obj_dtor    = frame_dtor,
  .obj_equals  = frame_equals,
  .obj_bool    = frame_bool,
  .obj_hash    = NULL,
  .obj_str     = frame_string,
  .obj_init    = frame_init,
  .obj_deinit  = frame_deinit,
  .obj_binops  = NULL,
  .obj_unops   = NULL,
  .obj_compops = &compops,
};