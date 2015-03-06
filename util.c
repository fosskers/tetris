#include <stdlib.h>

#include "util.h"
#include "cog/dbg.h"

// --- //

/* Append one GLfloat Array to another */
GLfloat* append(GLfloat* l1, int l1s, GLfloat* l2, int l2s) {
        GLfloat* new = NULL;
        int i;

        check(l1 && l2, "Null Lists given.");

        new = malloc(sizeof(GLfloat) * (l1s + l2s));
        check_mem(new);

        // Copy values
        for(i = 0; i < l1s; i++) {
                new[i]= l1[i];
        }

        for(i = 0; i < l2s; i++) {
                new[l1s + i] = l2[i];
        }

        return new;
 error:
        return NULL;
}
