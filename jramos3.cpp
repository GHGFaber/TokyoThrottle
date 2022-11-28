#include <iostream>
#include "jr3image.h"
#include "fonts.h"
#include <cstring>
#include <cmath>
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

const float RAD_CONV = 0.0175f;

void text_rect_2(Rect & rec, int bot, int left, int center, const char string[],
                 float value);

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

void accelerate(float & velocity)
{
    // change the velocity
    // can this work with cameraPosition[2]?
    velocity += 0.2f;
    
    if (velocity > 3.0f)
		velocity = 3.0f;
}

void decelerate(float & velocity)
{
    // lower the velocity
    velocity -= 0.3f;
    
    if (velocity < -5.0f)
		velocity = -5.0f;
}

void go_forwards(float & vel, float & cp1, float & cp2, float theta)
{
    accelerate(vel);
    
    theta = (int)theta % 360;
    
    
    //go forward according to value of angle
    //do we slow down when turning?
    
    //TODO: Maybe implement a turning velocoty
    if (theta == 0.0f)
        cp1 -= vel;
    else if (theta == 90.0f)
        cp2 += vel;
    else if (theta == 180.0f)
        cp1 += vel;
    else if (theta == 270.0f)
        cp2 -= vel;
    else if (theta == 360.0f)
        cp1 -= vel;
    else {
        if (theta < 90.0f) {
            cp1 -= 0.75f * vel * cos(conv_rad(theta));
            cp2 += 0.75f * vel * sin(conv_rad(theta));
        }
        else if (theta > 90.0f && theta < 180.0f) {
            cp2 += 0.75f * vel * cos(conv_rad(theta - 90.0f));
            cp1 += 0.75f * vel * sin(conv_rad(theta - 90.0f));
        }
        else if (theta > 180.0f && theta < 270.0f) {
            cp2 -= 0.75f * vel * sin(conv_rad(theta - 180.0f));
            cp1 += 0.75f * vel * cos(conv_rad(theta - 180.0f));
        }
        else if (theta > 270.0f && theta < 360.0f) {
            cp2 -= 0.75f * vel * cos(conv_rad(theta - 270.0f));
            cp1 -= 0.75f * vel * sin(conv_rad(theta - 270.0f));
        }
    }
    cout << theta << endl;
}
void go_forwards_grass(float & vel, float & cp1, float & cp2, float theta)
{ 
	vel += 0.1f;
	
    theta = (int)theta % 360;
    
    //go forward according to value of angle
    //do we slow down when turning?
    
    //TODO: Maybe implement a turning velocoty
    if (theta == 0.0f)
        cp1 -= vel;
    else if (theta == 90.0f)
        cp2 += vel;
    else if (theta == 180.0f)
        cp1 += vel;
    else if (theta == 270.0f)
        cp2 -= vel;
    else if (theta == 360.0f)
        cp1 -= vel;
    else {
        if (theta < 90.0f) {
            cp1 -= 0.75f * vel * cos(conv_rad(theta));
            cp2 += 0.75f * vel * sin(conv_rad(theta));
        }
        else if (theta > 90.0f && theta < 180.0f) {
            cp2 += 0.75f * vel * cos(conv_rad(theta - 90.0f));
            cp1 += 0.75f * vel * sin(conv_rad(theta - 90.0f));
        }
        else if (theta > 180.0f && theta < 270.0f) {
            cp2 -= 0.75f * vel * sin(conv_rad(theta - 180.0f));
            cp1 += 0.75f * vel * cos(conv_rad(theta - 180.0f));
        }
        else if (theta > 270.0f && theta < 360.0f) {
            cp2 -= 0.75f * vel * cos(conv_rad(theta - 270.0f));
            cp1 -= 0.75f * vel * sin(conv_rad(theta - 270.0f));
        }
    }
}

