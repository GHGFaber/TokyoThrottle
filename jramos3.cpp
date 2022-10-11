#include <iostream>
#include "jr3image.h"
#include "fonts.h"
#include <cstring>
#include <GL/gl.h>
#include <GL/glx.h>
#include <GL/glu.h>
using namespace std;
// ============================================================================
// NAME: Jarl Ramos
// ASGT: Lab 7 / Group Project - Tokyo Throttle
// FILE: jramos3.cpp
// ORGN: CSUB - CMPS-3350
// DATE: 5 October 2022
// ============================================================================
class OtherCar
{
    private:
    int xPosition;
    int yPosition;
    int velocity;
    public:
    // add data regarding car sprites
    // tie the car position to the street
};
/*
extern class MyImage myimage;

MyImage::~MyImage() {delete [] data;}
    MyImage::MyImage(const char *fname) {
        if (fname[0] == '\0')
            return;
        char name[40];
        strcpy (name, fname);
        int slen = strlen(name);
        name[slen - 4] = '\0';
        char ppmname[80];
        sprintf(ppmname, "%s.ppm", name);
        char ts[100];
        sprintf(ts, "convert %s %s, fname, ppmname");
        system(ts);
        FILE *fpi = fopen(ppmname, "r");
        if (fpi) {
            char line[200];
            fgets(line, 200, fpi);
            fgets(line, 200, fpi);
            //skip comments and blank lines
            while (line[0] == '#' || strlen(line) < 2)
                fgets(line, 200, fpi);
                //get pixel data
                int n = width * height * 3;
                data = new unsigned char[n];
                for (int i = 0; i < n; ++i)
                    data[i] = fgetc(fpi);
                    fclose(fpi);
        } else {
            printf("ERROR opening image: %s\n", ppmname);
            exit(0);
        }
        unlink(ppmname);
    }
*/
enum Direction
{
    Left,
    Right
};

void car_motion(Direction direction, float & position)
{
    // add code relating to movement of the camera (W, A, S, D)
    // this might work with cameraPosition[0]
    switch (direction) {
        case (Left):
            position -= 1.0f;
        case (Right):
            position += 1.0f;
    }
}

void accelerate(float & velocity)
{
    // change the velocity
    // can this work with cameraPosition[2]?
    velocity += 0.1f;
}

void decelerate(float & velocity)
{
    // lower the velocity
    velocity -= 0.1f;
}

void apply_velocity(int vel, float & position)
{
    position += vel;
}
/*
unsigned int manage_state(unsigned int s)
{
    s = s ^ 1;
    return s;
}
*/

// will set the state of whether or not the game is over
bool isOver(float velocity)
{
    bool isItOver = false;
/*
    int xcent = xr / 2;
    int ycent = yr / 2;
    int w = 100;
    glColor3f(1.0, 0.0, 0.0);
    glBegin(GL_QUADS);
    	glVertex2f(xcent - w, ycent - w);
	glVertex2f(xcent - w, ycent - w);
	glVertex2f(xcent + w, ycent + w);

    int xcent = xr / 2;
    int ycent = yr / 2;
    int w = 200;
*/
    // right now, velocity will be the main condition for game over
    // actual game over conditions will be implemented later
    if (velocity > -10.0f) {
	//  cout << "It ran." << endl;
    	isItOver = true;
    }

    return isItOver;
}

// build the rectangle used for the game over screen.
void build_rectangle(float width, float height, float d, float p0, float p1, 
                     GLubyte red, GLubyte green, GLubyte blue)
{
    glPushMatrix(); 
    glColor3ub(red, green, blue);
    glTranslatef(p0, p1, 0.0f);
    glBegin(GL_QUADS);
          glVertex2f(-width, -height);
          glVertex2f(-width,  height);
          glVertex2f( width,  height);
          glVertex2f( width, -height);
        glEnd();
        glPopMatrix();
}

/*
bool challenge_mode(float position)
{
	bool passed = false;
	
	float goal = 50.0f;
	
	if (position >= goal)
		passed = true;
	
	return passed;
}
*/

//constructs the text used for the game over screen.
void text_rect(Rect & rec, int bot, int left, int center, const char string[])
{
    //sets appropriate dimensions
    rec.bot = bot;
    rec.left = left;
    rec.center = center;
    ggprint8b(&rec, 16, 0x00ffff00, string);
}

//this will display the game over screen when the correct conditions are met;
//the function will call both the build_rectangle() and text_rect() functions
//in order to convey information to the game player
void render_the_game_over(int xr, int yr, bool flag) {
	
	if (!flag) {return;}
	
    //glClear(GL_COLOR_BUFFER_BIT);
    //game over messages
    string mess1 = "GAME OVER!";
    string mess2 = "Press any key to continue";
    int xcent = xr / 2;
    int ycent = yr / 2;
    int w = 200;
 
    int h = 200;

    //for the text that will show up on screen
    Rect r1;
    Rect r2;

    //prints the game over message
    text_rect(r1, ycent, 0.9f * xcent, 0, "GAME OVER!");
    text_rect(r2, 0.9 * ycent, 0.6f * xcent, 0, "Press any key to continue");
    
    //builds the background for the game over screen
    build_rectangle(w, h, 0.0f, xcent, ycent, 0, 225, 0);

    //r1.bot = 0.5f * ycent + ycent;
    //r1.left = 0.5f * xcent;
    //r1.center = 0;
    
    //r2.bot = 0.25f * ycent;
    //r2.left = 0.5f * xcent;
    //r2.center = 0;
   
    //ggprint8b(&r1, 16, 0x00ff0000, "GAME OVER!");
    //ggprint8b(&r2, 16, 0x00ff0000, "Press any key to continue");
  
}

//how will this be implemented with feature mode?
void you_win(bool flag, int xr, int yr)
{
	Rect r3;
	
	int xcent = xr / 2;
	int ycent = yr / 2;
	
	if (flag)
		text_rect(r3, ycent, xcent * 0.8, 0, "YOU WIN!!!!!");
}
void show_name_jr3()
{
    std::cout << "Jarl Ramos / Geoffrey De Palme" << std::endl;
}
