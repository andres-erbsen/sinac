/*****************************************************************************
 *
 * xidletime
 *
 * derived from xautolock supplied by
 * Authors: Michel Eyckmans (MCE) & Stefan De Troch (SDT)
 *
 * --------------------------------------------------------------------------
 * 
 * Copyright 1990,1992-1999,2001-2002 by Stefan De Troch and Michel Eyckmans.
 * Copyright 2005 by Stefan Siegl <stesie@brokenpipe.de>
 * Copyright 2007 by Christian Dietrich <stettberger@dokucode.de>
 * 
 * Versions 2.0 and above of xautolock are available under version 2 of the
 * GNU GPL. 
 *
 * sinac.c -L/usr/X11R6/lib -lX11 -lXss -lXext -o sinac 
 * 
 *****************************************************************************/

#include <X11/Xos.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/Xatom.h>
#include <X11/Xresource.h>

#include <X11/extensions/scrnsaver.h>

#include <stdio.h>

#define VERSION "0.1.2"
  
static XScreenSaverInfo* xss_info = 0; 

int 
msec_idle(Display *d)
{
  if (! xss_info ) 
    xss_info = XScreenSaverAllocInfo();
  XScreenSaverQueryInfo(d, DefaultRootWindow(d), xss_info);
  return xss_info->idle;

}

int
main (int argc, char* argv[])
{
  Display* d;
  Time idleTime;
  int i, idle;
  float wait = -1;

  for (i = 1; i < argc; i++) {
    if ((strcmp(argv[i], "-w") == 0) && (i+1 < argc)
        && (sscanf(argv[i+1],"%f",&wait) == 1) ) {
		i++;
		wait *= 1000; // seconds to milliseconds
	} else {
      fprintf(stderr, "sinac - " VERSION ": %s [-w <seconds>]\n", argv[0]);
      return 1;
    }
  }

  if (!(d = XOpenDisplay (0))) {
    fprintf (stderr, "Couldn't connect to %s\n", XDisplayName (0));
    return 1;
  }
  (void) XSync (d, 0);

  if (wait >= 0)
    while ((idle = msec_idle(d)) < wait)
      usleep( (wait - idle) * 1000); // milliseconds to microseconds
  else
    fprintf(stdout, "%ld\n", msec_idle(d)/1000 );

  return 0;
}

