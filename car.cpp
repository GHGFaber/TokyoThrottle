
//program: car.cpp
//author:  Gordon Griesel
//date:    summer 2017
//
//Framework for group attempting a 3D game.
//
#include <stdio.h>
#include <stdlib.h>
//#include <unistd.h>
//#include <time.h>
#include <math.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/keysym.h>
#include <GL/gl.h>
#include <GL/glx.h>
#include <GL/glu.h>
#include "log.h"
#include "fonts.h"
#include "mfuentes.h"
#include "jquinonez.h"
#include "sdenney.h"
#include "jr3image.h"
#include <string>
typedef float Flt;
typedef Flt Vec[3];
typedef Flt	Matrix[4][4];
//some defined macros
#define MakeVector(x, y, z, v) (v)[0]=(x),(v)[1]=(y),(v)[2]=(z)
#define VecNegate(a) (a)[0]=(-(a)[0]); (a)[1]=(-(a)[1]); (a)[2]=(-(a)[2]);
#define VecDot(a,b) ((a)[0]*(b)[0]+(a)[1]*(b)[1]+(a)[2]*(b)[2])
#define VecLen(a) ((a)[0]*(a)[0]+(a)[1]*(a)[1]+(a)[2]*(a)[2])
#define VecLenSq(a) sqrtf((a)[0]*(a)[0]+(a)[1]*(a)[1]+(a)[2]*(a)[2])
#define VecCopy(a,b) (b)[0]=(a)[0];(b)[1]=(a)[1];(b)[2]=(a)[2];
#define VecAdd(a,b,c) \
	(c)[0]=(a)[0]+(b)[0];\
	(c)[1]=(a)[1]+(b)[1];\
	(c)[2]=(a)[2]+(b)[2]
#define VecSub(a,b,c) \
	(c)[0]=(a)[0]-(b)[0]; \
	(c)[1]=(a)[1]-(b)[1]; \
	(c)[2]=(a)[2]-(b)[2]
#define VecS(A,a,b) (b)[0]=(A)*(a)[0]; (b)[1]=(A)*(a)[1]; (b)[2]=(A)*(a)[2]
#define VecAddS(A,a,b,c) \
	(c)[0]=(A)*(a)[0]+(b)[0]; \
	(c)[1]=(A)*(a)[1]+(b)[1]; \
	(c)[2]=(A)*(a)[2]+(b)[2]
#define VecCross(a,b,c) \
	(c)[0]=(a)[1]*(b)[2]-(a)[2]*(b)[1]; \
	(c)[1]=(a)[2]*(b)[0]-(a)[0]*(b)[2]; \
	(c)[2]=(a)[0]*(b)[1]-(a)[1]*(b)[0]
#define VecZero(v) (v)[0]=0.0;(v)[1]=0.0;v[2]=0.0
#define ABS(a) (((a)<0)?(-(a)):(a))
#define SGN(a) (((a)<0)?(-1):(1))
#define SGND(a) (((a)<0.0)?(-1.0):(1.0))
#define rnd() (float)rand() / (float)RAND_MAX
#define PI 3.14159265358979323846264338327950
#define MY_INFINITY 1000.0
//using namespace std;
//
// TODO: Finalize WASD movement of the camera/car object
// uncomment all commented-out lines when finished
//
//
void init();
void init_opengl();
void check_mouse(XEvent *e);
int check_keys(XEvent *e);
void physics();
void render();
void show_name();
void show_name_jr3(void);
void show_name_s();
void display_name();
void print_name();
void accelerate(float & velocity);
void decelerate(float & velocity);
bool startState(int count); 
bool helpState(bool);

int frames = 0;
bool printGO = false;
int startCounter = 4;
//MyImage img[1] = {"kachow.jpeg"};


//class MyImage myimage = {"kachow.jpeg"};

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
	Flt aspectRatio;
	Vec cameraPosition;
	GLfloat lightPosition[4];
	unsigned int feature_mode; //race mode
	bool pPressed, cPressed, wPressed, aPressed, sPressed, dPressed, hPressed;
	bool raceModeOn = false;
	float vel;
	//int xres, yres;	
	Texture tex;
	Global() {
		//constructor
		xres=640;
		yres=480;
		aspectRatio = (GLfloat)xres / (GLfloat)yres;
		MakeVector(0.0, 1.0, 8.0, cameraPosition);
		//light is up high, right a little, toward a little
		MakeVector(100.0f, 240.0f, 40.0f, lightPosition);
		lightPosition[3] = 1.0f;
		vel = 0.0f;
		wPressed = false;
		aPressed = false;
		sPressed = false;
		dPressed = false;
		cPressed = false;
        //pause
        pPressed = false;
		//help screen
		hPressed = false;
	}
} g;


