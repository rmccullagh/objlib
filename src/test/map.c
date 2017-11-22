#include <stdio.h>
#include <assert.h>

#include <como.h>

/* For freeing */
static como_object *root = NULL;

int main(void)
{
  como_object *map = como_map_new(8);
  como_size_t i;

  for(i = 0; i < 25; i++) 
  {
    como_object *lval = como_longfromlong(i);
    lval->next = root;
    root = lval;
    como_map_put(map, lval, lval);

    if(i % 5 == 0)
      printf("size=%ld ,capacity=%ld\n", 
          como_map_size(map), como_map_capacity(map));
  }

  for(i = 0; i < 25; i++)
  {
    como_object *lval = como_longfromlong(i);
    lval->next = root;
    root = lval;

    como_object *val = como_map_get(map, lval);
    assert(val);
  }

  while(root != NULL) 
  {
    como_object *next = root->next;

    como_object_dtor(root);

    root = next;
  }

  como_object_dtor(map);

  return 0;
}


