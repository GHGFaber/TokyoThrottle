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
    float rails = 0.2;
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

void box1(float w1, float h1, float d1)
{
	float w=w1*0.5;
	float d=d1*0.5;
	float h=h1*0.5;
	//notice the normals being set
	glBegin(GL_QUADS);
		//top
		glNormal3f( 0.0f, 1.0f, 0.0f);
		glVertex3f( w, h,-d);
		glVertex3f(-w, h,-d);
		glVertex3f(-w, h, d);
		glVertex3f( w, h, d);
		// bottom
		glNormal3f( 0.0f, -1.0f, 0.0f);
		glVertex3f( w,-h, d);
		glVertex3f(-w,-h, d);
		glVertex3f(-w,-h,-d);
		glVertex3f( w,-h,-d);
		// front
		glNormal3f( 0.0f, 0.0f, 1.0f);
		glVertex3f( w, h, d);
		glVertex3f(-w, h, d);
		glVertex3f(-w,-h, d);
		glVertex3f( w,-h, d);
		// back
		glNormal3f( 0.0f, 0.0f, -1.0f);
		glVertex3f( w,-h,-d);
		glVertex3f(-w,-h,-d);
		glVertex3f(-w, h,-d);
		glVertex3f( w, h,-d);
		// left side
		glNormal3f(-1.0f, 0.0f, 0.0f);
		glVertex3f(-w, h, d);
		glVertex3f(-w, h,-d);
		glVertex3f(-w,-h,-d);
		glVertex3f(-w,-h, d);
		// Right side
		glNormal3f( 1.0f, 0.0f, 0.0f);
		glVertex3f( w, h,-d);
		glVertex3f( w, h, d);
		glVertex3f( w,-h, d);
		glVertex3f( w,-h,-d);
		glEnd();
	glEnd();
}



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
    gl.rails = pressed;
	return pressed;
}
/*bool unpaused(bool pressed)
{
    pressed = false;
    return pressed;
}*/
double rails(double rails) {
    int a = 0.2;
    int b = 5.0;

    if (rails == a) {
        return b;
    }
    if (rails == b) {
        return a;
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
void tunnel() {
    double k = 2.0;
    for (int i=0; i<400; i++) {
        if (i <= 200){
            k = k + 0.05;
		    glPushMatrix();
		    glTranslatef(6.0f, -0.5f, (float)-i*2.5);
            //3rd element was 0.2
            //2nd element was 5.0
		    box1(0.2, k, gl.rails);
		    glPopMatrix();
		    glPushMatrix();
		    glTranslatef(-6.0f, -0.5f, (float)-i*2.5);
            //3rd element was 0.2
            //2nd element was 5.0
		    box1(0.2, k, gl.rails);
		    glPopMatrix();
        }
        else if (i > 200 && i <= 250) {
            k = k - 0.1;
		    glPushMatrix();
		    glTranslatef(6.0f, -0.5f, (float)-i*2.5);
            //3rd element was 0.2
            //2nd element was 5.0
		    box1(0.2, k, gl.rails);
		    glPopMatrix();
		    glPushMatrix();
		    glTranslatef(-6.0f, -0.5f, (float)-i*2.5);
            //3rd element was 0.2
            //2nd element was 5.0
		    box1(0.2, k, gl.rails);
		    glPopMatrix();
        }
        else if (i > 250 && i <= 300) {
            k = k + 0.05;
		    glPushMatrix();
		    glTranslatef(6.0f, -0.5f, (float)-i*2.5);
            //3rd element was 0.2
            //2nd element was 5.0
		    box1(0.2, k, gl.rails);
		    glPopMatrix();
		    glPushMatrix();
		    glTranslatef(-6.0f, -0.5f, (float)-i*2.5);
            //3rd element was 0.2
            //2nd element was 5.0
		    box1(0.2, k, gl.rails);
		    glPopMatrix();
        }
        else {
            k = k - 0.05;
		    glPushMatrix();
		    glTranslatef(6.0f, -0.5f, (float)-i*2.5);
            //3rd element was 0.2
            //2nd element was 5.0
		    box1(0.2, k, gl.rails);
		    glPopMatrix();
		    glPushMatrix();
		    glTranslatef(-6.0f, -0.5f, (float)-i*2.5);
            //3rd element was 0.2
            //2nd element was 5.0
		    box1(0.2, k, gl.rails);
		    glPopMatrix();
        }
	}
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
 
