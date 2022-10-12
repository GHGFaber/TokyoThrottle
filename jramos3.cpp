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
	
	if (flag) {return;}
	
    //glClear(GL_COLOR_BUFFER_BIT);
    //game over messages
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
  
}

//how will this be implemented with feature mode?
void render_game_mode_title(bool flag, int xr, int yr)
{
	Rect rRM;
	
	if (flag)
		text_rect(rRM, xr / 2, yr + 30, 0, "RACE MODE");

}
float get_init_pos(float position)
{
	return position;
}
void race_mode(int frames, float init_pos, float position,
			   bool & won)
{
	int countdown = 5;
	frames = frames + 60;
	if (frames <= 60)
		--countdown;
	else if (frames > 60 && frames <= 120)
		--countdown;
	else if (frames > 120 && frames <= 180)
		--countdown;
	else if (frames > 180 && frames <= 240)
		--countdown;
	else if (frames > 240 && frames <= 300)
		--countdown;
		
	if (position >= init_pos - 5.0f)
		won = true;
		
	if (countdown == 0)
		won = false;
}
void you_win(bool flag, int xr, int yr)
{
	Rect r3;
	
	int xcent = xr / 2;
	int ycent = yr / 2;
	
	if (flag)
		text_rect(r3, ycent, xcent * 0.8, 0, "YOU WIN!!!!!");
}
void you_lose(bool flag, int xr, int yr)
{
	if (!flag)
		render_the_game_over(flag, xr, yr);
}
void show_name_jr3()
{
    std::cout << "Jarl Ramos / Geoffrey De Palme" << std::endl;
}
