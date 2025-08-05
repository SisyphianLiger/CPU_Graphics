#ifndef MESH_H
#define MESH_H

#include "triangle.h"
#include "vector.h"

#define N_CUBE_VERTICES 8
extern vec3_t cube_vertices[N_CUBE_VERTICES];

// mesh faces 6 * 2 triangles per face
#define N_CUBE_FACES (6 * 2)
extern face_t cube_faces[N_CUBE_FACES];

// Defines struct for dynamic sized meshes with array of vertices/faces
typedef struct {
  vec3_t *vertices;     // dynamic array for vertices
  face_t *faces;        // dynamic array for faces
  vec3_t mesh_rotation; // rotation with x,y,z values
} mesh_t;

extern mesh_t mesh;

void load_cube_mesh_data(void);
void print_all_data(void);
#endif
