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

2.  
