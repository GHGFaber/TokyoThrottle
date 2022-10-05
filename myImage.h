//Modified by: Moises B. Fuentes
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
