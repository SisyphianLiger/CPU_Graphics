#ifndef DISPLAY_H
#define DISPLAY_H

#include <stdbool.h>
#include <SDL2/SDL.h>
#include <stdbool.h>
#include <stdint.h>

extern SDL_Window* window;
extern SDL_Renderer* renderer;
extern uint32_t* color_buffer;
extern SDL_Texture * color_buffer_texture; 

// Screen Size
#define WIDTH 800
#define HEIGHT 600

bool initialize_window(void);
void destroy(void);
void render_color_buffer(void);
void draw_right_triangle(int x, int y, int base, int height, uint32_t color);
void clear_color_buffer(uint32_t color); 
void draw_grid(void); 
void draw_square(int x, int y, int height, int width, uint32_t color);

#endif
