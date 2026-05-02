#include "cpu/cpu_instructions.hpp"
#include "cpu/cpu.hpp"


int main() {
  //instruction cycle
  while(true) {
    unsigned char instruction = memory[registers[PC]++];

    decode_execute(instruction);
  }

  return 1;
}