void go_backwards(float & vel, float & cp1, float & cp2, float theta)
{
    decelerate(vel);
    
    theta = (int)theta % 360;
    
    //go backward according to value of angle
    if (theta == 0.0f)
        cp1 += vel;
    else if (theta == 90.0f)
        cp2 -= vel;
    else if (theta == 180.0f)
        cp1 -= vel;
    else if (theta == 270.0f)
        cp2 += vel;
    else if (theta == 360.0f)
        cp1 += vel;
    else {
        if (theta < 90.0f) {
            cp1 += 0.75f * vel * cos(conv_rad(theta));
            cp2 -= 0.75f * vel * sin(conv_rad(theta));
        }
        else if (theta > 90.0f && theta < 180.0f) {
            cp2 -= 0.75f * vel * cos(conv_rad(theta - 90.0f));
            cp1 -= 0.75f * vel * sin(conv_rad(theta - 90.0f));
        }
        else if (theta > 180.0f && theta < 270.0f) {
            cp2 += 0.75f * vel * sin(conv_rad(theta - 180.0f));
            cp1 -= 0.75f * vel * cos(conv_rad(theta - 180.0f));
        }
        else if (theta > 270.0f && theta < 360.0f) {
            cp2 += 0.75f * vel * cos(conv_rad(theta - 270.0f));
            cp1 += 0.75f * vel * sin(conv_rad(theta - 270.0f));
        }
    }
    
}
void pedal_off_slow_down(bool pressed1, bool pressed2, 
						 float & vel, float & cp1, float & cp2, float theta)
{
	if (!pressed1 && !pressed2 && vel > 0) {
		vel -= 0.07f;
		if (theta == 0.0f)
			cp1 -= vel;
		else if (theta == 90.0f)
			cp2 += vel;
		else if (theta == 180.0f)
			cp1 += vel;
		else if (theta == 270.0f)
			cp2 -= vel;
		else if (theta == 360.0f)
			cp1 -= vel;
		else {
			if (theta < 90.0f) {
				cp1 -= 0.75f * vel * cos(conv_rad(theta));
				cp2 += 0.75f * vel * sin(conv_rad(theta));
			}
			else if (theta > 90.0f && theta < 180.0f) {
				cp2 += 0.75f * vel * cos(conv_rad(theta - 90.0f));
				cp1 += 0.75f * vel * sin(conv_rad(theta - 90.0f));
			}
			else if (theta > 180.0f && theta < 270.0f) {
				cp2 -= 0.75f * vel * sin(conv_rad(theta - 180.0f));
				cp1 += 0.75f * vel * cos(conv_rad(theta - 180.0f));
			}
			else if (theta > 270.0f && theta < 360.0f) {
				cp2 -= 0.75f * vel * cos(conv_rad(theta - 270.0f));
				cp1 -= 0.75f * vel * sin(conv_rad(theta - 270.0f));
			}
		}
		if (vel < 0.0f)
			vel = 0.0f;
	}
	else if (!pressed1 && !pressed2 && vel < 0) {
		vel += 0.07f;
		if (theta == 0.0f)
			cp1 -= vel;
		else if (theta == 90.0f)
			cp2 += vel;
		else if (theta == 180.0f)
			cp1 += vel;
		else if (theta == 270.0f)
			cp2 -= vel;
		else if (theta == 360.0f)
			cp1 -= vel;
		else {
			if (theta < 90.0f) {
				cp1 -= 0.75f * vel * cos(conv_rad(theta));
				cp2 += 0.75f * vel * sin(conv_rad(theta));
			}
			else if (theta > 90.0f && theta < 180.0f) {
				cp2 += 0.75f * vel * cos(conv_rad(theta - 90.0f));
				cp1 += 0.75f * vel * sin(conv_rad(theta - 90.0f));
			}
			else if (theta > 180.0f && theta < 270.0f) {
				cp2 -= 0.75f * vel * sin(conv_rad(theta - 180.0f));
				cp1 += 0.75f * vel * cos(conv_rad(theta - 180.0f));
			}
			else if (theta > 270.0f && theta < 360.0f) {
				cp2 -= 0.75f * vel * cos(conv_rad(theta - 270.0f));
				cp1 -= 0.75f * vel * sin(conv_rad(theta - 270.0f));
			}
		}
		if (vel > 0.0f)
			vel = 0.0f;
	}
}

