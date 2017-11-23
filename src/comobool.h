#ifndef COMO_BOOL_OBJECT
#define COMO_BOOL_OBJECT

# if !(defined(COMO_BASE_INCLUDED))
#   error "Please do not include bool.h directly"
#endif

typedef struct _como_bool {
  como_object base;
  int value;
} como_bool;

COMO_OBJECT_API como_object *como_boolfromint(int value);
COMO_OBJECT_API como_object *como_boolfromcomoobject(como_object *);

#define como_get_bool(o) ((como_bool *)((o)))
#define como_false como_boolfromint(0)
#define como_true como_boolfromint(1)

extern como_type como_bool_type;

#endif