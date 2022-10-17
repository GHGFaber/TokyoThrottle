#ifndef IMAGE_H
#define IMAGE_H
extern void accelerate(float & velocity);
extern void decelerate(float & velocity);
extern void go_forwards(float & vel, float & cp1, float & cp2, float theta);
extern void go_backwards(float & vel, float & cp1, float & cp2, float theta);
extern void shift_left(float & theta);
extern void shift_right(float & theta);
extern float conv_rad(float deg);
extern bool isOver(float velocity);
//extern void text_rect(Rect & rec, int bot, int left, int center, const char string[]);
extern void render_the_game_over(int xr, int yr);
extern void render_game_mode_title(bool flag, int xr, int yr);
extern float get_init_pos(float position);
extern void race_mode(int & ctdn, int & frames, float init_pos, float position,
                      bool & sec0, bool & sec1, bool & sec2, bool & sec3,
                      bool & sec4, bool & sec5, bool & won, int xr, int yr);
extern void go_go_go(bool flag, float init_pos, float position);
extern void you_win(int xr, int yr);
extern void you_lose(int xr, int yr);
#endif
