#include "cpu.hpp"
#include "utils.hpp"

void decode_execute(char ins) {
  switch (ins) {
  case 0x00:
    break;

  case 0x01: {
    short n16 = memory[registers[PC]++];
    n16 = n16 << 8;
    n16 += memory[registers[PC]++];
    load16(BC, n16);
    break;
  }
  case 0x02: {
    unsigned char a = registers[AF] >> 8;
    memory[registers[BC]] = a;
    break;
  }
  case 0x03: {
    registers[BC]++;
    break;
  }
  case 0x04: {
    unsigned char b = registers[BC] >> 8;

    setFlag(HALF_CARRY_FLAG, b == 255);

    b++;
    registers[BC] = ((short)b << 8) & (registers[BC] & 0x0f);

    setFlag(ZERO_FLAG, b==0);
    setFlag(SUBTRACTION_FLAG, false);

    break;
  }
  case 0x05: {
    unsigned char b = registers[BC] >> 8;

    setFlag(HALF_CARRY_FLAG, b == 0);

    b--;
    registers[BC] = ((short)b << 8) & (registers[BC] & 0x0f);

    setFlag(ZERO_FLAG, b==0);
    setFlag(SUBTRACTION_FLAG, true);

    break;
  }
  case 0x06: {
      load8(B, memory[registers[PC]++]);
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
      setFlag(CARRY_FLAG, msb==1);

      break;
  }
  case 0x08: {
      char addr = memory[registers[PC]++];
      aload16(addr, SP);

      break;
  }
  case 0x09: {
      setFlag(CARRY_FLAG, registers[HL] > 0xffff - registers[BC]);

      unsigned char l = registers[HL] >> 8;
      unsigned char c = registers[BC] >> 8;
      setFlag(HALF_CARRY_FLAG, l > 0xff - c);

      addr16(HL, BC);

      setFlag(SUBTRACTION_FLAG, 0);
  }
  case 0x0A: {
      unsigned char val = memory[registers[BC]];
      load8(A, static_cast<unsigned short>(val));
  }
  case 0x0B: {
      registers[BC]--;
      break;
  }
  }
}
