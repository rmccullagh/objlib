#include <stdio.h>
#include <assert.h>

#include <como.h>

/* For freeing */
static como_object *root = NULL;

typedef struct _spair {
  char *s1;
  char *s2;
} spair;

static spair collisions[] = {
  { "hetairas",    "mentioner"  },
  { "heliotropes", "neurospora" },
  { "depravement", "serafins"   },
  { "stylist",     "subgenera"  },
  { "joyful",      "synaphea"   },
  { "redescribed", "urites"     },
  { "dram",        "vivency"    },
  { NULL,          NULL         }
};

static void test_collisions(void)
{
  como_object *root = NULL;

  /* Make sure to not test the resize function */
  como_object *map = como_map_new(16);
  map->next = root;
  root = map;

  como_size_t i;

  for(i = 0; collisions[i].s1 != NULL; i++)
  {
    spair pair = collisions[i];
    
    como_object *s1 = como_stringfromstring(pair.s1);
    s1->next = root;
    root = s1;

    como_object *s2 = como_stringfromstring(pair.s2);
    s2->next = root;
    root =s2;

    como_map_put(map, s1, s1);
    como_map_put(map, s2, s2);
  }

  while(root != NULL)
  {
    como_object *next = root->next;
    
    como_object_dtor(root);

    root = next;
  }
}

int main(void)
{
  test_collisions();

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


