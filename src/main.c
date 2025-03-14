#include "SDL2/SDL_timer.h"
#include "display.h"
#include "triangle.h"
#include "vector.h"
#include "mesh.h"


triangle_t triangles_to_render[N_MESH_FACES];
vec3_t camera_position = { .x = 0.0, .y = 0.0, .z = -5.0 };
vec3_t cube_rotation = {.x = 0.0, .y = 0.0, .z = 0.0 };
float fov_factor = 640.0;

bool is_running = false;
int previous_frame_time = 0;

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

/**
 * We do Orthographic
 */ 
vec2_t project(vec3_t point) {
	vec2_t projected_pnt = {
		.x = (fov_factor * point.x) / point.z,
		.y = (fov_factor * point.y) / point.z,
	};

	return projected_pnt;
}

void update(void) {
	
	// Time Buffer to enforce 30 FPS
	
	// How Many Milli seconds to slepp until to resume process
	// time_to_wait take the Frame Target (30 FPS) - current ticks
	int time_to_wait = FRAME_TARGET_TIME - (SDL_GetTicks() - previous_frame_time);
	
	// If the time is too fast then we wait
	if (time_to_wait > 0 && time_to_wait <= FRAME_TARGET_TIME) {
		SDL_Delay(time_to_wait);
	}

	
	// How many milliseconds have pased
	previous_frame_time = SDL_GetTicks();


	cube_rotation.x += 0.01;
	cube_rotation.y += 0.01;
	cube_rotation.z += 0.01;

	// Loops Over all triangle Faces of Cube Mesh
	for (int i = 0; i < N_MESH_FACES; i++) {
		face_t mesh_face = mesh_faces[i];
		vec3_t face_vertices[3]; 


		face_vertices[0] = mesh_vertices[mesh_face.a - 1];
		face_vertices[1] = mesh_vertices[mesh_face.b - 1];
		face_vertices[2] = mesh_vertices[mesh_face.c - 1];
		
		triangle_t projected_triangle;
		for (int j = 0; j < 3; j++) {
			vec3_t transform_vertex = face_vertices[j];
			transform_vertex = vec3_rotate_y(transform_vertex, cube_rotation.x);
			transform_vertex = vec3_rotate_x(transform_vertex, cube_rotation.y);
			transform_vertex = vec3_rotate_z(transform_vertex, cube_rotation.z);

			// Translate the vertex away from camera
			transform_vertex.z -= camera_position.z;
			

			// Project it into the current vertex plane
			vec2_t projected_point = project(transform_vertex);

			// Scale and project points to middle of screen
			projected_point.x += (window_width / 2);
			projected_point.y += (window_height / 2);

			projected_triangle.points[j] = projected_point;
		
		}
		// Saving new projected triangle to array of triangles to render
		triangles_to_render[i] = projected_triangle;
		
	
	}

}


void render(void) {
	
	draw_grid();


	// PINK #FFC0CB

	for (int i = 0; i < N_MESH_FACES; i++) {
		triangle_t triangle = triangles_to_render[i];

		// Draw the 3 vertices
		draw_rect(triangle.points[0].x, triangle.points[0].y, 3, 3, 0xFFFFC0CB);
		draw_rect(triangle.points[1].x, triangle.points[1].y, 3, 3, 0xFFFFC0CB);
		draw_rect(triangle.points[2].x, triangle.points[2].y, 3, 3, 0xFFFFC0CB);

		draw_triangle(	
				triangle.points[0].x, 
				triangle.points[0].y,
				triangle.points[1].x,
				triangle.points[1].y,
				triangle.points[2].x,
				triangle.points[2].y,
				0xFFFFC0CB
		);
				
	}
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

	// how can we waste time
	while(is_running) {
		process_input();
		update();
		render();
	}
	
	destroy();
	return 0;
}

