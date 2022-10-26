//Name: Jesus Quinonez
#include <iostream>
#include "fonts.h"
#include "log.h"

using namespace std;

void display_name(){
    cout << "Jesus hello" << endl;
}

bool startState(int count)
{
    if(count <= 0) {
        return true;
    } else {
        return false;
    }
}

void startPrint(int frames)
{
    Rect r;
    r.bot = 1080;
    r.left = 1230;
    r.center = 0;
    Rect s;
    s.bot = 1100;
    s.left = 1170;
    s.center = 0;

    if(frames < 60) {
    	ggprint16(&s, 16, 0x00eb1010, "Tokyo Throttle");
        ggprint16(&r, 16,  0x00eb1010, "3");
    }
    else if(frames >= 60 && frames < 120) {
    	ggprint16(&s, 16, 0x00eb1010, "Tokyo Throttle");
        ggprint16(&r, 16, 0x00eb1010, "2");
    }
    else if(frames >= 120 && frames < 180) {
    	ggprint16(&s, 16, 0x00eb1010, "Tokyo Throttle");
        ggprint16(&r, 16, 0x00eb1010, "1");
    }
    else if(frames >= 180 && frames < 240) {
    	ggprint16(&s, 16, 0x00eb1010, "Tokyo Throttle");
        ggprint16(&r, 16,  0x0038eb10, "Go!");
    }
}

int startCount(int frames) {
    int start = 1;
    if(frames >= 180) {
        start = 0;
    }

    return start;
}

void restartPrint()
{
     Rect r;
    r.bot = 1080;
    r.left = 1230;
    r.center = 0;
    Rect s;
    s.bot = 1100;
    s.left = 1170;
    s.center = 0;

    ggprint16(&s, 16, 0x00eb1010, "Do You Want To Restart?");
    ggprint16(&r, 16,  0x00eb1010, "Yes(y) No(t)");
}

void boundsPrint(int frames)
{
    Rect r;
    r.bot = 1080;
    r.left = 1230;
    r.center = 0;
    Rect s;
    s.bot = 1100;
    s.left = 1170;
    s.center = 0;

    if(frames  < 540) {
        ggprint16(&s, 16, 0x00eb1010, "Out Of Bounds");
        ggprint16(&r, 16,  0x00eb1010, "3");
    }
    else if(frames >= 540 && frames < 600) {
        ggprint16(&s, 16, 0x00eb1010, "Out Of Bounds");
        ggprint16(&r, 16, 0x00eb1010, "2");
    }
    else if(frames >= 600 && frames < 660) {
        ggprint16(&s, 16, 0x00eb1010, "Out Of Bounds");
        ggprint16(&r, 16, 0x00eb1010, "1");
    }
    else if(frames >= 660 && frames < 720) {
        ggprint16(&s, 16, 0x00eb1010, "Out Of Bounds");
        ggprint16(&r, 16,  0x0038eb10, "Back In!");
    }
}

void boundModePrint()
{
    Rect s;
    s.bot = 1200;
    s.left = 1170;
    s.center = 0;

    ggprint16(&s, 16, 0x00eb1010, "OUT OF BOUNDS MODE");
}