class X11_wrapper {
private:
	Display *dpy;
	Window win;
	GLXContext glc;
public:
	X11_wrapper() {
		//Look here for information on XVisualInfo parameters.
		//http://www.talisman.org/opengl-1.1/Reference/glXChooseVisual.html
		Window root;
		GLint att[] = { GLX_RGBA,
						GLX_STENCIL_SIZE, 2,
						GLX_DEPTH_SIZE, 24,
						GLX_DOUBLEBUFFER, None };
		//GLint att[] = { GLX_RGBA, GLX_DEPTH_SIZE, 24, GLX_DOUBLEBUFFER, None };
		//GLint att[] = { GLX_RGBA, GLX_DEPTH_SIZE, 24, None };
		//XVisualInfo *vi;
		Colormap cmap;
		XSetWindowAttributes swa;
		setup_screen_res(640, 480);
		dpy = XOpenDisplay(NULL);
		if (dpy == NULL) {
			printf("\n\tcannot connect to X server\n\n");
			exit(EXIT_FAILURE);
		}
		root = DefaultRootWindow(dpy);
		XVisualInfo *vi = glXChooseVisual(dpy, 0, att);
		if (vi == NULL) {
			printf("\n\tno appropriate visual found\n\n");
			exit(EXIT_FAILURE);
		} 
		cmap = XCreateColormap(dpy, root, vi->visual, AllocNone);
		swa.colormap = cmap;
		swa.event_mask = ExposureMask | KeyPressMask | KeyReleaseMask |
							StructureNotifyMask | SubstructureNotifyMask;
		win = XCreateWindow(dpy, root, 0, 0, g.xres, g.yres, 0,
								vi->depth, InputOutput, vi->visual,
								CWColormap | CWEventMask, &swa);
		set_title();
		glc = glXCreateContext(dpy, vi, NULL, GL_TRUE);
		glXMakeCurrent(dpy, win, glc);
	}
	~X11_wrapper() {
		XDestroyWindow(dpy, win);
		XCloseDisplay(dpy);
	}
	void setup_screen_res(const int w, const int h) {
		g.xres = w;
		g.yres = h;
		g.aspectRatio = (GLfloat)g.xres / (GLfloat)g.yres;
	}
	void check_resize(XEvent *e) {
		//The ConfigureNotify is sent by the
		//server if the window is resized.
		if (e->type != ConfigureNotify)
			return;
		XConfigureEvent xce = e->xconfigure;
		if (xce.width != g.xres || xce.height != g.yres) {
			//Window size did change.
			reshape_window(xce.width, xce.height);
		}
	}
	void reshape_window(int width, int height) {
		//window has been resized.
		setup_screen_res(width, height);
		//
		glViewport(0, 0, (GLint)width, (GLint)height);
		glMatrixMode(GL_PROJECTION); glLoadIdentity();
		glMatrixMode(GL_MODELVIEW); glLoadIdentity();
		glOrtho(0, g.xres, 0, g.yres, -1, 1);
		set_title();
	}
	void set_title() {
		//Set the window title bar.
		XMapWindow(dpy, win);
		XStoreName(dpy, win, "car demo");
	}
	bool getXPending() {
		return XPending(dpy);
	}
	XEvent getXNextEvent() {
		XEvent e;
		XNextEvent(dpy, &e);
		return e;
	}
	void swapBuffers() {
		glXSwapBuffers(dpy, win);
	}
} x11;


int main()
{
	init_opengl();
	int done = 0;
	while (!done) {
		while (x11.getXPending()) {
			XEvent e = x11.getXNextEvent();
			x11.check_resize(&e);
			check_mouse(&e);
			done = check_keys(&e);
		}
		physics();
		render();
		x11.swapBuffers();
	}
	cleanup_fonts();
	return 0;
}

void init()
{

}

