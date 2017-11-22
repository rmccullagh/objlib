#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include <como.h>

int main(void)
{
  como_object *left  = como_longfromlong(15L);
  como_object *right = como_longfromlong(15L);

  como_object *sum = como_object_add(left, right);

  assert(sum->type == &como_long_type);

  como_object_print(sum);

  como_object *dval = como_doublefromdouble(15.1);

  como_object *sum2 = como_object_add(sum, dval);

  assert(sum2->type == &como_double_type);

  return 0;
}

