#ifndef IMAGE_H
#define IMAGE_H
/*
class MyImage {
public:
	int width, height;
	unsigned char *data;
	~MyImage(); //destructor
	MyImage(const char *fname);
};

extern void show_game_over(int xr, int yr, float position);
*/

extern bool isOver(float velocity);
//extern bool challenge_mode(float position);
//extern void render_the_game_over(int xr, int yr);
//extern void text_rect(Rect & rec, int bot, int left, int center, const char string[]);
extern void render_the_game_over(int xr, int yr, bool flag);
extern void render_game_mode_title(bool flag, int xr, int yr);
extern float get_init_pos(float position);
extern void race_mode(int frames, float init_pos, float position, bool & won);
extern void you_win(bool flag, int xr, int yr);
extern void you_lose(bool flag, int xr, int yr);


#endif
