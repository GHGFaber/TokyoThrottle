//Author: Irene Chavez
#include <iostream>
#include <GL/glx.h>
#include <X11/Xlib.h>
#include <X11/keysym.h>
using namespace std;

void print_name(){
	cout<< "irene a." << endl;
}
bool helpState(bool touch){
	touch = true; 
	return touch; 
}
void finish(){
    Rect r;
    r.bot = 1000;
    r.left = 1100;
    r.center = 0;
    ggprint16(&r, 16, 0x00eb1010, "You are now in practice mode, go! go! go!");
}

void practice(){
    Rect s;
    s.bot = 1100;
    s.left = 1100;
    s.center = 0;
    ggprint16(&s, 16, 0x00ff01de, " Congratulations you won!!!");
}
