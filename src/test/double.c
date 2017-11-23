#include <stdio.h>
#include <como.h>

int main(void)
{
  /* 2.455 % 2
   * 0.45500000000000007
   */

  como_object *left = como_doublefromdouble(2.455);
  como_object *right = como_longfromlong(2.4L);
  como_object *result = left->type->obj_binops->obj_rem(left, right);
  
  como_object_print(result);
  
  como_object *rep = result->type->obj_str(result);
  como_object_print(rep); 

  como_object_dtor(left);
  como_object_dtor(right);
  como_object_dtor(result);
  como_object_dtor(rep);

  return 0;
}

