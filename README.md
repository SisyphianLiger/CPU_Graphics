# Dependencies
## SDL
    - We need to draw Pixels
    - SDL allows us to open a display at particular color
    - Simple Task but modern computers with OS are not that simple
    - We use SDL to avoid how the OS's api's work 


## Idea
                C
                |   
               SDL
             /  |  \
          Mac Linux Windows

## Compiler for MacOS
    1. Insall with brew
    - sdl2 

## Concept of a GameLoop
    - Having Frames being displayed

```javascript
        setup()
        while (TRUE){
            process_input();
            update();
            render();
        }
```

    - For each frame we process input
    - We update the postions of game objects etc
    - Then we render the function (draw the window)

## Color Buffer -> Pixel Buffer
    - When we look at a screen, we have a an array of 3 colors
    - RGB or combinations of them
    - We allocate a space in memory that is a series of numbers
        [ [R,G,B],[R,G,B],[R,G,B],[R,G,B],[R,G,B] ]
        [ [R,G,B],[R,G,B],[R,G,B],[R,G,B],[R,G,B] ]
        [ [R,G,B],[R,G,B],[R,G,B],[R,G,B],[R,G,B] ]
        [ [R,G,B],[R,G,B],[R,G,B],[R,G,B],[R,G,B] ]
    
    - 0xFFFF0000 <-- How do we know this is Red?
          A  R  G  B
    - 0x  FF FF 00 00
        A: Alpha or transparency
        R: Red Color
        G: Green Color
        B: Blue Color

    Range 00 --> FF (0 -> 256)

### Fixed-Size Types
    - Representing Colors needs a fixed set of bits
    - uint8_t for example

### ColorBuffor DS
    - uint32_t* color_buffer <-- So we can have a uint32_t ptr
    - ptr to address in memory where every element there is a element that is 32 bits
    - Width x Height == How many elements I need to allocate in memory

```C
    // Declare the array of uint32 elements
    uint32_t* color_buffer = NULL;

    void setup(void)	{
        // Allocate teh required bytes in memory for color buffer 
        color_buffer = (uint32_t*) malloc(sizeof(uint32_t) * window_width * window_height);
        // Set the array with pixels
        color_buffer[0] = 0xFFFF0000;

        // This will navigate the colorbuffer, we start by row then column
        color_buffer[(window_width * 10) + 20] = 0xFFFF0000;
    }


```

*** Note ***

Colorbuffer can also be referred to as a frame-buffer but are the same thing.


## Rastor 
The Mesh we use to set up the window is called a Rastor, which is pretty great and yellow in our case :)

# Excercise Time!!

1. Create a function called draw_grid():
    - renders a background grid that shows a line every row or column of pixels 
    - Lines are multiples of 10
    - Basically Grids
    - Called in render function()

# Points and Vectors

Now we add a Z coordinate!

## 1: Vectors
    - Vectors x,y,z
    - Vectors: intuitively as arrows
    - Direction is very important
    - What is the magnitude of the vector (strength) and where is it pointing

    1. Scalar Quantities
        - Only a single number (scalar) 
        - Examples: Temperature, Area, Length, Pressure

    2. Vector Quantities
        - Multiple parameters
        - Velocity
        - Acceleration
        - Force
        - List
        - Drag
        - Displacement

    3. Why are these quantities about 3D?
        - With 3D we have an x and a y and a z
                        z
                        |
                        |
                        |______ y
                       /
                      /
                     /
                    x
        - Now there is three points 
            - (3.0, 0.0, 3.0)
        
        - Computer Programmers with 3D objects, we call points as vectors
        - x,y --> we can think of as a vector, meaning we can make a triangle 
        - Vectors will determine points in the plane
        - A Cube has vertices or we can think of a cube as a set of vectors
        - A 2D vectors has 2 Components (6.0, 2.0)
        - A 3D vectors has 3 Components (6.0, 2.0, 8.0)

        - We need to make a struct for these

        ```C
        typedef struct {
            float x;
            float y;
        } vec2_t;

        // initialized with 
        vec2_t p0 = { 0.0, 2.0 };
        ``` 
        - This vec2_t represends a 2D type

        
### Projection
        - Having a 3D idea that gets projected on a 2d plane
        - In Ortographic Projection we ignore the screen 
#### Perspective Projection
        - frustum, the idea of the view from a human pov on a 2d screen
        - We now use the z length (depth) to move the items to in the back
        - Projection Plane - The Screen
        - Eye Point - Where we view it
        - Point -> Frustum needs to maintain a new point from where the 
        
        - How Can we calculate x --> P to P1 of X
        - Monitor is a top view of display 
        - We can deduce the Px with P and Pz so now we need to fine P1
        - We can solve p1 by using the same logic of the bigger triangle

        - Similar Triangles: the triangles that are the same shap but scaled up/down
        - Property is:
                    BC   AB
                    -- = --
                    DE   AD
        -        Px
           P`x = --
                 Pz

        -        Py
           P`y = --
                 Pz
    
        - These two formulas are called Perspective Divide
        - The Bigger the z the smaller the display


### Coordinate System Handedness
    - Z values get larger and lager the further away you look
    - This is not neccesarily always the case, can be that z values increase towards the user
    - Left Hand Coordinate system -> z values grow inside the monitor
    - Right Hand Coordinate system -> z values grow outside the monitor
    - OpenGL is a Right Handed Coodrinate System
    - Understand the Handedness when implementing the system

## Vector Transformations
    - The Current Projection we have made are static
    - WE NEED MOVEMENT!
    - Linear Transformations: linear equatins, linear functions and their representations
    - Scaling, Translate, Rotation

