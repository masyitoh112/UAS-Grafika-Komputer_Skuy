#include <freeglut.h>
#include <stdlib.h>
#include <math.h>
#include <iostream>
#include <glew.h>
#include "glew_helper.h"
#define DEG2RAD 3.14159 / 180.0
using namespace std;
int bubbleColor[3] = { 255, 255, 255 };
int bubbleCount = 500;
extern "C" void keyCallback(unsigned char key, int x, int y);
float x[10], buby[10] = { -.95 }, bubx = -3.14, r[10], offset[10], pos[10], z[10], yy[10], speed[10], sizee[10], grass[100], ff = -.6, tv[10] = { 0 };
int dx[10] = { 1 }, zx[10], ee[10];
int colors[10][3] = { {255, 165, 0},
                    {242, 38, 19},
                    {44, 62, 80},
                    {219, 10, 91},
                    {236, 236, 236},
                    {243, 156, 18},
                    {102, 51, 153},
                    {224, 130, 131},
                    {207, 0, 15},
                    {162, 222, 208} };

void circle(float x, float y, float r);
void DrawEllipse(float x, float y, float radiusX, float radiusY);
void DrawBubble(int i, float t);
void DrawGrass(int k, float t);
void DrawFish(int i, int c0[], float sc);
void ground();
void DrawRock(float x, float y, float size);
void DrawStarfish(float x, float y, float size);
void mainInit();
void keyCallback(unsigned char key, int x, int y);
void display();
int main(int argc, char** argv)
{
    mainInit();
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE);
    glutInitWindowSize(1280, 720);
    glutInitWindowPosition(50, 50);
    glutCreateWindow("Tugas Akhir Kelompok Grafika Skuy");
    initGLEW();
    glutDisplayFunc(display);
    glutKeyboardFunc(keyCallback);
    glutMainLoop();
}
void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(66 / 255., 161 / 255., 198 / 255., 1);
    glEnable(GL_BLEND);
    glEnable(GL_POLYGON_SMOOTH);
    glLineWidth(2);
    ground();

    DrawGrass(0, -0.95);
    DrawGrass(1, -0.90);
    DrawGrass(2, -0.85);
    DrawGrass(3, -0.90);
    DrawGrass(4, 0.1);
    DrawGrass(5, 0.15);
    DrawGrass(6, 0.2);

    for (int i = 0; i < 5; i++)
    {
        DrawFish(i, colors[i], sizee[i]);
        if (i < 10)
            DrawBubble(i, pos[i]);
    }

    glutPostRedisplay();
    glutSwapBuffers();
}
void initFish(int i)
{
    r[i] = (float)(rand() % 4 + 4) / 1000;
    offset[i] = (2 * (float)rand() / RAND_MAX) - 1;
    pos[i] = 2 * (float)rand() / RAND_MAX - 1;
    yy[i] = (rand() % (9 - (-7) + 1) + -7) / 10.0;
    sizee[i] = (float)(rand() % 5) / 10 + .3;
    speed[i] = (float)(rand() % 70) / 10000 + .001;
    z[i] = 0;
    zx[i] = 1;
    ee[i] = -10 + 2 * i;
    x[i] = (2 * (float)rand() / RAND_MAX) - 1;
    tv[i] = 0;
}
void initGrassAndBubble()
{
    ee[0] = -9;
    ee[1] = -10;
    ee[2] = -9;
    ee[3] = -10;
    ee[4] = -11;
    ee[5] = -8;
    ee[6] = -9;
    for (int i = 0; i < 100; i++)
        grass[i] = (rand() % 10 < 1) ? rand() % 10 : 0;
}
void DrawStarfish(float x, float y, float size)
{
    glPushMatrix();
    glTranslatef(x, y, 0);
    glScalef(size, size, 1);
    glColor3ub(255, 182, 193);
    DrawEllipse(0, 0, 0.1, 0.1);
    for (int i = 0; i < 5; i++)
    {
        glRotatef(72, 0, 0, 1);
        glBegin(GL_TRIANGLES);
        glVertex2f(0, 0);
        glVertex2f(0.25, 0);
        glVertex2f(0.1, 0.7); 
        glEnd();
    }
    glPopMatrix();
}
void mainInit()
{
    srand(time(0));
    for (int i = 0; i < 10; i++)
        initFish(i);
    initGrassAndBubble();
}
void keyCallback(unsigned char key, int x, int y) {
    switch (key) {
    case '1':
        std::cout << "Case 1 executed" << std::endl;
        generateRandomColor(bubbleColor);
        break;

    case '2':
        for (int i = 0; i < 5; i++) {
            colors[i][0] = 255 - colors[i][0];
            colors[i][1] = 255 - colors[i][1];
            colors[i][2] = 255 - colors[i][2];
        }
        break;

    case '3':
        glClearColor(0.0, 0.0, 0.0, 1.0);
        break;
    }
}
void ground()
{
    glPushMatrix();
    glTranslatef(0, -.5, 0);
    glRotatef(50, 1, 0, 0);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glBegin(GL_POLYGON);
    glColor3f(66 / 255., 161 / 255., 198 / 255.);
    glVertex2d(-1, -0.25);
    glColor3ub(230, 126, 34);
    glVertex2d(-1, -1);
    glVertex2d(1, -1);
    glColor3f(66 / 255., 161 / 255., 198 / 255.);
    glVertex2d(1, -0.25);
    glEnd();

    DrawRock(-0.5, -0.7, 0.08);
    DrawRock(-0.8, -0.5, 0.12);
    DrawRock(0.5, -0.7, 0.1);

    DrawStarfish(-0.20, -0.5, 0.2);
    DrawStarfish(0.2, -0.6, 0.15);
    DrawStarfish(0.75, -0.65, 0.18);

    glPopMatrix();
}
void DrawRock(float x, float y, float size)
{
    glPushMatrix();
    glColor3ub(169, 169, 169); // Gray color
    glBegin(GL_POLYGON);
    glVertex2f(x - size, y);
    glVertex2f(x - size / 2, y + size);
    glVertex2f(x + size / 2, y + size);
    glVertex2f(x + size, y);
    glEnd();
    glPopMatrix();
}
void DrawFish(int i, int c0[], float sc)
{
    //body
    glPushMatrix();
    glColor3ub(c0[0], c0[1], c0[2]);
    if (dx[i] == 1)
    {
        glScalef(1, 1, 1);
        DrawEllipse(x[i], 0 + yy[i], .18 * sc, .12 * sc);
    }
    else
    {
        glScalef(-1, 1, 1);
        DrawEllipse(-x[i], 0 + yy[i], .18 * sc, .12 * sc);
    }
    glPopMatrix();

    //lower
    glPushMatrix();
    glTranslatef(0, +yy[i], 0);
    if (dx[i] == 1)
    {
        glScalef(1, 1, 1);
        glRotatef(40, 1, 0, 1);
        glTranslatef(x[i], 0, x[i]);
    }
    else
    {
        glScalef(-1, 1, 1);
        glRotatef(40, 1, 0, 1);
        glTranslatef(-x[i], 0, -x[i]);
    }
    DrawEllipse(-.17 * sc, .035 * sc, .1 * sc, .075 * sc);
    glPopMatrix();

    // upper
    glPushMatrix();
    glTranslatef(0, +yy[i], 0);
    if (dx[i] == 1)
    {
        glScalef(1, 1, 1);
        glRotatef(-40, 1, 0, 1);
        glTranslatef(x[i], 0, x[i]);
    }
    else
    {
        glScalef(-1, 1, 1);
        glRotatef(-40, 1, 0, 1);
        glTranslatef(-x[i], 0, -x[i]);
    }
    DrawEllipse(-.17 * sc, -.035 * sc, .1 * sc, .075 * sc);
    glPopMatrix();

    // eye
    glPushMatrix();
    glColor3f(1, 1, 1);
    if (dx[i] == 1)
    {
        glScalef(1, 1, 1);
        DrawEllipse(x[i] + .1 * sc, 0 + .03 * sc + yy[i], .025 * sc, .025 * sc);
        glColor3f(0, 0, 0);
        DrawEllipse(x[i] + .1 * sc, 0 + .03 * sc + yy[i], .01 * sc, .01 * sc);
    }
    else
    {
        glScalef(-1, 1, 1);
        DrawEllipse(-x[i] + .1 * sc, .03 * sc + yy[i], .025 * sc, .025 * sc);
        glColor3f(0, 0, 0);
        DrawEllipse(-x[i] + .1 * sc, .03 * sc + yy[i], .01 * sc, .01 * sc);
    }
    glPopMatrix();
    dx[i] = (x[i] > .87) ? -1 : (x[i] < -.87) ? 1 : dx[i];
    x[i] = (dx[i] == 1) ? x[i] + speed[i] : x[i] - speed[i];
}
void circle(float x, float y, float r)
{
    float t;
    glBegin(GL_POINTS);
    for (int i = -1000; i < 1000; i++)
    {
        t = i / 1000.0;
        glVertex2f(t + x, sqrt(r * r - t * t) + y);
        glVertex2f(t + x, -sqrt(r * r - t * t) + y);
    }
    glEnd();
}
void DrawEllipse(float x, float y, float radiusX, float radiusY)
{
    glBegin(GL_POLYGON);
    for (int i = 0; i < 360; i++)
    {
        glVertex2f(x + cos(i * DEG2RAD) * radiusX, y + sin(i * DEG2RAD) * radiusY);
    }
    glEnd();
}
void DrawGrass(int k, float t)
{
    glPushMatrix();
    glLineWidth(10);
    glBegin(GL_LINE_STRIP);
    float j = 0;
    for (int i = 0; i < 79 + ee[k]; j += 0.006, i++, tv[k] += 0.1)
    {
        glColor3f(109 / 255.0 - j, 154 / 255.0 + j, 109 / 255.0 - j);
        glVertex2f(t + sin(.9 * tv[k]) / 70 + z[k] * cos(.005 * tv[k]) / 70, (float)i / 150 - 1);
    }
    glEnd();
    glPopMatrix();
    z[k] += 0.001 * zx[k];
    zx[k] = (z[k] > 1.56) ? -1 : (z[k] < -1.56) ? 1 : zx[k];
}
void generateRandomColor(int color[3]) {
    color[0] = rand() % 256;
    color[1] = rand() % 256;
    color[2] = rand() % 256;
}
void DrawBubble(int i, float t) {
    glPushMatrix();
    float bubbleRadius = 0.03;
    if (i % 2 == 0) {
        glColor4ub(bubbleColor[0], bubbleColor[1], bubbleColor[2], .3);
        DrawEllipse(t + sin(bubx) / 20, buby[i] + offset[i], bubbleRadius, bubbleRadius);
        glColor3ub(bubbleColor[0], bubbleColor[1], bubbleColor[2]);
        glPointSize(1);
        glBegin(GL_POINTS);
        circle(t + sin(bubx) / 20, buby[i] + offset[i], bubbleRadius);
        glEnd();
    }
    else {
        glColor4ub(bubbleColor[0], bubbleColor[1], bubbleColor[2], .3);
        DrawEllipse(t + cos(bubx) / 20, buby[i] + offset[i], bubbleRadius, bubbleRadius);
        glColor3ub(bubbleColor[0], bubbleColor[1], bubbleColor[2]);
        glPointSize(1);
        glBegin(GL_POINTS);
        circle(t + cos(bubx) / 20, buby[i] + offset[i], bubbleRadius);
        glEnd();
    }
    glPopMatrix();
    buby[i] += r[i];
    if (buby[i] > 1.3) {
        buby[i] = -1.5;
        pos[i] = 2 * (float)rand() / RAND_MAX - 1;
    }
    bubx += 0.01;
}
void Drawcircle(float x, float y, float r, float n, bool f1, bool f2)
{
    float t;
    glBegin(GL_POINTS);
    for (int i = -n; i < n; i++)
    {
        t = i / 1000.0;
        if (f1)
            glVertex2f(t + x, sqrt(r * r - t * t) + y);
        if (f2)
            glVertex2f(t + x, -sqrt(r * r - t * t) + y);
    }
    glEnd();
}