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
    break;
  }
  case 0x30: {
    jumpCondition(NC);
    break;
  }
  case 0x31: {
    load16(SP);
    break;
  }
  case 0x32: {
    unsigned char regVal = getHalfRegister(A);
    memory[registers[HL - 1]] = regVal;
    break;
  }
  case 0x33: {
    registers[SP]++;
    break;
  }
  case 0x34: {
    setFlag(HALF_CARRY_FLAG, memory[registers[HL]] == 255);
    memory[registers[HL]]++;
    setFlag(ZERO_FLAG, memory[registers[HL]] == 0);
    setFlag(SUBTRACTION_FLAG, 0);
    break;
  }
  case 0x35: {
    setFlag(HALF_CARRY_FLAG, memory[registers[HL]] == 0);
    memory[registers[HL]]--;
    setFlag(ZERO_FLAG, memory[registers[HL]] == 0);
    setFlag(SUBTRACTION_FLAG, 1);
    break;
  }
  case 0x36: {
      aload8(HL);
      break;
  }
  case 0x37: {
      setFlag(CARRY_FLAG, 1);
      break;
  }
  case 0x38: {
      jumpCondition(CC);
      break;
  }
  case 0x39: {
      addr16(HL, SP);
      break;
  }
  case 0x3A: {
      load8(A, memory[registers[HL] - 1]);
      break;
  }
  case 0x3B: {
      registers[SP]--;
      break;
  }
  case 0x3C: {
      incHalfReg(A);
      break;
  }
  case 0x3D: {
      decHalfReg(A);
      break;
  }
  case 0x3E: {
      load8(A);
      break;
  }
  case 0x3F: {
      setFlag(CARRY_FLAG, !getFlag(CARRY_FLAG));
      break;
  }
  case 0x40: {
      load8(B, B);
      break;
  }
  case 0x41: {
      load8(B, C);
      break;
  }
  case 0x42: {
      load8(B, D);
      break;
  }
  case 0x43: {
      load8(B, E);
      break;
  }
  case 0x44: {
     load8(B, H);
    break;
  }
  case 0x45: {
      load8(B, L);
      break;
  }
  case 0x46: {
      load8(B, HL);
      break;
  }
  case 0x47: {
      load8(B, A);
      break;
  }
  case 0x48: {
      load8(C, B);
      break;
  }
  case 0x49: {
      load8(C, C);
      break;
  }
  case 0x4A: {
      load8(C, D);
      break;
  }
  case 0x4B: {
      load8(C, E);
      break;
  }
  case 0x4C: {
      load8(C, H);
      break;
  }
  case 0x4D: {
      load8(C, L);
      break;
  }
  case 0x4E: {
      load8(C, HL);
      break;
  }
  case 0x4F: {
      load8(C, A);
      break;
  }
  case 0x50: {
      load8(D, B);
      break;
  }
  case 0x51: {
      load8(D, C);
      break;
  }
  case 0x52: {
      load8(D, D);
      break;
  }
  case 0x53: {
      load8(D, E);
      break;
  }
  case 0x54: {
      load8(D, H);
      break;
  }
  case 0x55: {
      load8(D, D);
      break;
  }
  case 0x56: {
      load8(D, HL);
      break;
  }
  case 0x57: {
      load8(D, A);
      break;
  }
  case 0x58: {
      load8(E, B);
      break;
  }
  case 0x59: {
      load8(E, C);
      break;
  }
  case 0x5A: {
      load8(E, D);
      break;
  }
  case 0x5B: {
      load8(E, E);
      break;
  }
  case 0x5C: {
      load8(E, H);
      break;
  }
  case 0x5D: {
      load8(E, L);
      break;
  }
  case 0x5E: {
      load8(E, HL);
      break;
  }
  case 0x5F: {
      load8(E, A);
      break;
  }
  case 0x60: {
      load8(H, B);
      break;
  }
  case 0x61: {
      load8(H, C);
      break;
  }
  case 0x62: {
      load8(H, D);
      break;
  }
  case 0x63: {
      load8(H, E);
      break;
  }
  case 0x64: {
      load8(H, H);
      break;
  }
  case 0x65: {
      load8(H, L);
      break;
  }
  case 0x66: {
      load8(H, HL);
      break;
  }
  case 0x67: {
      load8(H, A);
      break;
  }
  case 0x68: {
      load8(L, B);
      break;
  }
  case 0x69: {
      load8(L, C);
      break;
  }
  case 0x6A: {
      load8(L, D);
      break;
  }
  case 0x6B: {
      load8(L, E);
      break;
  }
  case 0x6C: {
      load8(L, H);
      break;
  }
  case 0x6D: {
      load8(L, L);
      break;
  }
  case 0x6E: {
      load8(L, HL);
      break;
  }
  case 0x6F: {
      load8(L, A);
      break;
  }
  }
}
