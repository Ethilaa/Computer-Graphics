#include <windows.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <cmath>
#include <ctime>
#include <iostream>

#define MAX_DROPS 200000
using namespace std;

//================================================================================
// Global Variables & State Management
//================================================================================

// Scene control flags
bool isNight = false;           // Toggles between day and night
bool isDoorWindowLight = false; // Toggles lights in houses
bool tentVisible = true;        // Toggles the visibility of the tent
bool rainOn = false;            // Toggles the rain effect
bool animationPaused = false;   // Pauses/resumes all animations

// Animation positions and angles
float upper_boat1_pos = 0.0f;   // Horizontal position for upper boat 1
float upper_boat2_pos = 0.0f;   // Horizontal position for upper boat 2
float lower_boat1_pos = 0.0f;   // Horizontal position for lower boat 1
float lower_boat2_pos = 0.0f;   // Horizontal position for lower boat 2
float cloud1_pos = 0.0f;        // Horizontal position for cloud 1
float cloud2_pos = 0.0f;        // Horizontal position for cloud 2
float cloud3_pos = 0.0f;        // Horizontal position for cloud 3
float bladeAngle = 0.0f;        // Rotation angle for the turbine blades
float plane_x = -20.0f;         // Horizontal position for the airplane

// Rain simulation variables
float dropX[MAX_DROPS];         // X coordinates of raindrops
float dropY[MAX_DROPS];         // Y coordinates of raindrops
float dropSpeed[MAX_DROPS];     // Speed of raindrops
int dropCount = 0;              // Current number of active raindrops
float globalRainSpeed = .20f;   // Universal speed for all raindrops

//================================================================================
// Initialization and Core Drawing Helpers
//================================================================================


void init() {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-20.00f, 20.00f, -10.00f, 15.00f, -1.00f, 1.00f);
    glMatrixMode(GL_MODELVIEW);
}

/**
 Animation Village-1
 */
void setDoorWindowColor() {
    if (isDoorWindowLight)
        glColor3ub(255, 223, 170); // Lit color
    else
        glColor3ub(0, 0, 0);      // Unlit color
}


void drawCircle(float radius, float xc, float yc, float r, float g, float b) {
    glBegin(GL_POLYGON);
    if (r == -1 && g == -1 && b == -1) {
        setDoorWindowColor();
    } else {
        glColor3f(r / 255.0f, g / 255.0f, b / 255.0f);
    }
    for (int i = 0; i < 200; i++) {
        float pi = 3.1416f;
        float angle = (i * 2.0f * pi) / 200.0f;
        float x = radius * cos(angle);
        float y = radius * sin(angle);
        glVertex2f(x + xc, y + yc);
    }
    glEnd();
}

//================================================================================
// Scene Object Drawing Functions
//================================================================================

//--------------------------------------------------------------------------------
// Background Elements (Sky, Sun, Moon, Clouds)
//--------------------------------------------------------------------------------

/**
 * Object ID: OBJ001
 */
void drawSky1() {
    if (isNight) {
        glBegin(GL_QUADS);
        glColor3ub(5, 14, 57); // Dark blue for night
        glVertex2f(-20.00f, 15.00f);
        glVertex2f(-20.00f, 1.20f);
        glVertex2f(20.00f, 1.20f);
        glVertex2f(20.00f, 15.00f);
        glEnd();
    } else {
        glBegin(GL_QUADS);
        glColor3ub(40, 130, 178); // Light blue for day
        glVertex2f(-20.00f, 15.00f);
        glVertex2f(-20.00f, 1.20f);
        glVertex2f(20.00f, 1.20f);
        glVertex2f(20.00f, 15.00f);
        glEnd();
    }
}

/**
 Object ID: OBJ002
 */
void drawSun1() {
    if (!isNight) {
        drawCircle(2.00f, 16.00f, 11.50f, 255.0f, 255.0f, 0.0f);
    }
}

/**
 * Object ID: OBJ003
 */
void drawMoon1() {
    if (isNight) {
        drawCircle(1.13f, -8.13f, 12.14f, 255.0f, 255.0f, 255.0f);
    }
}

/**
 * Object ID: OBJ004
  Animation Village-2
 */
void Clouds1() {
    glPushMatrix();
    glTranslatef(cloud1_pos, 0.0f, 0.0f);
    if (isNight) {
        drawCircle(1.2f, -14.0f, 13.0f, 90, 90, 110);
        drawCircle(1.0f, -13.0f, 13.2f, 90, 90, 110);
        drawCircle(1.0f, -15.0f, 13.2f, 90, 90, 110);
        drawCircle(0.7f, -13.7f, 12.3f, 90, 90, 110);
    }
    else {
        drawCircle(1.2f, -14.0f, 13.0f, 255, 255, 255);
        drawCircle(1.0f, -13.0f, 13.2f, 255, 255, 255);
        drawCircle(1.0f, -15.0f, 13.2f, 255, 255, 255);
        drawCircle(0.7f, -13.7f, 12.3f, 255, 255, 255);
    }
    glPopMatrix();
}

/**
 * Object ID: OBJ005
  Animation Village-3
 */
void Clouds2() {
    glPushMatrix();
    glTranslatef(cloud2_pos, 0.0f, 0.0f);
    if (isNight) {
        drawCircle(1.0f, -2.0f, 13.5f, 90, 90, 110);
        drawCircle(0.8f, -2.8f, 13.7f, 90, 90, 110);
        drawCircle(0.7f, -1.2f, 13.7f, 90, 90, 110);
        drawCircle(0.6f, -2.0f, 12.9f, 90, 90, 110);
    } else {
        drawCircle(1.0f, -2.0f, 13.5f, 255, 255, 255);
        drawCircle(0.8f, -2.8f, 13.7f, 255, 255, 255);
        drawCircle(0.7f, -1.2f, 13.7f, 255, 255, 255);
        drawCircle(0.6f, -2.0f, 12.9f, 255, 255, 255);
    }
    glPopMatrix();
}

/**

 * Object ID: OBJ006
  Animation Village-4
 */
void Clouds3() {
    glPushMatrix();
    glTranslatef(cloud3_pos, 0.0f, 0.0f);
    if (isNight) {
        drawCircle(1.1f, 10.0f, 12.8f, 90, 90, 110);
        drawCircle(0.8f, 10.9f, 13.0f, 90, 90, 110);
        drawCircle(0.6f, 9.2f, 13.1f, 90, 90, 110);
        drawCircle(0.7f, 10.2f, 12.1f, 90, 90, 110);
    } else {
        drawCircle(1.1f, 10.0f, 12.8f, 255, 255, 255);
        drawCircle(0.8f, 10.9f, 13.0f, 255, 255, 255);
        drawCircle(0.6f, 9.2f, 13.1f, 255, 255, 255);
        drawCircle(0.7f, 10.2f, 12.1f, 255, 255, 255);
    }
    glPopMatrix();
}


//--------------------------------------------------------------------------------
// Landscape Elements (Mountains, River, Ground Layers)
//--------------------------------------------------------------------------------

/**
 * Object ID: OBJ007
 */
void mountain1() {
    glBegin(GL_POLYGON);
    glColor3ub(165, 212, 196);
    glVertex2f(-20.00f, 10.16f);
    glVertex2f(-18.96f, 10.97f);
    glVertex2f(-18.67f, 11.07f);
    glVertex2f(-18.33f, 11.09f);
    glVertex2f(-18.00f, 11.00f);
    glVertex2f(-17.74f, 10.84f);
    glVertex2f(-17.57f, 10.66f);
    glVertex2f(-17.26f, 10.14f);
    glVertex2f(-17.03f, 9.94f);
    glVertex2f(-16.80f, 9.86f);
    glVertex2f(-16.54f, 9.83f);
    glVertex2f(-16.29f, 9.91f);
    glVertex2f(-12.73f, 12.96f);
    glVertex2f(-20.00f, 3.82f);
    glEnd();
}

/**
 * Object ID: OBJ008
 */
void mountain2() {
    glBegin(GL_POLYGON);
    glColor3ub(165, 201, 163);
    glVertex2f(-20.00f, 3.82f);
    glVertex2f(-12.73f, 12.96f);
    glVertex2f(-12.22f, 13.24f);
    glVertex2f(-11.73f, 13.36f);
    glVertex2f(-11.35f, 13.40f);
    glVertex2f(-10.91f, 13.37f);
    glVertex2f(-10.34f, 13.15f);
    glVertex2f(-7.90f, 9.38f);
    glVertex2f(-7.35f, 8.17f);
    glVertex2f(-6.81f, 5.28f);
    glEnd();
}

