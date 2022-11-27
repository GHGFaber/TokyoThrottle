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
#ifdef USE_OPENAL_SOUND
#include </usr/include/AL/alut.h>
#endif //USE_OPENAL_SOUND

using namespace std;
float red = 0.0f;
float green = 0.0f;
float blue = 0.0f;

ALuint alBufferDrip, alBufferTick;
ALuint alSourceDrip, alSourceTick;


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

void initSound()
{
        #ifdef USE_OPENAL_SOUND
        alutInit(0, NULL);
        if (alGetError() != AL_NO_ERROR) {
                printf("ERROR: alutInit()\n");
                return;
        }
        //Clear error state.
        alGetError();
        //g.background3 = &img[3];
        //Setup the listener.
        //Forward and up vectors are used.
        float vec[6] = {0.0f,0.0f,1.0f, 0.0f,1.0f,0.0f};
        alListener3f(AL_POSITION, 0.0f, 0.0f, 0.0f);
        alListenerfv(AL_ORIENTATION, vec);
        alListenerf(AL_GAIN, 1.0f);
        //
        //Buffer holds the sound information.
        alBufferDrip = alutCreateBufferFromFile("tokyo.wav");
        alBufferTick = alutCreateBufferFromFile("select.wav");
        //
        //Source refers to the sound.
        //Generate a source, and store it in a buffer.
        alGenSources(1, &alSourceDrip);
        alSourcei(alSourceDrip, AL_BUFFER, alBufferDrip);
        //Set volume and pitch to normal, no looping of sound.
        alSourcef(alSourceDrip, AL_GAIN, 1.0f);
        alSourcef(alSourceDrip, AL_PITCH, 1.0f);
        alSourcei(alSourceDrip, AL_LOOPING, AL_FALSE);
        if (alGetError() != AL_NO_ERROR) {
                printf("ERROR: setting source\n");
                return;
        }
        //Generate a source, and store it in a buffer.
        alGenSources(1, &alSourceTick);
        alSourcei(alSourceTick, AL_BUFFER, alBufferTick);
        //Set volume and pitch to normal, no looping of sound.
        alSourcef(alSourceTick, AL_GAIN, 1.0f);
        alSourcef(alSourceTick, AL_PITCH, 1.0f);
        alSourcei(alSourceTick, AL_LOOPING, AL_FALSE);
        if (alGetError() != AL_NO_ERROR) {
                printf("ERROR: setting source\n");
                return;
        }
        #endif //USE_OPENAL_SOUND
}

void cleanupSound()
{
        #ifdef USE_OPENAL_SOUND
        //First delete the source.
        alDeleteSources(1, &alSourceDrip);
        alDeleteSources(1, &alSourceTick);
        //Delete the buffer.
        alDeleteBuffers(1, &alBufferDrip);
        alDeleteBuffers(1, &alBufferTick);
        //Close out OpenAL itself.
        //Get active context.
        ALCcontext *Context = alcGetCurrentContext();
        //Get device for active context.
        ALCdevice *Device = alcGetContextsDevice(Context);
        //Disable context.
        alcMakeContextCurrent(NULL);
        //Release context(s).
        alcDestroyContext(Context);
        //Close device.
        alcCloseDevice(Device);
        #endif //USE_OPENAL_SOUND
}

void playSound(ALuint source)
{
        #ifdef USE_OPENAL_SOUND
        alSourcePlay(source);
        #endif
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