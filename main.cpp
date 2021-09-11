//  ========================================================================
//  COSC363: Computer Graphics (2021);  CSSE, University of Canterbury.
//
//  FILE NAME: Main.cpp
//  CREATOR: Michael Woodard
//  STUDENT CODE: mdw85
//  STUDENT ID: 24643695
//  ========================================================================
 
#define _USE_MATH_DEFINES
#define GL_CLAMP_TO_EDGE 0x812F

#include <iostream>
#include <cmath> 
#include <GL/freeglut.h>
#include "loadBMP.h"

using namespace std;


const int N = 6;  // Total number of vertices on the base curve
float vx_init[N] = { 9, 8.77496, 8.06226, 7.21913, 6.084723, 0 };
float vy_init[N] = { 0, 4, 8, 12, 15, 15 };
float vz_init[N] = { 0 };

float angle = 0;
float theta =  20 * M_PI / 180;
float rot = 0;

float look_x = 0, look_y = 42, look_z = 0;
float eye_x = 0, eye_y = 70, eye_z = 155;

float ball1_y = 30.0, ball2_y = 27.0, ball3_y = 21.0, ball4_y = 27.0;
float ball1_v = 0, ball2_v = 1.0, ball3_v = -2.0, ball4_v = -1.2;
float max_height = 30, min_height = 19, grav = -0.2;

GLuint txId[8];   //Texture ids

//----------------------------------------------------------
void loadTexture()
{
	glGenTextures(8, txId); 	// Create 8 texture ids

	glBindTexture(GL_TEXTURE_2D, txId[0]);
	loadBMP("back.bmp");
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glBindTexture(GL_TEXTURE_2D, txId[1]);
	loadBMP("down.bmp");
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glBindTexture(GL_TEXTURE_2D, txId[2]);
	loadBMP("front.bmp");
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glBindTexture(GL_TEXTURE_2D, txId[3]);
	loadBMP("left.bmp");
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glBindTexture(GL_TEXTURE_2D, txId[4]);
	loadBMP("right.bmp");
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glBindTexture(GL_TEXTURE_2D, txId[5]);
	loadBMP("up.bmp");
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	
	glBindTexture(GL_TEXTURE_2D, txId[6]);
	loadBMP("VaseTexture.bmp");
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	
	glBindTexture(GL_TEXTURE_2D, txId[7]);
	loadBMP("WoodTexture.bmp");
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);



	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
}

//-------------------------------------------------------------------
void initialise(void) 
{
    float grey[4] = {0.2, 0.2, 0.2, 1.0};
    float white[4]  = {1.0, 1.0, 1.0, 1.0};

	loadTexture();
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_NORMALIZE);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
    glLightfv(GL_LIGHT0, GL_AMBIENT, grey);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, white);
    glLightfv(GL_LIGHT0, GL_SPECULAR, white);
	glEnable(GL_SMOOTH);

	glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
	glEnable(GL_COLOR_MATERIAL);

    glClearColor (1.0, 1.0, 1.0, 0.0);

    glMatrixMode (GL_PROJECTION);
    glLoadIdentity ();
    gluPerspective(40.0, 1.0, 20.0, 500.0);
}

//-------------------------------------------------------------------
void normal(float x1, float y1, float z1, 
            float x2, float y2, float z2,
		      float x3, float y3, float z3 )
{
	  float nx, ny, nz;
	  nx = y1*(z2-z3)+ y2*(z3-z1)+ y3*(z1-z2);
	  ny = z1*(x2-x3)+ z2*(x3-x1)+ z3*(x1-x2);
	  nz = x1*(y2-y3)+ x2*(y3-y1)+ x3*(y1-y2);

      glNormal3f(nx, ny, nz);
}

//-- Ground Plane --------------------------------------------------------
void drawGrid()
{
	glDisable(GL_LIGHTING);
	glColor3f(0.7, 0.7, 0.7);			//Floor colour

	for (int i = -180; i <= 180; i += 5)
	{
		glBegin(GL_LINES);			//A set of grid lines on the xz-plane
		glVertex3f(-180, 0, i);
		glVertex3f(180, 0, i);
		glVertex3f(i, 0, -180);
		glVertex3f(i, 0, 180);
		glEnd();
	}
	glEnable(GL_LIGHTING);
}

//-------------------------------------------------------------------
void back()
{
	glBindTexture(GL_TEXTURE_2D, txId[0]);
	glBegin(GL_QUADS);
	glNormal3f(0.0, 0.0, -1.0);
	glTexCoord2f(0.0, 1.0);     glVertex3f(-180, 180, -180);
	glTexCoord2f(0.0, 0.0);     glVertex3f(-180, 0, -180);
	glTexCoord2f(1.0, 0.0);     glVertex3f(180, 0, -180);
	glTexCoord2f(1.0, 1.0);     glVertex3f(180, 180, -180);
	glEnd();
}

