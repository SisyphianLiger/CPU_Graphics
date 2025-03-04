#include "display.h"
#include "vector.h"

bool is_running = false;

void setup(void) {
	color_buffer = (uint32_t*) malloc(sizeof(uint32_t) * window_width * window_height);

	if (!color_buffer) {
		fprintf(stderr, "Error Creating the Color Buffer\n");
		return;
	}

	/*
	 * Creating SDL Texture to display color buffer
	 * What is the Renderer to manage the texture
	 * What is the Pixel Format? Colors sending 
	 * We are going frame by frame continously streaming
	 * Width and Height
	 */
	color_buffer_texture = SDL_CreateTexture(
		renderer,
		SDL_PIXELFORMAT_ARGB8888,
		SDL_TEXTUREACCESS_STREAMING,
		window_width,
		window_height
	);
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

void update(void) {
	// TODO:
}


void render(void) {
	SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
	SDL_RenderClear(renderer);
	
	// Draw here
	draw_grid();
	draw_square(50, 50, 100, 100, 0x0000FFFF);

	// Render here
	render_color_buffer();

	// Clear here
	clear_color_buffer(0xFF000000); // Black 
	
	SDL_RenderPresent(renderer);
}


int main(void) {

	/* Create an SDL window */
	is_running = initialize_window();

	setup();	

	vec3_t myvec = { 2.0, 3.0, -4.0};

	while(is_running) {
		process_input();
		update();
		render();
	}
	
	destroy();
	return 0;
}

