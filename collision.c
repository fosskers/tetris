#include "block.h"
#include "collision.h"
#include "cog/dbg.h"

// --- //

/* Is the given Block colliding with the world? */
Collision isColliding(block_t* b, Fruit* fs) {
        int* cells = blockCells(b);

        if(collidingDown(cells, fs)) {
                return Bottom;
        } else if(collidingLeft(cells,fs)) {
                return Left;
                
        } else if(collidingRight(cells,fs)) {
                return Right;
        }
        else {
                return Clear;
        }
}

/* In which direction is the Block colliding? */
bool collidingLeft(int* cells, Fruit* fs) {
        int i;

        for(i = 0; i < 8; i+=2) {
                if(cells[i] == 0 ||
                   fs[cells[i] - 1 + cells[i+1] * 10] != None) {
                        return true;
                }
        }

        return false;
}

bool collidingRight(int* cells, Fruit* fs) {
        int i;

        for(i = 0; i < 8; i+=2) {
                if(cells[i] == 9 ||
                   fs[cells[i] + 1 + cells[i+1] * 10] != None) {
                        return true;
                }
        }

        return false;
}

bool collidingDown(int* cells, Fruit* fs) {
        int i;

        for(i = 0; i < 8; i+=2) {
                if(cells[i+1] == 0 ||
                   fs[cells[i] + (cells[i+1] - 1) * 10] != None) {
                        return true;
                }
        }

        return false;
}
