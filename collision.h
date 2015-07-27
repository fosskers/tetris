#ifndef __collision_h__
#define __collision_h__

#include <stdbool.h>
#include "block.h"

// --- //

typedef enum { Clear, Left, Right, Sides,
               Bottom, BotLeft, BotRight, Total } Collision;
        
/* Is the given Block colliding with the world? */
Collision isColliding(block_t* b, Colour* board);

/* In which direction is the Block colliding? */
bool collidingLeft(int*  cells, Colour* board);
bool collidingRight(int* cells, Colour* board);
bool collidingDown(int*  cells, Colour* board);

/* Is this Collision type any form of `Bottom`? */
bool isBottom(Collision c);

/* Is this Collision type any form of `Right`? */
bool isRight(Collision c);

/* Is this Collision type any form of `Left`? */
bool isLeft(Collision c);

#endif
