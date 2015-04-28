#include <stdlib.h>

#include "block.h"
#include "cog/dbg.h"

// --- //

/* All coordinates for all blocks in "Block Space".
 * Values come in pairs that represent the positions of cell
 * A, B, and D in that order. C is always at (0,0) in Block Space,
 * so we need not list it here.
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
int oBlock[1][6] = {{ -1,0, -1,-1, 0,-1 }};

// Fruit Colours
GLfloat black[]  = { 0.0, 0.0, 0.0 };
GLfloat purple[] = { 1.0, 0.0, 1.0 };
GLfloat red[]    = { 1.0, 0.0, 0.0 };
GLfloat yellow[] = { 1.0, 1.0, 0.0 };
GLfloat green[]  = { 0.0, 1.0, 0.0 };
GLfloat orange[] = { 1.0, 0.5, 0.0 };

// --- //

/* Create a I block in the default position */
block_t* newI() {
        block_t* b = malloc(sizeof(block_t));
        check_mem(b);

        Colour c = randColour();
        
        b->coords = &iBlock[0][0];
        b->variations = 2;
        b->curr = 0;
        b->x = 5;
        b->y = 19;
        b->c = c;
        b->name = 'I';

        return b;
 error:
        return NULL;
}

/* Create a S block in the default position */
block_t* newS() {
        block_t* b = malloc(sizeof(block_t));
        check_mem(b);

        Colour c = randColour();

        b->coords = &sBlock[0][0];
        b->variations = 2;
        b->curr = 0;
        b->x = 5;
        b->y = 19;
        b->c = c;
        b->name = 'S';

        return b;
 error:
        return NULL;
}

/* Create a Z block in the default position */
block_t* newZ() {
        block_t* b = malloc(sizeof(block_t));
        check_mem(b);

        Colour c = randColour();

        b->coords = &zBlock[0][0];
        b->variations = 2;
        b->curr = 0;
        b->x = 5;
        b->y = 19;
        b->c = c;
        b->name = 'Z';

        return b;
 error:
        return NULL;
}

/* Create a L block in the default position */
block_t* newL() {
        block_t* b = malloc(sizeof(block_t));
        check_mem(b);

        Colour c = randColour();

        b->coords = &lBlock[0][0];
        b->variations = 4;
        b->curr = 0;
        b->x = 5;
        b->y = 19;
        b->c = c;
        b->name = 'L';

        return b;
 error:
        return NULL;
}

/* Create a O block (a square) in the default position */
block_t* newO() {
        block_t* b = malloc(sizeof(block_t));
        check_mem(b);

        Colour c = randColour();

        b->coords = &oBlock[0][0];
        b->variations = 1;
        b->curr = 0;
        b->x = 5;
        b->y = 19;
        b->c = c;
        b->name = 'O';

        return b;
 error:
        return NULL;
}

/* Generate a random Colour */
Colour randColour() {
        return (rand() % 5) + 1;
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
        default:
                colour = black;  // You should never see this!
        }

        return colour;
}

/* Generate a random Block */
block_t* randBlock() {
        block_t* b = NULL;
        int choice = rand() % 5;

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
        default:
                b->coords = &lBlock[b->curr][0];
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