//-------------------------------------------------------------------
void down()
{
	glBindTexture(GL_TEXTURE_2D, txId[1]);
	glBegin(GL_QUADS);
	glNormal3f(0.0, -1.0, 0.0);
	glTexCoord2f(0.0, 1.0);     glVertex3f(-180, 0, -180);
	glTexCoord2f(0.0, 0.0);     glVertex3f(-180, 0, 180);
	glTexCoord2f(1.0, 0.0);     glVertex3f(180, 0, 180);
	glTexCoord2f(1.0, 1.0);     glVertex3f(180, 0, -180);
	glEnd();
}

//-------------------------------------------------------------------
void front()
{
	glBindTexture(GL_TEXTURE_2D, txId[2]);
	glBegin(GL_QUADS);
	glNormal3f(0.0, 0.0, 1.0);
	glTexCoord2f(0.0, 1.0);     glVertex3f(180, 180, 180);
	glTexCoord2f(0.0, 0.0);     glVertex3f(180, 0, 180);
	glTexCoord2f(1.0, 0.0);     glVertex3f(-180, 0, 180);
	glTexCoord2f(1.0, 1.0);     glVertex3f(-180, 180, 180);
	glEnd();
}

//-------------------------------------------------------------------
void left()
{
	glBindTexture(GL_TEXTURE_2D, txId[3]);
	glBegin(GL_QUADS);
	glNormal3f(-1.0, 0.0, 0.0);
	glTexCoord2f(1.0, 1.0);     glVertex3f(-180, 180, -180);
	glTexCoord2f(0.0, 1.0);     glVertex3f(-180, 180, 180);
	glTexCoord2f(0.0, 0.0);     glVertex3f(-180, 0, 180);
	glTexCoord2f(1.0, 0.0);     glVertex3f(-180, 0, -180);
	glEnd();
}

//-------------------------------------------------------------------
void right()
{
	glBindTexture(GL_TEXTURE_2D, txId[4]);
	glBegin(GL_QUADS);
	glNormal3f(1.0, 0.0, 0.0);
	glTexCoord2f(0.0, 1.0);     glVertex3f(180, 180, -180);
	glTexCoord2f(1.0, 1.0);     glVertex3f(180, 180, 180);
	glTexCoord2f(1.0, 0.0);     glVertex3f(180, 0, 180);
	glTexCoord2f(0.0, 0.0);     glVertex3f(180, 0, -180);
	glEnd();
}

//-------------------------------------------------------------------
void up()
{
	glBindTexture(GL_TEXTURE_2D, txId[5]);
	glBegin(GL_QUADS);
	glNormal3f(0.0, 1.0, 0.0);
	glTexCoord2f(0.0, 1.0);     glVertex3f(-180, 180, -180);
	glTexCoord2f(1.0, 1.0);     glVertex3f(-180, 180, 180);
	glTexCoord2f(1.0, 0.0);     glVertex3f(180, 180, 180);
	glTexCoord2f(0.0, 0.0);     glVertex3f(180, 180, -180);
	glEnd();
}

//-------------------------------------------------------------------
void drawObject()
{
	float vx[N], vy[N], vz[N];
	float wx[N], wy[N], wz[N];

	for (int i = 0; i < N; i++)		//Initialize data everytime
	{
		vx[i] = vx_init[i];
		vy[i] = vy_init[i];
		vz[i] = vz_init[i];
	}

	for (int j = 0; j < 18; j++) //360 slices in 1 deg steps
	{
		for (int i = 0; i < N; i++) {
			wx[i] = vx[i] * cos(theta) + vz[i] * sin(theta);
			wy[i] = vy[i];
			wz[i] = vx[i] * sin(theta) * -1.0 + vz[i] * cos(theta);
		}
		
		glBindTexture(GL_TEXTURE_2D, txId[6]);
		glBegin(GL_TRIANGLE_STRIP);
		for (int i = 0; i < N; i++) {
			if (i > 0) normal(vx[i - 1], vy[i - 1], vz[i - 1],
				wx[i - 1], wy[i - 1], wz[i - 1],
				vx[i], vy[i], vz[i]);
			glTexCoord2f((float)j/N, (float)i/(N-1)); 
			glVertex3f(vx[i], vy[i], vz[i]);
			if (i > 0) normal(wx[i - 1], wy[i - 1], wz[i - 1],
				wx[i], wy[i], wz[i],
				vx[i], vy[i], vz[i]);
			glTexCoord2f((float)(j+1)/N, (float)i/(N-1));
			glVertex3f(wx[i], wy[i], wz[i]);
		}
		for (int i = 0; i < N; i++)
		{
			vx[i] = wx[i];
			vy[i] = wy[i];
			vz[i] = wz[i];
		}

	}

	glEnd();
}

