//Name: Jesus Quinonez
#include <iostream>
#include "fonts.h"
#include "log.h"
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/keysym.h>
#include <GL/gl.h>
#include <GL/glx.h>
#include <GL/glu.h>

using namespace std;


void myBox(float w, float h, float d, float x, float y, float z)
{
	
	glPushMatrix();
        glTranslatef(x, y, z);
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
	ggprint16(&r, 16,  0x0038eb10, "0");
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

void boundModePrint()
{
    Rect s;
    s.bot = 1100;
    s.left = 1170;
    s.center = 0;

    ggprint16(&s, 16, 0x00eb1010, "OUT OF BOUNDS MODE");

}

void grass(int frames)
{
    //grass
        glPushMatrix();
        glColor3f(0.0f, 1.0f, 0.0f);
        float w = 3.5;
        float d = 1000.0;
        float h = 0.0;
        glTranslatef(-8.5f, 0.0f, 0.0f);
        glBegin(GL_QUADS);
                glNormal3f( 0.0f, 1.0f, 0.0f);
                glVertex3f( w, h,-d);
                glVertex3f(-w, h,-d);
                glVertex3f(-w, h, d);
                glVertex3f( w, h, d);
        glEnd();
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.0f, 1.0f, 0.0f);
        glTranslatef(8.5f, 0.0f, 0.0f);
        glBegin(GL_QUADS);
                glNormal3f( 0.0f, 1.0f, 0.0f);
                glVertex3f( w, h,-d);
                glVertex3f(-w, h,-d);
                glVertex3f(-w, h, d);
                glVertex3f( w, h, d);
        glEnd();
        glPopMatrix();
        //grass
	
	//sideline squares
        w = 0.5;
        d = 0.5;
        h = 0.0;
	for (int i=0; i<1000; i++) {
	    if((i%2) == 0) {
		glColor3f(0.0f, 0.0f, 0.0f);
	    } else {
		glColor3f(1.0f, 1.0f, 1.0f);
	    } 
		glPushMatrix();
		glTranslatef(12.5f, 0.0f, (float)-i);
		glBegin(GL_QUADS);
                	glNormal3f( 0.0f, 1.0f, 0.0f);
                	glVertex3f( w, h,-d);
                	glVertex3f(-w, h,-d);
                	glVertex3f(-w, h, d);
                	glVertex3f( w, h, d);
                glEnd();
		glPopMatrix();

		glPushMatrix();
		glTranslatef(-12.5f, 0.0f, (float)-i);
		glBegin(GL_QUADS);
                	glNormal3f( 0.0f, 1.0f, 0.0f);
                	glVertex3f( w, h,-d);
                	glVertex3f(-w, h,-d);
                	glVertex3f(-w, h, d);
                	glVertex3f( w, h, d);
                glEnd();
		glPopMatrix();
	}
	//sideline squares
	
	//stop light
	myBox(0.1, 3.0, 0.1, -5.0, 0.0, 0.0);//left post
	myBox(2.6, 0.1, 0.1, -2.5, 3.0, 0.0);//top post
	glColor3f(0.0f, 0.0f, 0.0f);
 	myBox(0.2, 0.7, 0.2, 0.0, 2.4, 0.0);//light box
	glColor3f(1.0f, 1.0f, 1.0f);
	if(frames < 120) {
	    glColor3f(1.0f, 0.0f, 0.0f);
	}
	myBox(0.15, 0.15, 0.1, 0.0, 2.8, 0.2);
	glColor3f(1.0f, 1.0f, 1.0f);
	if(frames >= 120 && frames < 180) {
	    glColor3f(1.0f, 1.0f, 0.2f);
	}
	myBox(0.15, 0.15, 0.1, 0.0, 2.35, 0.2);
	glColor3f(1.0f, 1.0f, 1.0f);
	if(frames >= 180 && frames < 240) {
	    glColor3f(0.0f, 1.0f, 0.0f);
	}
	myBox(0.15, 0.15, 0.1, 0.0, 1.9, 0.2);
   	//stop light
	
	//light posts
         	
	/*glColor3f(1.0f, 1.0f, 1.0f);
	myBox(0.1, 3.0, 0.1, -5.0, 0.0, -5.0);//left post
	myBox(2.6, 0.1, 0.1, -2.5, 3.0, -5.0);//top post
	glColor3f(0.0f, 0.0f, 0.0f);
 	myBox(0.2, 0.7, 0.2, 0.0, 2.4, -5.0);//light box*/
}

void grassAccelerate(float & velocity)
{
    if(velocity > 10) {
	velocity = 10;
    }else {
	velocity += 0.05;
    }

}





