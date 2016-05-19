#include "counter.h"
#include <curses.h>

int numStrokes = 0;
int numDeletes = 0;

int main(int argc, const char *argv[]) {

    // Create an event tap to retrieve keypresses.
    CGEventMask eventMask = (CGEventMaskBit(kCGEventKeyDown) | CGEventMaskBit(kCGEventFlagsChanged));
    CFMachPortRef eventTap = CGEventTapCreate(
        kCGSessionEventTap, kCGHeadInsertEventTap, 0, eventMask, CGEventCallback, NULL
    );

    // Exit the program if unable to create the event tap.
    if(!eventTap) {
        fprintf(stderr, "ERROR: Unable to create event tap.\n");
        exit(1);
    }

    // Create a run loop source and add enable the event tap.
    CFRunLoopSourceRef runLoopSource = CFMachPortCreateRunLoopSource(kCFAllocatorDefault, eventTap, 0);
    CFRunLoopAddSource(CFRunLoopGetCurrent(), runLoopSource, kCFRunLoopCommonModes);
    CGEventTapEnable(eventTap, true);
    
    initscr();
    int row, col;
    getmaxyx(stdscr,row,col);
    mvprintw(row/2,(col-10)/2,"0.0000000%");   
    refresh();
    CFRunLoopRun();

    return 0;
}

CGEventRef CGEventCallback(CGEventTapProxy proxy, CGEventType type, CGEventRef event, void *refcon) {
    if (type != kCGEventKeyDown && type != kCGEventFlagsChanged && type != kCGEventKeyUp) { return event; }

    // Retrieve the incoming keycode.
    CGKeyCode keyCode = (CGKeyCode) CGEventGetIntegerValueField(event, kCGKeyboardEventKeycode);
    
    if (keyCode == 51 || keyCode == 117) {
        numDeletes += 1;
    }
    
    numStrokes += 1;

    // Update the count
    float percent = (float) numDeletes / (float) numStrokes * 100.0;
    int row, col;
    getmaxyx(stdscr,row,col);
    mvprintw(row/2,(col-10)/2,"%f%%", percent);   
    // mvprintw(0,0,"%f%%", percent);
    refresh();

    return event;
}