void init_opengl()
{
	//OpenGL initialization
	glClearColor(0.0f, 0.4f, 0.5f, 0.0f);
	glClearDepth(1.0);
	glDepthFunc(GL_LESS);
	glEnable(GL_DEPTH_TEST);
	glShadeModel(GL_SMOOTH);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0f, g.aspectRatio, 0.1f, 100.0f);
	glMatrixMode(GL_MODELVIEW);
	//Enable this so material colors are the same as vert colors.
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_LIGHTING);
	//Turn on a light
	glLightfv(GL_LIGHT0, GL_POSITION, g.lightPosition);
	glEnable(GL_LIGHT0);
	//Do this to allow fonts
	glEnable(GL_TEXTURE_2D);
	//g.tex.backImage = &img[0];
    //create opengl texture elements

    /*glGenTextures(1, &g.tex.backTexture);
    int w = g.tex.backImage->width;
    int h = g.tex.backImage->height;
    glBindTexture(GL_TEXTURE_2D, g.tex.backTexture);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, 3, w, h, 0,
            GL_RGB, GL_UNSIGNED_BYTE, g.tex.backImage->data);
    g.tex.xc[0] = 0.0;
    g.tex.xc[1] = 0.25;
    g.tex.yc[0] = 0.0;
    g.tex.yc[1] = 1.0;
	*/
	initialize_fonts();
	//init_textures();
}

Flt vecNormalize(Vec vec) {
	Flt len = vec[0]*vec[0] + vec[1]*vec[1] + vec[2]*vec[2];
	if (len == 0.0) {
		MakeVector(0.0,0.0,1.0,vec);
		return 1.0;
	}
	len = sqrt(len);
	Flt tlen = 1.0 / len;
	vec[0] *= tlen;
	vec[1] *= tlen;
	vec[2] *= tlen;
	return len;
}

void check_mouse(XEvent *e)
{
	//Did the mouse move?
	//Was a mouse button clicked?
	static int savex = 0;
	static int savey = 0;
	//
	if (e->type == ButtonRelease) {
		return;
	}
	if (e->type == ButtonPress) {
		if (e->xbutton.button==1) {
			//Left button is down
		}
		if (e->xbutton.button==3) {
			//Right button is down
			
	g.cameraPosition[2] -= 0.1;
	g.cameraPosition[0] = 1.0 + sin(g.cameraPosition[2]*0.3);
		}
	}
	if (savex != e->xbutton.x || savey != e->xbutton.y) {
		//Mouse moved
		savex = e->xbutton.x;
		savey = e->xbutton.y;
	}
}

int check_keys(XEvent *e)
{
	//Was there input from the keyboard?
	if (e->type == KeyPress) {
		int key = (XLookupKeysym(&e->xkey, 0) & 0x0000ffff);
		switch(key) {
			case XK_1:
				break;
			case XK_w:
				g.wPressed = startState(startCounter);
				break;
			case XK_a:
				g.aPressed = startState(startCounter);
				break;
			case XK_s:
				g.sPressed = startState(startCounter);
				break;
			case XK_d:
				g.dPressed = startState(startCounter);
				break;
			case XK_i:
				print_name();
				break;
			case XK_q:
				display_name();
				break;
			case XK_m:
			    	show_name();
			    	break;
			case XK_j:
				show_name_jr3();
				break;
			case XK_b:
                //g.pPressed = false; //unpause
                g.pPressed = unpaused(g.pPressed);
                g.cPressed = rmcredits(g.cPressed);
				break;
			case XK_p:
				show_name_s();
                g.pPressed = paused(g.pPressed); //pause
				break;
			case XK_c:
            	g.cPressed = credits(g.cPressed);
                break;
			case XK_h:
				g.hPressed = true; 
				break;
			case XK_r:
				g.feature_mode ^= 1;
				if (g.feature_mode == 1)
					g.raceModeOn = true;
			case XK_Escape:
				return 1;
		}
	}
	return 0;
}

void box(float w1, float h1, float d1)
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


void identity33(Matrix m)
{
	m[0][0] = m[1][1] = m[2][2] = 1.0f;
	m[0][1] = m[0][2] = m[1][0] = m[1][2] = m[2][0] = m[2][1] = 0.0f;
}

