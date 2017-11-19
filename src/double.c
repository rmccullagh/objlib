#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include <stdio.h>
#include <float.h>

#include "double.h"

COMO_OBJECT_API como_object *como_doublefromdouble(double dval)
{
	como_double *obj = malloc(sizeof(*obj));

	obj->base.type = &como_double_type;
	obj->base.next = NULL;	
	obj->value = dval;

	return (como_object *)obj;
}

static void double_print(como_object *ob)
{
	como_double *dval = (como_double *)ob;

	printf("%.*G\n", DBL_DIG, dval->value);
}

static void double_dtor(como_object *ob)
{
	como_double *dval = (como_double *)ob;
	free(dval);
}

como_type como_double_type = {
	"double",
	double_print,
	double_dtor,
	NULL,
	NULL,
	NULL
};

