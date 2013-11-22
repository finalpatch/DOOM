#pragma once
#include <stdint.h>

#define FREQ 50000000

extern volatile char*     io;
extern volatile uint32_t* fpga;

enum {
	InterruptControl,
	InterruptStatus,
	TimerCounter,
	TimerSet,
	LCDEnable,
	LCDLookupTable,
	LCDFrameBuffer = LCDLookupTable + 0x100,
	NumOfRegisters,
};
