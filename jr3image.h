#ifndef IMAGE_H
#define IMAGE_H

class MyImage {
public:
	int width, height;
	unsigned char *data;
	~MyImage(); //destructor
	MyImage(const char *fname);
};

#endif
