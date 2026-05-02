#include "cpu.hpp"

//half registers
unsigned char getHalfRegister(HalfRegister hr);
void setHalfRegister(HalfRegister hr, unsigned char val);

//Load
void load16(Register reg, short n16);
void load8(HalfRegister hreg, short n8);
void aload16(char mem, Register reg);
void loada8(HalfRegister hr, Register reg);

//Flags
void setFlag(RegisterFlags flag, bool val);

//Arithmetic
void addr16(Register r1, Register r2);
