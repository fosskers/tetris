#include <GL/glew.h>  // This must be before other GL libs.
#include <GLFW/glfw3.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "collision.h"
#include "block.h"
#include "cog/camera/camera.h"
#include "cog/dbg.h"
#include "cog/shaders/shaders.h"
#include "util.h"

// --- //

GLfloat* blockToCoords(block_t*);
void initBoard();
void clearBoard();
void newBlock();
void refreshBlock(block_t* b, GLuint VAO, GLuint VBO);
int refreshBoard();

// --- //

#define BOARD_CELLS 200
// 9 floats per vertex, 3 vertices per triangle, 12 triangles per Cell
#define CELL_FLOATS 9 * 3 * 12
#define TOTAL_FLOATS BOARD_CELLS * CELL_FLOATS

bool gameOver = false;
bool running  = true;
bool keys[1024];
GLuint wWidth  = 600;
GLuint wHeight = 720;

/* Buffer Objects */
// Grid
GLuint gVAO;
GLuint gVBO;
// Small Grid
GLuint sgVAO;
GLuint sgVBO;
// (Current) Block
GLuint bVAO;
GLuint bVBO;
// (Next) Block
GLuint nVAO;
GLuint nVBO;
// Board
GLuint fVAO;
GLuint fVBO;

// Timing Info
GLfloat deltaTime = 0.0f;
GLfloat lastFrame = 0.0f;
GLfloat keyDelta  = 0.0f;
GLfloat lastKey   = 0.0f;

camera_t* camera;
matrix_t* view;
block_t*  currBlock;  // The Tetris block.
block_t*  nextBlock;  // The next block that will appear.
Colour board[BOARD_CELLS];  // The Board, represented as colours.

// --- //

/* Move Camera with WASD */
void moveCamera() {
        cogcMove(camera,
                 deltaTime,
                 keys[GLFW_KEY_W],
                 keys[GLFW_KEY_S],
                 keys[GLFW_KEY_A],
                 keys[GLFW_KEY_D]);
}

/* Init/Reset the Camera */
void resetCamera() {
        matrix_t* camPos = coglV3(0,0,4);
        matrix_t* camDir = coglV3(0,0,-1);
        matrix_t* camUp = coglV3(0,1,0);

        camera = cogcCreate(camPos,camDir,camUp);
}

/* Clears the board and starts over */
void resetGame() {
        initBoard();
        newBlock();
}

void newBlock() {
        currBlock = nextBlock;
        nextBlock = randBlock();
        refreshBlock(currBlock, bVAO, bVBO);
        refreshBlock(nextBlock, nVAO, nVBO);
}

