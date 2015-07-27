#include "block.h"
#include "collision.h"
#include "cog/dbg.h"

// --- //

/* Is the given Block colliding with the world? */
Collision isColliding(block_t* b, Colour* board) {
        int* cells = blockCells(b);

        bool bot   = collidingDown(cells, board);
        bool left  = collidingLeft(cells,board);
        bool right = collidingRight(cells,board);

        if(bot) {
                if(left) {
                        if(right) {
                                return Total;
                        } else {
                                return BotLeft;
                        }
                } else if(right) {
                        return BotRight;
                } else {
                        return Bottom;
                }
        } else if(left) {
                if(right) {
                        return Sides;
                } else {
                        return Left;
                }
        } else if(right) {
                return Right;
        } else {
                return Clear;
        }
}

/* In which direction is the Block colliding? */
bool collidingLeft(int* cells, Colour* board) {
        int i;

        for(i = 0; i < 8; i+=2) {
                if(cells[i] == 0 ||
                   board[cells[i] - 1 + cells[i+1] * 10] != None) {
                        return true;
                }
        }

        return false;
}

bool collidingRight(int* cells, Colour* board) {
        int i;

        for(i = 0; i < 8; i+=2) {
                if(cells[i] == 9 ||
                   board[cells[i] + 1 + cells[i+1] * 10] != None) {
                        return true;
                }
        }

        return false;
}

bool collidingDown(int* cells, Colour* board) {
        int i;

        for(i = 0; i < 8; i+=2) {
                if(cells[i+1] == 0 ||
                   board[cells[i] + (cells[i+1] - 1) * 10] != None) {
                        return true;
                }
        }

        return false;
}

/* Is this Collision type any form of `Bottom`? */
bool isBottom(Collision c) {
        return (c == Bottom || c == BotLeft || c == BotRight || c == Total);
}

/* Is this Collision type any form of `Right`? */
bool isRight(Collision c) {
        return (c == Right || c == BotRight || c == Sides || c == Total);
}

/* Is this Collision type any form of `Left`? */
bool isLeft(Collision c) {
        return (c == Left || c == BotLeft || c == Sides || c == Total);
}
