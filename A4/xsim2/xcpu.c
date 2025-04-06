#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "xis.h"
#include "xcpu.h"
#include "xmem.h"

/* Use 
 *   xcpu_print( c );
 * to print cpu state, where c is of type xcpu * 
 * See xcpu.h for full prototype of xcpu_print()
 */

 extern int xcpu_execute(xcpu *c) {
  unsigned char instruction[2];
  unsigned short opcode;
  unsigned short operand;
  
  // 1. Fetch instruction
  xmem_load(c->pc, instruction);
  opcode = instruction[0];
  operand = instruction[1];
  c->pc += 2;

  // 2. Decode and execute instruction
  switch (opcode) {
      // 0-operand instructions
      case 0x01:  // ret
          xmem_load(c->regs[X_STACK_REG], instruction);
          c->pc = (instruction[0] << 8) | instruction[1];
          c->regs[X_STACK_REG] += 2;
          break;
          
      case 0x02:  // cld
          c->state &= ~X_STATE_DEBUG_ON;
          break;
          
      case 0x03:  // std
          c->state |= X_STATE_DEBUG_ON;
          break;
          
      // 1-operand instructions
      case 0x41:  // neg rD
          c->regs[XIS_REG1(operand)] = -c->regs[XIS_REG1(operand)];
          break;
          
      case 0x42:  // not rD
          c->regs[XIS_REG1(operand)] = ~c->regs[XIS_REG1(operand)];
          break;
          
      case 0x43:  // push rS
          c->regs[X_STACK_REG] -= 2;
          xmem_store((unsigned char *)&c->regs[XIS_REG1(operand)], c->regs[X_STACK_REG]);
          break;
          
      case 0x44:  // pop rD
          xmem_load(c->regs[X_STACK_REG], instruction);
          c->regs[XIS_REG1(operand)] = (instruction[0] << 8) | instruction[1];
          c->regs[X_STACK_REG] += 2;
          break;
          
      case 0x47:  // out rS
          putchar(c->regs[XIS_REG1(operand)] & 0xFF);
          break;
          
      case 0x48:  // inc rD
          c->regs[XIS_REG1(operand)]++;
          break;
          
      case 0x49:  // dec rD
          c->regs[XIS_REG1(operand)]--;
          break;
          
      // 2-operand instructions
      case 0x81:  // add rS, rD
          c->regs[XIS_REG2(operand)] += c->regs[XIS_REG1(operand)];
          break;
          
      case 0x82:  // sub rS, rD
          c->regs[XIS_REG2(operand)] -= c->regs[XIS_REG1(operand)];
          break;
          
      case 0x83:  // mul rS, rD
          c->regs[XIS_REG2(operand)] *= c->regs[XIS_REG1(operand)];
          break;
          
      case 0x84:  // div rS, rD
          if (c->regs[XIS_REG1(operand)] != 0) {
              c->regs[XIS_REG2(operand)] /= c->regs[XIS_REG1(operand)];
          }
          break;
          
      case 0x8D:  // mov rS, rD
          c->regs[XIS_REG2(operand)] = c->regs[XIS_REG1(operand)];
          break;
          
      case 0x8E:  // load rS, rD
          xmem_load(c->regs[XIS_REG1(operand)], instruction);
          c->regs[XIS_REG2(operand)] = (instruction[0] << 8) | instruction[1];
          break;
          
      case 0x8F:  // stor rS, rD
          xmem_store((unsigned char *)&c->regs[XIS_REG1(operand)], c->regs[XIS_REG2(operand)]);
          break;
          
      // Extended instructions
      case 0xE1:  // loadi V, rD
          xmem_load(c->pc, instruction);
          c->regs[XIS_REG1(operand)] = (instruction[0] << 8) | instruction[1];
          c->pc += 2;
          break;
          
      default:
          return 0;  // Illegal instruction
  }
  
  // 3. Handle debug mode
  if (c->state & X_STATE_DEBUG_ON) {
      xcpu_print(c);
  }
  
  return 1;
}