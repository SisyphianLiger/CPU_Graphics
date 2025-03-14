#include <SDL2/SDL.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include "display.h"

SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;
uint32_t* color_buffer = NULL;
SDL_Texture * color_buffer_texture = NULL; 
int window_height = 800;
int window_width = 600;

/*
 * This is the initialize function
 * It uses SDL_Init, SDL_CreateWindow(), SDL_Renderer
 * This is the process SDL uses to request a window from the 
 * operating system
 *
 * */
bool initialize_window(void) {
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		fprintf(stderr, "Error initializing SDL.\n");
		return false;
	}

	// We Query SDL for full screen
	SDL_DisplayMode display_mode;
	if (SDL_GetCurrentDisplayMode(0, &display_mode) != 0) {
		fprintf(stderr, "Could Not Get Diplay Information");
		return false;
	}

	// This is Actually Fake Full Screen
	// display_mode.w,
	// display_mode.h,
	
	// This Function sets the screen to fullscreen
	SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN);

	//  Create SDL Window
	window = SDL_CreateWindow(
			NULL,
			SDL_WINDOWPOS_CENTERED,
			SDL_WINDOWPOS_CENTERED,
			display_mode.w,
			display_mode.h,
			SDL_WINDOW_BORDERLESS);
	if (!window) {
		fprintf(stderr, "Error Creating SDL Window\n");
		return false;
	}

	//  CREATE SDL Renderer
	renderer = SDL_CreateRenderer(window, -1, 0);
	if (!renderer) {
		fprintf(stderr, "Error Creating SDL Renderer\n");
		return false;
	}

	return true;
}

void clear_color_buffer(uint32_t color) {
	for (int y = 0; y < window_height; y++) {
		for(int x = 0; x < window_width; x++) {
			color_buffer[(window_width * y) + x] = color;
		}
	}
}
void draw_grid(void) {
    for (int y = 0; y < window_height; y += 10) {
        for (int x = 0; x < window_width; x += 10) {
            color_buffer[(window_width * y) + x] = 0xFF444444;
        }
    }
}


void draw_pixel(int x, int y, uint32_t color) {
	if (x >= 0 && x < window_width && y >= 0 && y < window_height) 
		color_buffer[window_width * y + x] = color;
}

void draw_rect(int x, int y, int height, int width, uint32_t color) {

	// We iterate on the specific row that y starts, width * y + x and begin
	// to color
	// if y == 5 and window_width == 100 then y == 500 and the x value 

	for (int row = 0; row < width; row++) {
		for(int col = 0; col < height; col++) {
			int current_x = x + row;
			int current_y = y + col;
			draw_pixel(current_x, current_y, color);
		}
	}
}


void draw_right_triangle(int x, int y, int base, int height, uint32_t color) {
	
	//  We need to iterate like before but increment only when a pixel i

}


void render_color_buffer(void) {
	SDL_UpdateTexture(
		color_buffer_texture,
		NULL, 
		color_buffer, 
		window_width * (sizeof (uint32_t))
	);

	SDL_RenderCopy(
		renderer, 
		color_buffer_texture, 
		NULL,
		NULL
	);
}

/* 
 * Making sure here we free all memory we have used,
 * for malloced functions we use free, but for SDL there are specific 
 * functions to remove their memory
 */
void destroy(void) {
	free(color_buffer);

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}



/*
 * Take the Delta x and y and increment
 * It takes side length (the longest side) to produce the ratio needed to increment
 * Using the draw_pixel function it places a color on the pixel map based on integer value
 */

void draw_line(int x0, int y0, int x1, int y1, uint32_t color) {
	
	int delta_x = (x1 - x0);
	int delta_y = (y1 - y0);

	// Here we calculate how much we need to run, we use abs() because we don't want negatives
	int side_length = abs(delta_x)  >= abs(delta_y) ? abs(delta_x) : abs(delta_y);

	// Find how much both x and y need each step
	float x_inc = delta_x / (float) side_length;
	float y_inc = delta_y / (float) side_length;

	// We store a variable 
	float current_x = x0;	
	float current_y = y0;	

	for(int i = 0; i < side_length; i++) {
		draw_pixel(round(current_x), round(current_y), color);
		current_x += x_inc;
		current_y += y_inc;
	}

}

void swap(int * num0, int * num1) {
	int * temp = num0;
	*num0 = *num1;
	*num1 = *temp;
}

void draw_horizontal_line(int x0, int  y0, int x1, int y1, uint32_t color) {
	if (x0 > x1) {
		swap(&x0, &x1);
		swap(&y0, &y1);
	}

	int delta_x = (x1 - x0);
	int delta_y = (y1 - y0);

	int direction = delta_y < 0 ? -1 : 1;
	delta_y *= direction;

	int y = y0;
	int pixel_movement = 2*delta_y - delta_x;

	for (int i = 0; i < delta_x + 1; i++) {
		draw_pixel(x0 + i, y, color);
		if (pixel_movement >= 0) {
			y += direction;
			pixel_movement = pixel_movement - 2*delta_x;
		}
		pixel_movement = pixel_movement + 2*delta_y;
	}

}

void draw_vertical_line(int x0, int  y0, int x1, int y1, uint32_t color) {

	if (y0 > y1) {
		swap(&x0, &x1);
		swap(&y0, &y1);
	}

	int delta_x = (x1 - x0);
	int delta_y = (y1 - y0);

	int direction = delta_x < 0 ? -1 : 1;
	delta_x *= direction;

	int x = x0;
	int pixel_movement = 2*delta_x - delta_y;

	for (int i = 0; i < delta_y + 1; i++) {
		draw_pixel(x, y0 + i, color);
		if (pixel_movement >= 0) {
			x += direction;
			pixel_movement = pixel_movement - 2*delta_y;
		}
		pixel_movement = pixel_movement + 2*delta_x;
	}
}

void draw_bres_line(int x0, int y0, int x1, int y1, uint32_t color){
	if (abs(x1-x0) > abs(y1-y0)) 
		draw_horizontal_line(x0,  y0, x1, y1, color);
	else 
		draw_vertical_line(x0,  y0, x1, y1, color);
	
}


void draw_triangle(int x0, int y0,int x1, int y1,int x2, int y2, uint32_t  color) {
	draw_bres_line(x0, y0, x1,  y1, color);
	draw_bres_line(x1, y1, x2,  y2, color);
	draw_bres_line(x2, y2, x0,  y0, color);
}