void shift_left(float & theta)
{
    // modify camera angle
    theta = theta - 5.0f;
}

void shift_right(float & theta)
{
    //modify camera position
    theta = theta + 5.0f;
}

float conv_rad(float deg)
{
    return deg * RAD_CONV;
}

// will set the state of whether or not the game is over
bool isOver(float velocity)
{
    bool isItOver = false;

    if (velocity > -10.0f)
    	isItOver = true;

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

//constructs the text used for the game over screen.
void text_rect(Rect & rec, int bot, int left, int center, const char string[])
{
    //sets appropriate dimensions
    rec.bot = bot;
    rec.left = left;
    rec.center = center;
    ggprint16(&rec, 16, 0x00ffff00, string);
}

//this will display the game over screen when the correct conditions are met;
//the function will call both the build_rectangle() and text_rect() functions
//in order to convey information to the game player
void render_the_game_over(bool won, bool done, int xr, int yr) {
    //glClear(GL_COLOR_BUFFER_BIT);
    //game over messages
    //int xcent = xr / 2;
    //int ycent = yr / 2;
    int w = 200;
 
    int h = 200;

    //for the text that will show up on screen
    Rect r1;
    Rect r2;

    //prints the game over message
    if (!won && done) {
        text_rect(r1, 825.0f, 1240.0f, 0, "GAME OVER!");
        text_rect(r2, 775.0f, 1180.0f, 0, "Press any key to continue");
        //builds the background for the game over screen
        build_rectangle(w, h, 0.0f, 1290.0f, 800.0f, 0, 225, 0);
    }
}

//how will this be implemented with feature mode?
void render_game_mode_title(bool isModeOn, int xr, int yr)
{
	Rect rRM;
	
	if (isModeOn)
		text_rect(rRM, 80, 1230, 0, "RACE MODE");

}
float get_init_pos(float position)
{
	return position;
}
void race_mode(int & ctdn, int & frames, float init_pos, float position,
			   bool & sec0, bool & sec1, bool & sec2, bool & sec3, 
			   bool & sec4, bool & sec5, bool & won, bool & done,
               int xr, int yr)
{
	frames = frames + 1;
	if (frames <= 60 && !sec0)
		sec0 = true;
	else if (frames > 60 && frames <= 120 && !sec1) {
		--ctdn;
		sec1 = true;
	} else if (frames > 120 && frames <= 180 && !sec2) {
		--ctdn;
		sec2 = true;
	} else if (frames > 180 && frames <= 240 && !sec3) {
		--ctdn;
		sec3 = true;
	} else if (frames > 240 && frames <= 300 && !sec4) {
		--ctdn;
		sec4 = true;
	} else if (frames > 300 && frames <= 360 && !sec5) {
		--ctdn;
		sec5 = true;
	}
	
    if (position <= init_pos - 500.0f) {
        won = true;
        done = true;
    }
    if (ctdn == 0 && position > init_pos - 500.0f) {
        won = false;
        done = true;
    }
    
}
void display_rm_options(bool isModeOn, bool rTestOn)
{
	Rect optionR;
	Rect optionS;
	
	if (!isModeOn && !rTestOn) {
		text_rect(optionR, 80.0f, 1180.0f, 0, 
				  "Press R for Race Mode!");
		text_rect(optionS, 20.0f, 1180.0f, 0, 
				  "Press f to Test Rotation");			  
	}
}
//======================================================================
//FEATURE MODE IS HERE
//======================================================================
//Moves anchor box according to angular value.
//TODO: New revision to feature mode
//Implement mechanism that will render a shape in front of player.
//This will face the car at the specified angle.


void rotation_test_mode(bool rTestOn, float cp0, float cp2,
						float & ap0, float & ap2, float theta)
{
	theta = (int)theta % 360;
	if (theta < 0)
		theta = theta + 360;
	
	cout << theta << endl;
	
	if (rTestOn) {
		if (theta == 0.0f)
			ap2 = cp2 - 10.0f;
		else if (theta == 90.0f)
			ap0 = cp0 + 10.0f;
		else if (theta == 180.0f)
			ap2 = cp2 + 10.0f;
		else if (theta == 270.0f)
			ap0 = cp0 - 10.0f;
		else if (theta == 360.0f)
			ap2 = cp2 - 10.0f;
		else {
			if (theta < 90.0f) {
				ap2 = cp2 - 10.0f * cos(conv_rad(theta));
				ap0 = cp0 + 10.0f * sin(conv_rad(theta));
			}
			else if (theta > 90.0f && theta < 180.0f) {
				ap2 = cp2 + 10.0f * cos(conv_rad(theta - 90.0f));
				ap0 = cp0 + 10.0f * sin(conv_rad(theta - 90.0f));
				
			}
			else if (theta > 180.0f && theta < 270.0f) {
				ap2 = cp2 + 10.0f * cos(conv_rad(theta - 180.0f));
				ap0 = cp0 - 10.0f * sin(conv_rad(theta - 180.0f));
				
			}
			else if (theta > 270.0f && theta < 360.0f) {
				ap2 = cp2 - 10.0f * sin(conv_rad(theta - 270.0f));
				ap0 = cp0 - 10.0f * cos(conv_rad(theta - 270.0f));	
			}
		}
	}
}
//Displays when rotation test mode is on.
void display_rotation_text(bool rTestOn)
{
	Rect displayR;
	
	if (rTestOn) {
		text_rect(displayR, 80, 1230, 0, "ROTATION TEST MODE");
	}
}
//Guide for determining the direction the car faces.
void rot_instructions(bool rTestOn)
{
	Rect insR1;
	Rect insR2;
	Rect insR3;
	
	if (rTestOn) {
		text_rect(insR1, 1200, 900, 0, "The angle will signify");
		text_rect(insR2, 1100, 900, 0, "what direction the car is facing.");
		text_rect(insR3, 1000, 900, 0, "0 degrees will make car face forward.");
	}
}
//Theta value will be displayed; helps tester know what direction the car
//object is facing.
void display_theta(bool rTestOn, float theta)
{
	Rect thetaR1;
	Rect thetaR2;
	
	if (rTestOn) {
		text_rect_2(thetaR1, 1200, 100, 0, "%i", theta);
		text_rect(thetaR2, 1200, 200, 0, "degrees");
	}
}
void text_rect_2(Rect & rec, int bot, int left, int center, const char string[],
                 float value)
{
    //sets appropriate dimensions
    rec.bot = bot;
    rec.left = left;
    rec.center = center;
    ggprint16(&rec, 16, 0x00ffff00, string, value);
}
//======================================================================
//END OF FEATURE MODE
//======================================================================
void display_countdown(bool isModeOn, int ctdn)
{
	Rect rCD;
	
    if (isModeOn)
    {
        switch (ctdn) {
            case 5:
                text_rect(rCD, 1000, 1230, 0, "5");
                break;
            case 4:
                text_rect(rCD, 1000, 1230, 0, "4");
                break;
            case 3:
                // cout << "This case ran" << endl;
                text_rect(rCD, 1000, 1230, 0, "3");
                break;
            case 2:
                text_rect(rCD, 1000, 1230, 0, "2");
                break;
            case 1:
                text_rect(rCD, 1000, 1230, 0, "1");
                break;
                
        }
    }
}
void go_go_go(bool isModeOn, float init_pos, float position)
{
	Rect r4;
	
	if (isModeOn && position > init_pos - 500.0f)
		 text_rect(r4, 1200, 1200, 0, "GO GO GO!!!!!");
	
}
void you_win(bool won, int xr, int yr)
{
    if (won)
    {
        Rect r3;
        text_rect(r3, 700, 1230, 0, "YOU WIN!!!!!");
    }
	
}
void show_name_jr3()
{
    std::cout << "Jarl Ramos / Geoffrey De Palme" << std::endl;
}