/**
 * Object ID: OBJ009
 */
void mountain3() {
    glBegin(GL_POLYGON);
    glColor3ub(164, 205, 173);
    glVertex2f(-6.81f, 5.28f);
    glVertex2f(-7.35f, 8.17f);
    glVertex2f(-7.90f, 9.38f);
    glVertex2f(-10.34f, 13.15f);
    glVertex2f(-8.13f, 12.13f);
    glVertex2f(-4.34f, 10.86f);
    glVertex2f(-1.82f, 9.18f);
    glVertex2f(-12.22f, 13.24f);
    glVertex2f(-0.16f, 7.33f);
    glVertex2f(0.97f, 6.83f);
    glVertex2f(2.72f, 6.65f);
    glVertex2f(3.43f, 6.55f);
    glVertex2f(4.13f, 6.25f);
    glVertex2f(5.76f, 4.66f);
    glVertex2f(7.00f, 4.00f);
    glVertex2f(8.98f, 3.63f);
    glVertex2f(11.05f, 2.47f);
    glVertex2f(11.09f, 1.20f);
    glVertex2f(4.60f, 1.20f);
    glVertex2f(2.69f, 2.94f);
    glVertex2f(1.75f, 3.37f);
    glVertex2f(0.84f, 3.89f);
    glVertex2f(-0.43f, 4.26f);
    glVertex2f(-1.41f, 4.40f);
    glVertex2f(-2.12f, 4.46f);
    glVertex2f(-3.50f, 4.50f);
    glVertex2f(-4.06f, 4.63f);
    glEnd();
}

/**
 * Object ID: OBJ010
 */
void mountain4() {
    glBegin(GL_POLYGON);
    glColor3ub(165, 211, 191);
    glVertex2f(-4.34f, 10.86f);
    glVertex2f(-1.82f, 9.18f);
    glVertex2f(-12.22f, 13.24f);
    glVertex2f(-0.16f, 7.33f);
    glVertex2f(0.97f, 6.83f);
    glVertex2f(2.72f, 6.65f);
    glVertex2f(3.43f, 6.55f);
    glVertex2f(4.13f, 6.25f);
    glVertex2f(5.76f, 4.66f);
    glVertex2f(7.00f, 4.00f);
    glVertex2f(8.98f, 3.63f);
    glVertex2f(11.05f, 2.47f);
    glVertex2f(16.42f, 2.48f);
    glVertex2f(13.12f, 3.52f);
    glVertex2f(12.81f, 3.81f);
    glVertex2f(12.52f, 4.17f);
    glVertex2f(12.00f, 4.50f);
    glVertex2f(10.76f, 4.97f);
    glVertex2f(8.98f, 5.38f);
    glVertex2f(8.66f, 5.55f);
    glVertex2f(7.72f, 6.31f);
    glVertex2f(6.68f, 7.10f);
    glVertex2f(6.07f, 7.45f);
    glVertex2f(5.41f, 7.73f);
    glVertex2f(2.91f, 7.95f);
    glVertex2f(1.79f, 8.16f);
    glVertex2f(1.05f, 8.42f);
    glVertex2f(0.33f, 8.94f);
    glVertex2f(-1.40f, 9.77f);
    glEnd();
}

/**

 * Object ID: OBJ011
 */
void drawRiver1() {
    glBegin(GL_QUADS);
    glColor3ub(70, 153, 164);
    glVertex2f(-20.00f, -10.00f);
    glVertex2f(20.00f, -10.00f);
    glVertex2f(20.00f, 1.20f);
    glVertex2f(-20.00f, 1.20f);
    glEnd();
}

/**
 Object ID: OBJ012
 */
void backside_Field_Left() {
    glBegin(GL_POLYGON);
    glColor3ub(80, 110, 65);
    glVertex2f(-20.00f, 1.20f);
    glVertex2f(4.60f, 1.21f);
    glVertex2f(2.69f, 2.95f);
    glVertex2f(1.75f, 3.38f);
    glVertex2f(0.84f, 3.9f);
    glVertex2f(-0.43f, 4.27f);
    glVertex2f(-1.41f, 4.41f);
    glVertex2f(-2.12f, 4.47f);
    glVertex2f(-3.50f, 4.51f);
    glVertex2f(-4.06f, 4.63f);
    glVertex2f(-4.78f, 4.81f);
    glVertex2f(-6.81f, 5.29f);
    glVertex2f(-8.50f, 5.51f);
    glVertex2f(-11.33f, 5.63f);
    glVertex2f(-13.80f, 5.81f);
    glVertex2f(-15.46f, 5.95f);
    glVertex2f(-16.32f, 6.1f);
    glVertex2f(-18.95f, 6.61f);
    glVertex2f(-20.00f, 6.75f);
    glEnd();
}

/**
 *
 * Object IDs: OBJ013
 */
void backside_Field_With_Trees_Right() {
    // Main field polygon
    glColor3ub(127, 155, 70);
    glBegin(GL_POLYGON);
    glVertex2f(2.69f, 2.95f);
    glVertex2f(4.60f, 1.21f);
    glVertex2f(20.00f, 1.21f);
    glVertex2f(20.00f, 3.36f);
    glVertex2f(16.57f, 3.26f);
    glVertex2f(11.23f, 2.92f);
    glVertex2f(8.68f, 2.69f);
    glVertex2f(6.12f, 3.41f);
    glEnd();

    // Trees on the backside field
    glColor3ub(93, 134, 66);
    // Tree 1
    glBegin(GL_POLYGON);
    glVertex2f(4.02f, 3.22f);
    glVertex2f(3.65f, 2.90f);
    glVertex2f(3.87f, 2.29f);
    glVertex2f(3.75f, 1.84f);
    glVertex2f(4.26f, 1.41f);
    glVertex2f(4.89f, 1.73f);
    glVertex2f(5.08f, 2.70f);
    glVertex2f(4.31f, 3.23f);
    glEnd();
    // Tree 2
    glBegin(GL_POLYGON);
    glVertex2f(5.46f, 3.75f);
    glVertex2f(5.08f, 2.70f);
    glVertex2f(4.89f, 1.73f);
    glVertex2f(5.08f, 1.49f);
    glVertex2f(5.60f, 1.52f);
    glVertex2f(5.95f, 1.76f);
    glVertex2f(5.89f, 2.50f);
    glEnd();
    // Tree 3
    glBegin(GL_POLYGON);
    glVertex2f(6.22f, 3.29f);
    glVertex2f(5.89f, 2.50f);
    glVertex2f(5.95f, 1.76f);
    glVertex2f(5.60f, 1.52f);
    glVertex2f(6.09f, 1.32f);
    glVertex2f(6.58f, 1.42f);
    glVertex2f(6.50f, 2.00f);
    glVertex2f(6.41f, 2.66f);
    glVertex2f(6.22f, 3.29f);
    glEnd();
    // Tree 4
    glBegin(GL_POLYGON);
    glVertex2f(7.27f, 3.82f);
    glVertex2f(6.63f, 2.39f);
    glVertex2f(7.40f, 1.49f);
    glVertex2f(8.21f, 2.18f);
    glVertex2f(7.88f, 2.78f);
    glEnd();
    // Tree 5
    glBegin(GL_POLYGON);
    glVertex2f(9.89f, 3.62f);
    glVertex2f(9.54f, 3.17f);
    glVertex2f(9.42f, 2.27f);
    glVertex2f(9.80f, 1.65f);
    glVertex2f(10.24f, 1.21f);
    glVertex2f(10.71f, 1.91f);
    glVertex2f(10.74f, 2.98f);
    glVertex2f(10.22f, 3.43f);
    glEnd();
    // Tree 6
    glBegin(GL_POLYGON);
    glVertex2f(11.95f, 3.27f);
    glVertex2f(11.70f, 2.76f);
    glVertex2f(11.58f, 2.16f);
    glVertex2f(11.49f, 1.42f);
    glVertex2f(11.73f, 1.36f);
    glVertex2f(12.06f, 1.33f);
    glVertex2f(12.31f, 1.39f);
    glVertex2f(12.23f, 1.99f);
    glVertex2f(12.17f, 2.63f);
    glEnd();
    // Tree 7
    glBegin(GL_POLYGON);
    glVertex2f(12.94f, 2.85f);
    glVertex2f(12.67f, 2.79f);
    glVertex2f(12.54f, 2.39f);
    glVertex2f(12.32f, 2.20f);
    glVertex2f(12.30f, 1.80f);
    glVertex2f(13.08f, 1.28f);
    glVertex2f(13.30f, 1.43f);
    glVertex2f(13.56f, 1.49f);
    glVertex2f(13.78f, 2.17f);
    glVertex2f(13.51f, 2.62f);
    glVertex2f(13.25f, 2.85f);
    glEnd();
    // Tree 8
    glBegin(GL_POLYGON);
    glVertex2f(14.50f, 4.00f);
    glVertex2f(14.22f, 3.47f);
    glVertex2f(14.05f, 2.79f);
    glVertex2f(13.90f, 2.30f);
    glVertex2f(13.81f, 1.88f);
    glVertex2f(13.89f, 1.46f);
    glVertex2f(14.30f, 1.45f);
    glVertex2f(14.46f, 1.25f);
    glVertex2f(15.00f, 1.50f);
    glVertex2f(15.04f, 2.15f);
    glVertex2f(14.98f, 2.50f);
    glVertex2f(14.81f, 3.33f);
    glVertex2f(14.50f, 4.00f);
    glEnd();
    // Tree 9
    glBegin(GL_POLYGON);
    glVertex2f(15.58f, 3.71f);
    glVertex2f(15.08f, 3.09f);
    glVertex2f(14.98f, 2.50f);
    glVertex2f(15.04f, 2.15f);
    glVertex2f(15.81f, 1.21f);
    glVertex2f(16.47f, 1.77f);
    glVertex2f(16.42f, 2.49f);
    glVertex2f(16.35f, 2.97f);
    glEnd();
    // Tree 10
    glBegin(GL_POLYGON);
    glVertex2f(17.00f, 4.00f);
    glVertex2f(16.69f, 3.75f);
    glVertex2f(16.59f, 3.51f);
    glVertex2f(16.35f, 2.97f);
    glVertex2f(16.47f, 1.77f);
    glVertex2f(16.79f, 1.55f);
    glVertex2f(17.43f, 1.78f);
    glVertex2f(17.50f, 2.59f);
    glVertex2f(17.38f, 2.92f);
    glEnd();
    // Tree 11
    glBegin(GL_POLYGON);
    glVertex2f(18.00f, 3.50f);
    glVertex2f(17.38f, 2.92f);
    glVertex2f(17.50f, 2.59f);
    glVertex2f(17.43f, 1.78f);
    glVertex2f(17.81f, 1.69f);
    glVertex2f(18.75f, 2.08f);
    glVertex2f(18.64f, 2.81f);
    glVertex2f(18.44f, 2.83f);
    glVertex2f(18.62f, 3.22f);
    glEnd();
}

