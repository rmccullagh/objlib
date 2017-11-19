#include "comoobject.h"
#include "string.h"
#include "long.h"
#include "double.h"
#include "map.h"

#include <stdio.h>

int main(void)
{
  como_object *str = como_stringfromstring("This file ");
  como_object_print(str);

  como_object *str2 = como_stringfromstring("This file ");
  como_object_print(str2);


  como_object *lval = como_longfromlong(144L);
  como_object_print(lval);

  como_object *map = como_map_new(8);

  como_map_put(map, str, str);
  como_map_put(map, lval, str);

  printf("map.size=%ld\n", como_map_size(map));


  fprintf(stdout, " --- como_map_get:\n");
  como_object_print(como_map_get(map, lval));
  fprintf(stdout, " ---\n");
  
  como_map_delete(map, str);
  printf("map.size=%ld\n", como_map_size(map));


  como_object *val = como_map_get(map, str);

  if(val) {
    printf("after deleting, I still found str\n");
  }

  como_map_delete(map, lval);
  printf("map.size=%ld\n", como_map_size(map));


  if(como_map_get(map, lval)) {
    printf("after deleting, I still found lval\n");
  }

  printf("%ld\n", como_map_size(map));



  como_object *dval = como_doublefromdouble(1424242424.2204); 
  como_object_print(dval);

  como_object_dtor(str);
  como_object_dtor(str2);
  como_object_dtor(lval);
  como_object_dtor(dval);
  como_object_dtor(map);


  return 0;
}