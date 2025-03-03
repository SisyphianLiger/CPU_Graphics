#include "SDL2/SDL_events.h"
#include "SDL2/SDL_keycode.h"
#include "SDL2/SDL_pixels.h"
#include "SDL2/SDL_render.h"
#include "SDL2/SDL_video.h"
#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <sys/syslimits.h>


// SDL Window
SDL_Window* window = NULL;

// SDL Renderer
SDL_Renderer* renderer = NULL;

// SDL Texture
SDL_Texture * color_buffer_texture = NULL;

bool is_running = false;

// Color Buffer
uint32_t* color_buffer = NULL;

// Screen Size
#define WIDTH 800
#define HEIGHT 600


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
	//  Create SDL Window
	window = SDL_CreateWindow(
			NULL,
			SDL_WINDOWPOS_CENTERED,
			SDL_WINDOWPOS_CENTERED,
			WIDTH,
			HEIGHT,
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


void setup(void) {
	color_buffer = (uint32_t*) malloc(sizeof(uint32_t) * WIDTH * HEIGHT);

	if (!color_buffer) {
		fprintf(stderr, "Error Creating the Color Buffer\n");
		return;
	}

	/*
	 * Creating SDL Texture to display color buffer
	 *
	 * What is the Renderer to manage the texture
	 * What is the Pixel Format? Colors sending 
	 * We are going frame by frame continously streaming
	 * Width and Height
	 */
	color_buffer_texture = SDL_CreateTexture(
		renderer,
		SDL_PIXELFORMAT_ARGB8888,
		SDL_TEXTUREACCESS_STREAMING,
		WIDTH,
		HEIGHT
	);
}

void update(void) {
	// TODO:
}

void clear_color_buffer(uint32_t color) {
	for (int y = 0; y < HEIGHT; y++) {
		for(int x = 0; x < WIDTH; x++) {
			color_buffer[(WIDTH * y) + x] = color;
		}
	}
}

/*
 * Processes Input Commands by first creating a event struct and then receives what that event
 * struct has recieved by polling the event. PollEvent is a way to recieve system inputs
 * */
void process_input(void) {
	SDL_Event event;
	SDL_PollEvent(&event);
	switch (event.type) {
		case SDL_QUIT:
			is_running = false;
			break;
		case SDL_KEYDOWN:
			if (event.key.keysym.sym == SDLK_ESCAPE)
			is_running = false;
			break;
	}
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

void render(void) {
	SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
	SDL_RenderClear(renderer);
	render_color_buffer();
	clear_color_buffer(0xFFFFFF00); // Yellowish Color
	SDL_RenderPresent(renderer);
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

int main(void) {

	/* Create an SDL window */
	is_running = initialize_window();

	setup();	

	while(is_running) {
		process_input();
		update();
		render();
	}
	
	destroy();
	return 0;
}