/**
 * Object ID: OBJ014
 */
void drawMiddleGroundLayer1() {
    glBegin(GL_POLYGON);
    glColor3ub(133, 154, 61);
    glVertex2f(1.06f, 0.44f);
    glVertex2f(1.06f, -0.17f);
    glVertex2f(3.67f, -0.45f);
    glVertex2f(5.51f, -0.64f);
    glVertex2f(6.85f, -0.96f);
    glVertex2f(7.64f, -1.39f);
    glVertex2f(11.65f, -1.40f);
    glVertex2f(10.64f, -1.15f);
    glVertex2f(9.68f, -1.03f);
    glVertex2f(7.96f, -0.81f);
    glVertex2f(6.60f, -0.25f);
    glVertex2f(5.77f, -0.03f);
    glVertex2f(4.83f, 0.08f);
    glVertex2f(3.54f, 0.09f);
    glVertex2f(2.42f, 0.19f);
    glVertex2f(1.06f, 0.44f);
    glEnd();
}

/**

 * Object ID: OBJ015
 */
void drawMiddleGroundLayer2() {
    glBegin(GL_POLYGON);
    glColor3ub(108, 142, 66);
    glVertex2f(-5.61f, 1.31f);
    glVertex2f(-5.61f, 0.22f);
    glVertex2f(-4.29f, -0.09f);
    glVertex2f(-2.65f, -0.55f);
    glVertex2f(-0.94f, -0.66f);
    glVertex2f(0.05f, -0.72f);
    glVertex2f(1.23f, -0.93f);
    glVertex2f(2.43f, -1.31f);
    glVertex2f(4.06f, -1.41f);
    glVertex2f(7.64f, -1.39f);
    glVertex2f(6.85f, -0.96f);
    glVertex2f(5.51f, -0.64f);
    glVertex2f(3.67f, -0.45f);
    glVertex2f(1.06f, -0.17f);
    glVertex2f(0.68f, -0.11f);
    glVertex2f(0.1f, -0.01f);
    glVertex2f(0.03f, -0.00f);
    glVertex2f(-0.55f, 0.1f);
    glVertex2f(-0.93f, 0.16f);
    glVertex2f(-4.53f, 1.05f);
    glEnd();
}
/**
 * Object ID: OBJ016
 */
void drawMiddleGroundLayer3() {
    glBegin(GL_POLYGON);
    glColor3ub(83, 128, 69);
    glVertex2f(-10.85f, 0.86f);
    glVertex2f(-10.67f, 0.12f);
    glVertex2f(-10.67f, 0.11f);
    glVertex2f(-10.39f, -0.59f);
    glVertex2f(-10.24f, -1.34f);
    glVertex2f(-9.01f, -1.31f);
    glVertex2f(-7.41f, -1.37f);
    glVertex2f(-3.39f, -1.55f);
    glVertex2f(-2.41f, -1.51f);
    glVertex2f(-1.72f, -1.45f);
    glVertex2f(-0.87f, -1.47f);
    glVertex2f(-0.17f, -1.52f);
    glVertex2f(0.42f, -1.47f);
    glVertex2f(1.30f, -1.36f);
    glVertex2f(2.43f, -1.31f);
    glVertex2f(1.23f, -0.93f);
    glVertex2f(0.05f, -0.72f);
    glVertex2f(-0.94f, -0.66f);
    glVertex2f(-2.65f, -0.55f);
    glVertex2f(-4.29f, -0.09f);
    glVertex2f(-5.61f, 0.22f);
    glVertex2f(-6.15f, 0.29f);
    glVertex2f(-6.80f, 0.36f);
    glVertex2f(-7.42f, 0.43f);
    glVertex2f(-9.91f, 0.67f);
    glVertex2f(-10.38f, 0.75f);
    glVertex2f(-10.80f, 0.84f);
    glVertex2f(-10.85f, 0.86f);
    glEnd();
}

/**

 * Object ID: OBJ017
 */
void drawMiddleGroundLayer4() {
    glBegin(GL_POLYGON);
    glColor3ub(37, 75, 49);
    glVertex2f(-20.00f, -0.24f);
    glVertex2f(-20.00f, -1.67f);
    glVertex2f(6.41f, -1.66f);
    glVertex2f(4.06f, -1.41f);
    glVertex2f(2.43f, -1.31f);
    glVertex2f(0.42f, -1.47f);
    glVertex2f(-0.17f, -1.52f);
    glVertex2f(-0.87f, -1.47f);
    glVertex2f(-1.72f, -1.45f);
    glVertex2f(-2.41f, -1.51f);
    glVertex2f(-3.39f, -1.55f);
    glVertex2f(-7.41f, -1.37f);
    glVertex2f(-9.01f, -1.31f);
    glVertex2f(-10.24f, -1.34f);
    glVertex2f(-12.51f, -1.35f);
    glVertex2f(-13.90f, -1.28f);
    glVertex2f(-18.05f, -0.73f);
    glEnd();
}

/**
 * Object ID: OBJ018
 */