//-------------------------------------------------------------------
void drawBall()
{
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, txId[7]);
	GLUquadric *q = gluNewQuadric();
	gluQuadricDrawStyle (q, GLU_FILL);
	gluQuadricNormals (q, GLU_SMOOTH);
	gluQuadricTexture(q, GL_TRUE);
	gluSphere (q, 4, 40, 20);
	glDisable(GL_TEXTURE_2D);
}

//-------------------------------------------------------------------
void drawModel()
{
	float shadowMat[16] = { 50.0f,0,0,0, -5.0f,0,-100.0f,-1, 0,0,50.0f,0, 0,0,0,50.0f };
	glDisable(GL_LIGHTING);

	/* Bounce Pad  1 */
	glPushMatrix();
	glTranslatef(0, 0.1, 0);
	glMultMatrixf(shadowMat);
	glColor4f(0.2, 0.2, 0.2, 1.0);
	glTranslatef(25, 0, 0);
	drawObject();
	glPopMatrix();

	/* Bounce Pad  2 */
	glPushMatrix();
	glTranslatef(0, 0.1, 0);
	glMultMatrixf(shadowMat);
	glColor4f(0.2, 0.2, 0.2, 1.0);
	glTranslatef(-25, 0, 0);
	drawObject();
	glPopMatrix();

	/* Bounce Pad  3 */
	glPushMatrix();
	glTranslatef(0, 0.1, 0);
	glMultMatrixf(shadowMat);
	glColor4f(0.2, 0.2, 0.2, 1.0);
	glTranslatef(0, 0, 25);
	drawObject();
	glPopMatrix();

	/* Bounce Pad  4 */
	glPushMatrix();
	glTranslatef(0, 0.1, 0);
	glMultMatrixf(shadowMat);
	glColor4f(0.2, 0.2, 0.2, 1.0);
	glTranslatef(0, 0, -25);
	drawObject();
	glPopMatrix();

	glEnable(GL_LIGHTING);
	glEnable(GL_TEXTURE_2D);

	/* Bounce Pad  1 */
	glPushMatrix(); //Draw Actual Object
	glTranslatef(25, 0, 0);
	drawObject();
	glPopMatrix();

	/* Bounce Pad  2 */
	glPushMatrix();
	glTranslatef(-25, 0, 0);
	drawObject();
	glPopMatrix();

	/* Bounce Pad  3 */
	glPushMatrix();
	glTranslatef(0, 0, 25);
	drawObject();
	glPopMatrix();

	/* Bounce Pad  4 */
	glPushMatrix();
	glTranslatef(0, 0, -25);
	drawObject();
	glPopMatrix();
	
	glDisable(GL_TEXTURE_2D);

	/* Ball 1 */
	glPushMatrix();
	glColor3f(0.2, 0.6, 0.2);
	glTranslatef(25, ball1_y, 0);
	drawBall();
	glPopMatrix();

	/* Ball 2 */
	glPushMatrix();
	glTranslatef(0, ball2_y, 25);
	drawBall();
	glPopMatrix();

	/* Ball 3 */
	glPushMatrix();
	glTranslatef(-25, ball3_y, 0);
	drawBall();
	glPopMatrix();

	/* Ball 4 */
	glPushMatrix();
	glTranslatef(0, ball4_y, -25);
	drawBall();
	glPopMatrix();

	/* Torus */
	glPushMatrix();
	glColor3f(0.1, 0.1, 0.1);
	glRotatef(-rot, 0, 1, 0);
	glTranslatef(25, max_height, 0);
	glutSolidTorus(2, 6, 40, 20);
	glPopMatrix();

	/* Bar */
	glPushMatrix();
	glColor3f(0.4, 0.2, 0);
	glRotatef(-rot, 0, 1, 0);
	glTranslatef(0, 60, 0);
	glRotatef(40, 0, 0, 1);
	glTranslatef(0, -60, 0);
	glTranslatef(0, 40, 0);
	glScalef(3, 25, 3);
	glutSolidCube(1);
	glPopMatrix();
}

