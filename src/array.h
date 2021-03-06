#ifndef COMO_ARRAY_H
#define COMO_ARRAY_H

# if !(defined(COMO_BASE_INCLUDED))
#   error "Please do not include array.h directly"
#endif

/* Inheritence:
 *  como_object
 *      como_container
 *          como_array
 */
typedef struct _como_array 
{
  como_container base;
  como_object **items;
} como_array;

COMO_OBJECT_API como_object *como_array_new(como_size_t);
COMO_OBJECT_API como_object *como_array_push(como_object *, como_object *);
COMO_OBJECT_API como_object *como_array_push_index(como_object *, como_size_t i, como_object *);
COMO_OBJECT_API como_object *como_array_get(como_object *, como_size_t i);

#define como_get_array(o) ((como_array *)((o)))

extern como_type como_array_type;

#endif
