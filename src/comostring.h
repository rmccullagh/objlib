#ifndef COMO_STRING_H
#define COMO_STRING_H

# if !(defined(COMO_BASE_INCLUDED))
#   error "Please do not include string.h directly"
#endif

typedef struct _como_string {
  como_object base;
  como_size_t len;
  como_usize_t hash;
  char *value;
} como_string;

COMO_OBJECT_API como_object *como_stringfromstring(char *val);

extern como_type como_string_type;

#endif
