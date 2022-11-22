//Author: Irene Chavez
#include <iostream>
#include <GL/glx.h>
#include <X11/Xlib.h>
#include <X11/keysym.h>
#include "fonts.h"
#include "log.h"
#include "math.h"
typedef float Flt;
typedef Flt vec[3];
#define MakeVector(x, y, z, v) (v)[0]=(x),(v)[1]=(y),(v)[2]=(z)

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
    vec camera;
    Global() {
        //constructor
        xres=640;
        yres=480;
        vel = 0.0f;
        MakeVector(0.0, 1.0, 8.0, camera);
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
void practice(){
    Rect s;
    s.bot = 1100;
    s.left = 1100;
    s.center = 0;
    ggprint16(&s, 16, 0x00ff01de, " Congratulations you won!!!");
}
void finish(){
    //this is not baby green 
    glColor3f(240.0f, 230.0f, 140.0f);//sign
    box2(7.0, 2.0, 0.1, 0.0, 5.0, -74.0);

    //this is not brown
    glColor3f(255.0f, 160.0f, 122.0f);// left pole 
    box2(0.3, 7.0, 0.1, -7.0, 0.0, -74.0);
       
    glColor3f(255.0f, 160.0f, 122.0f);//rightpole
    box2(0.3, 7.0, 0.1, 7.0, 0.0, -74.0);
    if(gx.camera[2] <= -74.0f){
        practice();
    }  
}
void mainFinish(){
    //this is brown
    glColor3f(0.54f, 0.27f, 0.7f);// left pole 
    box2(0.3, 7.0, 0.1, -7.0, 0.0, -950.0);
       
    glColor3f(0.54f, 0.27f, 0.07f);//rightpole
    //glColor3f(150.0f, 200.0f, 120.0f);
    box2(0.3, 7.0, 0.1, 7.0, 0.0, -950.0);

    //this is baby green 
    glColor3f(0.45f, 0.70f, 0.22f);//sign
    box2(7.0, 2.0, 0.1, 0.0, 5.0, -950.0);

}

void finishText(){
    Rect r;
    r.bot = 1000;
    r.left = 1100;
    r.center = 0;
    ggprint16(&r, 16, 0x00eb1010, "You are now in practice mode, go! go! go!");
    }
    
/*void practice(){
    Rect s;
    s.bot = 1100;
    s.left = 1100;
    s.center = 0;
    ggprint16(&s, 16, 0x00ff01de, " Congratulations you won!!!");
}*/