void yy_transform(const Vec rotate, Matrix a)
{
	//This function applies a rotation to a matrix.
	//Call this function first, then call trans_vector() to apply the
	//rotations to an object or vertex.
	//
	if (rotate[0] != 0.0f) {
		Flt ct = cos(rotate[0]), st = sin(rotate[0]);
		Flt t10 = ct*a[1][0] - st*a[2][0];
		Flt t11 = ct*a[1][1] - st*a[2][1];
		Flt t12 = ct*a[1][2] - st*a[2][2];
		Flt t20 = st*a[1][0] + ct*a[2][0];
		Flt t21 = st*a[1][1] + ct*a[2][1];
		Flt t22 = st*a[1][2] + ct*a[2][2];
		a[1][0] = t10;
		a[1][1] = t11;
		a[1][2] = t12;
		a[2][0] = t20;
		a[2][1] = t21;
		a[2][2] = t22;
		return;
	}
	if (rotate[1] != 0.0f) {
		Flt ct = cos(rotate[1]), st = sin(rotate[1]);
		Flt t00 = ct*a[0][0] - st*a[2][0];
		Flt t01 = ct*a[0][1] - st*a[2][1];
		Flt t02 = ct*a[0][2] - st*a[2][2];
		Flt t20 = st*a[0][0] + ct*a[2][0];
		Flt t21 = st*a[0][1] + ct*a[2][1];
		Flt t22 = st*a[0][2] + ct*a[2][2];
		a[0][0] = t00;
		a[0][1] = t01;
		a[0][2] = t02;
		a[2][0] = t20;
		a[2][1] = t21;
		a[2][2] = t22;
		return;
	}
	if (rotate[2] != 0.0f) {
		Flt ct = cos(rotate[2]), st = sin(rotate[2]);
		Flt t00 = ct*a[0][0] - st*a[1][0];
		Flt t01 = ct*a[0][1] - st*a[1][1];
		Flt t02 = ct*a[0][2] - st*a[1][2];
		Flt t10 = st*a[0][0] + ct*a[1][0];
		Flt t11 = st*a[0][1] + ct*a[1][1];
		Flt t12 = st*a[0][2] + ct*a[1][2];
		a[0][0] = t00;
		a[0][1] = t01;
		a[0][2] = t02;
		a[1][0] = t10;
		a[1][1] = t11;
		a[1][2] = t12;
		return;
	}
}

void trans_vector(Matrix mat, const Vec in, Vec out)
{
	Flt f0 = mat[0][0] * in[0] + mat[1][0] * in[1] + mat[2][0] * in[2];
	Flt f1 = mat[0][1] * in[0] + mat[1][1] * in[1] + mat[2][1] * in[2];
	Flt f2 = mat[0][2] * in[0] + mat[1][2] * in[1] + mat[2][2] * in[2];
	out[0] = f0;
	out[1] = f1;
	out[2] = f2;
}
/*
void show_kachow()
{
         //glClear(GL_COLOR_BUFFER_BIT);
         glColor3f(1.0, 1.0, 1.0);
         //main
        glBindTexture(GL_TEXTURE_2D, g.tex.backTexture);
        glBegin(GL_QUADS);
                glTexCoord2f(g.tex.xc[0], g.tex.yc[1]); glVertex2i(10,      10);
                glTexCoord2f(g.tex.xc[0], g.tex.yc[0]); glVertex2i(10,      g.yres);
                glTexCoord2f(g.tex.xc[1], g.tex.yc[0]); glVertex2i(g.xres,  g.yres);
                glTexCoord2f(g.tex.xc[1], g.tex.yc[1]); glVertex2i(g.xres,  10);
        glEnd();
}
*/
void credits() 
{
    Rect r;
	Rect s;
	Rect p;
	Rect l;
	Rect m;
        //credits location 
        r.bot = g.yres -230;	
        r.left = 300;
        r.center = 0;
		s.bot = g.yres -240;
        s.left = 300;
        s.center = 0;
		p.bot = g.yres -250;
        p.left = 300;
        p.center = 0;
		l.bot = g.yres -260;
        l.left = 300;
        l.center = 0;
		m.bot = g.yres -270;
        m.left = 300;
        m.center = 0;
        ggprint8b(&r, 6, 0x00000000, "Moises Fuentes");
		ggprint8b(&s, 6, 0x00000000, "Jarls Ramos");
		ggprint8b(&p, 6, 0x00000000, "Spencer Denney");
		ggprint8b(&l, 6, 0x00000000, "Irene Chavez");
		ggprint8b(&m, 6, 0x00000000, "Jesus Quinonez");
         //glClear(GL_COLOR_BUFFER_BIT);
         glColor3f(1.0, 1.0, 1.0);
         //main
        //glBindTexture(GL_TEXTURE_2D, g.tex.backTexture);
        glBegin(GL_QUADS);
                glTexCoord2f(g.tex.xc[0], g.tex.yc[1]); glVertex2i(10,      10);
                glTexCoord2f(g.tex.xc[0], g.tex.yc[0]); glVertex2i(10,      g.yres);
                glTexCoord2f(g.tex.xc[1], g.tex.yc[0]); glVertex2i(g.xres,  g.yres);
                glTexCoord2f(g.tex.xc[1], g.tex.yc[1]); glVertex2i(g.xres,  10);
        glEnd();

}

