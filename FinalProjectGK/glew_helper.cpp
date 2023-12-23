#include "glew_helper.h"
#include <glut.h>
#include <glew.h>
#include <cstdio>
#include <cstdlib>
void initGLEW()
{
    GLenum err = glewInit();
    if (GLEW_OK != err)
    {
        fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
        exit(1);
    }
}
