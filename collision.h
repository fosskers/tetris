#ifndef __collision_h__
#define __collision_h__

#include <stdbool.h>
#include "block.h"

// --- //

typedef enum { Clear, Left, Right, Bottom } Collision;
        

/* Is the given Block colliding with the world? */
Collision isColliding(block_t* b, Fruit* fs);

/* In which direction is the Block colliding? */
bool collidingLeft(int*  cells, Fruit* fs);
bool collidingRight(int* cells, Fruit* fs);
bool collidingDown(int*  cells, Fruit* fs);

#endif
