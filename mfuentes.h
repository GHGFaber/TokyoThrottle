//Modified by: Moises B. Fuentes
/*
#ifndef _MYIMAGE_H_
#define _MYIMAGE_H_
class MyImage {
public:
    int width, height;
    unsigned char *data;
    ~MyImage(); //destructor
    MyImage(const char *fname);
};
#endif
*/

extern float red;
extern float green;
extern float blue;

extern bool credits(bool pressed);
extern bool rmcredits(bool pressed);
extern bool startMenu(bool pressed);
extern void switchColor();