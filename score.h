#ifndef __score_h__
#define __score_h__

/* Data here was generated with:
 * https://github.com/fosskers/playground/blob/master/haskell/points.hs
 */

#include <GL/glew.h>

// --- //

#define PRISM_FLOATS 1080

GLfloat prism[PRISM_FLOATS] = {
        0.250,0.162,0.500, 0.500,0.500,0.500, 1.000,0.000,0.000,
0.250,0.425,0.309, 0.500,0.500,0.500, 1.000,0.000,0.000,
0.250,0.000,0.000, 0.500,0.500,0.500, 1.000,0.000,0.000,
0.250,0.425,0.309, 0.500,0.500,0.500, 1.000,0.000,0.000,
0.250,0.526,0.000, 0.500,0.500,0.500, 1.000,0.000,0.000,
0.250,0.000,0.000, 0.500,0.500,0.500, 1.000,0.000,0.000,
0.250,0.526,0.000, 0.500,0.500,0.500, 1.000,0.000,0.000,
0.250,0.425,-0.309, 0.500,0.500,0.500, 1.000,0.000,0.000,
0.250,0.000,0.000, 0.500,0.500,0.500, 1.000,0.000,0.000,
0.250,0.425,-0.309, 0.500,0.500,0.500, 1.000,0.000,0.000,
0.250,0.162,-0.500, 0.500,0.500,0.500, 1.000,0.000,0.000,
0.250,0.000,0.000, 0.500,0.500,0.500, 1.000,0.000,0.000,
0.250,0.162,-0.500, 0.500,0.500,0.500, 1.000,0.000,0.000,
0.250,-0.162,-0.500, 0.500,0.500,0.500, 1.000,0.000,0.000,
0.250,0.000,0.000, 0.500,0.500,0.500, 1.000,0.000,0.000,
0.250,-0.162,-0.500, 0.500,0.500,0.500, 1.000,0.000,0.000,
0.250,-0.425,-0.309, 0.500,0.500,0.500, 1.000,0.000,0.000,
0.250,0.000,0.000, 0.500,0.500,0.500, 1.000,0.000,0.000,
0.250,-0.425,-0.309, 0.500,0.500,0.500, 1.000,0.000,0.000,
0.250,-0.526,-0.000, 0.500,0.500,0.500, 1.000,0.000,0.000,
0.250,0.000,0.000, 0.500,0.500,0.500, 1.000,0.000,0.000,
0.250,-0.526,-0.000, 0.500,0.500,0.500, 1.000,0.000,0.000,
0.250,-0.425,0.309, 0.500,0.500,0.500, 1.000,0.000,0.000,
0.250,0.000,0.000, 0.500,0.500,0.500, 1.000,0.000,0.000,
0.250,-0.425,0.309, 0.500,0.500,0.500, 1.000,0.000,0.000,
0.250,-0.162,0.500, 0.500,0.500,0.500, 1.000,0.000,0.000,
0.250,0.000,0.000, 0.500,0.500,0.500, 1.000,0.000,0.000,
0.250,-0.162,0.500, 0.500,0.500,0.500, 1.000,0.000,0.000,
0.250,0.162,0.500, 0.500,0.500,0.500, 1.000,0.000,0.000,
0.250,0.000,0.000, 0.500,0.500,0.500, 1.000,0.000,0.000,
-0.250,0.162,0.500, 0.500,0.500,0.500, -1.000,0.000,0.000,
-0.250,0.425,0.309, 0.500,0.500,0.500, -1.000,0.000,0.000,
-0.250,0.000,0.000, 0.500,0.500,0.500, -1.000,0.000,0.000,
-0.250,0.425,0.309, 0.500,0.500,0.500, -1.000,0.000,0.000,
-0.250,0.526,0.000, 0.500,0.500,0.500, -1.000,0.000,0.000,
-0.250,0.000,0.000, 0.500,0.500,0.500, -1.000,0.000,0.000,
-0.250,0.526,0.000, 0.500,0.500,0.500, -1.000,0.000,0.000,
-0.250,0.425,-0.309, 0.500,0.500,0.500, -1.000,0.000,0.000,
-0.250,0.000,0.000, 0.500,0.500,0.500, -1.000,0.000,0.000,
-0.250,0.425,-0.309, 0.500,0.500,0.500, -1.000,0.000,0.000,
-0.250,0.162,-0.500, 0.500,0.500,0.500, -1.000,0.000,0.000,
-0.250,0.000,0.000, 0.500,0.500,0.500, -1.000,0.000,0.000,
-0.250,0.162,-0.500, 0.500,0.500,0.500, -1.000,0.000,0.000,
-0.250,-0.162,-0.500, 0.500,0.500,0.500, -1.000,0.000,0.000,
-0.250,0.000,0.000, 0.500,0.500,0.500, -1.000,0.000,0.000,
-0.250,-0.162,-0.500, 0.500,0.500,0.500, -1.000,0.000,0.000,
-0.250,-0.425,-0.309, 0.500,0.500,0.500, -1.000,0.000,0.000,
-0.250,0.000,0.000, 0.500,0.500,0.500, -1.000,0.000,0.000,
-0.250,-0.425,-0.309, 0.500,0.500,0.500, -1.000,0.000,0.000,
-0.250,-0.526,-0.000, 0.500,0.500,0.500, -1.000,0.000,0.000,
-0.250,0.000,0.000, 0.500,0.500,0.500, -1.000,0.000,0.000,
-0.250,-0.526,-0.000, 0.500,0.500,0.500, -1.000,0.000,0.000,
-0.250,-0.425,0.309, 0.500,0.500,0.500, -1.000,0.000,0.000,
-0.250,0.000,0.000, 0.500,0.500,0.500, -1.000,0.000,0.000,
-0.250,-0.425,0.309, 0.500,0.500,0.500, -1.000,0.000,0.000,
-0.250,-0.162,0.500, 0.500,0.500,0.500, -1.000,0.000,0.000,
-0.250,0.000,0.000, 0.500,0.500,0.500, -1.000,0.000,0.000,
-0.250,-0.162,0.500, 0.500,0.500,0.500, -1.000,0.000,0.000,
-0.250,0.162,0.500, 0.500,0.500,0.500, -1.000,0.000,0.000,
-0.250,0.000,0.000, 0.500,0.500,0.500, -1.000,0.000,0.000,
0.250,0.162,0.500, 0.500,0.500,0.500, 0.000,0.588,0.809,
0.250,0.425,0.309, 0.500,0.500,0.500, 0.000,0.588,0.809,
-0.250,0.162,0.500, 0.500,0.500,0.500, 0.000,0.588,0.809,
-0.250,0.162,0.500, 0.500,0.500,0.500, 0.000,0.588,0.809,
-0.250,0.425,0.309, 0.500,0.500,0.500, 0.000,0.588,0.809,
0.250,0.425,0.309, 0.500,0.500,0.500, 0.000,0.588,0.809,
0.250,0.425,0.309, 0.500,0.500,0.500, 0.000,0.951,0.309,
0.250,0.526,0.000, 0.500,0.500,0.500, 0.000,0.951,0.309,
-0.250,0.425,0.309, 0.500,0.500,0.500, 0.000,0.951,0.309,
-0.250,0.425,0.309, 0.500,0.500,0.500, 0.000,0.951,0.309,
-0.250,0.526,0.000, 0.500,0.500,0.500, 0.000,0.951,0.309,
0.250,0.526,0.000, 0.500,0.500,0.500, 0.000,0.951,0.309,
0.250,0.526,0.000, 0.500,0.500,0.500, 0.000,0.951,-0.309,
0.250,0.425,-0.309, 0.500,0.500,0.500, 0.000,0.951,-0.309,
-0.250,0.526,0.000, 0.500,0.500,0.500, 0.000,0.951,-0.309,
-0.250,0.526,0.000, 0.500,0.500,0.500, 0.000,0.951,-0.309,
-0.250,0.425,-0.309, 0.500,0.500,0.500, 0.000,0.951,-0.309,
0.250,0.425,-0.309, 0.500,0.500,0.500, 0.000,0.951,-0.309,
0.250,0.425,-0.309, 0.500,0.500,0.500, 0.000,0.588,-0.809,
0.250,0.162,-0.500, 0.500,0.500,0.500, 0.000,0.588,-0.809,
-0.250,0.425,-0.309, 0.500,0.500,0.500, 0.000,0.588,-0.809,
-0.250,0.425,-0.309, 0.500,0.500,0.500, 0.000,0.588,-0.809,
-0.250,0.162,-0.500, 0.500,0.500,0.500, 0.000,0.588,-0.809,
0.250,0.162,-0.500, 0.500,0.500,0.500, 0.000,0.588,-0.809,
0.250,0.162,-0.500, 0.500,0.500,0.500, 0.000,0.000,-1.000,
0.250,-0.162,-0.500, 0.500,0.500,0.500, 0.000,0.000,-1.000,
-0.250,0.162,-0.500, 0.500,0.500,0.500, 0.000,0.000,-1.000,
-0.250,0.162,-0.500, 0.500,0.500,0.500, 0.000,0.000,-1.000,
-0.250,-0.162,-0.500, 0.500,0.500,0.500, 0.000,0.000,-1.000,
0.250,-0.162,-0.500, 0.500,0.500,0.500, 0.000,0.000,-1.000,
0.250,-0.162,-0.500, 0.500,0.500,0.500, -0.000,-0.588,-0.809,
0.250,-0.425,-0.309, 0.500,0.500,0.500, -0.000,-0.588,-0.809,
-0.250,-0.162,-0.500, 0.500,0.500,0.500, -0.000,-0.588,-0.809,
-0.250,-0.162,-0.500, 0.500,0.500,0.500, -0.000,-0.588,-0.809,
-0.250,-0.425,-0.309, 0.500,0.500,0.500, -0.000,-0.588,-0.809,
0.250,-0.425,-0.309, 0.500,0.500,0.500, -0.000,-0.588,-0.809,
0.250,-0.425,-0.309, 0.500,0.500,0.500, -0.000,-0.951,-0.309,
0.250,-0.526,-0.000, 0.500,0.500,0.500, -0.000,-0.951,-0.309,
-0.250,-0.425,-0.309, 0.500,0.500,0.500, -0.000,-0.951,-0.309,
-0.250,-0.425,-0.309, 0.500,0.500,0.500, -0.000,-0.951,-0.309,
-0.250,-0.526,-0.000, 0.500,0.500,0.500, -0.000,-0.951,-0.309,
0.250,-0.526,-0.000, 0.500,0.500,0.500, -0.000,-0.951,-0.309,
0.250,-0.526,-0.000, 0.500,0.500,0.500, 0.000,-0.951,0.309,
0.250,-0.425,0.309, 0.500,0.500,0.500, 0.000,-0.951,0.309,
-0.250,-0.526,-0.000, 0.500,0.500,0.500, 0.000,-0.951,0.309,
-0.250,-0.526,-0.000, 0.500,0.500,0.500, 0.000,-0.951,0.309,
-0.250,-0.425,0.309, 0.500,0.500,0.500, 0.000,-0.951,0.309,
0.250,-0.425,0.309, 0.500,0.500,0.500, 0.000,-0.951,0.309,
0.250,-0.425,0.309, 0.500,0.500,0.500, 0.000,-0.588,0.809,
0.250,-0.162,0.500, 0.500,0.500,0.500, 0.000,-0.588,0.809,
-0.250,-0.425,0.309, 0.500,0.500,0.500, 0.000,-0.588,0.809,
-0.250,-0.425,0.309, 0.500,0.500,0.500, 0.000,-0.588,0.809,
-0.250,-0.162,0.500, 0.500,0.500,0.500, 0.000,-0.588,0.809,
0.250,-0.162,0.500, 0.500,0.500,0.500, 0.000,-0.588,0.809,
0.250,-0.162,0.500, 0.500,0.500,0.500, 0.000,-0.000,1.000,
0.250,0.162,0.500, 0.500,0.500,0.500, 0.000,-0.000,1.000,
-0.250,-0.162,0.500, 0.500,0.500,0.500, 0.000,-0.000,1.000,
-0.250,-0.162,0.500, 0.500,0.500,0.500, 0.000,-0.000,1.000,
-0.250,0.162,0.500, 0.500,0.500,0.500, 0.000,-0.000,1.000,
0.250,0.162,0.500, 0.500,0.500,0.500, 0.000,-0.000,1.000
};

#endif
