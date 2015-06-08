#ifndef __score_h__
#define __score_h__

/* Data here was generated with:
 * https://github.com/fosskers/playground/blob/master/haskell/points.hs
 */

#include <GL/glew.h>

// --- //

#define PRISM_FLOATS 720

GLfloat prism[PRISM_FLOATS] = {
        /* Right Face */
        0.25,0.16245984,0.5,0.5,0.5,0.5,
        0.25,0.42532536,0.309017,0.5,0.5,0.5,
        0.25,0.0,0.0,0.5,0.5,0.5,
        0.25,0.42532536,0.309017,0.5,0.5,0.5,
        0.25,0.5257311,3.9691592e-8,0.5,0.5,0.5,
        0.25,0.0,0.0,0.5,0.5,0.5,
        0.25,0.5257311,3.9691592e-8,0.5,0.5,0.5,
        0.25,0.4253254,-0.30901694,0.5,0.5,0.5,
        0.25,0.0,0.0,0.5,0.5,0.5,
        0.25,0.4253254,-0.30901694,0.5,0.5,0.5,
        0.25,0.16245987,-0.49999997,0.5,0.5,0.5,
        0.25,0.0,0.0,0.5,0.5,0.5,
        0.25,0.16245987,-0.49999997,0.5,0.5,0.5,
        0.25,-0.16245984,-0.5,0.5,0.5,0.5,
        0.25,0.0,0.0,0.5,0.5,0.5,
        0.25,-0.16245984,-0.5,0.5,0.5,0.5,
        0.25,-0.4253253,-0.30901706,0.5,0.5,0.5,
        0.25,0.0,0.0,0.5,0.5,0.5,
        0.25,-0.4253253,-0.30901706,0.5,0.5,0.5,
        0.25,-0.5257311,-2.4441886e-7,0.5,0.5,0.5,
        0.25,0.0,0.0,0.5,0.5,0.5,
        0.25,-0.5257311,-2.4441886e-7,0.5,0.5,0.5,
        0.25,-0.4253256,0.3090167,0.5,0.5,0.5,
        0.25,0.0,0.0,0.5,0.5,0.5,
        0.25,-0.4253256,0.3090167,0.5,0.5,0.5,
        0.25,-0.1624603,0.49999982,0.5,0.5,0.5,
        0.25,0.0,0.0,0.5,0.5,0.5,
        0.25,-0.1624603,0.49999982,0.5,0.5,0.5,
        0.25,0.16245928,0.5000001,0.5,0.5,0.5,
        0.25,0.0,0.0,0.5,0.5,0.5,
        /* Left Face */
        -0.25,0.16245984,0.5,0.5,0.5,0.5,
        -0.25,0.42532536,0.309017,0.5,0.5,0.5,
        -0.25,0.0,0.0,0.5,0.5,0.5,
        -0.25,0.42532536,0.309017,0.5,0.5,0.5,
        -0.25,0.5257311,3.9691592e-8,0.5,0.5,0.5,
        -0.25,0.0,0.0,0.5,0.5,0.5,
        -0.25,0.5257311,3.9691592e-8,0.5,0.5,0.5,
        -0.25,0.4253254,-0.30901694,0.5,0.5,0.5,
        -0.25,0.0,0.0,0.5,0.5,0.5,
        -0.25,0.4253254,-0.30901694,0.5,0.5,0.5,
        -0.25,0.16245987,-0.49999997,0.5,0.5,0.5,
        -0.25,0.0,0.0,0.5,0.5,0.5,
        -0.25,0.16245987,-0.49999997,0.5,0.5,0.5,
        -0.25,-0.16245984,-0.5,0.5,0.5,0.5,
        -0.25,0.0,0.0,0.5,0.5,0.5,
        -0.25,-0.16245984,-0.5,0.5,0.5,0.5,
        -0.25,-0.4253253,-0.30901706,0.5,0.5,0.5,
        -0.25,0.0,0.0,0.5,0.5,0.5,
        -0.25,-0.4253253,-0.30901706,0.5,0.5,0.5,
        -0.25,-0.5257311,-2.4441886e-7,0.5,0.5,0.5,
        -0.25,0.0,0.0,0.5,0.5,0.5,
        -0.25,-0.5257311,-2.4441886e-7,0.5,0.5,0.5,
        -0.25,-0.4253256,0.3090167,0.5,0.5,0.5,
        -0.25,0.0,0.0,0.5,0.5,0.5,
        -0.25,-0.4253256,0.3090167,0.5,0.5,0.5,
        -0.25,-0.1624603,0.49999982,0.5,0.5,0.5,
        -0.25,0.0,0.0,0.5,0.5,0.5,
        -0.25,-0.1624603,0.49999982,0.5,0.5,0.5,
        -0.25,0.16245928,0.5000001,0.5,0.5,0.5,
        -0.25,0.0,0.0,0.5,0.5,0.5,
        /* Surrounding Edge */
        0.25,0.16245984,0.5,0.5,0.5,0.5,
        0.25,0.42532536,0.309017,0.5,0.5,0.5,
        -0.25,0.16245984,0.5,0.5,0.5,0.5,
        -0.25,0.16245984,0.5,0.5,0.5,0.5,
        -0.25,0.42532536,0.309017,0.5,0.5,0.5,
        0.25,0.42532536,0.309017,0.5,0.5,0.5,
        0.25,0.42532536,0.309017,0.5,0.5,0.5,
        0.25,0.5257311,3.9691592e-8,0.5,0.5,0.5,
        -0.25,0.42532536,0.309017,0.5,0.5,0.5,
        -0.25,0.42532536,0.309017,0.5,0.5,0.5,
        -0.25,0.5257311,3.9691592e-8,0.5,0.5,0.5,
        0.25,0.5257311,3.9691592e-8,0.5,0.5,0.5,
        0.25,0.5257311,3.9691592e-8,0.5,0.5,0.5,
        0.25,0.4253254,-0.30901694,0.5,0.5,0.5,
        -0.25,0.5257311,3.9691592e-8,0.5,0.5,0.5,
        -0.25,0.5257311,3.9691592e-8,0.5,0.5,0.5,
        -0.25,0.4253254,-0.30901694,0.5,0.5,0.5,
        0.25,0.4253254,-0.30901694,0.5,0.5,0.5,
        0.25,0.4253254,-0.30901694,0.5,0.5,0.5,
        0.25,0.16245987,-0.49999997,0.5,0.5,0.5,
        -0.25,0.4253254,-0.30901694,0.5,0.5,0.5,
        -0.25,0.4253254,-0.30901694,0.5,0.5,0.5,
        -0.25,0.16245987,-0.49999997,0.5,0.5,0.5,
        0.25,0.16245987,-0.49999997,0.5,0.5,0.5,
        0.25,0.16245987,-0.49999997,0.5,0.5,0.5,
        0.25,-0.16245984,-0.5,0.5,0.5,0.5,
        -0.25,0.16245987,-0.49999997,0.5,0.5,0.5,
        -0.25,0.16245987,-0.49999997,0.5,0.5,0.5,
        -0.25,-0.16245984,-0.5,0.5,0.5,0.5,
        0.25,-0.16245984,-0.5,0.5,0.5,0.5,
        0.25,-0.16245984,-0.5,0.5,0.5,0.5,
        0.25,-0.4253253,-0.30901706,0.5,0.5,0.5,
        -0.25,-0.16245984,-0.5,0.5,0.5,0.5,
        -0.25,-0.16245984,-0.5,0.5,0.5,0.5,
        -0.25,-0.4253253,-0.30901706,0.5,0.5,0.5,
        0.25,-0.4253253,-0.30901706,0.5,0.5,0.5,
        0.25,-0.4253253,-0.30901706,0.5,0.5,0.5,
        0.25,-0.5257311,-2.4441886e-7,0.5,0.5,0.5,
        -0.25,-0.4253253,-0.30901706,0.5,0.5,0.5,
        -0.25,-0.4253253,-0.30901706,0.5,0.5,0.5,
        -0.25,-0.5257311,-2.4441886e-7,0.5,0.5,0.5,
        0.25,-0.5257311,-2.4441886e-7,0.5,0.5,0.5,
        0.25,-0.5257311,-2.4441886e-7,0.5,0.5,0.5,
        0.25,-0.4253256,0.3090167,0.5,0.5,0.5,
        -0.25,-0.5257311,-2.4441886e-7,0.5,0.5,0.5,
        -0.25,-0.5257311,-2.4441886e-7,0.5,0.5,0.5,
        -0.25,-0.4253256,0.3090167,0.5,0.5,0.5,
        0.25,-0.4253256,0.3090167,0.5,0.5,0.5,
        0.25,-0.4253256,0.3090167,0.5,0.5,0.5,
        0.25,-0.1624603,0.49999982,0.5,0.5,0.5,
        -0.25,-0.4253256,0.3090167,0.5,0.5,0.5,
        -0.25,-0.4253256,0.3090167,0.5,0.5,0.5,
        -0.25,-0.1624603,0.49999982,0.5,0.5,0.5,
        0.25,-0.1624603,0.49999982,0.5,0.5,0.5,
        0.25,-0.1624603,0.49999982,0.5,0.5,0.5,
        0.25,0.16245984,0.5,0.5,0.5,0.5,
        -0.25,-0.1624603,0.49999982,0.5,0.5,0.5,
        -0.25,-0.1624603,0.49999982,0.5,0.5,0.5,
        -0.25,0.16245984,0.5,0.5,0.5,0.5,
        0.25,0.16245984,0.5,0.5,0.5,0.5
};
        
#endif