//-------------------------------------------------------------------
void display(void)
{
	float lgt_pos[]={5.0f, 50.0f, 100.0f, 1.0f};  //light0 position 

	glClear (GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(eye_x, eye_y, eye_z, look_x, look_y, look_z, 0.0, 1.0, 0.0);

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	glLightfv(GL_LIGHT0, GL_POSITION, lgt_pos);   //light position

	glPushMatrix();
	glTranslatef(0, -0.2, 0);
	drawGrid();
	glPopMatrix();
	
	glEnable(GL_TEXTURE_2D);
	glPushMatrix();
	back();
	glPopMatrix();

	glPushMatrix();
	down();
	glPopMatrix();

	glPushMatrix();
	front();
	glPopMatrix();

	glPushMatrix();
	left();
	glPopMatrix();

	glPushMatrix();
	right();
	glPopMatrix();

	glPushMatrix();
	up();
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);


	glColor3f (0.0, 0.0, 1.0);    //Used for wireframe display

	//  Include code for drawing the surface of revolution here.
	// ---- Start here ----
	drawModel();

	glutSwapBuffers();
}

//--------------------------------------------------------------------------------
void special(int key, int x, int y)
{
	if (key == GLUT_KEY_LEFT) angle -= 0.1;  //Change direction
	else if (key == GLUT_KEY_RIGHT) angle += 0.1;
	else if (key == GLUT_KEY_DOWN)
	{  //Move backward
		eye_x -= 1.0 * sin(angle);
		eye_z += 1.0 * cos(angle);
		if (eye_x >= 180) {
			eye_x = 180;
		} else if (eye_x <= -180) {
			eye_x = -180;
		} else if (eye_z >= 180) {
			eye_z = 180;
		} else if (eye_z <= -180) {
			eye_z = -180;
		}
	}
	else if (key == GLUT_KEY_UP)
	{ //Move forward
		eye_x += 1.0 * sin(angle);
		eye_z -= 1.0 * cos(angle);
		if (eye_x >= 180) {
			eye_x = 180;
		} else if (eye_x <= -180) {
			eye_x = -180;
		} else if (eye_z >= 180) {
			eye_z = 180;
		} else if (eye_z <= -180) {
			eye_z = -180;
		}
	}
	else if (key == GLUT_KEY_PAGE_UP)
	{
		eye_y += 10;
		if (eye_y >= 180) {
			eye_y = 180;
		}
	}
	else if (key == GLUT_KEY_PAGE_DOWN)
	{
		eye_y -= 10;
		if (eye_y <= 0) {
			eye_y = 0;
		}
	}
	else if (key == GLUT_KEY_HOME)
	{
		look_y += 10;
	}
	else if (key == GLUT_KEY_END)
	{
		look_y -= 10;
	}

	look_x = eye_x + 100 * sin(angle);
	look_z = eye_z - 100 * cos(angle);
	glutPostRedisplay();
}

//-------------------------------------------------------------------
void bounce()
{
	ball1_y += ball1_v;
	if (ball1_y <= min_height) {
		ball1_v *= -1;
	}
	else if (ball1_y >= max_height) {
		ball1_v = 0;
		ball1_v += grav;
	}
	else {
		ball1_v += grav;
	}

	ball2_y += ball2_v;
	if (ball2_y <= min_height) {
		ball2_v *= -1;
	}
	else if (ball2_y >= max_height) {
		ball2_v = 0;
		ball2_v += grav;
	}
	else {
		ball2_v += grav;
	}
	
	ball3_y += ball3_v;
	if (ball3_y <= min_height) {
		ball3_v *= -1;
	}
	else if (ball3_y >= max_height) {
		ball3_v = 0;
		ball3_v += grav;
	}
	else {
		ball3_v += grav;
	}

	ball4_y += ball4_v;
	if (ball4_y <= min_height) {
		ball4_v *= -1;
	}
	else if (ball4_y >= max_height) {
		ball4_v = 0;
		ball4_v += grav;
	}
	else {
		ball4_v += grav;
	}
}

//-------------------------------------------------------------------
void rotate()
{
	rot += 18;
}

//-------------------------------------------------------------------
void myTimer(int value)
{
	rotate();
	bounce();
	glutPostRedisplay();
	glutTimerFunc(50, myTimer, 0);
}

//-------------------------------------------------------------------
int main(int argc, char** argv)
{
   glutInit(&argc, argv);
   glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
   glutInitWindowSize (1000, 1000); 
   glutInitWindowPosition (100, 100);
   glutCreateWindow ("Assignment 1");
   initialise ();

   glutDisplayFunc(display);
   glutSpecialFunc(special);
   glutTimerFunc(50, myTimer, 0);
   glutMainLoop();
   return 0;
}