void refreshBlock(block_t* b, GLuint VAO, GLuint VBO) {
        GLfloat* coords = blockToCoords(b);
        
        glBindVertexArray(VAO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferSubData(GL_ARRAY_BUFFER, 0, 
                        CELL_FLOATS * 4 * sizeof(GLfloat), coords);
        glBindVertexArray(0);

        free(coords);  // Necessary?
}

void key_callback(GLFWwindow* w, int key, int code, int action, int mode) {
        GLfloat currentTime = glfwGetTime();

        // Update key timing.
        keyDelta = currentTime - lastKey;
        lastKey  = currentTime;

        if(action == GLFW_PRESS ||
           (action == GLFW_REPEAT && keyDelta > 0.01)) {
                keys[key] = true;

                if(keys[GLFW_KEY_Q]) {
                        glfwSetWindowShouldClose(w, GL_TRUE);
                } else if(key == GLFW_KEY_P) {
                        if(running) {
                                log_info("Game paused.");
                                running = false;
                        } else {
                                log_info("Game unpaused.");
                                running = true;
                        }
                } else if(key == GLFW_KEY_C) {
                        resetCamera();
                } else if(key == GLFW_KEY_R) {
                        resetGame();
                } else if(key == GLFW_KEY_LEFT && currBlock->x > 0) {
                        if(isColliding(currBlock,board) != Left) {
                                currBlock->x -= 1;
                                refreshBlock(currBlock, bVAO, bVBO);
                        }
                } else if(key == GLFW_KEY_RIGHT && currBlock->x < 9) {
                        if(isColliding(currBlock,board) != Right) {
                                currBlock->x += 1;
                                refreshBlock(currBlock, bVAO, bVBO);
                        }
                } else if(key == GLFW_KEY_DOWN && currBlock->y > 0) {
                        currBlock->y -= 1;
                        refreshBlock(currBlock, bVAO, bVBO);
                } else if(key == GLFW_KEY_UP && currBlock->y < 19) {
                        block_t* copy = copyBlock(currBlock);
                        copy = rotateBlock(copy);
                        if(isColliding(copy,board) == Clear) {
                                currBlock = rotateBlock(currBlock);
                                destroyBlock(copy);
                                refreshBlock(currBlock, bVAO, bVBO);
                        } else {
                                debug("Flip would collide!");
                        }
                }
        } else if(action == GLFW_RELEASE) {
                keys[key] = false;
        }
}

void mouse_callback(GLFWwindow* w, double xpos, double ypos) {
        cogcPan(camera,xpos,ypos);
}

GLfloat* gridLocToCoords(int x, int y, Colour colour) {
        GLfloat* coords = NULL;
        GLfloat* c      = ctof(colour);
        GLuint i;

        GLfloat temp[CELL_FLOATS] = {
                // Back T1
                x, y,     -0.5, c[0], c[1], c[2], 0, 0, -1,
                x, 1 + y, -0.5, c[0], c[1], c[2], 0, 0, -1,
                1 + x, y, -0.5, c[0], c[1], c[2], 0, 0, -1,
                // Back T2
                x, 1 + y,     -0.5, c[0], c[1], c[2], 0, 0, -1,
                1 + x, y,     -0.5, c[0], c[1], c[2], 0, 0, -1,
                1 + x, 1 + y, -0.5, c[0], c[1], c[2], 0, 0, -1,
                // Front T1
                x, y,     0.5, c[0], c[1], c[2], 0, 0, 1,
                x, 1 + y, 0.5, c[0], c[1], c[2], 0, 0, 1,
                1 + x, y, 0.5, c[0], c[1], c[2], 0, 0, 1,
                // Front T2
                x, 1 + y,     0.5, c[0], c[1], c[2], 0, 0, 1,
                1 + x, y,     0.5, c[0], c[1], c[2], 0, 0, 1,
                1 + x, 1 + y, 0.5, c[0], c[1], c[2], 0, 0, 1,
                // Left T1
                x, y,     -0.5, c[0], c[1], c[2], -1, 0, 0,
                x, 1 + y, -0.5, c[0], c[1], c[2], -1, 0, 0,
                x, 1 + y,  0.5, c[0], c[1], c[2], -1, 0, 0,
                // Left T2
                x, y,    -0.5, c[0], c[1], c[2], -1, 0, 0,
                x, 1 + y, 0.5, c[0], c[1], c[2], -1, 0, 0,
                x, y,     0.5, c[0], c[1], c[2], -1, 0, 0,
                // Right T1
                1 + x, 1 + y, -0.5, c[0], c[1], c[2], 1, 0, 0,
                1 + x, y,     -0.5, c[0], c[1], c[2], 1, 0, 0,
                1 + x, 1 + y,  0.5, c[0], c[1], c[2], 1, 0, 0,
                // Right T2
                1 + x, 1 + y, 0.5, c[0], c[1], c[2], 1, 0, 0,
                1 + x, y,     0.5, c[0], c[1], c[2], 1, 0, 0,
                1 + x, y,    -0.5, c[0], c[1], c[2], 1, 0, 0,
                // Top T1
                x, 1 + y,      0.5, c[0], c[1], c[2], 0, 1, 0,
                1 + x, 1 + y,  0.5, c[0], c[1], c[2], 0, 1, 0,
                1 + x, 1 + y, -0.5, c[0], c[1], c[2], 0, 1, 0,
                // Top T2
                x, 1 + y,     0.5, c[0], c[1], c[2],  0, 1, 0,
                x, 1 + y,     -0.5, c[0], c[1], c[2], 0, 1, 0,
                1 + x, 1 + y, -0.5, c[0], c[1], c[2], 0, 1, 0,
                // Bottom T1
                x, y,      0.5, c[0], c[1], c[2], 0, -1, 0,
                1 + x, y,  0.5, c[0], c[1], c[2], 0, -1, 0,
                1 + x, y, -0.5, c[0], c[1], c[2], 0, -1, 0,
                // Bottom T2
                x, y,      0.5, c[0], c[1], c[2], 0, -1, 0,
                x, y,     -0.5, c[0], c[1], c[2], 0, -1, 0,
                1 + x, y, -0.5, c[0], c[1], c[2], 0, -1, 0
        };

        check(x > -1 && x < 10 &&
              y > -1 && x < 20,
              "Invalid coords given.");

        coords = malloc(sizeof(GLfloat) * CELL_FLOATS);
        check_mem(coords);

        if(colour == None) {
                // Nullify all the coordinates
                for(i = 0; i < CELL_FLOATS; i++) {
                        temp[i] = 0.0;
                }
        }

        // Copy values.
        for(i = 0; i < CELL_FLOATS; i++) {
                coords[i] = temp[i];
        }
        
        return coords;
 error:
        return NULL;
}

/* Produce locations and colours based on the current global Block */
GLfloat* blockToCoords(block_t* block) {
        GLfloat* temp1;
        GLfloat* temp2;
        GLfloat* cs = NULL;

        // 4 cells, each has 36 vertices of 6 data points each.
        //GLfloat* cs = malloc(sizeof(GLfloat) * 4 * 36 * 6);
        //check_mem(cs);

        // Coords and colours for each cell.
        GLfloat* a = gridLocToCoords(block->x+block->coords[0],
                                     block->y+block->coords[1],
                                     block->c);
        GLfloat* b = gridLocToCoords(block->x+block->coords[2],
                                     block->y+block->coords[3],
                                     block->c);
        GLfloat* c = gridLocToCoords(block->x,
                                     block->y,
                                     block->c);
        GLfloat* d = gridLocToCoords(block->x+block->coords[4],
                                     block->y+block->coords[5],
                                     block->c);

        check(a && b && c && d, "Couldn't get Cell coordinates.");

         // Construct return value
        temp1 = append(a, CELL_FLOATS, b, CELL_FLOATS);
        temp2 = append(c, CELL_FLOATS, d, CELL_FLOATS);
        cs    = append(temp1, CELL_FLOATS * 2, temp2, CELL_FLOATS * 2);
        check(cs, "Couldn't construct final list of coords/colours.");

        free(temp1); free(temp2);
        free(a); free(b); free(c); free(d);
        
        return cs;
 error:
        if(cs) { free(cs); }
        return NULL;
}

/* Initialize the Block */
int initBlock() {
        currBlock = randBlock();
        nextBlock = randBlock();
        check(currBlock && nextBlock, "Failed to initialize first Blocks.");
        debug("First Block: %c", currBlock->name);
        debug("Next Block: %c", nextBlock->name);

        debug("Initializing Block.");

        GLfloat* c_coords = blockToCoords(currBlock);
        GLfloat* n_coords = blockToCoords(nextBlock);

        /* Current Block */
        // Set up VAO/VBO
        glGenVertexArrays(1,&bVAO);
        glBindVertexArray(bVAO);
        glGenBuffers(1,&bVBO);
        glBindBuffer(GL_ARRAY_BUFFER,bVBO);
        glBufferData(GL_ARRAY_BUFFER,
                     CELL_FLOATS * 4 * sizeof(GLfloat),c_coords,
                     GL_DYNAMIC_DRAW);

        /* Tell OpenGL how to process Block Vertices */
        // Vertex location
        glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,
                              9 * sizeof(GLfloat),(GLvoid*)0);
        glEnableVertexAttribArray(0);
        // Vertex colour
        glVertexAttribPointer(1,3,GL_FLOAT,GL_FALSE,
                              9 * sizeof(GLfloat),
                              (GLvoid*)(3 * sizeof(GLfloat)));
        glEnableVertexAttribArray(1);
        // Vertex normal
        glVertexAttribPointer(2,3,GL_FLOAT,GL_FALSE,
                              9 * sizeof(GLfloat),
                              (GLvoid*)(6 * sizeof(GLfloat)));
        glEnableVertexAttribArray(2);
        glBindVertexArray(0);  // Reset the VAO binding.
        glBindBuffer(GL_ARRAY_BUFFER, 0);

        /* Next Block */
        // Set up VAO/VBO
        glGenVertexArrays(1,&nVAO);
        glBindVertexArray(nVAO);
        glGenBuffers(1,&nVBO);
        glBindBuffer(GL_ARRAY_BUFFER,nVBO);
        glBufferData(GL_ARRAY_BUFFER,
                     CELL_FLOATS * 4 * sizeof(GLfloat),n_coords,
                     GL_DYNAMIC_DRAW);

        /* Tell OpenGL how to process Block Vertices */
        // Vertex location
        glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,
                              9 * sizeof(GLfloat),(GLvoid*)0);
        glEnableVertexAttribArray(0);
        // Vertex colour
        glVertexAttribPointer(1,3,GL_FLOAT,GL_FALSE,
                              9 * sizeof(GLfloat),
                              (GLvoid*)(3 * sizeof(GLfloat)));
        glEnableVertexAttribArray(1);
        // Vertex normal
        glVertexAttribPointer(2,3,GL_FLOAT,GL_FALSE,
                              9 * sizeof(GLfloat),
                              (GLvoid*)(6 * sizeof(GLfloat)));
        glEnableVertexAttribArray(2);
        glBindVertexArray(0);  // Reset the VAO binding.
        glBindBuffer(GL_ARRAY_BUFFER, 0);

        debug("Blocks initialized.");

        return 1;
 error:
        return 0;
}

