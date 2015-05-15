#ifndef __block_h__
#define __block_h__

#include <GL/glew.h>

typedef enum { None, Purple, Red, Yellow, Green, Orange, Blue, Gray } Colour;

typedef struct block_t {
        // Block Shape/Rotation
        int* coords;     // Set of all "Block Space" coordinates
        int variations;  // How many "images" does this block have?
        int curr;        // Which variation are we on?
        // Block's grid coordinates (coord of C block)
        int x;
        int y;
        // Block Colour
        Colour c;
        // Which Block is it?
        char name;
} block_t;

// --- //

/* Create a new Block */
block_t* createBlock(int* coords, int vars, Colour c, char name);

/* Create a I block in the default position */
block_t* newI();

/* Create a S block in the default position */
block_t* newS();

/* Create a Z block in the default position */
block_t* newZ();

/* Create a L block in the default position */
block_t* newL();

/* Create a J block in the default position */
block_t* newJ();

/* Create a T block in the default position */
block_t* newT();

/* Create a O block (a square) in the default position */
block_t* newO();

/* Generate a random Colour */
Colour randColour();

/* Alter which `Colour` corresponds to which RGB values */
void rotateColours();

/* Get the float values for a Colour. Cannot fail */
GLfloat* ctof(Colour c);

/* Generate a random Block */
block_t* randBlock();

/* Rotate a Block to its next configuration */
block_t* rotateBlock(block_t* b);

/* Yield a list of grid-space coordinates occupied by the Block */
int* blockCells(block_t* b);

/* Copy a Block */
block_t* copyBlock(block_t* b);

/* Deallocate a Block */
void destroyBlock(block_t* b);

#endif
