#include <SDL2/SDL.h>
#include <stdbool.h>
#include <stdint.h>
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
