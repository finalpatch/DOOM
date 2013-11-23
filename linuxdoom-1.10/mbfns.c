#include "hal.h"
#include "doomdef.h"
#include "d_event.h"

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

int mb_gettime()
{
    static uint32_t counter = 0;
    static uint32_t basetime = 0;
    static uint32_t last = 0;
    uint32_t newtime = fpga[TimerCounter];
    if (basetime == 0)
    {
        basetime = newtime;
        return 0;
    }
    uint32_t elapsed = (newtime - basetime) * TICRATE / FREQ;
    if (elapsed == 0 && last != 0)
        counter += (uint32_t)(-1) * TICRATE / FREQ;
    last = elapsed;
    return counter + elapsed;
}

void D_PostEvent (event_t* ev);

#define handle_button(N, K)                                             \
    if(changed & (1 << N))                                              \
    {                                                                   \
        e.data1 = K;                                                    \
        e.type = (buttonStatus & (1 << N)) ? ev_keydown : ev_keyup;     \
        D_PostEvent(&e);                                                \
    }

__attribute__ ((interrupt_handler))
void isr()
{
    const char* p;
	event_t e;
    if(fpga[InterruptStatus] == 1 << ButtonInterrupt)
    {
        fpga[InterruptStatus] = 1 << ButtonInterrupt;
        static uint32_t lastButtonStatus = 0;
        uint32_t buttonStatus = fpga[ButtonStatus];
        uint32_t changed = buttonStatus ^ lastButtonStatus;
        lastButtonStatus = buttonStatus;
        if (!changed)
            return;
        handle_button(0, KEY_UPARROW);
        handle_button(1, KEY_DOWNARROW);
        handle_button(2, KEY_LEFTARROW);
        handle_button(3, KEY_RIGHTARROW);
        handle_button(4, KEY_ESCAPE);
        handle_button(5, KEY_RCTRL);
        handle_button(6, KEY_RSHIFT);
        handle_button(7, KEY_RALT);
        handle_button(8, KEY_ENTER);
        handle_button(9, KEY_TAB);
    }
}
