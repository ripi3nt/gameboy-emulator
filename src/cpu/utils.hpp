#include "cpu.hpp"

//half registers
unsigned char getHalfRegister(HalfRegister hr);
void setHalfRegister(HalfRegister hr);
void incHalfReg(HalfRegister hr);
void decHalfReg(HalfRegister hr);

//Load
void load16(Register reg);
void load8(HalfRegister hreg, unsigned short n8);
void load8(HalfRegister hreg);
void load8(HalfRegister dest, Register addr);
void aload16(Register reg);
void aload8(Register addr, HalfRegister val);

//Flags
void setFlag(RegisterFlags flag, bool val);
bool getFlag(RegisterFlags flag);

//Arithmetic
void addr16(Register r1, Register r2);

//Jumps
void jumpCondition(ConditionCode cond);
