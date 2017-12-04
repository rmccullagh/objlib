#ifndef COMO_SYSTEM_H
#define COMO_SYSTEM_H

typedef unsigned int como_uint32_t;
typedef unsigned long como_usize_t;
typedef int como_int;
typedef char* como_exception;

//printf("0x%" PRIXPTR "\n", (uintptr_t)your_pointer);
// https://stackoverflow.com/questions/9053658/correct-format-specifier-to-print-pointer-address

#define COMO_UNUSED(x) ((void)x)
#define COMO_PTR(x) ((uintptr_t)((x)))

#define COMO_PTR_FMT "0x%X"
#define COMO_LNG_FMT "%ld"

#endif
