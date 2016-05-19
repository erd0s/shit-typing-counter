#ifndef __KEYLOGGER_H__
#define __KEYLOGGER_H__

#include <stdio.h>
#include <time.h>
#include <string.h>
#include <ApplicationServices/ApplicationServices.h>
#include <Carbon/Carbon.h>
#include <curses.h>

CGEventRef CGEventCallback(CGEventTapProxy, CGEventType, CGEventRef, void*);

#endif