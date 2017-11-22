#include <stdio.h>
#include <assert.h>

#include "comoobject.h"
#include "long.h"
#include "array.h"

/* For freeing */
static como_object *root = NULL;

int main(void)
{
  como_object *ar = como_array_new(8);
  como_size_t i;
  como_size_t max = 100;

  for(i = 0; i < max; i++) 
  {
    como_object *lval = como_longfromlong(i);
    lval->next = root;
    root = lval;
    como_array_push(ar, lval);

    if(i % 5 == 0)
      printf("size=%ld ,capacity=%ld\n", 
          como_container_size(ar), como_container_capacity(ar));
  }

  for(i = 0; i < max; i++)
  {
    como_object *val = como_array_get(ar, i);
    assert(val);
  }

  while(root != NULL) 
  {
    como_object *next = root->next;

    como_object_dtor(root);

    root = next;
  }

  como_object_dtor(ar);

  return 0;
}
