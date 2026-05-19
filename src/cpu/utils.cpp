#include "cpu.hpp"

void load16(Register reg) {
  short n16 = memory[registers[PC]++];
  n16 += memory[registers[PC]++] << 8;
  registers[reg] = n16;
}

void aload16(Register reg) {
  unsigned short regVal = registers[reg];

  unsigned char p1 = static_cast<unsigned char>(regVal & 0x00ff);
  unsigned char p2 = static_cast<unsigned char>(regVal >> 8);

  memory[registers[PC]++] = p1;
  memory[registers[PC]++] = p2;
}

void load8(HalfRegister hreg, unsigned char val) {
  unsigned short n8 = static_cast<unsigned short>(val);
  switch (hreg) {
  case A: {
    registers[AF] = registers[AF] & 0x0f;
    n8 = n8 << 8;
    registers[AF] += n8;
    break;
  }
  case F: {
    registers[AF] = registers[AF] & 0xf0;
    registers[AF] += n8;
    break;
  }
  case B: {
    registers[BC] = registers[BC] & 0x0f;
    n8 = n8 << 8;
    registers[BC] += n8;
    break;
  }
  case C: {
    registers[BC] = registers[BC] & 0xf0;
    registers[BC] += n8;
    break;
  }
  case D: {
    registers[DE] = registers[DE] & 0x0f;
    n8 = n8 << 8;
    registers[DE] += n8;
    break;
  }
  case E: {
    registers[DE] = registers[DE] & 0xf0;
    registers[DE] += n8;
    break;
  }
  case H: {
    registers[HL] = registers[HL] & 0x0f;
    n8 = n8 << 8;
    registers[HL] += n8;
    break;
  }
  case L: {
    registers[HL] = registers[HL] & 0xf0;
    registers[HL] += n8;
    break;
  }
  }
}

void setFlag(RegisterFlags flag, bool val) {
  // TODO: am i shifting correctly?
  switch (flag) {
  case ZERO_FLAG: {
    // clear and set flag bit
    registers[AF] &= ~(1 << 7);
    registers[AF] |= val << 7;
    break;
  }
  case SUBTRACTION_FLAG: {
    // clear and set flag bit
    registers[AF] &= ~(1 << 6);
    registers[AF] |= val << 6;
    break;
  }
  case HALF_CARRY_FLAG: {
    // clear and set flag bit
    registers[AF] &= ~(1 << 5);
    registers[AF] |= val << 5;
    break;
  }
  case CARRY_FLAG: {
    // clear and set flag bit
    registers[AF] &= ~(1 << 4);
    registers[AF] |= val << 4;
    break;
  }
  }
}

void load8(HalfRegister hr) { load8(hr, memory[registers[PC]++]); }

void addr16(Register r1, Register r2) {
  setFlag(CARRY_FLAG, registers[r1] > 0xffff - registers[r2]);

  unsigned char l = registers[r1] >> 8;
  unsigned char c = registers[r2] >> 8;
  setFlag(HALF_CARRY_FLAG, l > 0xff - c);

  registers[r1] += registers[r2];
  setFlag(SUBTRACTION_FLAG, 0);
}

unsigned char getHalfRegister(HalfRegister hr) {
  if (hr == A || hr == B || hr == D || hr == H) {
    return static_cast<unsigned char>(registers[hr] >> 8);
  } else {
    return static_cast<unsigned char>(registers[hr] & 0x0f);
  }
}

void incHalfReg(HalfRegister hreg) {
  unsigned char hregVal = getHalfRegister(hreg);
  setFlag(HALF_CARRY_FLAG, hregVal == 255);

  hregVal++;
  load8(hreg, hregVal);

  setFlag(ZERO_FLAG, hregVal == 0);
  setFlag(SUBTRACTION_FLAG, 0);
}

void decHalfReg(HalfRegister hreg) {
  unsigned char hregVal = getHalfRegister(hreg);
  setFlag(HALF_CARRY_FLAG, hregVal == 255);

  hregVal--;
  load8(hreg, hregVal);

  setFlag(ZERO_FLAG, hregVal == 0);
  setFlag(SUBTRACTION_FLAG, 1);
}

void aload8(Register addr, HalfRegister val) {
  unsigned char regVal = getHalfRegister(val);
  memory[registers[addr]] = regVal;
}

void aload8(Register addr) {
  unsigned char regVal = memory[registers[PC]++];
  memory[registers[addr]] = regVal;
}

void load8(HalfRegister dest, Register addr) {
  unsigned char val = memory[registers[addr]];
  load8(dest, val);
}