## 2: Matrices
    - Rotation Matrices
    - The way we manipulate objects 
    - What does it look like?
    _                       _
    | cos alpha, -sin alpha |
    | sin aplha, cos alpha  |
    -                       _

    - start with 2d vector (x,y)
    - How can we increase a 2D vector by its angle
        
## 3: Trigonometry
    - Cos -->
    - Sin --> 
    - Tan -->

                |\<--- Alpha
                | \
    adjacent--> |  \ <--- Hypotenuse
                |   \
                |____\
                opposite

            opposite              adjacent               opposite
     sin =  ----------     cos = ----------        tan = --------- 
            hypotenuse           hypotenuse              adjacent 

    
       pnemonic: s = o/h, c = a/h, t = o/a

        We know:
        x = r cos(alpha)
        y = r sin(aplha)
        AND VIA SUBSTITUTION
        x' = r (cos(aplha + beta))
        y' = r (sin(aplha + beta))

        x' = r cos(alpha + beta) == x' = r(cos aplha cos beta - sin alpha sin beta)
        x' = r (cos aplha cos beta) - r (sin alpha sin beta))
                        |                       |
                        We have a substitution here!
        To find the new x we substitue the original x and original y * the beta of cos/sin
        x' =  x * cos(beta) - y * sin(beta)


        y' = r sin(alpha + beta)
        y' = r * (sin alpha * cos beta + cos alpha * sin beta)
                    |                           |
                    We again has a substitution!!!
        y' = (y * cos beta) + (x * sin beta)

# IMPORTANT
        TO GET THE ROTATION EFFECT, WE SIMPLY LOCK ONE AXIS, CAUSING THE ROTATION TO BE PERCEIEVED

        x' =  x * cos(beta) - y * sin(beta)
        y' = (y * cos beta) + (x * sin beta)


# Lets Prove it!
   
        -  Let us start with the following:
           P1: sin(alpha + beta) = sin(alpha) cos(beta) + cos(alpha) sin(beta)
            
        Hypotenuse = 1  (just for simplicity)
        First Triangle is A, B C
        Second Triangle is C, D, A

        sin Alpa + Beta is the point from x to the top of the second triangle
        or a triangle formed from A,F,D

        What is the sin of the first and second?
        
        sin(alpha + Beta) = DE + EF 
        
        We can subsitute EF with CB
        Now we can solve CB with the cos of 
        
          
          


        cos(alpha + beta) = cos(alpha) cos(beta) + sin(alpha) sin(beta)

        

## Delay and FPS

```C
    // How Many Milli seconds to slepp until to resume process
    // time_to_wait take the Frame Target (30 FPS) - current ticks
    int time_to_wait = FRAME_TARGET_TIME - (SDL_GetTicks() - previous_frame_time);

    // If the time is too fast then we wait
    if (time_to_wait > 0 && time_to_wait <= FRAME_TARGET_TIME) {
            SDL_Delay(time_to_wait);
    }
```

The naive implementation used a While loop...while fine the problem arises that from a memory perspective (OS), we will be using the entire process of the cpu, even though the main action is to sleep, i.e. delay so we have the correct FPS. The solution is seen above, instead we chose to use SDL_Delay(), a function that directly communicates with the OS, and does not hijack the entire Processing unit, meaning our OS doesn't feel like its such a heavy lift

## Triangles and Meshes

    - The Standford Bunny: A 3D Mesh, a collection of triangles arranged in a collection to create the impression of a solid object
    
    - A triangle is defined by three corner points (vertices)
    
    - Vertices is 1 or more vertex points

    - Every Vertex has an X,Y,Z --> Creating a Triangle or Triangle Face
    
### Vertices
    1. Each one of Vertex point has XYZ values
    To represent this type of array we can use the following
```C
    /* Declare an array of vertices */
    vec3_t cube_vertices[8] = {
        { .x = -1, .y = -1, .z = -1 }, // 1
        { .x = -1, .y =  1, .z = -1 }, // 2
        { .x =  1, .y =  1, .z = -1 }, // 3
        { .x =  1, .y = -1, .z = -1 }, // 4
        { .x =  1, .y =  1, .z =  1 }, // 5
        { .x =  1, .y = -1, .z =  1 }, // 6 
        { .x = -1, .y =  1, .z =  1 }, // 7
        { .x = -1, .y = -1, .z =  1 }, // 8
    };
```

### Faces
    - Vertices are great, but now we need to draw the face!
    - Face is a collection of the 1st, 2nd, 3rd, vertex

```C
    /* Declare a new type of face information */
    typedef struct {
        int a, b, c;
    } face_t;

    /* Declare an array of cube triangle faces */
    face_t cube_faces[12] = {
        // Front 
        { .a = 1, .b = 2, .c = 3 }, 
        { .a = 1, .b = 3, .c = 4 }, 
        // Right 
        { .a = 4, .b = 3, .c = 5 }, 
        { .a = 4, .b = 5, .c = 6 }, 
        // Back
        { .a = 6, .b = 5, .c = 7 }, 
        { .a = 6, .b = 7, .c = 8 }, 
        // left
        { .a = 6, .b = 7, .c = 2 }, 
        { .a = 6, .b = 2, .c = 1 }, 
        // top
        { .a = 2, .b = 7, .c = 5 }, 
        { .a = 2, .b = 5, .c = 3 }, 
        // bottom
        { .a = 6, .b = 8, .c = 1 }, 
        { .a = 6, .b = 1, .c = 4 }, 
    }:
```

    - So Each vertex is a vec3 and each face is a index value of the vertexs
        
    1. Does the order of the vertexes matter?
        - ORDER MATTERS
        - Order can determine what is front and back
    
## Drawing Triangles
    
    - We have written Vertices woo hoo!

