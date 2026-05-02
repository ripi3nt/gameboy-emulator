#pragma once

enum Register {
  AF, BC, DE, HL, SP, PC
};

enum HalfRegister {
  A, F, B, C, D, E, H, L
};

enum RegisterFlags { ZERO_FLAG, SUBTRACTION_FLAG, HALF_CARRY_FLAG, CARRY_FLAG };

unsigned short registers[6];

unsigned char memory[0xffff];
