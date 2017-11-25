#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include <stdio.h>

#include <como.h>

static unsigned long hash(unsigned char *str)
{
  unsigned long hash = 5381;
  int c;

  while((c = *str++))
    hash = ((hash << 5) + hash) + c;

  return hash;
}

COMO_OBJECT_API como_object *como_stringfromstring(char *val)
{
  como_string *obj = malloc(sizeof(*obj));
  size_t len = strlen(val);

  /* TODO check if len overflows */

  obj->base.type = &como_string_type;
  obj->base.next = NULL;
  
  obj->len = (como_size_t)len;
  
  obj->hash = hash((unsigned char*)val);
  /* TODO check if hash value would overflow as a signed value */

  obj->value = malloc(len + 1);
  memcpy(obj->value, val, len + 1);

  return (como_object *)obj;
}

static void string_print(como_object *ob)
{
  como_string *str = (como_string *)ob;

  printf("%s\n", str->value);
}

static void string_dtor(como_object *ob)
{
  como_string *str = (como_string *)ob;
  free(str->value);
  free(str);
}

static int string_equals(como_object *a, como_object *b)
{
  int retval = 0;

  if(como_type_is(a, como_string_type) &&
    como_type_is(b, como_string_type))
  {
    como_string *left  = (como_string *)a;
    como_string *right = (como_string *)b;

    retval = left->len == right->len 
      && memcmp(left->value, right->value, left->len) == 0;
  }

  return retval;
}

static como_usize_t string_hash(como_object *obj)
{
  como_string *self  = (como_string *)obj;

  return self->hash;
}

como_type como_string_type = {
  .obj_name   = "string",
  .obj_print  = string_print,
  .obj_dtor   = string_dtor,
  .obj_equals = string_equals,
  .obj_hash   = string_hash,
  .obj_str    = NULL,
  .obj_binops = NULL,
  .obj_unops  = NULL
};












