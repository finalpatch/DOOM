// Emacs style mode select   -*- C++ -*- 
//-----------------------------------------------------------------------------
//
// $Id:$
//
// Copyright (C) 1993-1996 by id Software, Inc.
//
// This source is available for distribution and/or modification
// only under the terms of the DOOM Source Code License as
// published by id Software. All rights reserved.
//
// The source is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// FITNESS FOR A PARTICULAR PURPOSE. See the DOOM Source Code License
// for more details.
//
// $Log:$
//
// DESCRIPTION:
//	DOOM graphics stuff for X11, UNIX.
//
//-----------------------------------------------------------------------------

static const char
rcsid[] = "$Id: i_x.c,v 1.6 1997/02/03 22:45:10 b1 Exp $";

#include <stdlib.h>
#include <unistd.h>
#include <sys/errno.h>
#include "doomstat.h"
#include "i_system.h"
#include "v_video.h"
#include "m_argv.h"
#include "d_main.h"
#include "doomdef.h"
#include "hal.h"

void I_InitGraphics(void)
{
	fpga[LCDEnable] = 1;
}

void I_ShutdownGraphics(void)
{
}

static int	lastmousex = 0;
static int	lastmousey = 0;
boolean		mousemoved = false;

void I_GetEvent(void)
{
    // TODO:
	// event_t e;
	// D_PostEvent(&e);
}

void I_StartTic (void)
{
	I_GetEvent();
}


void I_UpdateNoBlit (void)
{
}

void I_FinishUpdate (void)
{
	fpga[LCDFrameBuffer] = (uint32_t)screens[0];
}


void I_ReadScreen (byte* scr)
{
    memcpy (scr, screens[0], SCREENWIDTH*SCREENHEIGHT);
}

void I_SetPalette (byte* palette)
{
	unsigned r, g, b;
	int i;
	for (i=0 ; i<256 ; i++)
	{
		r = gammatable[usegamma][*palette++];
		g = gammatable[usegamma][*palette++];
		b = gammatable[usegamma][*palette++];
		fpga[LCDLookupTable + i] = b | (g << 8) | (r << 16) | (0xff << 24);
	}
}

void I_StartFrame (void)
{
}
