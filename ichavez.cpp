//Author: Irene Chavez
#include <iostream>
#include <GL/glx.h>
#include <X11/Xlib.h>
#include <X11/keysym.h>
#include "fonts.h"
#include "log.h"
using namespace std;

class Texture {
public:
    //MyImage *backImage;
    XImage *backImage;
    GLuint backTexture;
    float xc[2];
    float yc[2];
};

class Global {
public:
    int xres, yres;
    float vel;
    float rails = 0.2;
    Texture tex;
    Global() {
        //constructor
        xres=640;
        yres=480;
        vel = 0.0f;
    }   
} gx; 

void box2(float w, float h, float d, float x, float y, float z) 
{
    //float w=w1*0.5;
    //float d=d1*0.5;
    //float h=h1*0.5;
    //notice the normals being set
    glPushMatrix();
    glTranslatef(x,y,z);
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
    glPopMatrix();
}

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

    glColor3f(150.0f, 200.0f, 120.0f);
    box2(5.0, 2.0, 1.0, 0.0, 1.5, -70.0);
}

void finishText(){
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
