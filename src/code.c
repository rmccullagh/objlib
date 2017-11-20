#include <stdio.h>
#include <stdlib.h>

#include "system.h"
#include "comoobject.h"
#include "code.h"

COMO_OBJECT_API como_object *como_code_new(void)
{
  como_code *co = malloc(sizeof(*co));
  co->size     = 0;
  co->capacity = 8; 
  co->code = calloc(8, sizeof(como_uint32_t));

  return (como_object *)co;
}

COMO_OBJECT_API como_object *como_code_push(como_object *o, como_uint32_t val)
{
  como_code *cd = como_get_code(o);
  como_size_t newcap = cd->capacity * 2;
  como_size_t i;

  if(cd->size >= cd->capacity)
  {
    cd->code = realloc(cd->code, newcap);
    for(i = cd->size; i < newcap; i++)
     cd->code[i] = 0; 
  }
 
  cd->code[cd->size++] = val;  

  return o;
}

COMO_OBJECT_API como_uint32_t como_code_get(como_object *o, como_uint32_t i)
{
  return como_get_code(o)->code[i];
}
