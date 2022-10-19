//NAME: Spencer Denney
//FILE: sdenney.cpp
//individual source file

#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include "sdenney.h"
#include "log.h"
#include "fonts.h"
#include <GL/gl.h>
#include <GL/glx.h>
#include <GL/glu.h>

class Texture {
public:
    MyImage *backImage;
    GLuint backTexture;
    float xc[2];
    float yc[2];
};
class Global {
public:
	int xres, yres;
	
	float vel;
	//int xres, yres;	
	Texture tex;
	Global() {
		//constructor
		xres=640;
		yres=480;

		vel = 0.0f;
		// curTheta = 0.0f;
	}
} gl;



void show_name_s()
{
	printf("sdenney hi\n");
}

bool paused(bool pressed)
{
    if (pressed == false) {
        pressed = true;
    }
    else if (pressed == true) {
        pressed = false;
    }
	return pressed;
}
/*bool unpaused(bool pressed)
{
    pressed = false;
    return pressed;
}*/
double rails(double rails) {
    if (rails != 5.0) {
        return 5.0;
    }
    if (rails != 0.2) {
        return 0.2;
    }
    return 0;
}
bool car(bool z) {
    if (z == false)
        z = true;
    else
        z = false;
    return z;
}
void pause_state() 
{
    Rect r;
        //Pause Title
        r.bot = gl.yres -230;
        r.left = 300;
        r.center = 0;
        ggprint8b(&r, 6, 0x00000000, "PAUSED");
         //glClear(GL_COLOR_BUFFER_BIT);
         glColor3f(1.0, 1.0, 0.5);
         //main
        //glBindTexture(GL_TEXTURE_2D, g.tex.backTexture);
        glBegin(GL_QUADS);
                glTexCoord2f(gl.tex.xc[0], gl.tex.yc[1]); glVertex2i(10,      10);
                glTexCoord2f(gl.tex.xc[0], gl.tex.yc[0]); glVertex2i(10,      gl.yres);
                glTexCoord2f(gl.tex.xc[1], gl.tex.yc[0]); glVertex2i(gl.xres,  gl.yres);
                glTexCoord2f(gl.tex.xc[1], gl.tex.yc[1]); glVertex2i(gl.xres,  10);
        glEnd();

}
/*
extern class MyImage myimage;

MyImage::~MyImage() { delete [] data; }

MyImage::MyImage(const char *fname) {
    if (fname[0] == '\0')
    return;
    char name[40];
    strcpy(name, fname);
    int slen = strlen(name);
    name[slen-4] = '\0';
    char ppmname[80];
    sprintf(ppmname,"%s.ppm", name);
    char ts[100];
    sprintf(ts, "convert %s %s", fname, ppmname);
    system(ts);
    FILE *fpi = fopen(ppmname, "r");
    if (fpi) {
        char line[200];
        fgets(line, 200, fpi);
        fgets(line, 200, fpi);
        //skip comments and blank lines
        while (line[0] == '#' || strlen(line) < 2)
            fgets(line, 200, fpi);
        sscanf(line, "%i %i", &width, &height);
        fgets(line, 200, fpi);
        //get pixel data
        int n = width * height * 3;
        data = new unsigned char[n];
        for (int i=0; i<n; i++)
            data[i] = fgetc(fpi);
        fclose(fpi);
    } else {
        printf("ERROR opening image: %s\n", ppmname);
        exit(0);
    }
    unlink(ppmname);
}*/
 
