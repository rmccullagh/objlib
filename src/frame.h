#ifndef COMO_FRAME_H
#define COMO_FRAME_H

# if !(defined(COMO_BASE_INCLUDED))
#   error "Please do not include frame.h directly"
#endif

typedef struct _como_frame 
{
  como_object base;
  como_object *name; 
  como_object *code;
  como_object *constants;
  como_object *locals;
  como_object **stack;
  como_object *root;
  como_size_t pc;
  como_size_t sz;
  como_size_t sp;
  como_size_t nobjs;   /* Total objects currently in cycle */
  como_size_t nobjslt; /* Lifetime allocation count        */
  como_size_t mxobjs;  /* Max objects */
  como_object *parent;  /* The calling frame */
} como_frame;

#define como_get_frame(o) ((como_frame *)((o)))

extern como_type como_frame_type;

COMO_OBJECT_API como_object *como_frame_new(char *name, 
  como_object *callingframe);

COMO_OBJECT_API void como_frame_growstack(como_object *);

#define COMO_FRAME_STACK_SIZE     8
#define COMO_FRAME_CONSTANTS_SIZE 8
#define COMO_FRAME_LOCALS_SIZE    8
#define COMO_FRAME_MAX_OBJECTS    8
#define COMO_CODE_SIZE            8

#endif