// Insert TRON pun here.
void initGrid() {
        GLfloat gridPoints[18 * (11 + 21)];
        int i;

        debug("Initializing Grid.");

        // Vertical lines
	for (i = 0; i < 11; i++) {
                // Bottom coord
                gridPoints[18*i]     = i;
                gridPoints[18*i + 1] = 0.0;
                gridPoints[18*i + 2] = -0.5;
                // Bottom colour
                gridPoints[18*i + 3] = 1;
                gridPoints[18*i + 4] = 1;
                gridPoints[18*i + 5] = 1;
                // Bottom normal
                gridPoints[18*i + 6] = 0;
                gridPoints[18*i + 7] = 0;
                gridPoints[18*i + 8] = 1;
                // Top coord
                gridPoints[18*i + 9]  = i;
                gridPoints[18*i + 10] = 20.0;
                gridPoints[18*i + 11] = -0.5;
                // Top colour
                gridPoints[18*i + 12] = 1;
                gridPoints[18*i + 13] = 1;
                gridPoints[18*i + 14] = 1;
                // Top normal
                gridPoints[18*i + 15] = 0;
                gridPoints[18*i + 16] = 0;
                gridPoints[18*i + 17] = 1;
	}

	// Horizontal lines.
	for (i = 0; i < 21; i++) {
                // Left coord
                gridPoints[198 + 18*i]     = 0.0;
                gridPoints[198 + 18*i + 1] = i;
                gridPoints[198 + 18*i + 2] = -0.5;
                // Left colour
                gridPoints[198 + 18*i + 3] = 1;
                gridPoints[198 + 18*i + 4] = 1;
                gridPoints[198 + 18*i + 5] = 1;
                // Left normal
                gridPoints[198 + 18*i + 6] = 0;
                gridPoints[198 + 18*i + 7] = 0;
                gridPoints[198 + 18*i + 8] = 1;
                // Right coord
                gridPoints[198 + 18*i + 9]  = 10.0;
                gridPoints[198 + 18*i + 10] = i;
                gridPoints[198 + 18*i + 11] = -0.5;
                // Right colour
                gridPoints[198 + 18*i + 12] = 1;
                gridPoints[198 + 18*i + 13] = 1;
                gridPoints[198 + 18*i + 14] = 1;
                // Right normal
                gridPoints[198 + 18*i + 15] = 0;
                gridPoints[198 + 18*i + 16] = 0;
                gridPoints[198 + 18*i + 17] = 1;
	}

        // Set up VAO/VBO
        glGenVertexArrays(1,&gVAO);
        glBindVertexArray(gVAO);
        glGenBuffers(1,&gVBO);
        glBindBuffer(GL_ARRAY_BUFFER, gVBO);
        glBufferData(GL_ARRAY_BUFFER,sizeof(gridPoints),
                     gridPoints,GL_STATIC_DRAW);

        /* Tell OpenGL how to process Block Vertices */
        // Vertex location
        glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,
                              9 * sizeof(GLfloat),(GLvoid*)0);
        glEnableVertexAttribArray(0);
        // Vertex colour
        glVertexAttribPointer(1,3,GL_FLOAT,GL_FALSE,
                              9 * sizeof(GLfloat),
                              (GLvoid*)(3 * sizeof(GLfloat)));
        glEnableVertexAttribArray(1);
        // Vertex normal
        glVertexAttribPointer(2,3,GL_FLOAT,GL_FALSE,
                              9 * sizeof(GLfloat),
                              (GLvoid*)(6 * sizeof(GLfloat)));
        glEnableVertexAttribArray(2);
        glBindVertexArray(0);  // Reset the VAO binding.
        glBindBuffer(GL_ARRAY_BUFFER, 0);

        debug("Grid initialized.");
}