void drawFrontSideGround() {
    glBegin(GL_POLYGON);
    glColor3ub(126, 175, 52);
    glVertex2f(-11.90f, -10.00f);
    glVertex2f(20.00f, -10.00f);
    glVertex2f(20.00f, 2.41f);
    glVertex2f(19.96f, 2.40f);
    glVertex2f(18.75f, 2.07f);
    glVertex2f(17.02f, 1.36f);
    glVertex2f(16.31f, 0.86f);
    glVertex2f(14.90f, -0.11f);
    glVertex2f(13.11f, -1.00f);
    glVertex2f(11.08f, -1.69f);
    glVertex2f(9.40f, -1.94f);
    glVertex2f(6.04f, -2.56f);
    glVertex2f(3.89f, -3.32f);
    glVertex2f(1.57f, -4.71f);
    glVertex2f(0.53f, -5.13f);
    glVertex2f(-1.84f, -5.54f);
    glVertex2f(-3.28f, -5.94f);
    glVertex2f(-4.50f, -6.50f);
    glVertex2f(-5.05f, -6.75f);
    glVertex2f(-6.01f, -7.44f);
    glVertex2f(-6.12f, -7.52f);
    glVertex2f(-6.74f, -7.97f);
    glVertex2f(-6.90f, -8.08f);
    glVertex2f(-7.32f, -8.38f);
    glVertex2f(-7.98f, -8.63f);
    glVertex2f(-10.11f, -8.94f);
    glVertex2f(-11.07f, -9.32f);
    glEnd();
}

/**

 * Object ID: OBJ019
 */
void middle_ground_trees1() {
    glBegin(GL_POLYGON);
    glColor3ub(127, 155, 70);
    glVertex2f(-3.04f, 3.37f);
    glVertex2f(-3.28f, 2.51f);
    glVertex2f(-3.05f, 2.47f);
    glVertex2f(-2.85f, 2.55f);
    glVertex2f(-2.87f, 2.69f);
    glVertex2f(-2.93f, 3.04f);
    glEnd();
    glBegin(GL_POLYGON);
    glColor3ub(127, 155, 70);
    glVertex2f(-2.63f, 3.69f);
    glVertex2f(-2.73f, 3.57f);
    glVertex2f(-2.93f, 3.04f);
    glVertex2f(-2.87f, 2.69f);
    glVertex2f(-2.72f, 2.52f);
    glVertex2f(-2.49f, 2.56f);
    glVertex2f(-2.35f, 2.82f);
    glVertex2f(-2.39f, 3.09f);
    glVertex2f(-2.49f, 3.51f);
    glEnd();
    glBegin(GL_POLYGON);
    glColor3ub(127, 155, 70);
    glVertex2f(-2.07f, 3.77f);
    glVertex2f(-2.22f, 3.37f);
    glVertex2f(-2.35f, 2.82f);
    glVertex2f(-2.32f, 2.57f);
    glVertex2f(-1.87f, 2.54f);
    glVertex2f(-1.76f, 2.87f);
    glEnd();
    glBegin(GL_POLYGON);
    glColor3ub(127, 155, 70);
    glVertex2f(-1.66f, 3.39f);
    glVertex2f(-1.76f, 2.87f);
    glVertex2f(-1.87f, 2.54f);
    glVertex2f(-1.68f, 2.46f);
    glVertex2f(-1.46f, 2.49f);
    glVertex2f(-1.47f, 2.59f);
    glVertex2f(-1.50f, 2.83f);
    glVertex2f(-1.53f, 3.10f);
    glEnd();
}

/**

 *Object ID: OBJ020
 */
void middle_ground_trees2() {
    glBegin(GL_POLYGON);
    glColor3ub(127, 155, 70);
    glVertex2f(-5.53f, 4.24f);
    glVertex2f(-5.62f, 4.12f);
    glVertex2f(-5.83f, 3.64f);
    glVertex2f(-5.80f, 3.27f);
    glVertex2f(-5.65f, 3.10f);
    glVertex2f(-5.39f, 3.09f);
    glVertex2f(-5.26f, 3.47f);
    glVertex2f(-5.33f, 3.89f);
    glEnd();
    glBegin(GL_POLYGON);
    glColor3ub(127, 155, 70);
    glVertex2f(-5.12f, 3.92f);
    glVertex2f(-5.26f, 3.47f);
    glVertex2f(-5.39f, 3.09f);
    glVertex2f(-5.13f, 3.01f);
    glVertex2f(-4.93f, 3.05f);
    glVertex2f(-4.51f, 3.08f);
    glVertex2f(-4.62f, 3.52f);
    glVertex2f(-4.68f, 3.86f);
    glVertex2f(-4.78f, 4.03f);
    glVertex2f(-4.96f, 3.40f);
    glEnd();
}

/**

 * Object ID: OBJ021
 */
void drawMiddleTree1() {
    glBegin(GL_POLYGON);
    glColor3ub(49, 149, 65);
    glVertex2f(-13.50f, 1.39f);
    glVertex2f(-13.15f, 0.95f);
    glVertex2f(-12.80f, 0.15f);
    glVertex2f(-12.45f, -1.67f);
    glVertex2f(-10.17f, -1.69f);
    glVertex2f(-10.39f, -0.59f);
    glVertex2f(-10.67f, 0.10f);
    glVertex2f(-11.02f, 1.57f);
    glVertex2f(-11.11f, 1.91f);
    glVertex2f(-11.34f, 2.41f);
    glVertex2f(-11.49f, 3.18f);
    glVertex2f(-11.58f, 3.34f);
    glVertex2f(-11.82f, 3.92f);
    glVertex2f(-11.84f, 4.52f);
    glVertex2f(-11.92f, 5.00f);
    glVertex2f(-12.00f, 5.20f);
    glVertex2f(-12.05f, 5.26f);
    glVertex2f(-12.10f, 5.25f);
    glVertex2f(-12.22f, 5.12f);
    glVertex2f(-12.36f, 4.80f);
    glVertex2f(-12.43f, 4.38f);
    glVertex2f(-12.49f, 4.14f);
    glVertex2f(-12.80f, 3.40f);
    glVertex2f(-12.82f, 3.26f);
    glVertex2f(-12.85f, 2.66f);
    glVertex2f(-13.14f, 2.16f);
    glEnd();
}

/**

 * Object ID: OBJ022
 */
void drawMiddleTree2() {
    glBegin(GL_POLYGON);
    glColor3ub(38, 125, 55);
    glVertex2f(-16.41f, 2.04f);
    glVertex2f(-16.21f, 1.69f);
    glVertex2f(-16.08f, 1.35f);
    glVertex2f(-16.00f, 1.00f);
    glVertex2f(-16.02f, 0.25f);
    glVertex2f(-15.96f, -0.11f);
    glVertex2f(-15.77f, -0.51f);
    glVertex2f(-15.60f, -0.83f);
    glVertex2f(-15.55f, -1.10f);
    glVertex2f(-15.46f, -1.68f);
    glVertex2f(-12.45f, -1.67f);
    glVertex2f(-12.80f, 0.15f);
    glVertex2f(-13.15f, 0.95f);
    glVertex2f(-13.50f, 1.39f);
    glVertex2f(-13.75f, 2.17f);
    glVertex2f(-13.82f, 3.39f);
    glVertex2f(-13.92f, 3.86f);
    glVertex2f(-14.15f, 4.46f);
    glVertex2f(-14.22f, 4.83f);
    glVertex2f(-14.34f, 5.23f);
    glVertex2f(-14.63f, 5.80f);
    glVertex2f(-14.75f, 6.20f);
    glVertex2f(-14.85f, 6.37f);
    glVertex2f(-14.96f, 6.49f);
    glVertex2f(-15.03f, 6.51f);
    glVertex2f(-15.13f, 6.50f);
    glVertex2f(-15.19f, 6.46f);
    glVertex2f(-15.25f, 6.35f);
    glVertex2f(-15.30f, 6.00f);
    glVertex2f(-15.41f, 5.52f);
    glVertex2f(-15.85f, 4.54f);
    glVertex2f(-15.90f, 3.95f);
    glVertex2f(-16.02f, 3.32f);
    glEnd();
}

/**

 * Object ID: OBJ023
 */
