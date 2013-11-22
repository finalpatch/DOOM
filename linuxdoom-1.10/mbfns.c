#include "hal.h"

volatile char* io = (char*)0xfffffffc;
volatile uint32_t* fpga = (uint32_t*)0xffff0000;

void outbyte(char c)
{
	*io = c;
}

char inbyte()
{
	return *io;
}

int access(const char *path, int amode)
{
	if (strcmp(path, "./doom1.wad") == 0)
		return 0;
	return -1;
}

int usleep(unsigned  useconds)
{
	return 0;
}