void initSmallGrid() {
        // 5 each of horizontal and vertical lines.
        GLfloat gridPoints[18 * (5 + 5)];
        int i;

        debug("Initializing Grid.");

        // Vertical lines
	for (i = 0; i < 5; i++) {
                // Bottom coord
                gridPoints[18*i]     = i;
                gridPoints[18*i + 1] = 0.0;
                gridPoints[18*i + 2] = -0.5;
                // Bottom colour
                gridPoints[18*i + 3] = 1;
                gridPoints[18*i + 4] = 1;
                gridPoints[18*i + 5] = 1;
                // Bottom normal
                gridPoints[18*i + 6] = 0;
                gridPoints[18*i + 7] = 0;
                gridPoints[18*i + 8] = 1;
                // Top coord
                gridPoints[18*i + 9]  = i;
                gridPoints[18*i + 10] = 4.0;
                gridPoints[18*i + 11] = -0.5;
                // Top colour
                gridPoints[18*i + 12] = 1;
                gridPoints[18*i + 13] = 1;
                gridPoints[18*i + 14] = 1;
                // Top normal
                gridPoints[18*i + 15] = 0;
                gridPoints[18*i + 16] = 0;
                gridPoints[18*i + 17] = 1;
	}

	// Horizontal lines.
	for (i = 0; i < 5; i++) {
                // Left coord
                gridPoints[90 + 18*i]     = 0.0;
                gridPoints[90 + 18*i + 1] = i;
                gridPoints[90 + 18*i + 2] = -0.5;
                // Left colour
                gridPoints[90 + 18*i + 3] = 1;
                gridPoints[90 + 18*i + 4] = 1;
                gridPoints[90 + 18*i + 5] = 1;
                // Left normal
                gridPoints[90 + 18*i + 6] = 0;
                gridPoints[90 + 18*i + 7] = 0;
                gridPoints[90 + 18*i + 8] = 1;
                // Right coord
                gridPoints[90 + 18*i + 9]  = 4.0;
                gridPoints[90 + 18*i + 10] = i;
                gridPoints[90 + 18*i + 11] = -0.5;
                // Right colour
                gridPoints[90 + 18*i + 12] = 1;
                gridPoints[90 + 18*i + 13] = 1;
                gridPoints[90 + 18*i + 14] = 1;
                // Right normal
                gridPoints[90 + 18*i + 15] = 0;
                gridPoints[90 + 18*i + 16] = 0;
                gridPoints[90 + 18*i + 17] = 1;
	}

        // Set up VAO/VBO
        glGenVertexArrays(1,&sgVAO);
        glBindVertexArray(sgVAO);
        glGenBuffers(1,&sgVBO);
        glBindBuffer(GL_ARRAY_BUFFER, sgVBO);
        glBufferData(GL_ARRAY_BUFFER,sizeof(gridPoints),
                     gridPoints,GL_STATIC_DRAW);

        /* Tell OpenGL how to process Block Vertices */
        // Vertex location
        glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,
                              9 * sizeof(GLfloat),(GLvoid*)0);
        glEnableVertexAttribArray(0);
        // Vertex colour
        glVertexAttribPointer(1,3,GL_FLOAT,GL_FALSE,
                              9 * sizeof(GLfloat),
                              (GLvoid*)(3 * sizeof(GLfloat)));
        glEnableVertexAttribArray(1);
        // Vertex normal
        glVertexAttribPointer(2,3,GL_FLOAT,GL_FALSE,
                              9 * sizeof(GLfloat),
                              (GLvoid*)(6 * sizeof(GLfloat)));
        glEnableVertexAttribArray(2);
        glBindVertexArray(0);  // Reset the VAO binding.
        glBindBuffer(GL_ARRAY_BUFFER, 0);

        debug("Small Grid initialized.");
}