void drawMiddleTree3() {
    glBegin(GL_POLYGON);
    glColor3ub(60, 100, 36);
    glVertex2f(-20.00f, 1.59f);
    glVertex2f(-19.41f, 2.85f);
    glVertex2f(-19.36f, 4.40f);
    glVertex2f(-19.00f, 5.65f);
    glVertex2f(-18.80f, 6.20f);
    glVertex2f(-18.77f, 6.35f);
    glVertex2f(-18.72f, 6.67f);
    glVertex2f(-18.65f, 7.48f);
    glVertex2f(-18.58f, 7.68f);
    glVertex2f(-18.45f, 7.76f);
    glVertex2f(-18.31f, 7.74f);
    glVertex2f(-18.26f, 7.70f);
    glVertex2f(-18.13f, 7.44f);
    glVertex2f(-17.84f, 6.48f);
    glVertex2f(-17.61f, 6.17f);
    glVertex2f(-17.46f, 5.79f);
    glVertex2f(-17.38f, 5.42f);
    glVertex2f(-17.32f, 4.82f);
    glVertex2f(-17.17f, 4.36f);
    glVertex2f(-16.66f, 3.63f);
    glVertex2f(-16.59f, 3.42f);
    glVertex2f(-16.53f, 3.18f);
    glVertex2f(-16.51f, 2.76f);
    glVertex2f(-16.51f, 2.21f);
    glVertex2f(-16.50f, 2.20f);
    glVertex2f(-16.41f, 2.04f);
    glVertex2f(-16.21f, 1.69f);
    glVertex2f(-16.08f, 1.35f);
    glVertex2f(-16.00f, 1.00f);
    glVertex2f(-15.96f, -0.11f);
    glVertex2f(-15.77f, -0.51f);
    glVertex2f(-15.60f, -0.83f);
    glVertex2f(-15.55f, -1.10f);
    glVertex2f(-18.05f, -0.74f);
    glVertex2f(-20.00f, -0.25f);
    glEnd();
}

/**

 * Object ID: OBJ024
 */
void big_house1() {
    //roof
    glBegin(GL_POLYGON);
    glColor3ub(190, 82, 53);
    glVertex2f(-6.51f, 3.43f);
    glVertex2f(-10.41f, 3.46f);
    glVertex2f(-11.11f, 1.91f);
    glVertex2f(-11.02f, 1.57f);
    glVertex2f(-7.41f, 1.62f);
    glEnd();
    // wall
    glBegin(GL_QUADS);
    glColor3ub(217, 135, 111);
    glVertex2f(-11.02f, 1.57f);
    glVertex2f(-10.85f, 0.84f);
    glVertex2f(-7.42f, 0.42f);
    glVertex2f(-7.41f, 1.62f);
    glEnd();
    // left side
    glBegin(GL_POLYGON);
    glColor3ub(251, 239, 223);
    glVertex2f(-6.51f, 3.43f);
    glVertex2f(-7.41f, 1.62f);
    glVertex2f(-7.42f, 0.42f);
    glVertex2f(-5.61f, 0.22f);
    glVertex2f(-5.62f, 1.69f);
    glEnd();
    // windows
    glBegin(GL_QUADS);
    setDoorWindowColor();
    glVertex2f(-8.30f, 1.10f);
    glVertex2f(-8.30f, 0.75f);
    glVertex2f(-7.90f, 0.75f);
    glVertex2f(-7.90f, 1.10f);
    glEnd();
    glBegin(GL_QUADS);
    setDoorWindowColor();
    glVertex2f(-9.10f, 1.10f);
    glVertex2f(-9.10f, 0.75f);
    glVertex2f(-8.70f, 0.75f);
    glVertex2f(-8.70f, 1.10f);
    glEnd();
    glBegin(GL_QUADS);
    setDoorWindowColor();
    glVertex2f(-9.95f, 1.10f);
    glVertex2f(-9.95f, 0.75f);
    glVertex2f(-9.55f, 0.75f);
    glVertex2f(-9.55f, 1.10f);
    glEnd();
    glBegin(GL_QUADS);
    setDoorWindowColor();
    glVertex2f(-10.80f, 1.10f);
    glVertex2f(-10.80f, 0.83f);
    glVertex2f(-10.38f, 0.75f);
    glVertex2f(-10.38f, 1.10f);
    glEnd();
    //chimney
    glBegin(GL_QUADS);
    glColor3ub(217, 135, 111);
    glVertex2f(-10.16f, 3.86f);
    glVertex2f(-10.16f, 3.09f);
    glVertex2f(-9.72f, 3.09f);
    glVertex2f(-9.72f, 3.86f);
    glEnd();
    //chimney wall
    glBegin(GL_QUADS);
    glColor3ub(250, 239, 221);
    glVertex2f(-9.72f, 3.86f);
    glVertex2f(-9.72f, 3.09f);
    glVertex2f(-9.46f, 3.33f);
    glVertex2f(-9.47f, 3.86f);
    glEnd();
    //circle_windows
    drawCircle(0.22, -6.5, 2.12, -1, -1, -1);
    //front door
    glBegin(GL_QUADS);
    setDoorWindowColor();
    glVertex2f(-6.80f, 1.11f);
    glVertex2f(-6.80f, 0.36f);
    glVertex2f(-6.15f, 0.29f);
    glVertex2f(-6.15f, 1.11f);
    glEnd();
}

/**

 * Object ID: OBJ025
 */
void little_house1() {
    glColor3ub(190, 82, 53);
    glBegin(GL_POLYGON);
    glVertex2f(-8.20f, 5.15f);
    glVertex2f(-8.40f, 4.70f);
    glVertex2f(-8.00f, 4.70f);
    glVertex2f(-7.77f, 5.15f);
    glEnd();
    glColor3ub(217, 135, 111);
    glBegin(GL_POLYGON);
    glVertex2f(-8.40f, 4.70f);
    glVertex2f(-8.40f, 4.20f);
    glVertex2f(-8.00f, 4.20f);
    glVertex2f(-8.00f, 4.70f);
    glEnd();
    glColor3ub(251, 239, 223);
    glBegin(GL_POLYGON);
    glVertex2f(-7.77f, 5.15f);
    glVertex2f(-8.00f, 4.70f);
    glVertex2f(-8.00f, 4.20f);
    glVertex2f(-7.60f, 4.22f);
    glVertex2f(-7.60f, 4.70f);
    glEnd();
    setDoorWindowColor();
    glBegin(GL_POLYGON);
    glVertex2f(-8.15f, 4.60f);
    glVertex2f(-8.15f, 4.40f);
    glVertex2f(-8.05f, 4.40f);
    glVertex2f(-8.05f, 4.60f);
    glEnd();
    setDoorWindowColor();
    glBegin(GL_POLYGON);
    glVertex2f(-8.30f, 4.60f);
    glVertex2f(-8.30f, 4.40f);
    glVertex2f(-8.20f, 4.40f);
    glVertex2f(-8.20f, 4.60f);
    glEnd();
    setDoorWindowColor();
    glBegin(GL_POLYGON);
    glVertex2f(-7.84f, 4.56f);
    glVertex2f(-7.84f, 4.22f);
    glVertex2f(-7.77f, 4.22f);
    glVertex2f(-7.70f, 4.56f);
    glEnd();
}

/**

 * Object ID: OBJ026
 */
void little_house2() {
    glColor3ub(190, 82, 53);
    glBegin(GL_POLYGON);
    glVertex2f(-9.30f, 5.40f);
    glVertex2f(-9.40f, 5.20f);
    glVertex2f(-9.00f, 5.20f);
    glVertex2f(-8.90f, 5.40f);
    glEnd();
    glColor3ub(217, 135, 111);
    glBegin(GL_POLYGON);
    glVertex2f(-9.40f, 5.20f);
    glVertex2f(-9.40f, 4.84f);
    glVertex2f(-9.00f, 4.84f);
    glVertex2f(-9.00f, 5.20f);
    glEnd();
    glColor3ub(251, 239, 223);
    glBegin(GL_POLYGON);
    glVertex2f(-8.90f, 5.40f);
    glVertex2f(-9.00f, 5.20f);
    glVertex2f(-9.00f, 4.84f);
    glVertex2f(-8.80f, 4.85f);
    glEnd();
    setDoorWindowColor();
    glBegin(GL_POLYGON);
    glVertex2f(-8.95f, 5.05f);
    glVertex2f(-8.95f, 4.84f);
    glVertex2f(-8.85f, 4.85f);
    glVertex2f(-8.85f, 5.05f);
    glEnd();
}

/**

 * Object ID: OBJ0027
 */
