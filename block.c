#include <stdlib.h>

#include "block.h"
#include "cog/dbg.h"

// --- //

/* All coordinates for all blocks in "Block Space".
 * Values come in pairs that represent the positions of cell
 * A, B, and D in that order. C is always at (0,0) in Block Space,
 * so we need not list it here.
 *
 * Coordinates range from (-2,-2) to (1,1).
 * (-2,-2) is the bottom-left corner.
 */
int iBlock[2][6] = {{ -2,0, -1,0, 1,0  },
                    { 0,-2, 0,-1, 0,1  }};
int sBlock[2][6] = {{ -1,-1, 0,-1, 1,0 },
                    { 1,-1, 1,0, 0,1   }};
int zBlock[2][6] = {{ 1,-1, 0,-1, -1,0 },
                    { -1,-1, -1,0, 0,1 }};
int lBlock[4][6] = {{ -1,-1, -1,0, 1,0 },
                    { 1,-1, 0,-1, 0,1  },
                    { 1,1, 1,0, -1,0   },
                    { -1,1, 0,1, 0,-1  }};
int jBlock[4][6] = {{ 1,-1, -1,0, 1,0 },
                    { -1,-1, 0,-1, 0,1  },
                    { -1,1, 1,0, -1,0   },
                    { 1,1, 0,1, 0,-1  }};
int tBlock[4][6] = {{ -1,0, 0,1, 1,0  },
                    { 0,1, 1,0, 0,-1  },
                    { 1,0, 0,-1, -1,0 },
                    { 0,-1, -1,0, 0,1 }};
int oBlock[1][6] = {{ -1,0, -1,-1, 0,-1 }};

// Fruit Colours
GLfloat black[]  = { 0.0,  0.0,  0.0  };
GLfloat purple[] = { 0.76, 0.41, 0.99 };
GLfloat red[]    = { 1.0,  0.56, 0.56 };
GLfloat yellow[] = { 1.0,  1.0,  0.52 };
GLfloat green[]  = { 0.66, 0.99, 0.56 };
GLfloat orange[] = { 1.0,  0.78, 0.28 };
GLfloat blue[]   = { 0.27, 0.71, 0.84 };
GLfloat gray[]   = { 0.75, 0.75, 0.75  };

// --- //

/* Create a new Block */
block_t* createBlock(int* coords, int vars, Colour c, char name) {
        block_t* b = malloc(sizeof(block_t));
        check_mem(b);
        
        b->coords = coords;
        b->variations = vars;
        b->curr = 0;
        b->x = 5;
        b->y = 19;
        b->c = c;
        b->name = name;

        return b;
 error:
        return NULL;
}

/* Create a I block in the default position */
block_t* newI() {
        return createBlock(&iBlock[0][0], 2, Purple, 'I');
}

/* Create a S block in the default position */
block_t* newS() {
        return createBlock(&sBlock[0][0], 2, Red, 'S');
}

/* Create a Z block in the default position */
block_t* newZ() {
        return createBlock(&zBlock[0][0], 2, Yellow, 'Z');
}

/* Create a L block in the default position */
block_t* newL() {
        return createBlock(&lBlock[0][0], 4, Green, 'L');
}

/* Create a J block in the default position */
block_t* newJ() {
        return createBlock(&jBlock[0][0], 4, Blue, 'J');
}

/* Create a T block in the default position */
block_t* newT() {
        return createBlock(&tBlock[0][0], 4, Gray, 'T');
}

/* Create a O block (a square) in the default position */
block_t* newO() {
        return createBlock(&oBlock[0][0], 1, Orange, 'O');
}

/* Generate a random Colour */
Colour randColour() {
        return (rand() % 5) + 1;
}

/* Alter which `Colour` corresponds to which RGB values */
void rotateColours() {
        GLfloat temp[] = { purple[0], purple[1], purple[2] };

        purple[0] = red[0]; purple[1] = red[1]; purple[2] = red[2];
        red[0] = yellow[0]; red[1] = yellow[1]; red[2] = yellow[2];
        yellow[0] = green[0]; yellow[1] = green[1]; yellow[2] = green[2];
        green[0] = orange[0]; green[1] = orange[1]; green[2] = orange[2];
        orange[0] = blue[0]; orange[1] = blue[1]; orange[2] = blue[2];
        blue[0] = gray[0]; blue[1] = gray[1]; blue[2] = gray[2];
        gray[0] = temp[0]; gray[1] = temp[1]; gray[2] = temp[2];
}

/* Get the colour of a Fruit. Cannot fail */
GLfloat* ctof(Colour c) {
        GLfloat* colour = NULL;

        switch(c) {
        case Purple:
                colour = purple;
                break;
        case Red:
                colour = red;
                break;
        case Yellow:
                colour = yellow;
                break;
        case Green:
                colour = green;
                break;
        case Orange:
                colour = orange;
                break;
        case Blue:
                colour = blue;
                break;
        case Gray:
                colour = gray;
                break;
        default:
                colour = black;  // You should never see this!
        }

        return colour;
}

/* Generate a random Block */
block_t* randBlock() {
        block_t* b = NULL;
        int choice = rand() % 7;

        switch(choice) {
        case 0:
                b = newL();
                break;
        case 1:
                b = newS();
                break;
        case 2:
                b = newZ();
                break;
        case 3:
                b = newO();
                break;
        case 4:
                b = newJ();
                break;
        case 5:
                b = newT();
                break;
        default:
                b = newI();
        }

        check(b, "Failed to randomly generate a Block.");

        return b;
 error:
        return NULL;
}

/* Rotate a Block to its next configuration */
block_t* rotateBlock(block_t* b) {
        check(b, "Null Block given.");

        b->curr = (b->curr + 1) % b->variations;

        switch(b->name) {
        case 'I':
                b->coords = &iBlock[b->curr][0];
                break;
        case 'S':
                b->coords = &sBlock[b->curr][0];
                break;
        case 'Z':
                b->coords = &zBlock[b->curr][0];
                break;
        case 'O':
                // O block doesn't rotate.
                break;
        case 'J':
                b->coords = &jBlock[b->curr][0];
                break;
        case 'L':
                b->coords = &lBlock[b->curr][0];
                break;
        case 'T':
                b->coords = &tBlock[b->curr][0];
                break;
        default:
                sentinel("You should never see this.");
        }

        return b;
 error:
        return NULL;
}

/* Yield a list of grid-space coordinates occupied by the Block */
int* blockCells(block_t* b) {
        int* cells = NULL;

        check(b, "Null Block given.");

        cells = malloc(sizeof(int) * 8);
        check_mem(cells);
        
        cells[0] = b->x + b->coords[0]; cells[1] = b->y + b->coords[1];
        cells[2] = b->x + b->coords[2]; cells[3] = b->y + b->coords[3];
        cells[4] = b->x;                cells[5] = b->y;
        cells[6] = b->x + b->coords[4]; cells[7] = b->y + b->coords[5];
        
        return cells;
 error:
        return NULL;
}

/* Copy a Block */
block_t* copyBlock(block_t* b) {
        block_t* newB = NULL;

        check(b, "Null Block given.");

        newB = malloc(sizeof(block_t));
        check_mem(newB);

        newB->coords = b->coords;
        newB->variations = b->variations;
        newB->curr = b->curr;
        newB->x = b->x;
        newB->y = b->y;
        newB->c = b->c;
        newB->name = b->name;

        return newB;
 error:
        return NULL;
}

/* Deallocate a Block */
void destroyBlock(block_t* b) {
        check(b, "Cannot destroy NULL Block.");
        free(b);

 error:
        return;
}
