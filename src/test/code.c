#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "system.h"
#include "comoobject.h"
#include "container.h"
#include "code.h"

#define LOAD_CONST                      0x01
#define STORE_NAME                      0x02
#define CALL_FUNCTION                   0x16
#define IPRINT                          0x06
#define IADD                            0x07
#define IRETURN                         0x09
#define LABEL                           0x0b

#define PACK_INSTRUCTION(opcode, argument, flag) \
    (como_uint32_t)((((uint8_t)(opcode)) << 24) | \
    (((uint16_t)(argument)) << 8) | \
    ((uint8_t)(flag)))

#define OPCODE(i) ((i) >> 24 & 0xff)
#define ARG(i)  ((i) >> 8 & 0xffff)
#define FLAG(i) ((i) & 0xff)

int main(void)
{
  como_object *code = como_code_new();
  como_size_t i;

  como_code_push(code, PACK_INSTRUCTION(LOAD_CONST, 0, 0));
  como_code_push(code, PACK_INSTRUCTION(LOAD_CONST, 1, 0));
  como_code_push(code, PACK_INSTRUCTION(IADD,       0, 0));
  
  como_code_push(code, PACK_INSTRUCTION(LOAD_CONST, 0, 0));
  como_code_push(code, PACK_INSTRUCTION(LOAD_CONST, 1, 0));
  como_code_push(code, PACK_INSTRUCTION(IADD,       0, 0));

  for(i = 0; i < como_container_size(code); i++) {
    como_uint32_t opline = como_code_get(code, i);

    fprintf(stdout, "opcode=%u,arg=%u,flag=%u\n", 
      OPCODE(opline),
      ARG(opline),
      FLAG(opline)
    );

  }

  como_object_dtor(code);

  return 0;
}
