void little_house3() {
    glColor3ub(190, 82, 53);
    glBegin(GL_POLYGON);
    glVertex2f(-11.10f, 5.45f);
    glVertex2f(-11.30f, 5.00f);
    glVertex2f(-10.90f, 5.00f);
    glVertex2f(-10.68f, 5.45f);
    glEnd();
    glColor3ub(217, 135, 111);
    glBegin(GL_POLYGON);
    glVertex2f(-11.30f, 5.00f);
    glVertex2f(-11.30f, 4.50f);
    glVertex2f(-10.90f, 4.50f);
    glVertex2f(-10.90f, 5.00f);
    glEnd();
    glColor3ub(251, 239, 223);
    glBegin(GL_POLYGON);
    glVertex2f(-10.68f, 5.45f);
    glVertex2f(-10.90f, 5.00f);
    glVertex2f(-10.90f, 4.50f);
    glVertex2f(-10.52f, 4.52f);
    glVertex2f(-10.52f, 5.00f);
    glEnd();
    setDoorWindowColor();
    glBegin(GL_POLYGON);
    glVertex2f(-11.05f, 4.85f);
    glVertex2f(-11.05f, 4.70f);
    glVertex2f(-10.95f, 4.70f);
    glVertex2f(-10.95f, 4.85f);
    glEnd();
    setDoorWindowColor();
    glBegin(GL_POLYGON);
    glVertex2f(-11.20f, 4.85f);
    glVertex2f(-11.20f, 4.70f);
    glVertex2f(-11.10f, 4.70f);
    glVertex2f(-11.10f, 4.85f);
    glEnd();
    setDoorWindowColor();
    glBegin(GL_POLYGON);
    glVertex2f(-10.75f, 4.80f);
    glVertex2f(-10.75f, 4.51f);
    glVertex2f(-10.65f, 4.51f);
    glVertex2f(-10.65f, 4.80f);
    glEnd();
}

/**

 * Object ID: OBJ028
 */
void little_house4() {
    glColor3ub(190, 82, 53);
    glBegin(GL_POLYGON);
    glVertex2f(-13.40f, 5.00f);
    glVertex2f(-13.50f, 4.80f);
    glVertex2f(-13.10f, 4.80f);
    glVertex2f(-13.00f, 5.00f);
    glEnd();
    glColor3ub(217, 135, 111);
    glBegin(GL_POLYGON);
    glVertex2f(-13.50f, 4.80f);
    glVertex2f(-13.50f, 4.40f);
    glVertex2f(-13.10f, 4.40f);
    glVertex2f(-13.10f, 4.80f);
    glEnd();
    glColor3ub(251, 239, 223);
    glBegin(GL_POLYGON);
    glVertex2f(-13.00f, 5.00f);
    glVertex2f(-13.10f, 4.80f);
    glVertex2f(-13.10f, 4.40f);
    glVertex2f(-12.87f, 4.41f);
    glVertex2f(-12.88f, 4.80f);
    glEnd();
    setDoorWindowColor();
    glBegin(GL_POLYGON);
    glVertex2f(-13.04f, 4.64f);
    glVertex2f(-13.04f, 4.44f);
    glVertex2f(-12.94f, 4.41f);
    glVertex2f(-12.94f, 4.64f);
    glEnd();
}

/**

 * Object ID: OBJ029
 */
void barn() {
    // side walls
    glBegin(GL_POLYGON);
    glColor3ub(217, 133, 111);
    glVertex2f(-0.92f, 0.83f);
    glVertex2f(-3.65f, 0.83f);
    glVertex2f(-0.93f, 0.16f);
    glEnd();
    // front wall
    glBegin(GL_POLYGON);
    glColor3ub(251, 239, 223);
    glVertex2f(1.06f, -0.17f);
    glVertex2f(1.06f, 0.44f);
    glVertex2f(1.05f, 0.72f);
    glVertex2f(0.97f, 0.99f);
    glVertex2f(0.84f, 1.21f);
    glVertex2f(0.60f, 1.40f);
    glVertex2f(0.34f, 1.47f);
    glVertex2f(-0.18f, 1.47f);
    glVertex2f(-0.38f, 1.44f);
    glVertex2f(-0.61f, 1.28f);
    glVertex2f(-0.79f, 1.09f);
    glVertex2f(-0.92f, 0.83f);
    glVertex2f(-0.93f, 0.16f);
    glEnd();
    // front doors
    glBegin(GL_POLYGON);
    setDoorWindowColor();
    glVertex2f(-0.55f, 0.57f);
    glVertex2f(-0.55f, 0.10f);
    glVertex2f(0.03f, 0.00f);
    glVertex2f(0.03f, 0.57f);
    glEnd();
    glBegin(GL_POLYGON);
    setDoorWindowColor();
    glVertex2f(0.10f, 0.57f);
    glVertex2f(0.10f, -0.01f);
    glVertex2f(0.68f, -0.11f);
    glVertex2f(0.69f, 0.57f);
    glEnd();
    // roof
    glBegin(GL_POLYGON);
    glColor3ub(189, 81, 51);
    glVertex2f(-4.02f, 1.47f);
    glVertex2f(-4.25f, 1.36f);
    glVertex2f(-4.44f, 1.18f);
    glVertex2f(-4.53f, 1.05f);
    glVertex2f(-3.65f, 0.83f);
    glVertex2f(-0.92f, 0.83f);
    glVertex2f(-0.79f, 1.09f);
    glVertex2f(-0.61f, 1.28f);
    glVertex2f(-0.38f, 1.44f);
    glVertex2f(-0.18f, 1.47f);
    glEnd();
    // chimneys
    glBegin(GL_POLYGON);
    glColor3ub(251, 237, 223);
    glVertex2f(-3.72f, 1.70f);
    glVertex2f(-3.72f, 1.47f);
    glVertex2f(-3.40f, 1.47f);
    glVertex2f(-3.40f, 1.70f);
    glEnd();
    glBegin(GL_POLYGON);
    glColor3ub(251, 237, 223);
    glVertex2f(-2.38f, 1.70f);
    glVertex2f(-2.38f, 1.47f);
    glVertex2f(-2.05f, 1.47f);
    glVertex2f(-2.05f, 1.70f);
    glEnd();
    glBegin(GL_POLYGON);
    glColor3ub(251, 237, 223);
    glVertex2f(-1.10f, 1.70f);
    glVertex2f(-1.10f, 1.47f);
    glVertex2f(-0.85f, 1.47f);
    glVertex2f(-0.85f, 1.70f);
    glEnd();
}

/**

 * Object ID: OBJ030
 */
void turbine(){
    // Draw static body
    glColor3ub(255, 255, 255);
    glBegin(GL_POLYGON);
    glVertex2f(-4.65f, 5.13f);
    glVertex2f(-4.84f, 0.82f);
    glVertex2f(-4.34f, 0.84f);
    glVertex2f(-4.53f, 5.13f);
    glEnd();

    // Animate blades around the hub
    glPushMatrix();
    glTranslatef(-4.59f, 5.17f, 0.0f);
    glRotatef(bladeAngle, 0.0f, 0.0f, 1.0f);
    glTranslatef(-(-4.59f), -5.17f, 0.0f);

    // 1st wing
    glColor3ub(255, 255, 255);
    glBegin(GL_POLYGON);
    glVertex2f(-4.59f, 5.17f);
    glVertex2f(-4.59f, 3.85f);
    glVertex2f(-4.50f, 4.95f);
    glEnd();
    // 2nd wing
    glBegin(GL_POLYGON);
    glVertex2f(-3.34f, 6.46f);
    glVertex2f(-4.59f, 5.17f);
    glVertex2f(-4.34f, 5.30f);
    glEnd();
    // 3rd wing
    glBegin(GL_POLYGON);
    glVertex2f(-5.86f, 6.46f);
    glVertex2f(-4.85f, 5.30f);
    glVertex2f(-4.59f, 5.17f);
    glEnd();

    glPopMatrix();
}

/**

 * Object ID: OBJ031
 */
