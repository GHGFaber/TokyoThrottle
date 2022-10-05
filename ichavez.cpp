//Author: Irene Chavez
#include <iostream>
#include <GL/glx.h>
#include <X11/Xlib.h>
#include <X11/keysym.h>
using namespace std;

class Global {
public:
	int xres, yres;
	int helpState;
	Global() {
		xres = 640;
		yres = 480;
		helpState = 0;
	}
}gl;
void print_name(){
	cout<< "irene a." << endl;
	}
unsigned int manage_helpState(unsigned int x)
{ 
	x = x ^ 1;
	return x;
}
void show_helpState()
{
	int xcent = gl.xres /2;
	int ycent = gl.yres /2;
	int w = 100;
	glColor3f(1.0, 0.0, 1.0);
	glBegin(GL_QUADS);
		glVertex2f(xcent -w, ycent -w); 
		glVertex2f(xcent -w, ycent +w); 
		glVertex2f(xcent +w, ycent +w); 
		glVertex2f(xcent +w, ycent -w); 
	glEnd();
	if (gl.helpState){
		show_helpState();
	}
}