/* Initialize the game board */
void initBoard() {
        debug("Initializing Board.");

        GLfloat temp[TOTAL_FLOATS];
        
        // Set up VAO/VBO
        glGenVertexArrays(1,&fVAO);
        glBindVertexArray(fVAO);
        glGenBuffers(1,&fVBO);
        glBindBuffer(GL_ARRAY_BUFFER,fVBO);
        // 200 cells, each has 36 vertices of 6 data points each.
        glBufferData(GL_ARRAY_BUFFER, 
                     TOTAL_FLOATS * sizeof(GLfloat),
                     temp,
                     GL_DYNAMIC_DRAW);
        
        /* Tell OpenGL how to process Block Vertices */
        // Vertex location
        glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,
                              9 * sizeof(GLfloat),(GLvoid*)0);
        glEnableVertexAttribArray(0);
        // Vertex colour
        glVertexAttribPointer(1,3,GL_FLOAT,GL_FALSE,
                              9 * sizeof(GLfloat),
                              (GLvoid*)(3 * sizeof(GLfloat)));
        glEnableVertexAttribArray(1);
        // Vertex normal
        glVertexAttribPointer(2,3,GL_FLOAT,GL_FALSE,
                              9 * sizeof(GLfloat),
                              (GLvoid*)(6 * sizeof(GLfloat)));
        glEnableVertexAttribArray(2);
        glBindVertexArray(0);  // Reset the VAO binding.
        //        glBindBuffer(GL_ARRAY_BUFFER, 0);
        
        clearBoard();

        debug("Board initialized.");
}