void tent() {
    // front side
    glBegin(GL_POLYGON);
    glColor3ub(48, 89, 75);
    glVertex2f(6.84f, 0.24f);
    glVertex2f(4.52f, -2.81f);
    glVertex2f(4.68f, -2.87f);
    glVertex2f(4.08f, -5.24f);
    glVertex2f(9.47f, -5.56f);
    glVertex2f(9.26f, -2.92f);
    glVertex2f(9.42f, -2.92f);
    glEnd();
    // front side curtain
    glBegin(GL_POLYGON);
    glColor3ub(63, 106, 94);
    glVertex2f(6.81f, -0.45f);
    glVertex2f(6.41f, -1.67f);
    glVertex2f(6.35f, -1.85f);
    glVertex2f(6.04f, -2.56f);
    glVertex2f(5.83f, -3.01f);
    glVertex2f(5.24f, -3.91f);
    glVertex2f(4.73f, -4.49f);
    glVertex2f(5.85f, -5.34f);
    glVertex2f(6.80f, -0.71f);
    glVertex2f(7.10f, -5.42f);
    glVertex2f(8.72f, -4.58f);
    glVertex2f(7.64f, -2.99f);
    glVertex2f(7.15f, -1.83f);
    glEnd();
    // inside
    glBegin(GL_TRIANGLES);
    glColor3ub(0, 0, 0);
    glVertex2f(6.80f, -0.71f);
    glVertex2f(5.85f, -5.34f);
    glVertex2f(7.10f, -5.42f);
    glEnd();
    // side wall
    glBegin(GL_POLYGON);
    glColor3ub(34, 67, 56);
    glVertex2f(9.26f, -2.92f);
    glVertex2f(9.47f, -5.56f);
    glVertex2f(15.26f, -5.18f);
    glVertex2f(14.41f, -2.76f);
    glVertex2f(13.62f, -2.89f);
    glVertex2f(12.39f, -3.04f);
    glVertex2f(11.33f, -3.07f);
    glVertex2f(9.42f, -2.92f);
    glEnd();
    // roof
    glBegin(GL_POLYGON);
    glColor3ub(40, 78, 65);
    glVertex2f(14.56f, -2.76f);
    glVertex2f(12.42f, 0.18f);
    glVertex2f(11.24f, -0.17f);
    glVertex2f(10.63f, -0.25f);
    glVertex2f(9.85f, -0.28f);
    glVertex2f(8.82f, -0.23f);
    glVertex2f(7.72f, -0.01f);
    glVertex2f(6.84f, 0.24f);
    glVertex2f(9.42f, -2.92f);
    glVertex2f(11.33f, -3.07f);
    glVertex2f(12.39f, -3.04f);
    glVertex2f(13.62f, -2.89f);
    glVertex2f(14.41f, -2.76f);
    glEnd();
    //ropes
    glLineWidth(1.0f);
    glBegin(GL_LINES);
    glColor3ub(0, 0, 0);
    glVertex2f(4.52f, -2.80f);
    glVertex2f(2.43f, -5.12f);
    glVertex2f(9.42f, -2.91f);
    glVertex2f(12.01f, -5.71f);
    glVertex2f(14.56f, -2.75f);
    glVertex2f(16.36f, -5.08f);
    glEnd();
}

/**

 * Object ID: OBJ032
 */
void drawDock() {
    // Main dock surface
    glBegin(GL_QUADS);
    glColor3ub(166, 119, 49);
    glVertex2f(-8.47f, -5.95f);
    glVertex2f(-10.44f, -7.40f);
    glVertex2f(-6.01f, -7.44f);
    glVertex2f(-3.28f, -5.94f);
    glEnd();
    // Dock edge
    glBegin(GL_QUADS);
    glColor3ub(150, 75, 0);
    glVertex2f(-10.44f, -7.40f);
    glVertex2f(-10.44f, -7.51f);
    glVertex2f(-6.10f, -7.51f);
    glVertex2f(-5.95f, -7.40f);
    glEnd();
    // Lines for dock details
    glBegin(GL_LINES);
    glLineWidth(1.00f);
    glColor3ub(0, 0, 0);
    glVertex2f(-7.57f, -5.95f);
    glVertex2f(-9.50f, -7.40f);
    glVertex2f(-6.67f, -5.95f);
    glVertex2f(-8.64f, -7.40f);
    glVertex2f(-5.77f, -5.95f);
    glVertex2f(-7.74f, -7.40f);
    glVertex2f(-4.88f, -5.95f);
    glVertex2f(-6.84f, -7.40f);
    glVertex2f(-3.98f, -5.95f);
    glVertex2f(-5.05f, -6.75f);
    glEnd();
    // Dock supports
    glBegin(GL_QUADS);
    glColor3ub(150, 75, 0);
    glVertex2f(-9.72f, -7.51f);
    glVertex2f(-9.72f, -8.50f);
    glVertex2f(-9.53f, -8.50f);
    glVertex2f(-9.53f, -7.51f);
    glEnd();
    glBegin(GL_QUADS);
    glColor3ub(150, 75, 0);
    glVertex2f(-8.77f, -7.51f);
    glVertex2f(-8.77f, -8.50f);
    glVertex2f(-8.61f, -8.50f);
    glVertex2f(-8.61f, -7.51f);
    glEnd();
    glBegin(GL_QUADS);
    glColor3ub(150, 75, 0);
    glVertex2f(-7.84f, -7.51f);
    glVertex2f(-7.84f, -8.50f);
    glVertex2f(-7.68f, -8.50f);
    glVertex2f(-7.67f, -7.51f);
    glEnd();
    glBegin(GL_QUADS);
    glColor3ub(150, 75, 0);
    glVertex2f(-6.90f, -7.51f);
    glVertex2f(-6.90f, -8.08f);
    glVertex2f(-6.74f, -7.97f);
    glVertex2f(-6.74f, -7.51f);
    glEnd();
}
/**

 * Object ID: OBJ033
 */
void upperBoat1(){
    glPushMatrix();
    glTranslatef(upper_boat1_pos, 0.0f, 0.0f);
    // Lower part
    glColor3ub(0, 0, 0);
    glBegin(GL_POLYGON);
    glVertex2f(10.72f, 0.95f);
    glVertex2f(11.17f, 0.34f);
    glVertex2f(11.58f, 0.09f);
    glVertex2f(12.85f, 0.09f);
    glVertex2f(13.33f, 0.16f);
    glVertex2f(13.73f, 0.39f);
    glVertex2f(13.89f, 0.59f);
    glVertex2f(13.98f, 0.90f);
    glEnd();
    // Sail
    glColor3ub(255, 255, 180);
    glBegin(GL_POLYGON);
    glVertex2f(12.39f, 3.10f);
    glVertex2f(11.02f, 1.17f);
    glVertex2f(13.64f, 1.08f);
    glEnd();
    // Flag
    glColor3ub(200, 30, 70);
    glBegin(GL_POLYGON);
    glVertex2f(12.39f, 3.32f);
    glVertex2f(12.39f, 3.10f);
    glVertex2f(12.78f, 3.14f);
    glEnd();
    glPopMatrix();
}

/**

 * Object ID: OBJ034
 */
void upperBoat2() {
    glPushMatrix();
    glTranslatef(upper_boat2_pos, 0.0f, 0.0f);
    // Sail
    glColor3ub(255, 255, 180);
    glBegin(GL_TRIANGLES);
    glVertex2f(4.62f, 2.87f);
    glVertex2f(4.62f, 1.06f);
    glVertex2f(6.09f, 1.50f);
    glEnd();
    // Lower part
    glColor3ub(0, 0, 0);
    glBegin(GL_POLYGON);
    glVertex2f(3.34f, 1.06f);
    glVertex2f(3.60f, 0.51f);
    glVertex2f(6.00f, 0.50f);
    glVertex2f(6.22f, 1.06f);
    glEnd();
    glPopMatrix();
}

/**

 * Object ID: OBJ035
 */
void lowerBoat1() {
    glPushMatrix();
    glTranslatef(lower_boat1_pos, 0.0f, 0.0f);
    // Lower part
    glColor3ub(139, 69, 19);
    glBegin(GL_POLYGON);
    glVertex2f(-9.53f, -3.22f);
    glVertex2f(-8.06f, -4.73f);
    glVertex2f(-7.20f, -5.14f);
    glVertex2f(-2.35f, -5.13f);
    glVertex2f(-1.46f, -4.66f);
    glVertex2f(-0.56f, -3.24f);
    glEnd();
    // Sail big
    glColor3ub(220, 220, 220);
    glBegin(GL_POLYGON);
    glVertex2f(-4.62f, 1.26f);
    glVertex2f(-8.48f, -2.33f);
    glVertex2f(-5.81f, -2.66f);
    glVertex2f(-4.87f, -3.11f);
    glVertex2f(-4.87f, -3.23f);
    glEnd();
    // Sail small
    glColor3ub(200, 200, 200);
    glBegin(GL_POLYGON);
    glVertex2f(-4.33f, 0.60f);
    glVertex2f(-4.33f, -3.23f);
    glVertex2f(-4.15f, -3.23f);
    glVertex2f(-4.14f, -3.03f);
    glVertex2f(-3.50f, -2.75f);
    glVertex2f(-2.87f, -2.66f);
    glEnd();
    glPopMatrix();
}