//Pause screen pops up
void pause () 
{
    Rect r;
        //Pause Title
        r.bot = g.yres -230;
        r.left = 300;
        r.center = 0;
        ggprint8b(&r, 6, 0x00000000, "PAUSED");
         //glClear(GL_COLOR_BUFFER_BIT);
         glColor3f(1.0, 1.0, 0.5);
         //main
        //glBindTexture(GL_TEXTURE_2D, g.tex.backTexture);
        glBegin(GL_QUADS);
                glTexCoord2f(g.tex.xc[0], g.tex.yc[1]); glVertex2i(10,      10);
                glTexCoord2f(g.tex.xc[0], g.tex.yc[0]); glVertex2i(10,      g.yres);
                glTexCoord2f(g.tex.xc[1], g.tex.yc[0]); glVertex2i(g.xres,  g.yres);
                glTexCoord2f(g.tex.xc[1], g.tex.yc[1]); glVertex2i(g.xres,  10);
        glEnd();

}
//Help screen 
void help()
{
	 Rect r;
        //help title
        r.bot = g.yres -230;
        r.left = 300;
        r.center = 0;
        ggprint16(&r, 6, 0x00cd00cd, "HELP");
         //glClear(GL_COLOR_BUFFER_BIT);
         glColor3f(0.0, 0.0, 1.0);
         //main
        //glBindTexture(GL_TEXTURE_2D, g.tex.backTexture);
        glBegin(GL_QUADS);
                glTexCoord2f(g.tex.xc[0], g.tex.yc[1]); glVertex2i(10,      10);
                glTexCoord2f(g.tex.xc[0], g.tex.yc[0]); glVertex2i(10,      g.yres);
                glTexCoord2f(g.tex.xc[1], g.tex.yc[0]); glVertex2i(g.xres,  g.yres);
                glTexCoord2f(g.tex.xc[1], g.tex.yc[1]); glVertex2i(g.xres,  10);
		glEnd();
}
void drawStreet()
{
	glPushMatrix();
	glColor3f(0.2f, 0.2f, 0.2f);
	float w = 5.0;
    //d = 100.0 -> changed
	float d = 1000.0;
	float h = 0.0;
	glTranslatef(0.0f, 0.0f, 0.0f);
	glBegin(GL_QUADS);
		//top
		glNormal3f( 0.0f, 1.0f, 0.0f);
		glVertex3f( w, h,-d);
		glVertex3f(-w, h,-d);
		glVertex3f(-w, h, d);
		glVertex3f( w, h, d);
	glEnd();
	glPopMatrix();
	//double yellow line
	glColor3f(0.8f, 0.8f, 0.2f);
	w = 0.1;
    //d = 100.0 -> changed
	d = 1000.0;
	h = 0.01;
	glPushMatrix();
	glTranslatef(-0.15f, 0.0f, 0.0f);
	glBegin(GL_QUADS);
		//top
		glNormal3f( 0.0f, 1.0f, 0.0f);
		glVertex3f( w, h,-d);
		glVertex3f(-w, h,-d);
		glVertex3f(-w, h, d);
		glVertex3f( w, h, d);
	glEnd();
	glPopMatrix();
	glPushMatrix();
	glTranslatef(0.15f, 0.0f, 0.0f);
	glBegin(GL_QUADS);
		//top
		glNormal3f( 0.0f, 1.0f, 0.0f);
		glVertex3f( w, h,-d);
		glVertex3f(-w, h,-d);
		glVertex3f(-w, h, d);
		glVertex3f( w, h, d);
	glEnd();
	glPopMatrix();
	//guard rails
	glColor3f(1.0f, 1.0f, 1.0f);
    //i<40 -> changed
	for (int i=0; i<400; i++) {
		glPushMatrix();
		glTranslatef(6.0f, -0.5f, (float)-i*2.5);
		box(0.2, 5.0, 0.2);
		glPopMatrix();
		glPushMatrix();
		glTranslatef(-6.0f, -0.5f, (float)-i*2.5);
		box(0.2, 5.0, 0.2);
		glPopMatrix();
	}
}

