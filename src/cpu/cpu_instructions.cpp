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
  case 0x0C: {
    incHalfReg(C);
    break;
  }
  case 0x0D: {
    decHalfReg(D);
    break;
  }
  case 0x0E: {
    load8(C);
    break;
  }
  case 0x0f: {
    unsigned char a = getHalfRegister(A);

    unsigned char lsb = a & 1;
    lsb = lsb << 7;
    a = a >> 1;
    a &= 0b01111111;
    a += lsb;

    load8(A, a);

    setFlag(ZERO_FLAG, 0);
    setFlag(SUBTRACTION_FLAG, 0);
    setFlag(HALF_CARRY_FLAG, 0);
    setFlag(CARRY_FLAG, lsb == 1);

    break;
  }
  case 0x10: {
    // hibernate
    break;
  }
  case 0x11: {
    load16(DE);
    break;
  }
  case 0x12: {
    aload8(DE, A);
    break;
  }
  case 0x13: {
    registers[DE]++;
    break;
  }
  case 0x14: {
    incHalfReg(D);
    break;
  }
  case 0x15: {
    decHalfReg(D);
    break;
  }
  case 0x16: {
    load8(D);
    break;
  }
  case 0x17: {
    unsigned char a = getHalfRegister(A);

    unsigned char msb = a >> 7;
    a = a << 1;
    a += getFlag(CARRY_FLAG);

    load8(A, a);

    setFlag(ZERO_FLAG, 0);
    setFlag(SUBTRACTION_FLAG, 0);
    setFlag(HALF_CARRY_FLAG, 0);
    setFlag(CARRY_FLAG, msb == 1);

    break;
  }
  case 0x18: {
    signed char offset = memory[registers[PC]++];

    registers[PC] += offset;
    break;
  }
  case 0x19: {
    addr16(HL, BC);
    break;
  }
  case 0x1A: {
    load8(A, DE);
    break;
  }
  case 0x1B: {
    registers[DE]--;
    break;
  }
  case 0x1C: {
    incHalfReg(E);
    break;
  }
  case 0x1D: {
    decHalfReg(E);
    break;
  }
  case 0x1E: {
    load8(E);
    break;
  }
  case 0x1F: {
    unsigned char a = getHalfRegister(A);

    unsigned char lsb = a & 1;
    a = a >> 1;
    a += getFlag(CARRY_FLAG) ? 0b10000000 : 0;

    load8(A, a);

    setFlag(ZERO_FLAG, 0);
    setFlag(SUBTRACTION_FLAG, 0);
    setFlag(HALF_CARRY_FLAG, 0);
    setFlag(CARRY_FLAG, lsb == 1);

    break;
  }
  case 0x20: {
    jumpCondition(NZ);
    break;
  }
  case 0x21: {
    load16(HL);
    break;
  }
  case 0x22: {
    unsigned char regVal = getHalfRegister(A);
    memory[registers[HL + 1]] = regVal;
    break;
  }
  case 0x23: {
    registers[HL]++;
    break;
  }
  case 0x24: {
    incHalfReg(H);
    break;
  }
  case 0x25: {
    decHalfReg(H);
    break;
  }
  case 0x26: {
    load8(H);
  }
  case 0x27: {
    if (getFlag(SUBTRACTION_FLAG)) {
      unsigned char adjustment = 0;
      if (getFlag(HALF_CARRY_FLAG))
        adjustment += 0x6;
      if (getFlag(CARRY_FLAG))
        adjustment += 0x60;
      unsigned char a = getHalfRegister(A);
      load8(A, a - adjustment);
      setFlag(HALF_CARRY_FLAG, a < 0x0 + adjustment);
    } else {
      unsigned char adjustment = 0;
      unsigned char a = getHalfRegister(A);
      if (getFlag(HALF_CARRY_FLAG) || (a & 0xF) > 0x9)
        adjustment += 0x6;
      if (getFlag(CARRY_FLAG) || (a > 0x99))
        adjustment += 0x60;
      load8(A, a + adjustment);
      setFlag(HALF_CARRY_FLAG, a > 0xff - adjustment);
    }

    setFlag(ZERO_FLAG, getHalfRegister(A) == 0);
    setFlag(HALF_CARRY_FLAG, 0);
    break;
  }
  case 0x28: {
    jumpCondition(Z);
    break;
  }
  case 0x29: {
    addr16(HL, HL);
    break;
  }
  case 0x2A: {
    load8(A, memory[registers[HL + 1]]);
    break;
  }
  case 0x2B: {
    registers[HL]--;
    break;
  }
  case 0x2C: {
    incHalfReg(L);
    break;
  }
  case 0x2D: {
    decHalfReg(L);
    break;
  }
  case 0x2E: {
    load8(L);
    break;
  }
  case 0x2F: {
    unsigned char a = getHalfRegister(A);
    a = ~a;
    load8(A, a);
  }
  case 0x30: {

  }
  }
}