/* Move all coloured Cells from the Board */
void clearBoard() {
        int i;

        for(i = 0; i < BOARD_CELLS; i++) {
                board[i] = 0;
        }

        refreshBoard();
}

/* Draw all the coloured Board Cells */
int refreshBoard() {
        GLuint i,j,k;
        GLfloat* cellData;

        debug("Refreshing Board...");
        
        GLfloat* coords = malloc(sizeof(GLfloat) * TOTAL_FLOATS);
        check_mem(coords);

        for(i = 0; i < BOARD_CELLS; i++) {
                cellData = gridLocToCoords(i % 10, i / 10, board[i]);
                check(cellData, "Couldn't get coord data for Cell.");
                
                for(j = i*CELL_FLOATS, k=0; k < CELL_FLOATS; j++, k++) {
                        coords[j] = cellData[k];
                }
        }

        glBindVertexArray(fVAO);
        glBindBuffer(GL_ARRAY_BUFFER, fVBO);
        glBufferSubData(GL_ARRAY_BUFFER, 0, 
                        TOTAL_FLOATS * sizeof(GLfloat), coords);
        glBindVertexArray(0);

        free(coords);
        
        return 1;
 error:
        return 0;        
}

/* Removes any solid lines, if it can */
void lineCheck() {
        int i,j,k;
        bool fullRow = true;

        for(i = 0; i < BOARD_CELLS; i+=10) {
                fullRow = true;

                // Check for full row
                for(j = 0; j < 10; j++) {
                        if(board[i + j] == None) {
                                fullRow = false;
                                break;
                        }
                }

                if(fullRow) {
                        debug("Found a full row!");
                        // Empty the row
                        for(j = 0; j < 10; j++) {
                                board[i + j] = None;
                        }

                        // Drop the other pieces.
                        for(k = i + j; k < BOARD_CELLS; k++) {
                                board[k-10] = board[k];
                        }

                        // Are there any other completed rows?
                        lineCheck();

                        break;
                }
        }
}