/**

 * Object ID: OBJ036
 */
void lowerBoat2() {
    glPushMatrix();
    glTranslatef(lower_boat2_pos, 0.0f, 0.0f);
    // Lower part
    glColor3ub(80, 41, 21);
    glBegin(GL_POLYGON);
    glVertex2f(-18.21f, -2.50f);
    glVertex2f(-17.02f, -3.62f);
    glVertex2f(-16.36f, -3.98f);
    glVertex2f(-15.86f, -4.12f);
    glVertex2f(-15.16f, -4.04f);
    glVertex2f(-14.06f, -3.71f);
    glVertex2f(-13.08f, -3.25f);
    glVertex2f(-11.88f, -2.49f);
    glEnd();
    // Sail small
    glColor3ub(220, 190, 110);
    glBegin(GL_POLYGON);
    glVertex2f(-16.14f, 0.59f);
    glVertex2f(-16.40f, -0.21f);
    glVertex2f(-17.17f, -1.16f);
    glVertex2f(-18.25f, -2.10f);
    glVertex2f(-16.15f, -2.10f);
    glEnd();
    // Sail big
    glColor3ub(180, 180, 230);
    glBegin(GL_POLYGON);
    glVertex2f(-15.50f, 2.00f);
    glVertex2f(-15.23f, 0.61f);
    glVertex2f(-15.20f, -1.23f);
    glVertex2f(-15.53f, -2.10f);
    glVertex2f(-12.36f, -2.10f);
    glVertex2f(-13.18f, -0.56f);
    glVertex2f(-13.88f, 0.40f);
    glVertex2f(-14.75f, 1.38f);
    glEnd();
    glPopMatrix();
}

/**
 *Draws the airplane.
 * Object ID: OBJ037
 */
void plane() {
    glPushMatrix();
    glTranslatef(plane_x, 0.0f, 0.0f);
    // Main body
    glColor3ub(240, 244, 245);
    glBegin(GL_POLYGON);
    glVertex2f(0.80f, 12.20f);
    glVertex2f(0.40f, 12.40f);
    glVertex2f(-2.80f, 12.40f);
    glVertex2f(-3.00f, 12.00f);
    glVertex2f(0.60f, 12.00f);
    glEnd();
    // Tail fin
    glColor3ub(240, 244, 245);
    glBegin(GL_QUADS);
    glVertex2f(-3.40f, 12.80f);
    glVertex2f(-3.00f, 12.00f);
    glVertex2f(-2.80f, 12.40f);
    glVertex2f(-3.20f, 12.80f);
    glEnd();
    // Top wing
    glColor3ub(240, 244, 245);
    glBegin(GL_QUADS);
    glVertex2f(-2.20f, 13.20f);
    glVertex2f(-1.60f, 12.40f);
    glVertex2f(-0.80f, 12.40f);
    glVertex2f(-1.70f, 13.20f);
    glEnd();
    // Bottom wing
    glColor3ub(240, 244, 245);
    glBegin(GL_QUADS);
    glVertex2f(-1.40f, 12.00f);
    glVertex2f(-1.30f, 11.60f);
    glVertex2f(-1.00f, 11.60f);
    glVertex2f(-0.33f, 12.00f);
    glEnd();
    glPopMatrix();
}



/**
 *  Animation Village-5
 */
void drawDrops() {
    glColor3f(0.2f, 0.4f, 1.0f);
    glLineWidth(2.0f);
    for (int i = 0; i < dropCount; ++i) {
        glBegin(GL_LINES);
        glVertex2f(dropX[i], dropY[i]);
        glVertex2f(dropX[i], dropY[i] - 0.5f);
        glEnd();
    }
}

/**
 *Handles keyboard input for toggling scene effects.
 * Animation Village-6
 */
void handleKeypress(unsigned char key, int x, int y) {
    switch (key) {
    case 'r':
    case 'R':
        rainOn = !rainOn;
        break;
    case 'n':
    case 'N':
        isNight = true;
        isDoorWindowLight = true;
        break;
    case 'd':
    case 'D':
        isNight = false;
        isDoorWindowLight = false;
        break;
    case 'l':
    case 'L':
        isDoorWindowLight = !isDoorWindowLight;
        break;
    case 't':
    case 'T':
        tentVisible = !tentVisible;
        break;
    }
    glutPostRedisplay();
}

/**

 * Animation Village-6
 */
void handleMouse(int button, int state, int x, int y) {
    if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) {
        animationPaused = true;
    }
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        animationPaused = false;
    }
}

/**

Animation Village-8
 */
void update1(int value) {
     //Animation Village-7: Boat Moves
    if (!animationPaused) {
        // Update boat positions
        upper_boat1_pos += 0.06f;
        if (upper_boat1_pos > 22.0f) upper_boat1_pos = -22.0f;
        upper_boat2_pos -= 0.06f;
        if (upper_boat2_pos < -22.0f) upper_boat2_pos = 22.0f;
        lower_boat1_pos -= 0.06f;
        if (lower_boat1_pos < -22.0f) lower_boat1_pos = 22.0f;
        lower_boat2_pos -= 0.06f;
        if (lower_boat2_pos < -22.0f) lower_boat2_pos = 22.0f;

        // Animation Village-8: Cloud Moves
        // Update cloud positions
        cloud1_pos -= 0.1f;
        if ((-14.0f + cloud1_pos) < -20.0f) cloud1_pos = 22.0f;
        cloud2_pos -= 0.1f;
        if ((-2.0f  + cloud2_pos) < -20.0f) cloud2_pos = 22.0f;
        cloud3_pos -= 0.1f;
        if ((10.9f  + cloud3_pos) < -20.0f) cloud3_pos = 22.0f;

        //Animation Village-9: Turbine Moves
        // Update turbine rotation
        bladeAngle += 0.5f;
        if (bladeAngle > 360) bladeAngle -= 360;

        // Update airplane position
        plane_x += 0.05f;
        if (plane_x > 20.0f) plane_x = -20.0f;

        // Update rain animation
        if (rainOn) {
            int dropsPerFrame = 10; // Add new drops
            for (int d = 0; d < dropsPerFrame && dropCount < MAX_DROPS; ++d) {
                dropX[dropCount] = (rand() % 4000 / 100.0f) - 20.0f;
                dropY[dropCount] = 20.0f;
                dropSpeed[dropCount] = globalRainSpeed;
                dropCount++;
            }
            // Move existing drops
            for (int i = 0; i < dropCount; ) {
                dropY[i] -= dropSpeed[i];
                if (dropY[i] <= -10.0f) { // Remove drops that are off-screen
                    dropX[i] = dropX[dropCount - 1];
                    dropY[i] = dropY[dropCount - 1];
                    dropSpeed[i] = dropSpeed[dropCount - 1];
                    dropCount--;
                } else {
                    i++;
                }
            }
        } else {
            dropCount = 0; // Clear rain if turned off
        }
    }

    glutPostRedisplay();
    glutTimerFunc(16, update1, 0); // ~60 FPS
}




void display() {
glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();
    drawSky1();
    drawSun1();
    Clouds1();
    Clouds3();
    drawRiver1();
    drawMoon1();
    mountain1();
    mountain2();
    mountain3();
    mountain4();
    plane();
    Clouds2();
    backside_Field_Left();
    middle_ground_trees1();
    middle_ground_trees2();
    backside_Field_With_Trees_Right();
    upperBoat1();
    upperBoat2();
    turbine();
    big_house1();
    barn();
    drawMiddleTree3();
    drawMiddleTree2();
    drawMiddleTree1();
    drawMiddleGroundLayer1();
    drawMiddleGroundLayer2();
    drawMiddleGroundLayer3();
    drawMiddleGroundLayer4();
    lowerBoat1();
    lowerBoat2();
    little_house1();
    little_house2();
    little_house3();
    little_house4();
    drawDock();
    drawFrontSideGround();
    if (tentVisible)
        tent();
    if (rainOn)
        drawDrops();
    glutSwapBuffers();

}
/**
 *Main entry point of the program.
 */
int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(1000, 800);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Village Scenery");
    srand((unsigned int)time(0));
    init();

    glutDisplayFunc(display);
    glutKeyboardFunc(handleKeypress);
    glutMouseFunc(handleMouse);
    glutTimerFunc(20, update1, 0);
    glutMainLoop();
    return 0;
}