bool getFlag(RegisterFlags flag) {
  // TODO: am i shifting correctly?
  unsigned char flags = getHalfRegister(F);
  switch (flag) {
  case ZERO_FLAG: {
    return (flags & 0b10000000) > 0;
    break;
  }
  case SUBTRACTION_FLAG: {
    return (flags & 0b01000000) > 0;
    break;
  }
  case HALF_CARRY_FLAG: {
    return (flags & 0b00100000) > 0;
    break;
  }
  case CARRY_FLAG: {
    return (flags & 0b00010000) > 0;
    break;
  }
  }
}

void jumpCondition(ConditionCode cond) {
  switch (cond) {
  case NZ: {
    if (!getFlag(ZERO_FLAG)) {
      signed char offset = memory[registers[PC]++];
      registers[PC] += offset;
    }
  }
  case Z: {
    if (getFlag(ZERO_FLAG)) {
      signed char offset = memory[registers[PC]++];
      registers[PC] += offset;
    }
  }
  case NC: {
    if (!getFlag(CARRY_FLAG)) {
      signed char offset = memory[registers[PC]++];
      registers[PC] += offset;
    }
  }
  case CC: {
    if (getFlag(CARRY_FLAG)) {
      signed char offset = memory[registers[PC]++];
      registers[PC] += offset;
    }
  }
  }
}

void load8(HalfRegister dest, HalfRegister val) {
  load8(dest, getHalfRegister(val));
}

void addr8(HalfRegister r2) {
  unsigned char val1 = getHalfRegister(A);
  unsigned char val2 = getHalfRegister(r2);

  setFlag(ZERO_FLAG, val1 + val2 == 0);
  setFlag(SUBTRACTION_FLAG, 0);
  setFlag(CARRY_FLAG, val1 > 0xFF - val2);
  setFlag(HALF_CARRY_FLAG, (val1 & 0xF) + (val2 & 0xF) > 0xF);

  load8(A, val1 + val2);
}

void adcr8(HalfRegister r2) {
  unsigned char val1 = getHalfRegister(A);
  unsigned char val2 = getHalfRegister(r2);
  unsigned char carry = getFlag(CARRY_FLAG);

  setFlag(ZERO_FLAG, val1 + val2 + carry == 0);
  setFlag(SUBTRACTION_FLAG, 0);
  setFlag(CARRY_FLAG, val1 > 0xFF - val2 - carry);
  setFlag(HALF_CARRY_FLAG, (val1 & 0xF) + (val2 & 0xF) + carry > 0xF);

  load8(A, val1 + val2 + carry);
}

void subr8(HalfRegister r2) {
  unsigned char val1 = getHalfRegister(A);
  unsigned char val2 = getHalfRegister(r2);

  setFlag(ZERO_FLAG, val1 - val2 == 0);
  setFlag(SUBTRACTION_FLAG, 1);
  setFlag(CARRY_FLAG, val1 < val2);
  setFlag(HALF_CARRY_FLAG, (val1 & 0xF) < (val2 & 0xF));

  load8(A, val1 - val2);
}

void sbcr8(HalfRegister r2) {
  unsigned char val1 = getHalfRegister(A);
  unsigned char val2 = getHalfRegister(r2);
  unsigned char carry = getFlag(CARRY_FLAG);

  setFlag(ZERO_FLAG, val1 - val2 - carry == 0);
  setFlag(SUBTRACTION_FLAG, 1);
  setFlag(CARRY_FLAG, val1 < val2 + carry);
  setFlag(HALF_CARRY_FLAG, (val1 & 0xF) < (val2 & 0xF) + carry);

  load8(A, val1 - val2);
}

void andr8(HalfRegister r2) {
  unsigned char val1 = getHalfRegister(A);
  unsigned char val2 = getHalfRegister(r2);

  setFlag(ZERO_FLAG, (val1 & val2) == 0);
  setFlag(SUBTRACTION_FLAG, 0);
  setFlag(CARRY_FLAG, 0);
  setFlag(HALF_CARRY_FLAG, 1);

  load8(A, val1 & val2);
}

void xorr8(HalfRegister r2) {
  unsigned char val1 = getHalfRegister(A);
  unsigned char val2 = getHalfRegister(r2);

  setFlag(ZERO_FLAG, (val1 ^ val2) == 0);
  setFlag(SUBTRACTION_FLAG, 0);
  setFlag(CARRY_FLAG, 0);
  setFlag(HALF_CARRY_FLAG, 0);

  load8(A, val1 ^ val2);
}