/* Scrolls the Block naturally down */
void scrollBlock() {
        static double lastTime = 0;
        double currTime = glfwGetTime();
        int* cells = NULL;
        int i;

        if(!running) {
                return;
        }
        
        if(isColliding(currBlock, board) != Bottom) {
                if(currTime - lastTime > 0.5) {

                        lastTime = currTime;
                        currBlock->y -= 1;

                        GLfloat* coords = blockToCoords(currBlock);
        
                        glBindVertexArray(bVAO);
                        glBindBuffer(GL_ARRAY_BUFFER, bVBO);
                        glBufferSubData(GL_ARRAY_BUFFER, 0, 
                                        CELL_FLOATS * 4 * sizeof(GLfloat),
                                        coords);
                        glBindVertexArray(0);
                }
        } else if(currBlock->y == 19) {
                gameOver = true;
        } else {
                cells = blockCells(currBlock);

                // Add the Block's cells to the master Board
                for(i = 0; i < 8; i+=2) {
                        board[cells[i] + 10*cells[i+1]] = currBlock->c;
                }

                lineCheck();
                newBlock();
                refreshBoard();
        }
}

int main(int argc, char** argv) {
        // Initial settings.
        glfwInit();
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
        glfwWindowHint(GLFW_SAMPLES,4);  // Anti-aliasing.

        // Make a window.
        GLFWwindow* w = glfwCreateWindow(wWidth,wHeight,"Fetris",NULL,NULL);
        glfwMakeContextCurrent(w);

        // Fire up GLEW.
        glewExperimental = GL_TRUE;  // For better compatibility.
        glewInit();

        // For the rendering window.
        glViewport(0,0,wWidth,wHeight);

        // Register callbacks.
        glfwSetKeyCallback(w, key_callback);
        glfwSetInputMode(w,GLFW_CURSOR,GLFW_CURSOR_DISABLED);
        glfwSetCursorPosCallback(w,mouse_callback);
        
        /* Depth Testing */
        glEnable(GL_DEPTH_TEST);

        /* Enable Anti-Aliasing */
        glEnable(GL_MULTISAMPLE);
        
        /* Create Shader Program */
        debug("Making shader program.");
        shaders_t* shaders = cogsShaders("vertex.glsl", "fragment.glsl");
        GLuint shaderProgram = cogsProgram(shaders);
        cogsDestroy(shaders);
        check(shaderProgram > 0, "Shaders didn't compile.");
        debug("Shaders good.");

        /* Initial randomness */
        srand((GLuint)(100000 * glfwGetTime()));
        
        /* Initialize Board, Grid, and first Block */
        initBoard();
        initGrid();
        initSmallGrid();
        quiet_check(initBlock());

        /* Set initial Camera state */
        resetCamera();

        /* Model Matrix for Current Block and Grid */
        matrix_t* model = coglMIdentity(4);
        model = coglM4Translate(model,-8,-10,0);
        model = coglMScale(model,0.15);
        check(model, "Model creation failed.");

        /* Model Matrix for Next Block */
        matrix_t* nModel = coglMIdentity(4);
        nModel = coglM4Translate(nModel,1,-12,0);
        nModel = coglMScale(nModel,0.15);
        check(nModel, "Next-Block Model creation failed.");

        /* Model Matrix for Small Grid */
        matrix_t* sgModel = coglMIdentity(4);
        sgModel = coglM4Translate(sgModel,4,5,0);
        sgModel = coglMScale(sgModel,0.15);
        check(sgModel, "Small Grid Model creation failed.");
        
        /* Projection Matrix */
        matrix_t* proj = coglMPerspectiveP(tau/8, 
                                           (float)wWidth/(float)wHeight,
                                           0.1f,1000.0f);

        /* Lighting settings */
        glUseProgram(shaderProgram);
        matrix_t* lightPos = coglV3(0.5f,0.5f,2.0f);
        GLuint lghtLoc = glGetUniformLocation(shaderProgram,"lightPos");
        GLuint modlLoc = glGetUniformLocation(shaderProgram,"model");
        GLuint viewLoc = glGetUniformLocation(shaderProgram,"view");
        GLuint projLoc = glGetUniformLocation(shaderProgram,"proj");
        
        /* The current time since starting */
        GLfloat currentFrame;
        
        debug("Entering Loop.");
        while(!glfwWindowShouldClose(w)) {
                if(gameOver) {
                        sleep(1);
                        break;
                }

                currentFrame = glfwGetTime();
                deltaTime = currentFrame - lastFrame;
                lastFrame = currentFrame;

                glfwPollEvents();
                moveCamera();

                glClearColor(0.1f,0.1f,0.1f,1.0f);
                glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

                glUseProgram(shaderProgram);

                // Move the block down.
                scrollBlock();

                // Update View Matrix
                coglMDestroy(view);
                view = coglM4LookAtP(camera->pos,camera->tar,camera->up);

                // Set transformation Matrices
                glUniform3f(lghtLoc,lightPos->m[0],
                            lightPos->m[1],lightPos->m[2]);
                glUniformMatrix4fv(modlLoc,1,GL_FALSE,model->m);
                glUniformMatrix4fv(viewLoc,1,GL_FALSE,view->m);
                glUniformMatrix4fv(projLoc,1,GL_FALSE,proj->m);

                // Draw Grid
                glBindVertexArray(gVAO);
                glDrawArrays(GL_LINES, 0, 64);
                glBindVertexArray(0);
                
                // Draw Block
                glBindVertexArray(bVAO);
                glDrawArrays(GL_TRIANGLES,0,36 * 4);
                glBindVertexArray(0);

                // Draw Board
                glBindVertexArray(fVAO);
                glDrawArrays(GL_TRIANGLES,0,7200);
                glBindVertexArray(0);

                // Draw Next Block
                glUniformMatrix4fv(modlLoc,1,GL_FALSE,nModel->m);
                glBindVertexArray(nVAO);
                glDrawArrays(GL_TRIANGLES,0,36 * 4);
                glBindVertexArray(0);

                // Draw Small Grid
                glUniformMatrix4fv(modlLoc,1,GL_FALSE,sgModel->m);
                glBindVertexArray(sgVAO);
                glDrawArrays(GL_LINES, 0, 20);
                glBindVertexArray(0);

                // Always comes last.
                glfwSwapBuffers(w);
        }

        // Clean up.
        glfwTerminate();
        log_info("Thanks for playing!");

        return EXIT_SUCCESS;
 error:
        return EXIT_FAILURE;
}
