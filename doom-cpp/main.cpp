//
//  main.cpp
//  doom-cpp
//
//  Created by Luciano Mantovani on 26/06/2024.
//

#include <math.h>
#include <stdio.h>
#include <GLUT/GLUT.h>

#define res 1                       // 0=160x120 1=360x240 4=640x480
#define SW 160*res                  // screen width
#define SH 120*res                  // screen height
#define SW2 (SW/2)                  // half of screen width
#define SH2 (SH/2)                  // half of screen height
#define pixelscale 4/res            // OpenGL pixel scale
#define GLSW (SW*pixelscale)        // OpenGL window width
#define GLSH (SH*pixelscale)        // OpenGL window height

typedef struct
{
    int fr1, fr2;                   // frame1, frame2, to create constante frame rate
} time; time T;

typedef struct {
    int w, a, s, d; // move up, left, down, up
    int sl, sr;     // strafe left, right
    int m;          // move up, down, look up, down
} keys; keys K;

void pixel(int x, int y, int c){ // draw a pixel at x/y with rgb
    int rgb[3];
    if (c==0) { rgb[0] = 255; rgb[1] = 255; rgb[2] = 0;} // yellow
    if (c==1) { rgb[0] = 160; rgb[1] = 160; rgb[2] = 0;} // yellow darker
    if (c==2) { rgb[0] = 0; rgb[1] = 255; rgb[2] = 0;} // Green
    if (c==3) { rgb[0] = 0; rgb[1] = 160; rgb[2] = 0;} // Green darker
    if (c==4) { rgb[0] = 0; rgb[1] = 255; rgb[2] = 255;} // Cyan
    if (c==5) { rgb[0] = 0; rgb[1] = 160; rgb[2] = 160;} // Cyan darker
    if (c==6) { rgb[0] = 160; rgb[1] = 100; rgb[2] = 0;} // Brown
    if (c==7) { rgb[0] = 110; rgb[1] = 50; rgb[2] = 0;} // Brown darker
    if (c==8) { rgb[0] = 0; rgb[1] = 60; rgb[2] = 130;} // Background

    /* draw pixels in OpenGL */
    glColor3ub(rgb[0], rgb[1], rgb[2]);
    glBegin(GL_POINTS);
    glVertex2i(x*pixelscale+2, y*pixelscale+2);
    glEnd();
}

void movePlayer(){
    // move up, down, left right
    if (K.a == 1 && K.m == 0) { printf("left\n"); }
    if (K.d == 1 && K.m == 0) { printf("right\n"); }
    if (K.s == 1 && K.m == 0) { printf("down\n"); }
    if (K.w == 1 && K.m == 0) { printf("up\n"); }
    
    // strafe left, right
    if (K.sr == 1 && K.m == 0) { printf("strafe right\n"); }
    if (K.sl == 1 && K.m == 0) { printf("strafe left\n"); }
    
    // move up, down, look up, down
    if (K.a == 1 && K.m == 1) { printf("look up\n"); }
    if (K.d == 1 && K.m == 1) { printf("look down\n"); }
    if (K.w == 1 && K.m == 1) { printf("move up\n"); }
    if (K.s == 1 && K.m == 1) { printf("move down\n"); }
    
}

void clearBackground()
{
    for (int x = 0; x < SW; x++)
        for (int y = 0; y < SH; y++)
            pixel(x, y, 8);
}

int tick;
void draw3D(){
    int c = 0;
    for (int y = 0; y < SH2; y++)
        for (int x = 0; x < SW2; x++){
            pixel(x, y, c);
            c+=1; if(c > 8) {c = 0; }
        }
    // frame rate
    tick = tick <= 20 ? tick + 1 : 0;
    pixel(SW2, SH2+tick, 0);
}

void display(){
    int x, y;
    if (T.fr1-T.fr2 >= 50){
        clearBackground();
        movePlayer();
        draw3D();
        T.fr2 = T.fr1;
        glutSwapBuffers();
        glutReshapeWindow(GLSW, GLSH); // prevent window scaling
    }
    
    T.fr1 = glutGet(GLUT_ELAPSED_TIME);
    printf("%i\n", glutGet(GLUT_ELAPSED_TIME/1000));
    glutPostRedisplay();
}

void KeysDown(unsigned char key, int x, int y){
    if(key == 'w' == 1) {K.w = 1;}
    if(key == 'a' == 1) {K.a = 1;}
    if(key == 's' == 1) {K.s = 1;}
    if(key == 'd' == 1) {K.d = 1;}
    if(key == ',' == 1) {K.sl = 1;}
    if(key == '.' == 1) {K.sr = 1;}
}
void KeysUp(unsigned char key, int x, int y){
    if(key == 'w' == 1) {K.w = 0;}
    if(key == 'a' == 1) {K.a = 0;}
    if(key == 's' == 1) {K.s = 0;}
    if(key == 'd' == 1) {K.d = 0;}
    if(key == ',' == 1) {K.sl = 0;}
    if(key == '.' == 1) {K.sr = 0;}
}

void init(){
    
}

int main (int argc, char* argv[]){
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowPosition(GLSW/2, GLSH/2);
    glutInitWindowSize(GLSW, GLSH);
    glutCreateWindow("");
    glPointSize(pixelscale);
    gluOrtho2D(0, GLSW, 0, GLSH);
    init();
    glutDisplayFunc(display);
    glutKeyboardFunc(KeysDown);
    glutKeyboardUpFunc(KeysUp);
    glutMainLoop();
    return 0;
}
