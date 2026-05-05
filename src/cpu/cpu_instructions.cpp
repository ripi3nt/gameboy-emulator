#include "cpu.hpp"
#include "utils.hpp"

void decode_execute(char ins) {
  switch (ins) {
  case 0x00:
    break;

  case 0x01: {
    load16(BC);
    break;
  }
  case 0x02: {
    aload8(BC, A);
    break;
  }
  case 0x03: {
    registers[BC]++;
    break;
  }
  case 0x04: {
    incHalfReg(B);
    break;
  }
  case 0x05: {
    decHalfReg(B);
    break;
  }
  case 0x06: {
    load8(B);
    break;
  }
  case 0x07: {
    unsigned char a = registers[AF] >> 8;

    unsigned char msb = a >> 7;
    a = a << 1;
    a &= 0b11111110;
    a += msb;

    registers[AF] = ((short)a << 8) & (registers[BC] & 0x0f);

    setFlag(ZERO_FLAG, 0);
    setFlag(SUBTRACTION_FLAG, 0);
    setFlag(HALF_CARRY_FLAG, 0);
    setFlag(CARRY_FLAG, msb == 1);

    break;
  }
  case 0x08: {
    aload16(SP);
    break;
  }
  case 0x09: {
    addr16(HL, BC);
    break;
  }
  case 0x0A: {
    load8(A, memory[registers[BC]]);
  }
  case 0x0B: {
    registers[BC]--;
    break;
  }

  }
}
