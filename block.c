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

        Fruit* fs = randFruits();
        check(fs, "Failed to generate Fruits.");
        
        b->coords = &iBlock[0][0];
        b->variations = 2;
        b->curr = 0;
        b->x = 5;
        b->y = 19;
        b->fs = fs;
        b->name = 'I';

        return b;
 error:
        return NULL;
}

/* Create a S block in the default position */
block_t* newS() {
        block_t* b = malloc(sizeof(block_t));
        check_mem(b);

        Fruit* fs = randFruits();
        check(fs, "Failed to generate Fruits.");

        b->coords = &sBlock[0][0];
        b->variations = 2;
        b->curr = 0;
        b->x = 5;
        b->y = 19;
        b->fs = fs;
        b->name = 'S';

        return b;
 error:
        return NULL;
}

/* Create a Z block in the default position */
block_t* newZ() {
        block_t* b = malloc(sizeof(block_t));
        check_mem(b);

        Fruit* fs = randFruits();
        check(fs, "Failed to generate Fruits.");

        b->coords = &zBlock[0][0];
        b->variations = 2;
        b->curr = 0;
        b->x = 5;
        b->y = 19;
        b->fs = fs;
        b->name = 'Z';

        return b;
 error:
        return NULL;
}

/* Create a L block in the default position */
block_t* newL() {
        block_t* b = malloc(sizeof(block_t));
        check_mem(b);

        Fruit* fs = randFruits();
        check(fs, "Failed to generate Fruits.");

        b->coords = &lBlock[0][0];
        b->variations = 4;
        b->curr = 0;
        b->x = 5;
        b->y = 19;
        b->fs = fs;
        b->name = 'L';

        return b;
 error:
        return NULL;
}

/* Create a O block (a square) in the default position */
block_t* newO() {
        block_t* b = malloc(sizeof(block_t));
        check_mem(b);

        Fruit* fs = randFruits();
        check(fs, "Failed to generate Fruits.");

        b->coords = &oBlock[0][0];
        b->variations = 1;
        b->curr = 0;
        b->x = 5;
        b->y = 19;
        b->fs = fs;
        b->name = 'O';

        return b;
 error:
        return NULL;
}

/* Generate four random Fruits */
Fruit* randFruits() {
        int i;
        Fruit* fs = malloc(sizeof(Fruit) * 4);
        check_mem(fs);

        // There are five Fruit types available, so we mod5.
        for(i = 0; i < 4; i++) {
                fs[i] = (rand() % 5) + 1;
        }
 error:
        return fs;
}

/* Get the colour of a Fruit. Cannot fail */
GLfloat* fruitColour(Fruit f) {
        GLfloat* colour = NULL;

        switch(f) {
        case Grape:
                colour = purple;
                break;
        case Apple:
                colour = red;
                break;
        case Banana:
                colour = yellow;
                break;
        case Pear:
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

/* Shuffle the order of the fruits */
block_t* shuffleFruit(block_t* b) {
        check(b, "Null Block given.");

        Fruit d = b->fs[3];
        b->fs[3] = b->fs[2];
        b->fs[2] = b->fs[1];
        b->fs[1] = b->fs[0];
        b->fs[0] = d;

        return b;
 error:
        return NULL;
}

/* Copy a Block */
block_t* copyBlock(block_t* b) {
        block_t* newB = NULL;
        int i;

        check(b, "Null Block given.");

        newB = malloc(sizeof(block_t));
        check_mem(newB);

        newB->coords = b->coords;
        newB->variations = b->variations;
        newB->curr = b->curr;
        newB->x = b->x;
        newB->y = b->y;
        newB->fs = malloc(sizeof(Fruit) * 4);
        check_mem(newB->fs);
        
        for(i = 0; i < 4; i++) {
                newB->fs[i] = b->fs[i];
        }

        newB->name = b->name;

        return newB;
 error:
        return NULL;
}

/* Deallocate a Block */
void destroyBlock(block_t* b) {
        if(b) {
                free(b->fs);
                free(b);
        }
}