void physics()
{
    if (g.wPressed) {
		accelerate(g.vel);
		g.cameraPosition[2] -= g.vel;
		g.wPressed = false;
	}
	if (g.aPressed) {
		accelerate(g.vel);
		//g.cameraPosition[2] -= g.vel;
		g.cameraPosition[0] -= 0.1;
		g.aPressed = false;
	}	
	if (g.sPressed) {
		decelerate(g.vel);
		g.cameraPosition[2] += g.vel;
		g.sPressed = false;
	}
	if (g.dPressed) {
		accelerate(g.vel);
		//g.cameraPosition[2] -= g.vel;
		g.cameraPosition[0] += 0.1;
		g.dPressed = false;
	}	
}

void render()
{
	Rect r;
	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
	//
	//3D mode
	glMatrixMode(GL_PROJECTION); glLoadIdentity();
	gluPerspective(45.0f, g.aspectRatio, 0.1f, 100.0f);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	//for documentation...
	Vec up = {0,1,0};
	gluLookAt(
		g.cameraPosition[0], g.cameraPosition[1], g.cameraPosition[2],
		g.cameraPosition[0], g.cameraPosition[1], g.cameraPosition[2]-1.0,
		up[0], up[1], up[2]);
	glLightfv(GL_LIGHT0, GL_POSITION, g.lightPosition);
	//
	drawStreet();
	//
	//
	//
	//switch to 2D mode
	//
	glViewport(0, 0, g.xres, g.yres);
	glMatrixMode(GL_MODELVIEW);   glLoadIdentity();
	glMatrixMode (GL_PROJECTION); glLoadIdentity();
	gluOrtho2D(0, g.xres, 0, g.yres);
	glPushAttrib(GL_ENABLE_BIT);
	glDisable(GL_LIGHTING);
	//glDisable(GL_DEPTH_TEST);
	//glDisable(GL_CULL_FACE);

    //Start state 
    if(frames < 480) {
        frames++;
    }   
    startPrint(frames);
    startCounter = startCount(frames);
    //Start state


		if (isOver(g.vel)) {
		
		render_the_game_over(g.xres, g.yres, g.raceModeOn);
		
		/*
	    string mess1 = "GAME OVER!";
	    string mess2 = "Press any key to continue";
	    int xcent = g.xres / 2;
	    int ycent = g.yres / 2;
	    */
	    //int w = 200;
	    //Rect r1;
	    //Rect r2;

	    /*
	    glPushMatrix();
	    glColor3f(0.0, 1.0, 0.0);
	    glTranslatef(g.xres / 2, g.yres / 2, 0);
	    glBegin(GL_QUADS);
	    	glVertex2f(xcent - w, ycent - w);
		glVertex2f(xcent - w, ycent + w);
		glVertex2f(xcent + w, ycent + w);
		glVertex2f(xcent + w, ycent - w);
	    glEnd();
	    glPopMatrix();
	    */
	    
	    /*
	    Rect r1;
	    Rect r2;
	    r1.bot = 0.5f * ycent + ycent;
	    r1.left = 0.9 * xcent;
	    r1.center = 0;
	    r2.bot = ycent / 2;
	    r2.left = xcent;
	    r2.center = 0;
	    ggprint8b(&r1, 16, 0x00887766, "GAME OVER!");
	    ggprint8b(&r2, 16, 0x00887766, "Press any key to continue");
	    */
	    
		}	    






	r.bot = g.yres - 20;
	r.left = 10;
	r.center = 0;
	ggprint8b(&r, 16, 0x00887766, "car framework");
	  //if p is pressed then pause
    if(g.pPressed) {
        pause();
    }

	if(g.cPressed) {
        credits();
    }
	if(g.hPressed){
		help();
	}
	glPopAttrib();
  
}



