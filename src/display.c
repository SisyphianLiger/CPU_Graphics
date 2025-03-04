#include <SDL2/SDL.h>
#include <stdbool.h>
#include "display.h"

SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;
uint32_t* color_buffer = NULL;
SDL_Texture * color_buffer_texture = NULL; 


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
	for (int y = 0; y < HEIGHT; y++) {
		for(int x = 0; x < WIDTH; x++) {
			color_buffer[(WIDTH * y) + x] = color;
		}
	}
}
void draw_grid(void) {
	for (int y = 0; y < HEIGHT; y++) {
		for(int x = 0; x < WIDTH; x++) {
			// We need to check if width * y + x % 10
			uint32_t val = (WIDTH * y) + x;
			if (val % 10 == 0 || y % 10 == 0) {
				color_buffer[val] =  0x000000FF;
			} 
		}
	}
}

void draw_square(int x, int y, int height, int width, uint32_t color) {

	// if ((y + height) > HEIGHT) {
	// 	fprintf(stderr, "Square height is to large to draw\n");
	// 	return;
	// }
	//
	// if ((x + width) > WIDTH) {
	// 	fprintf(stderr, "Square width is to large to draw\n");
	// 	return;
	// }

	// Calculate y if y is 0 --> 800
	// y is 50 800 - 50 = 750  50 downwards
	// Cacluate x if x is 0 --> 800
	// x is 100 800 - 100 700 --> 100 to the right
	for (int row = 0; row < width; row++) {
		for(int col = 0; col < height; col++) {
			int current_x = x + row;
			int current_y = y + col;
			color_buffer[(WIDTH * current_y) + current_x] =  color;
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
		WIDTH * (sizeof (uint32_t))
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
