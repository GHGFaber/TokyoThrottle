//Author: Moises B. Fuentes
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <GL/gl.h>
#include <GL/glx.h>
#include <GL/glu.h>
#include "mfuentes.h"

using namespace std;
float red = 0.0f;
float green = 0.0f;
float blue = 0.0f;

void show_name(){
    cout << "Moises Fuentes:";
}

bool credits(bool pressed)
{
    pressed = true;
	return pressed;
}

bool rmcredits(bool pressed)
{
    pressed = false;
	return pressed;
}

bool startMenu(bool pressed)
{
    pressed = true;
    return pressed; 
}

void switchColor()
{
    //glColor3f(red, green, blue);
    glColor3f(red, green, blue);
}


/*extern class MyImage myimage;

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
}
*/