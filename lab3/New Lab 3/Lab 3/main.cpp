// CS3241Lab1.cpp : Defines the entry point for the console application.
//#include <cmath>
#include <Windows.h>
#include "math.h"
#include <iostream>
#include <fstream>
#include "GL\glut.h"


#define M_PI 3.141592654

// global variable

bool m_Smooth = FALSE;
bool m_Highlight = FALSE;
GLfloat angle = 0;   /* in degrees */
GLfloat angle2 = 0;   /* in degrees */
GLfloat zoom = 1.0;
int mouseButton = 0;
int moving, startx, starty;

#define NO_OBJECT 4;
int current_object = 0;

using namespace std;

void setupLighting()
{
	glShadeModel(GL_SMOOTH);
	glEnable(GL_NORMALIZE);

	// Lights, material properties
    GLfloat	ambientProperties[]  = {0.7f, 0.7f, 0.7f, 1.0f};
	GLfloat	diffuseProperties[]  = {0.8f, 0.8f, 0.8f, 1.0f};
    GLfloat	specularProperties[] = {1.0f, 1.0f, 1.0f, 1.0f};
	GLfloat lightPosition[] = {-100.0f,100.0f,100.0f,1.0f};
	
    glClearDepth( 1.0 );

	glLightfv( GL_LIGHT0, GL_POSITION, lightPosition);
	
    glLightfv( GL_LIGHT0, GL_AMBIENT, ambientProperties);
    glLightfv( GL_LIGHT0, GL_DIFFUSE, diffuseProperties);
    glLightfv( GL_LIGHT0, GL_SPECULAR, specularProperties);
    glLightModelf(GL_LIGHT_MODEL_TWO_SIDE, 0.0);

	// Default : lighting
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHTING);

}

void changeColor(float x,float y,float z,float r)
{
	float no_mat[] = {0.0f, 0.0f, 0.0f, 1.0f};
	float mat_ambient[] = {0.3f,0.3f,0.15f,1.0f};
	float mat_ambient_color[] = {0.8f,0.8f,0.2f,1.0f};
	float mat_secular[] = {1.0f,1.0f,1.0f,1.0f};
    float mat_diffuse[] = {x,y,z,r};
    float no_shininess = 0.0f;
	float shininess = 100.0f;
    float mat_emission[] = {0.3f, 0.2f, 0.2f, 0.0f};
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);

	if(m_Highlight)
	{
		// your codes for highlight here
		glMaterialfv(GL_FRONT, GL_SPECULAR, mat_secular);
		glMaterialf(GL_FRONT, GL_SHININESS, shininess);
	} else {
		glMaterialfv(GL_FRONT, GL_SPECULAR, no_mat);
		glMaterialf(GL_FRONT, GL_SHININESS, no_shininess);
	}

    glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
}
void drawSphere(double r)
{
	
    int i,j;
	int n = 20;
    for(i=0;i<n;i++)
		for(j=0;j<2*n;j++)
		if(m_Smooth)
		{
			glBegin(GL_POLYGON);

			    // the normal of each vertex is actaully its own coordinates normalized for a sphere

			    // your normal here
				// Set different normal vectors for different vertices
			    glNormal3d(sin((i)*M_PI/n)*cos((j)*M_PI/n),cos((i)*M_PI/n)*cos((j)*M_PI/n),sin((j)*M_PI/n));
				glVertex3d(r*sin(i*M_PI/n)*cos(j*M_PI/n),r*cos(i*M_PI/n)*cos(j*M_PI/n),r*sin(j*M_PI/n));
			    // your normal here
				glNormal3d(sin((i+1)*M_PI/n)*cos((j)*M_PI/n),cos((i+1)*M_PI/n)*cos((j)*M_PI/n),sin((j)*M_PI/n));
				glVertex3d(r*sin((i+1)*M_PI/n)*cos(j*M_PI/n),r*cos((i+1)*M_PI/n)*cos(j*M_PI/n),r*sin(j*M_PI/n));
			    // your normal here
				glNormal3d(sin((i+1)*M_PI/n)*cos((j+1)*M_PI/n),cos((i+1)*M_PI/n)*cos((j+1)*M_PI/n),sin((j+1)*M_PI/n));
				glVertex3d(r*sin((i+1)*M_PI/n)*cos((j+1)*M_PI/n),r*cos((i+1)*M_PI/n)*cos((j+1)*M_PI/n),r*sin((j+1)*M_PI/n));
			    // your normal here
				glNormal3d(sin((i)*M_PI/n)*cos((j+1)*M_PI/n),cos((i)*M_PI/n)*cos((j+1)*M_PI/n),sin((j+1)*M_PI/n));
				glVertex3d(r*sin(i*M_PI/n)*cos((j+1)*M_PI/n),r*cos(i*M_PI/n)*cos((j+1)*M_PI/n),r*sin((j+1)*M_PI/n));
 			glEnd();
		} else	{
			glBegin(GL_POLYGON);
			    // Explanation: the normal of the whole polygon is the coordinate of the center of the polygon for a sphere
			    glNormal3d(sin((i+0.5)*M_PI/n)*cos((j+0.5)*M_PI/n),cos((i+0.5)*M_PI/n)*cos((j+0.5)*M_PI/n),sin((j+0.5)*M_PI/n));
				glVertex3d(r*sin(i*M_PI/n)*cos(j*M_PI/n),r*cos(i*M_PI/n)*cos(j*M_PI/n),r*sin(j*M_PI/n));
				glVertex3d(r*sin((i+1)*M_PI/n)*cos(j*M_PI/n),r*cos((i+1)*M_PI/n)*cos(j*M_PI/n),r*sin(j*M_PI/n));
				glVertex3d(r*sin((i+1)*M_PI/n)*cos((j+1)*M_PI/n),r*cos((i+1)*M_PI/n)*cos((j+1)*M_PI/n),r*sin((j+1)*M_PI/n));
				glVertex3d(r*sin(i*M_PI/n)*cos((j+1)*M_PI/n),r*cos(i*M_PI/n)*cos((j+1)*M_PI/n),r*sin((j+1)*M_PI/n));
 			glEnd();
		}

}
void drawRing(double r)
{	
    int i,j;
	int n = 20;
	double len = 0.1;
	for(i=0;i<2*n;i++)
		if(m_Smooth)
		{
			glBegin(GL_POLYGON);
			    // Explanation: the normal of the whole polygon is the coordinate of the center of the polygon for a sphere
			    glNormal3d(0,0,len);
				glVertex3d(0.0f,0.0f,r*len);
				glNormal3d(sin((i)*M_PI/n),cos((i)*M_PI/n),len);
				glVertex3d(r*sin((i)*M_PI/n),r*cos((i)*M_PI/n),r*len);
				glNormal3d(sin((i+1)*M_PI/n),cos((i+1)*M_PI/n),len);
				glVertex3d(r*sin((i+1)*M_PI/n),r*cos((i+1)*M_PI/n),r*len);
 			glEnd();

			glBegin(GL_POLYGON);
			    // Explanation: the normal of the whole polygon is the coordinate of the center of the polygon for a sphere
			    glNormal3d(sin((i)*M_PI/n),cos((i)*M_PI/n),len);
				glVertex3d(r*sin((i)*M_PI/n),r*cos((i)*M_PI/n),r*len);
				glNormal3d(sin((i+1)*M_PI/n),cos((i+1)*M_PI/n),len);
				glVertex3d(r*sin((i+1)*M_PI/n),r*cos((i+1)*M_PI/n),r*len);
				glNormal3d(sin((i+1)*M_PI/n),cos((i+1)*M_PI/n),-len);
				glVertex3d(r*sin((i+1)*M_PI/n),r*cos((i+1)*M_PI/n),-r*len);
				glNormal3d(sin((i)*M_PI/n),cos((i)*M_PI/n),-len);
				glVertex3d(r*sin((i)*M_PI/n),r*cos((i)*M_PI/n),-r*len);
 			glEnd();

			glBegin(GL_POLYGON);
			    // Explanation: the normal of the whole polygon is the coordinate of the center of the polygon for a sphere
			    glNormal3d(0,0,-len);
				glVertex3d(0.0f,0.0f,-r*len);
				glNormal3d(sin((i)*M_PI/n),cos((i)*M_PI/n),-len);
				glVertex3d(r*sin((i)*M_PI/n),r*cos((i)*M_PI/n),-r*len);
				glNormal3d(sin((i+1)*M_PI/n),cos((i+1)*M_PI/n),-len);
				glVertex3d(r*sin((i+1)*M_PI/n),r*cos((i+1)*M_PI/n),-r*len);
 			glEnd();
		} else	{
			glBegin(GL_POLYGON);
			    // Explanation: the normal of the whole polygon is the coordinate of the center of the polygon for a sphere
			    glNormal3d(sin((i+0.5)*M_PI/n)/2,cos((i+0.5)*M_PI/n)/2,r*len);
				glVertex3d(0.0f,0.0f,r*len);
				glVertex3d(r*sin((i)*M_PI/n),r*cos((i)*M_PI/n),r*len);
				glVertex3d(r*sin((i+1)*M_PI/n),r*cos((i+1)*M_PI/n),r*len);
 			glEnd();

			glBegin(GL_POLYGON);
			    // Explanation: the normal of the whole polygon is the coordinate of the center of the polygon for a sphere
			    glNormal3d(sin((i+0.5)*M_PI/n)/2,cos((i+0.5)*M_PI/n)/2,0);
				glVertex3d(r*sin((i)*M_PI/n),r*cos((i)*M_PI/n),r*len);
				glVertex3d(r*sin((i+1)*M_PI/n),r*cos((i+1)*M_PI/n),r*len);
				glVertex3d(r*sin((i+1)*M_PI/n),r*cos((i+1)*M_PI/n),-r*len);
				glVertex3d(r*sin((i)*M_PI/n),r*cos((i)*M_PI/n),-r*len);
 			glEnd();

			glBegin(GL_POLYGON);
			    // Explanation: the normal of the whole polygon is the coordinate of the center of the polygon for a sphere
			    glNormal3d(sin((i+0.5)*M_PI/n)/2,cos((i+0.5)*M_PI/n)/2,-r*len);
				glVertex3d(0.0f,0.0f,-r*len);
				glVertex3d(r*sin((i)*M_PI/n),r*cos((i)*M_PI/n),-r*len);
				glVertex3d(r*sin((i+1)*M_PI/n),r*cos((i+1)*M_PI/n),-r*len);
 			glEnd();
		}

}
void drawCylindrical(double r,double lenGive)
{
    int i,j;
	int n = 20;
	double len = lenGive;
	for(i=0;i<2*n;i++)
		if(m_Smooth)
		{
			glBegin(GL_POLYGON);
			    // Explanation: the normal of the whole polygon is the coordinate of the center of the polygon for a sphere
			    glNormal3d(0,0,len);
				glVertex3d(0.0f,0.0f,r*len);
				glNormal3d(sin((i)*M_PI/n),cos((i)*M_PI/n),len);
				glVertex3d(r*sin((i)*M_PI/n),r*cos((i)*M_PI/n),r*len);
				glNormal3d(sin((i+1)*M_PI/n),cos((i+1)*M_PI/n),len);
				glVertex3d(r*sin((i+1)*M_PI/n),r*cos((i+1)*M_PI/n),r*len);
 			glEnd();

			glBegin(GL_POLYGON);
			    // Explanation: the normal of the whole polygon is the coordinate of the center of the polygon for a sphere
			    glNormal3d(sin((i)*M_PI/n),cos((i)*M_PI/n),len);
				glVertex3d(r*sin((i)*M_PI/n),r*cos((i)*M_PI/n),r*len);
				glNormal3d(sin((i+1)*M_PI/n),cos((i+1)*M_PI/n),len);
				glVertex3d(r*sin((i+1)*M_PI/n),r*cos((i+1)*M_PI/n),r*len);
				glNormal3d(sin((i+1)*M_PI/n),cos((i+1)*M_PI/n),-len);
				glVertex3d(r*sin((i+1)*M_PI/n),r*cos((i+1)*M_PI/n),-r*len);
				glNormal3d(sin((i)*M_PI/n),cos((i)*M_PI/n),-len);
				glVertex3d(r*sin((i)*M_PI/n),r*cos((i)*M_PI/n),-r*len);
 			glEnd();

			glBegin(GL_POLYGON);
			    // Explanation: the normal of the whole polygon is the coordinate of the center of the polygon for a sphere
			    glNormal3d(0,0,-len);
				glVertex3d(0.0f,0.0f,-r*len);
				glNormal3d(sin((i)*M_PI/n),cos((i)*M_PI/n),-len);
				glVertex3d(r*sin((i)*M_PI/n),r*cos((i)*M_PI/n),-r*len);
				glNormal3d(sin((i+1)*M_PI/n),cos((i+1)*M_PI/n),-len);
				glVertex3d(r*sin((i+1)*M_PI/n),r*cos((i+1)*M_PI/n),-r*len);
 			glEnd();
		} else	{
			glBegin(GL_POLYGON);
			    // Explanation: the normal of the whole polygon is the coordinate of the center of the polygon for a sphere
			    glNormal3d(sin((i+0.5)*M_PI/n)/2,cos((i+0.5)*M_PI/n)/2,r*len);
				glVertex3d(0.0f,0.0f,r*len);
				glVertex3d(r*sin((i)*M_PI/n),r*cos((i)*M_PI/n),r*len);
				glVertex3d(r*sin((i+1)*M_PI/n),r*cos((i+1)*M_PI/n),r*len);
 			glEnd();

			glBegin(GL_POLYGON);
			    // Explanation: the normal of the whole polygon is the coordinate of the center of the polygon for a sphere
			    glNormal3d(sin((i+0.5)*M_PI/n)/2,cos((i+0.5)*M_PI/n)/2,0);
				glVertex3d(r*sin((i)*M_PI/n),r*cos((i)*M_PI/n),r*len);
				glVertex3d(r*sin((i+1)*M_PI/n),r*cos((i+1)*M_PI/n),r*len);
				glVertex3d(r*sin((i+1)*M_PI/n),r*cos((i+1)*M_PI/n),-r*len);
				glVertex3d(r*sin((i)*M_PI/n),r*cos((i)*M_PI/n),-r*len);
 			glEnd();

			glBegin(GL_POLYGON);
			    // Explanation: the normal of the whole polygon is the coordinate of the center of the polygon for a sphere
			    glNormal3d(sin((i+0.5)*M_PI/n)/2,cos((i+0.5)*M_PI/n)/2,-r*len);
				glVertex3d(0.0f,0.0f,-r*len);
				glVertex3d(r*sin((i)*M_PI/n),r*cos((i)*M_PI/n),-r*len);
				glVertex3d(r*sin((i+1)*M_PI/n),r*cos((i+1)*M_PI/n),-r*len);
 			glEnd();
		}
}
void drawMinionsBody(double r)
{
	changeColor(1.0f, 1.0f, 0.0f, 1.0f);
	int i,j;
	int n = 20;
	int len = 1;
	double ratioHead = 0.9;
	double ratioBotton = 0.6;
	for(i=0;i<2*n;i++)
		if(m_Smooth)
		{
			glBegin(GL_POLYGON);
			    // Explanation: the normal of the whole polygon is the coordinate of the center of the polygon for a sphere
			    glNormal3d(sin((i)*M_PI/n),cos((i)*M_PI/n),len);
				glVertex3d(r*sin((i)*M_PI/n),r*cos((i)*M_PI/n),r*len);
				glNormal3d(sin((i+1)*M_PI/n),cos((i+1)*M_PI/n),len);
				glVertex3d(r*sin((i+1)*M_PI/n),r*cos((i+1)*M_PI/n),r*len);
				glNormal3d(sin((i+1)*M_PI/n),cos((i+1)*M_PI/n),-len);
				glVertex3d(r*sin((i+1)*M_PI/n),r*cos((i+1)*M_PI/n),-r*len);
				glNormal3d(sin((i)*M_PI/n),cos((i)*M_PI/n),-len);
				glVertex3d(r*sin((i)*M_PI/n),r*cos((i)*M_PI/n),-r*len);
 			glEnd();
			for(j=0;j<n;j++){
				glBegin(GL_POLYGON);
				glNormal3d(sin((i)*M_PI/n)*cos((j)*M_PI/n),cos((i)*M_PI/n)*cos((j)*M_PI/n),ratioHead*sin((j)*M_PI/n)+len);
				glVertex3d(r*sin(i*M_PI/n)*cos(j*M_PI/n),r*cos(i*M_PI/n)*cos(j*M_PI/n),r*ratioHead*sin(j*M_PI/n)+r*len);
			    // your normal here
				glNormal3d(sin((i+1)*M_PI/n)*cos((j)*M_PI/n),cos((i+1)*M_PI/n)*cos((j)*M_PI/n),ratioHead*sin((j)*M_PI/n)+len);
				glVertex3d(r*sin((i+1)*M_PI/n)*cos(j*M_PI/n),r*cos((i+1)*M_PI/n)*cos(j*M_PI/n),r*ratioHead*sin(j*M_PI/n)+r*len);
			    // your normal here
				glNormal3d(sin((i+1)*M_PI/n)*cos((j+1)*M_PI/n),cos((i+1)*M_PI/n)*cos((j+1)*M_PI/n),ratioHead*sin((j+1)*M_PI/n)+len);
				glVertex3d(r*sin((i+1)*M_PI/n)*cos((j+1)*M_PI/n),r*cos((i+1)*M_PI/n)*cos((j+1)*M_PI/n),r*ratioHead*sin((j+1)*M_PI/n)+r*len);
			    // your normal here
				glNormal3d(sin((i)*M_PI/n)*cos((j+1)*M_PI/n),cos((i)*M_PI/n)*cos((j+1)*M_PI/n),ratioHead*sin((j+1)*M_PI/n)+len);
				glVertex3d(r*sin(i*M_PI/n)*cos((j+1)*M_PI/n),r*cos(i*M_PI/n)*cos((j+1)*M_PI/n),r*ratioHead*sin((j+1)*M_PI/n)+r*len);
				glEnd();

				glBegin(GL_POLYGON);
				glNormal3d(sin((i)*M_PI/n)*cos((j)*M_PI/n),cos((i)*M_PI/n)*cos((j)*M_PI/n),-ratioBotton*sin((j)*M_PI/n)-len);
				glVertex3d(r*sin(i*M_PI/n)*cos(j*M_PI/n),r*cos(i*M_PI/n)*cos(j*M_PI/n),-r*ratioBotton*sin(j*M_PI/n)-r*len);
			    // your normal here
				glNormal3d(sin((i+1)*M_PI/n)*cos((j)*M_PI/n),cos((i+1)*M_PI/n)*cos((j)*M_PI/n),-ratioBotton*sin((j)*M_PI/n)-len);
				glVertex3d(r*sin((i+1)*M_PI/n)*cos(j*M_PI/n),r*cos((i+1)*M_PI/n)*cos(j*M_PI/n),-r*ratioBotton*sin(j*M_PI/n)-r*len);
			    // your normal here
				glNormal3d(sin((i+1)*M_PI/n)*cos((j+1)*M_PI/n),cos((i+1)*M_PI/n)*cos((j+1)*M_PI/n),-ratioBotton*sin((j+1)*M_PI/n)-len);
				glVertex3d(r*sin((i+1)*M_PI/n)*cos((j+1)*M_PI/n),r*cos((i+1)*M_PI/n)*cos((j+1)*M_PI/n),-r*ratioBotton*sin((j+1)*M_PI/n)-r*len);
			    // your normal here
				glNormal3d(sin((i)*M_PI/n)*cos((j+1)*M_PI/n),cos((i)*M_PI/n)*cos((j+1)*M_PI/n),-ratioBotton*sin((j+1)*M_PI/n)-len);
				glVertex3d(r*sin(i*M_PI/n)*cos((j+1)*M_PI/n),r*cos(i*M_PI/n)*cos((j+1)*M_PI/n),-r*ratioBotton*sin((j+1)*M_PI/n)-r*len);
				glEnd();
			}

		} else	{
			glBegin(GL_POLYGON);
			    // Explanation: the normal of the whole polygon is the coordinate of the center of the polygon for a sphere
			    glNormal3d(sin((i+0.5)*M_PI/n)/2,cos((i+0.5)*M_PI/n)/2,0);
				glVertex3d(r*sin((i)*M_PI/n),r*cos((i)*M_PI/n),r*len);
				glVertex3d(r*sin((i+1)*M_PI/n),r*cos((i+1)*M_PI/n),r*len);
				glVertex3d(r*sin((i+1)*M_PI/n),r*cos((i+1)*M_PI/n),-r*len);
				glVertex3d(r*sin((i)*M_PI/n),r*cos((i)*M_PI/n),-r*len);
 			glEnd();

			 for(j=0;j<n;j++){
				 glBegin(GL_POLYGON);
			    // Explanation: the normal of the whole polygon is the coordinate of the center of the polygon for a sphere
			    glNormal3d(sin((i+0.5)*M_PI/n)*cos((j+0.5)*M_PI/n),cos((i+0.5)*M_PI/n)*cos((j+0.5)*M_PI/n),ratioHead*sin((j+0.5)*M_PI/n)+len);
				glVertex3d(r*sin(i*M_PI/n)*cos(j*M_PI/n),r*cos(i*M_PI/n)*cos(j*M_PI/n),r*ratioHead*sin(j*M_PI/n)+r*len);
				glVertex3d(r*sin((i+1)*M_PI/n)*cos(j*M_PI/n),r*cos((i+1)*M_PI/n)*cos(j*M_PI/n),r*ratioHead*sin(j*M_PI/n)+r*len);
				glVertex3d(r*sin((i+1)*M_PI/n)*cos((j+1)*M_PI/n),r*cos((i+1)*M_PI/n)*cos((j+1)*M_PI/n),r*ratioHead*sin((j+1)*M_PI/n)+r*len);
				glVertex3d(r*sin(i*M_PI/n)*cos((j+1)*M_PI/n),r*cos(i*M_PI/n)*cos((j+1)*M_PI/n),r*ratioHead*sin((j+1)*M_PI/n)+r*len);
 				glEnd();

				 glBegin(GL_POLYGON);
			    // Explanation: the normal of the whole polygon is the coordinate of the center of the polygon for a sphere
			    glNormal3d(sin((i+0.5)*M_PI/n)*cos((j+0.5)*M_PI/n),cos((i+0.5)*M_PI/n)*cos((j+0.5)*M_PI/n),-ratioBotton*sin((j+0.5)*M_PI/n)-len);
				glVertex3d(r*sin(i*M_PI/n)*cos(j*M_PI/n),r*cos(i*M_PI/n)*cos(j*M_PI/n),-r*ratioBotton*sin(j*M_PI/n)-r*len);
				glVertex3d(r*sin((i+1)*M_PI/n)*cos(j*M_PI/n),r*cos((i+1)*M_PI/n)*cos(j*M_PI/n),-r*ratioBotton*sin(j*M_PI/n)-r*len);
				glVertex3d(r*sin((i+1)*M_PI/n)*cos((j+1)*M_PI/n),r*cos((i+1)*M_PI/n)*cos((j+1)*M_PI/n),-r*ratioBotton*sin((j+1)*M_PI/n)-r*len);
				glVertex3d(r*sin(i*M_PI/n)*cos((j+1)*M_PI/n),r*cos(i*M_PI/n)*cos((j+1)*M_PI/n),-r*ratioBotton*sin((j+1)*M_PI/n)-r*len);
 				glEnd();
			 }
		}
}

void drawGlass(double r)
{
	int i,j;
	int n = 20;
	int len = 1.0;
	double ratio = 0.7;
	for(i=0;i<2*n;i++)
		if(m_Smooth)
		{
			glBegin(GL_POLYGON);
			    // Explanation: the normal of the whole polygon is the coordinate of the center of the polygon for a sphere
				glNormal3d(sin((i)*M_PI/n),cos((i)*M_PI/n),len);
				glVertex3d(r*sin((i)*M_PI/n),r*cos((i)*M_PI/n),r*len);
				glNormal3d(sin((i+1)*M_PI/n),cos((i+1)*M_PI/n),len);
				glVertex3d(r*sin((i+1)*M_PI/n),r*cos((i+1)*M_PI/n),r*len);
				glNormal3d(ratio*sin((i+1)*M_PI/n),ratio*cos((i+1)*M_PI/n),len);
				glVertex3d(r*ratio*sin((i+1)*M_PI/n),r*ratio*cos((i+1)*M_PI/n),r*len);
				glNormal3d(ratio*sin((i)*M_PI/n),ratio*cos((i)*M_PI/n),len);
				glVertex3d(r*ratio*sin((i)*M_PI/n),r*ratio*cos((i)*M_PI/n),r*len);
 			glEnd();


			glBegin(GL_POLYGON);
			    // Explanation: the normal of the whole polygon is the coordinate of the center of the polygon for a sphere
			    glNormal3d(sin((i)*M_PI/n),cos((i)*M_PI/n),len);
				glVertex3d(r*sin((i)*M_PI/n),r*cos((i)*M_PI/n),r*len);
				glNormal3d(sin((i+1)*M_PI/n),cos((i+1)*M_PI/n),len);
				glVertex3d(r*sin((i+1)*M_PI/n),r*cos((i+1)*M_PI/n),r*len);
				glNormal3d(sin((i+1)*M_PI/n),cos((i+1)*M_PI/n),-len);
				glVertex3d(r*sin((i+1)*M_PI/n),r*cos((i+1)*M_PI/n),-r*len);
				glNormal3d(sin((i)*M_PI/n),cos((i)*M_PI/n),-len);
				glVertex3d(r*sin((i)*M_PI/n),r*cos((i)*M_PI/n),-r*len);
 			glEnd();

		} else	{
			glBegin(GL_POLYGON);
			    // Explanation: the normal of the whole polygon is the coordinate of the center of the polygon for a sphere
			    glNormal3d(sin((i+0.5)*M_PI/n)/2,ratio*cos((i+0.5)*M_PI/n)/2,r*len);
				glVertex3d(r*sin((i)*M_PI/n),r*cos((i)*M_PI/n),r*len);
				glVertex3d(r*sin((i+1)*M_PI/n),r*cos((i+1)*M_PI/n),r*len);
				glVertex3d(r*ratio*sin((i+1)*M_PI/n),r*ratio*cos((i+1)*M_PI/n),r*len);
				glVertex3d(r*ratio*sin((i)*M_PI/n),r*ratio*cos((i)*M_PI/n),r*len);
 			glEnd();

			glBegin(GL_POLYGON);
			    // Explanation: the normal of the whole polygon is the coordinate of the center of the polygon for a sphere
			    glNormal3d(sin((i+0.5)*M_PI/n)/2,cos((i+0.5)*M_PI/n)/2,0);
				glVertex3d(r*sin((i)*M_PI/n),r*cos((i)*M_PI/n),r*len);
				glVertex3d(r*sin((i+1)*M_PI/n),r*cos((i+1)*M_PI/n),r*len);
				glVertex3d(r*sin((i+1)*M_PI/n),r*cos((i+1)*M_PI/n),-r*len);
				glVertex3d(r*sin((i)*M_PI/n),r*cos((i)*M_PI/n),-r*len);
 			glEnd();
		}
}
void drawMinionsEye(double r)
{
	glPushMatrix();
			glTranslatef(0.0f,-1.0f,1.0f);
			changeColor(1.0f,1.0f,1.0f,1.0f);
			drawSphere(0.4);

		glPushMatrix();
			changeColor(0.64f,0.32f,0.17f,1.0f);
			glTranslatef(0.0f,-0.22f,0.0f);
			drawSphere(0.2);
		glPopMatrix();

		glPushMatrix();
			changeColor(0.0f,0.0f,0.0f,1.0f);
			glTranslatef(0.0f,-0.33f,0.0f);
			drawSphere(0.1);
		glPopMatrix();

		glPushMatrix();
			glRotatef(90,1.0f,0.0f,0.0f);
			changeColor(0.768f, 0.768f, 0.768f, 1.0f);
			drawGlass(0.44);
		glPopMatrix();

		glPushMatrix();
			changeColor(0.0f,0.0f,0.0f,1.0f);
			glTranslatef(0.0f,1.0f,-0.0f);
			drawRing(1.1);
		glPopMatrix();
	glPopMatrix();
}
void drawMouseOne(double r)
{
	int i,j;
	int n = 20;
	double len = 0.015;
	double adder;
	double addernext;
	for(i=0;i<2*n;i++)
	{
		if (i<n)
		{
			adder = -0.3*sin((i-10)*M_PI/n)+0.35;
			addernext = -0.3*sin((i+1-10)*M_PI/n)+0.35;
		}
		else
		{
			adder = 0.3*sin((i+10)*M_PI/n)+0.35;
			addernext = 0.3*sin((i+1+10)*M_PI/n)+0.35;
		}
		if(i>=18 && i <22)
		if(m_Smooth)
		{
			glBegin(GL_POLYGON);
			    // Explanation: the normal of the whole polygon is the coordinate of the center of the polygon for a sphere
			    glNormal3d(0,0,len);
				glVertex3d(0.0f,0.0f,r*len);
				glNormal3d(sin((i)*M_PI/n),cos((i)*M_PI/n),len +r* adder);
				glVertex3d(r*sin((i)*M_PI/n),r*cos((i)*M_PI/n),r*len +r* adder);
				glNormal3d(sin((i+1)*M_PI/n),cos((i+1)*M_PI/n),len + addernext);
				glVertex3d(r*sin((i+1)*M_PI/n),r*cos((i+1)*M_PI/n),r*len +r* addernext);
 			glEnd();

			glBegin(GL_POLYGON);
			    // Explanation: the normal of the whole polygon is the coordinate of the center of the polygon for a sphere
			    glNormal3d(sin((i)*M_PI/n),cos((i)*M_PI/n),len + adder);
				glVertex3d(r*sin((i)*M_PI/n),r*cos((i)*M_PI/n),r*len +r* adder);

				glNormal3d(sin((i+1)*M_PI/n),cos((i+1)*M_PI/n),len + addernext);
				glVertex3d(r*sin((i+1)*M_PI/n),r*cos((i+1)*M_PI/n),r*len +r* addernext);

				glNormal3d(sin((i+1)*M_PI/n),cos((i+1)*M_PI/n),-len + addernext);
				glVertex3d(r*sin((i+1)*M_PI/n),r*cos((i+1)*M_PI/n),-r*len +r* addernext);

				glNormal3d(sin((i)*M_PI/n),cos((i)*M_PI/n),-len + adder);
				glVertex3d(r*sin((i)*M_PI/n),r*cos((i)*M_PI/n),-r*len +r* adder);
 			glEnd();

			glBegin(GL_POLYGON);
			    // Explanation: the normal of the whole polygon is the coordinate of the center of the polygon for a sphere
			    glNormal3d(0,0,-len + adder);
				glVertex3d(0.0f,0.0f,-r*len +r* adder);
				glNormal3d(sin((i)*M_PI/n),cos((i)*M_PI/n),-len + adder);
				glVertex3d(r*sin((i)*M_PI/n),r*cos((i)*M_PI/n),-r*len +r* adder);
				glNormal3d(sin((i+1)*M_PI/n),cos((i+1)*M_PI/n),-len + addernext);
				glVertex3d(r*sin((i+1)*M_PI/n),r*cos((i+1)*M_PI/n),-r*len +r* addernext);
 			glEnd();
		} else	{
			glBegin(GL_POLYGON);
			    // Explanation: the normal of the whole polygon is the coordinate of the center of the polygon for a sphere
			    glNormal3d(sin((i+0.5)*M_PI/n)/2,cos((i+0.5)*M_PI/n)/2,r*len + adder);
				glVertex3d(0.0f,0.0f,r*len);
				glVertex3d(r*sin((i)*M_PI/n),r*cos((i)*M_PI/n),r*len +r* adder);
				glVertex3d(r*sin((i+1)*M_PI/n),r*cos((i+1)*M_PI/n),r*len +r* addernext);
 			glEnd();

			glBegin(GL_POLYGON);
			    // Explanation: the normal of the whole polygon is the coordinate of the center of the polygon for a sphere
			    glNormal3d(sin((i+0.5)*M_PI/n)/2,cos((i+0.5)*M_PI/n)/2,0 + adder);
				glVertex3d(r*sin((i)*M_PI/n),r*cos((i)*M_PI/n),r*len +r* adder);
				glVertex3d(r*sin((i+1)*M_PI/n),r*cos((i+1)*M_PI/n),r*len +r* addernext);
				glVertex3d(r*sin((i+1)*M_PI/n),r*cos((i+1)*M_PI/n),-r*len +r* addernext);
				glVertex3d(r*sin((i)*M_PI/n),r*cos((i)*M_PI/n),-r*len +r* adder);
 			glEnd();

			glBegin(GL_POLYGON);
			    // Explanation: the normal of the whole polygon is the coordinate of the center of the polygon for a sphere
			    glNormal3d(sin((i+0.5)*M_PI/n)/2,cos((i+0.5)*M_PI/n)/2,-len + adder);
				glVertex3d(0.0f,0.0f,-r*len );
				glVertex3d(r*sin((i)*M_PI/n),r*cos((i)*M_PI/n),-r*len +r* adder);
				glVertex3d(r*sin((i+1)*M_PI/n),r*cos((i+1)*M_PI/n),-r*len +r* addernext);
 			glEnd();
		}
	}
}
void drawMinionsMouse(double r)
{
	glPushMatrix();
		glTranslatef(0.0f,0.0f,0.3f);
		changeColor(1.0f,1.0f,1.0f,1.0f);
		drawMouseOne(1.035);		
	glPopMatrix();
}

void drawMinionsHand(double r)
{
	changeColor(1.0f,1.0f,0.0f,1.0f);	
	glPushMatrix();
		glTranslatef(1.1f,0.0f,-0.3f);
		glRotatef(-45,0,1,0);	
		drawCylindrical(0.12,4);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(1.4f,0.0f,-0.6f);
		drawSphere(0.15);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(-1.1f,0.0f,-0.3f);
		glRotatef(45,0,1,0);
		drawCylindrical(0.12,4);
	glPopMatrix();
	glPushMatrix();
		glTranslatef(-1.4f,0.0f,-0.6f);
		drawSphere(0.15);
	glPopMatrix();

	changeColor(0.0f,0.0f,0.0f,1.0f);	
	glPushMatrix();
		glTranslatef(1.55f,0.0f,-0.4f);
		glRotatef(25,0,1,0);
		drawCylindrical(0.03,15);
	glPopMatrix();

	changeColor(0.3f,0.76f,0.44f,0.3f);
	glPushMatrix();
		glTranslatef(1.82f,0.0f,0.25f);	
		drawSphere(0.4);
	glPopMatrix();
}
void drawClotheOne(double r)
{	
    int i,j;
	int n = 20;
	double len = 0.1;
	double adder;
	double addernext;
	for(i=0;i<2*n;i++)
	{
		if (i<n)
		{
			adder = 0.24*sin((i)*M_PI/n);
			addernext = 0.24*sin((i+1)*M_PI/n);
		}
		else
		{
			adder = -0.24*sin((i)*M_PI/n);
			addernext = -0.24*sin((i+1)*M_PI/n);
		}
		if(m_Smooth)
		{
			glBegin(GL_POLYGON);
			    // Explanation: the normal of the whole polygon is the coordinate of the center of the polygon for a sphere
			    glNormal3d(0,0,len);
				glVertex3d(0.0f,0.0f,r*len);
				glNormal3d(sin((i)*M_PI/n),cos((i)*M_PI/n),len +r* adder);
				glVertex3d(r*sin((i)*M_PI/n),r*cos((i)*M_PI/n),r*len +r* adder);
				glNormal3d(sin((i+1)*M_PI/n),cos((i+1)*M_PI/n),len + addernext);
				glVertex3d(r*sin((i+1)*M_PI/n),r*cos((i+1)*M_PI/n),r*len +r* addernext);
 			glEnd();

			glBegin(GL_POLYGON);
			    // Explanation: the normal of the whole polygon is the coordinate of the center of the polygon for a sphere
			    glNormal3d(sin((i)*M_PI/n),cos((i)*M_PI/n),len + adder);
				glVertex3d(r*sin((i)*M_PI/n),r*cos((i)*M_PI/n),r*len +r* adder);

				glNormal3d(sin((i+1)*M_PI/n),cos((i+1)*M_PI/n),len + addernext);
				glVertex3d(r*sin((i+1)*M_PI/n),r*cos((i+1)*M_PI/n),r*len +r* addernext);

				glNormal3d(sin((i+1)*M_PI/n),cos((i+1)*M_PI/n),-len + addernext);
				glVertex3d(r*sin((i+1)*M_PI/n),r*cos((i+1)*M_PI/n),-r*len +r* addernext);

				glNormal3d(sin((i)*M_PI/n),cos((i)*M_PI/n),-len + adder);
				glVertex3d(r*sin((i)*M_PI/n),r*cos((i)*M_PI/n),-r*len +r* adder);
 			glEnd();

			glBegin(GL_POLYGON);
			    // Explanation: the normal of the whole polygon is the coordinate of the center of the polygon for a sphere
			    glNormal3d(0,0,-len + adder);
				glVertex3d(0.0f,0.0f,-r*len +r* adder);
				glNormal3d(sin((i)*M_PI/n),cos((i)*M_PI/n),-len + adder);
				glVertex3d(r*sin((i)*M_PI/n),r*cos((i)*M_PI/n),-r*len +r* adder);
				glNormal3d(sin((i+1)*M_PI/n),cos((i+1)*M_PI/n),-len + addernext);
				glVertex3d(r*sin((i+1)*M_PI/n),r*cos((i+1)*M_PI/n),-r*len +r* addernext);
 			glEnd();
		} else	{
			glBegin(GL_POLYGON);
			    // Explanation: the normal of the whole polygon is the coordinate of the center of the polygon for a sphere
			    glNormal3d(sin((i+0.5)*M_PI/n)/2,cos((i+0.5)*M_PI/n)/2,r*len + adder);
				glVertex3d(0.0f,0.0f,r*len);
				glVertex3d(r*sin((i)*M_PI/n),r*cos((i)*M_PI/n),r*len +r* adder);
				glVertex3d(r*sin((i+1)*M_PI/n),r*cos((i+1)*M_PI/n),r*len +r* addernext);
 			glEnd();

			glBegin(GL_POLYGON);
			    // Explanation: the normal of the whole polygon is the coordinate of the center of the polygon for a sphere
			    glNormal3d(sin((i+0.5)*M_PI/n)/2,cos((i+0.5)*M_PI/n)/2,0 + adder);
				glVertex3d(r*sin((i)*M_PI/n),r*cos((i)*M_PI/n),r*len +r* adder);
				glVertex3d(r*sin((i+1)*M_PI/n),r*cos((i+1)*M_PI/n),r*len +r* addernext);
				glVertex3d(r*sin((i+1)*M_PI/n),r*cos((i+1)*M_PI/n),-r*len +r* addernext);
				glVertex3d(r*sin((i)*M_PI/n),r*cos((i)*M_PI/n),-r*len +r* adder);
 			glEnd();

			glBegin(GL_POLYGON);
			    // Explanation: the normal of the whole polygon is the coordinate of the center of the polygon for a sphere
			    glNormal3d(sin((i+0.5)*M_PI/n)/2,cos((i+0.5)*M_PI/n)/2,-len + adder);
				glVertex3d(0.0f,0.0f,-r*len );
				glVertex3d(r*sin((i)*M_PI/n),r*cos((i)*M_PI/n),-r*len +r* adder);
				glVertex3d(r*sin((i+1)*M_PI/n),r*cos((i+1)*M_PI/n),-r*len +r* addernext);
 			glEnd();
		}
	}
}
void drawClotheTwo(double r)
{	
    int i,j;
	int n = 20;
	double len = 0.52;
	for(i=0;i<2*n;i++)
		if(m_Smooth)
		{
			if(i<4 || (i>=16 && i<24) || i>=36){
				glBegin(GL_POLYGON);
					// Explanation: the normal of the whole polygon is the coordinate of the center of the polygon for a sphere
					glNormal3d(0,0,len);
					glVertex3d(0.0f,0.0f,r*len);
					glNormal3d(sin((i)*M_PI/n),cos((i)*M_PI/n),len);
					glVertex3d(r*sin((i)*M_PI/n),r*cos((i)*M_PI/n),r*len);
					glNormal3d(sin((i+1)*M_PI/n),cos((i+1)*M_PI/n),len);
					glVertex3d(r*sin((i+1)*M_PI/n),r*cos((i+1)*M_PI/n),r*len);
 				glEnd();

				glBegin(GL_POLYGON);
					// Explanation: the normal of the whole polygon is the coordinate of the center of the polygon for a sphere
					glNormal3d(sin((i)*M_PI/n),cos((i)*M_PI/n),len);
					glVertex3d(r*sin((i)*M_PI/n),r*cos((i)*M_PI/n),r*len);
					glNormal3d(sin((i+1)*M_PI/n),cos((i+1)*M_PI/n),len);
					glVertex3d(r*sin((i+1)*M_PI/n),r*cos((i+1)*M_PI/n),r*len);
					glNormal3d(sin((i+1)*M_PI/n),cos((i+1)*M_PI/n),-len);
					glVertex3d(r*sin((i+1)*M_PI/n),r*cos((i+1)*M_PI/n),-r*len);
					glNormal3d(sin((i)*M_PI/n),cos((i)*M_PI/n),-len);
					glVertex3d(r*sin((i)*M_PI/n),r*cos((i)*M_PI/n),-r*len);
 				glEnd();

				glBegin(GL_POLYGON);
					// Explanation: the normal of the whole polygon is the coordinate of the center of the polygon for a sphere
					glNormal3d(0,0,-len);
					glVertex3d(0.0f,0.0f,-r*len);
					glNormal3d(sin((i)*M_PI/n),cos((i)*M_PI/n),-len);
					glVertex3d(r*sin((i)*M_PI/n),r*cos((i)*M_PI/n),-r*len);
					glNormal3d(sin((i+1)*M_PI/n),cos((i+1)*M_PI/n),-len);
					glVertex3d(r*sin((i+1)*M_PI/n),r*cos((i+1)*M_PI/n),-r*len);
 				glEnd();
			}
		} else	{
			if(i<4 || (i>=16 && i<24) || i>=36){
				glBegin(GL_POLYGON);
					// Explanation: the normal of the whole polygon is the coordinate of the center of the polygon for a sphere
					glNormal3d(sin((i+0.5)*M_PI/n)/2,cos((i+0.5)*M_PI/n)/2,r*len);
					glVertex3d(0.0f,0.0f,r*len);
					glVertex3d(r*sin((i)*M_PI/n),r*cos((i)*M_PI/n),r*len);
					glVertex3d(r*sin((i+1)*M_PI/n),r*cos((i+1)*M_PI/n),r*len);
 				glEnd();

				glBegin(GL_POLYGON);
					// Explanation: the normal of the whole polygon is the coordinate of the center of the polygon for a sphere
					glNormal3d(sin((i+0.5)*M_PI/n)/2,cos((i+0.5)*M_PI/n)/2,0);
					glVertex3d(r*sin((i)*M_PI/n),r*cos((i)*M_PI/n),r*len);
					glVertex3d(r*sin((i+1)*M_PI/n),r*cos((i+1)*M_PI/n),r*len);
					glVertex3d(r*sin((i+1)*M_PI/n),r*cos((i+1)*M_PI/n),-r*len);
					glVertex3d(r*sin((i)*M_PI/n),r*cos((i)*M_PI/n),-r*len);
 				glEnd();

				glBegin(GL_POLYGON);
					// Explanation: the normal of the whole polygon is the coordinate of the center of the polygon for a sphere
					glNormal3d(sin((i+0.5)*M_PI/n)/2,cos((i+0.5)*M_PI/n)/2,len);
					glVertex3d(0.0f,0.0f,-r*len);
					glVertex3d(r*sin((i)*M_PI/n),r*cos((i)*M_PI/n),-r*len);
					glVertex3d(r*sin((i+1)*M_PI/n),r*cos((i+1)*M_PI/n),-r*len);
 				glEnd();
			}
		}

}
void drawClotheThree(double r)
{
	int i,j;
	int n = 20;
	double len = 1;
	double lenOne = 1;
	double ratioBotton = 0.6;
	for(i=0;i<2*n;i++)
		if(m_Smooth)
		{
			glBegin(GL_POLYGON);
			    // Explanation: the normal of the whole polygon is the coordinate of the center of the polygon for a sphere
			    glNormal3d(sin((i)*M_PI/n),cos((i)*M_PI/n),-lenOne/4);
				glVertex3d(r*sin((i)*M_PI/n),r*cos((i)*M_PI/n),-r*lenOne/2);
				glNormal3d(sin((i+1)*M_PI/n),cos((i+1)*M_PI/n),-lenOne/2);
				glVertex3d(r*sin((i+1)*M_PI/n),r*cos((i+1)*M_PI/n),-r*lenOne/2);
				glNormal3d(sin((i+1)*M_PI/n),cos((i+1)*M_PI/n),-lenOne);
				glVertex3d(r*sin((i+1)*M_PI/n),r*cos((i+1)*M_PI/n),-r*lenOne);
				glNormal3d(sin((i)*M_PI/n),cos((i)*M_PI/n),-lenOne);
				glVertex3d(r*sin((i)*M_PI/n),r*cos((i)*M_PI/n),-r*lenOne);
 			glEnd();
			
			for(j=0;j<n;j++){
				glBegin(GL_POLYGON);
				glNormal3d(sin((i)*M_PI/n)*cos((j)*M_PI/n),cos((i)*M_PI/n)*cos((j)*M_PI/n),-ratioBotton*sin((j)*M_PI/n)-len);
				glVertex3d(r*sin(i*M_PI/n)*cos(j*M_PI/n),r*cos(i*M_PI/n)*cos(j*M_PI/n),-r*ratioBotton*sin(j*M_PI/n)-r*len);
				// your normal here
				glNormal3d(sin((i+1)*M_PI/n)*cos((j)*M_PI/n),cos((i+1)*M_PI/n)*cos((j)*M_PI/n),-ratioBotton*sin((j)*M_PI/n)-len);
				glVertex3d(r*sin((i+1)*M_PI/n)*cos(j*M_PI/n),r*cos((i+1)*M_PI/n)*cos(j*M_PI/n),-r*ratioBotton*sin(j*M_PI/n)-r*len);
				// your normal here
				glNormal3d(sin((i+1)*M_PI/n)*cos((j+1)*M_PI/n),cos((i+1)*M_PI/n)*cos((j+1)*M_PI/n),-ratioBotton*sin((j+1)*M_PI/n)-len);
				glVertex3d(r*sin((i+1)*M_PI/n)*cos((j+1)*M_PI/n),r*cos((i+1)*M_PI/n)*cos((j+1)*M_PI/n),-r*ratioBotton*sin((j+1)*M_PI/n)-r*len);
				// your normal here
				glNormal3d(sin((i)*M_PI/n)*cos((j+1)*M_PI/n),cos((i)*M_PI/n)*cos((j+1)*M_PI/n),-ratioBotton*sin((j+1)*M_PI/n)-len);
				glVertex3d(r*sin(i*M_PI/n)*cos((j+1)*M_PI/n),r*cos(i*M_PI/n)*cos((j+1)*M_PI/n),-r*ratioBotton*sin((j+1)*M_PI/n)-r*len);
				glEnd();
			}
			
		} else	{
			glBegin(GL_POLYGON);
			    // Explanation: the normal of the whole polygon is the coordinate of the center of the polygon for a sphere
			    glNormal3d(sin((i+0.5)*M_PI/n)/2,cos((i+0.5)*M_PI/n)/2,-lenOne/4);
				glVertex3d(r*sin((i)*M_PI/n),r*cos((i)*M_PI/n),-r*lenOne/2);
				glVertex3d(r*sin((i+1)*M_PI/n),r*cos((i+1)*M_PI/n),-r*lenOne/2);
				glVertex3d(r*sin((i+1)*M_PI/n),r*cos((i+1)*M_PI/n),-r*lenOne);
				glVertex3d(r*sin((i)*M_PI/n),r*cos((i)*M_PI/n),-r*lenOne);
 			glEnd();

			for(j=0;j<n;j++){
				glBegin(GL_POLYGON);
				// Explanation: the normal of the whole polygon is the coordinate of the center of the polygon for a sphere
				glNormal3d(sin((i+0.5)*M_PI/n)*cos((j+0.5)*M_PI/n),cos((i+0.5)*M_PI/n)*cos((j+0.5)*M_PI/n),-ratioBotton*sin((j+0.5)*M_PI/n)-len);
				glVertex3d(r*sin(i*M_PI/n)*cos(j*M_PI/n),r*cos(i*M_PI/n)*cos(j*M_PI/n),-r*ratioBotton*sin(j*M_PI/n)-r*len);
				glVertex3d(r*sin((i+1)*M_PI/n)*cos(j*M_PI/n),r*cos((i+1)*M_PI/n)*cos(j*M_PI/n),-r*ratioBotton*sin(j*M_PI/n)-r*len);
				glVertex3d(r*sin((i+1)*M_PI/n)*cos((j+1)*M_PI/n),r*cos((i+1)*M_PI/n)*cos((j+1)*M_PI/n),-r*ratioBotton*sin((j+1)*M_PI/n)-r*len);
				glVertex3d(r*sin(i*M_PI/n)*cos((j+1)*M_PI/n),r*cos(i*M_PI/n)*cos((j+1)*M_PI/n),-r*ratioBotton*sin((j+1)*M_PI/n)-r*len);
				glEnd();
			}
			
		}
}
void drawMinionsClothes(double r)
{

	glPushMatrix();
		changeColor(0.0f,0.0f,1.0f,1.0f);
		drawClotheOne(1.03);
		glPushMatrix();
			glTranslatef(0.0f,0.0f,-0.3f);
			drawClotheTwo(1.031);
		glPopMatrix();
		drawClotheThree(1.03);

		changeColor(0.0f,0.0f,0.0f,1.0f);
		glPushMatrix();
			glTranslatef(0.34f,-0.78f,0.07f);
			drawSphere(0.20);
		glPopMatrix();

		glPushMatrix();
			glTranslatef(-0.34f,-0.78f,0.07f);
			drawSphere(0.20);
		glPopMatrix();
	glPopMatrix();

}

void drawLegOne(double r)
{
	int i,j;
	int n = 20;
	double len = 0.6;
	double ratio = 0.6 ;
	for(i=0;i<2*n;i++)
		if(m_Smooth)
		{
			glBegin(GL_POLYGON);
			    // Explanation: the normal of the whole polygon is the coordinate of the center of the polygon for a sphere
			    glNormal3d(0,0,len);
				glVertex3d(0.0f,0.0f,r*len);
				glNormal3d(sin((i)*M_PI/n),cos((i)*M_PI/n),len);
				glVertex3d(r*sin((i)*M_PI/n),r*cos((i)*M_PI/n),r*len);
				glNormal3d(sin((i+1)*M_PI/n),cos((i+1)*M_PI/n),len);
				glVertex3d(r*sin((i+1)*M_PI/n),r*cos((i+1)*M_PI/n),r*len);
 			glEnd();

			glBegin(GL_POLYGON);
			    // Explanation: the normal of the whole polygon is the coordinate of the center of the polygon for a sphere
			    glNormal3d(sin((i)*M_PI/n),cos((i)*M_PI/n),len-1);
				glVertex3d(r*sin((i)*M_PI/n),r*cos((i)*M_PI/n),r*len);
				glNormal3d(sin((i+1)*M_PI/n),cos((i+1)*M_PI/n),len-1);
				glVertex3d(r*sin((i+1)*M_PI/n),r*cos((i+1)*M_PI/n),r*len);
				glNormal3d(ratio*sin((i+1)*M_PI/n),ratio*cos((i+1)*M_PI/n),-len-0.6);
				glVertex3d(ratio*r*sin((i+1)*M_PI/n),ratio*r*cos((i+1)*M_PI/n),-r*len);
				glNormal3d(ratio*sin((i)*M_PI/n),ratio*cos((i)*M_PI/n),-len-0.6);
				glVertex3d(ratio*r*sin((i)*M_PI/n),ratio*r*cos((i)*M_PI/n),-r*len);
 			glEnd();

			glBegin(GL_POLYGON);
			    // Explanation: the normal of the whole polygon is the coordinate of the center of the polygon for a sphere
			    glNormal3d(0,0,-len);
				glVertex3d(0.0f,0.0f,-r*len);
				glNormal3d(ratio*sin((i)*M_PI/n),ratio*cos((i)*M_PI/n),-len);
				glVertex3d(ratio*r*sin((i)*M_PI/n),ratio*r*cos((i)*M_PI/n),-r*len);
				glNormal3d(ratio*sin((i+1)*M_PI/n),ratio*cos((i+1)*M_PI/n),-len);
				glVertex3d(ratio*r*sin((i+1)*M_PI/n),ratio*r*cos((i+1)*M_PI/n),-r*len);
 			glEnd();
		} else	{
			glBegin(GL_POLYGON);
			    // Explanation: the normal of the whole polygon is the coordinate of the center of the polygon for a sphere
			    glNormal3d(sin((i+0.5)*M_PI/n)/2,cos((i+0.5)*M_PI/n)/2,r*len);
				glVertex3d(0.0f,0.0f,r*len);
				glVertex3d(r*sin((i)*M_PI/n),r*cos((i)*M_PI/n),r*len);
				glVertex3d(r*sin((i+1)*M_PI/n),r*cos((i+1)*M_PI/n),r*len);
 			glEnd();

			glBegin(GL_POLYGON);
			    // Explanation: the normal of the whole polygon is the coordinate of the center of the polygon for a sphere
			    glNormal3d(sin((i+0.5)*M_PI/n)/2,cos((i+0.5)*M_PI/n)/2,-0.6);
				glVertex3d(r*sin((i)*M_PI/n),r*cos((i)*M_PI/n),r*len);
				glVertex3d(r*sin((i+1)*M_PI/n),r*cos((i+1)*M_PI/n),r*len);
				glVertex3d(ratio*r*sin((i+1)*M_PI/n),ratio*r*cos((i+1)*M_PI/n),-r*len);
				glVertex3d(ratio*r*sin((i)*M_PI/n),ratio*r*cos((i)*M_PI/n),-r*len);
 			glEnd();

			glBegin(GL_POLYGON);
			    // Explanation: the normal of the whole polygon is the coordinate of the center of the polygon for a sphere
			    glNormal3d(sin((i+0.5)*M_PI/n)/2,cos((i+0.5)*M_PI/n)/2,-r*len);
				glVertex3d(0.0f,0.0f,-r*len);
				glVertex3d(ratio*r*sin((i)*M_PI/n),ratio*r*cos((i)*M_PI/n),-r*len);
				glVertex3d(ratio*r*sin((i+1)*M_PI/n),ratio*r*cos((i+1)*M_PI/n),-r*len);
 			glEnd();
		}
}

void drawFootOne(double r)
{
	int i,j;
	int n = 20;
	double len = 0.6;
	double ratioHead = 0.7;
	double ratio = 0.65 ;
	for(i=0;i<2*n;i++)
		if(m_Smooth)
		{
			for(j=0;j<n;j++){
				glBegin(GL_POLYGON);
				glNormal3d(ratio*sin((i)*M_PI/n)*cos((j)*M_PI/n),cos((i)*M_PI/n)*cos((j)*M_PI/n),ratioHead*sin((j)*M_PI/n)-0.5);
				glVertex3d(ratio*r*sin(i*M_PI/n)*cos(j*M_PI/n),r*cos(i*M_PI/n)*cos(j*M_PI/n),r*ratioHead*sin(j*M_PI/n));
			    // your normal here
				glNormal3d(ratio*sin((i+1)*M_PI/n)*cos((j)*M_PI/n),cos((i+1)*M_PI/n)*cos((j)*M_PI/n),ratioHead*sin((j)*M_PI/n)-0.5);
				glVertex3d(ratio*r*sin((i+1)*M_PI/n)*cos(j*M_PI/n),r*cos((i+1)*M_PI/n)*cos(j*M_PI/n),r*ratioHead*sin(j*M_PI/n));
			    // your normal here
				glNormal3d(ratio*sin((i+1)*M_PI/n)*cos((j+1)*M_PI/n),cos((i+1)*M_PI/n)*cos((j+1)*M_PI/n),ratioHead*sin((j+1)*M_PI/n)-0.5);
				glVertex3d(ratio*r*sin((i+1)*M_PI/n)*cos((j+1)*M_PI/n),r*cos((i+1)*M_PI/n)*cos((j+1)*M_PI/n),r*ratioHead*sin((j+1)*M_PI/n));
			    // your normal here
				glNormal3d(ratio*sin((i)*M_PI/n)*cos((j+1)*M_PI/n),cos((i)*M_PI/n)*cos((j+1)*M_PI/n),ratioHead*sin((j+1)*M_PI/n)-0.5);
				glVertex3d(ratio*r*sin(i*M_PI/n)*cos((j+1)*M_PI/n),r*cos(i*M_PI/n)*cos((j+1)*M_PI/n),r*ratioHead*sin((j+1)*M_PI/n));
				glEnd();
			}
			glBegin(GL_POLYGON);
			    // Explanation: the normal of the whole polygon is the coordinate of the center of the polygon for a sphere
			    glNormal3d(0,0,0);
				glVertex3d(0.0f,0.0f,0);
				glNormal3d(ratio*sin((i)*M_PI/n),cos((i)*M_PI/n),0);
				glVertex3d(ratio*r*sin((i)*M_PI/n),r*cos((i)*M_PI/n),0);
				glNormal3d(ratio*sin((i+1)*M_PI/n),cos((i+1)*M_PI/n),0);
				glVertex3d(ratio*r*sin((i+1)*M_PI/n),r*cos((i+1)*M_PI/n),0);
 			glEnd();
		} else	{
			for(j=0;j<n;j++){
				 glBegin(GL_POLYGON);
			    // Explanation: the normal of the whole polygon is the coordinate of the center of the polygon for a sphere
			    glNormal3d(ratio*sin((i+0.5)*M_PI/n)*cos((j+0.5)*M_PI/n),cos((i+0.5)*M_PI/n)*cos((j+0.5)*M_PI/n),ratioHead*sin((j+0.5)*M_PI/n)-0.6);
				glVertex3d(ratio*r*sin(i*M_PI/n)*cos(j*M_PI/n),r*cos(i*M_PI/n)*cos(j*M_PI/n),r*ratioHead*sin(j*M_PI/n));
				glVertex3d(ratio*r*sin((i+1)*M_PI/n)*cos(j*M_PI/n),r*cos((i+1)*M_PI/n)*cos(j*M_PI/n),r*ratioHead*sin(j*M_PI/n));
				glVertex3d(ratio*r*sin((i+1)*M_PI/n)*cos((j+1)*M_PI/n),r*cos((i+1)*M_PI/n)*cos((j+1)*M_PI/n),r*ratioHead*sin((j+1)*M_PI/n));
				glVertex3d(ratio*r*sin(i*M_PI/n)*cos((j+1)*M_PI/n),r*cos(i*M_PI/n)*cos((j+1)*M_PI/n),r*ratioHead*sin((j+1)*M_PI/n));
 				glEnd();
			}
			glBegin(GL_POLYGON);
			    // Explanation: the normal of the whole polygon is the coordinate of the center of the polygon for a sphere
			    glNormal3d(sin((i+0.5)*M_PI/n)/2,cos((i+0.5)*M_PI/n)/2,0);
				glVertex3d(0.0f,0.0f,0);
				glVertex3d(ratio*r*sin((i)*M_PI/n),r*cos((i)*M_PI/n),0);
				glVertex3d(ratio*r*sin((i+1)*M_PI/n),r*cos((i+1)*M_PI/n),0);
 			glEnd();
		}
}
void drawMinionsLegs(double r)
{
	glPushMatrix();
		glTranslatef(0.33f,0.0f,-1.7f);
		changeColor(0.0f,0.0f,1.0f,1.0f);
		drawLegOne(0.4);
		glTranslatef(0.0f,-0.12f,-0.3f);
		changeColor(0.16f,0.14f,0.13f,1.0f);
		drawFootOne(0.45);
	glPopMatrix();
	glPushMatrix();
		glTranslatef(-0.33f,0.0f,-1.7f);
		changeColor(0.0f,0.0f,1.0f,1.0f);
		drawLegOne(0.4);
		glTranslatef(0.0f,-0.12f,-0.3f);
		changeColor(0.16f,0.14f,0.13f,1.0f);
		drawFootOne(0.45);
	glPopMatrix();
}

void drawMinions(double r)
{	
	glPushMatrix();
		glRotatef(-90,1.0f,0.0f,0.0f);
		drawMinionsBody(r);
		drawMinionsEye(r);
		drawMinionsMouse(r);
		drawMinionsHand(r);
		drawMinionsClothes(r);
		drawMinionsLegs(r);
	glPopMatrix();
}
void drawOneChain()
{
	changeColor(1.0f,1.0f,0.0f,1.0f);	
	glPushMatrix();
		glTranslatef(0.0f,0.0f,0.0f);
		glRotatef(90,0,1,0);
		drawCylindrical(0.1,10);
	glPopMatrix();

	changeColor(0.1f,0.5f,0.8f,1.0f);
	glPushMatrix();
		glTranslatef(0.9f,0.0f,0.0f);
		drawSphere(0.2);
	glPopMatrix();
	glPushMatrix();
		glTranslatef(-0.9f,0.0f,0.0f);
		drawSphere(0.2);
	glPopMatrix();
}
void firstComposite()
{

	int i=0;
	for(i=1; i<=30; i++)
	{
		glPushMatrix();
			GLfloat theta2;
				theta2 =i*8;
			glTranslatef(0.0f,0.0f,(i-15)*0.35);
			glRotatef(theta2, 0.0, 0.0, 1.0);
			drawOneChain();
		glPopMatrix();
	}

}
void secondComposite()
{
	glScalef(0.2,0.2,0.2);

	int i=0;
	for(i=1; i<=10; i++)
	{
		glPushMatrix();
			double theta2;
			theta2 =i*M_PI/5;
			glTranslatef(7.0*sin(theta2),7.0*cos(theta2),0.0f);
			drawMinions(1);
		glPopMatrix();
	}
}
void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glPushMatrix();
		glTranslatef(0, 0, -6);

	    glRotatef(angle2, 1.0, 0.0, 0.0);
		glRotatef(angle, 0.0, 1.0, 0.0);

		glScalef(zoom,zoom,zoom);

		switch (current_object) {
		case 0:
			changeColor(0.1f,0.5f,0.8f,1.0f);
			drawSphere(1);
			break;
		case 1:
			drawMinions(1);
			break;
		case 2:
			// draw your first composite object here
			firstComposite();
			break;
		case 3:
			// draw your second composite object here
			secondComposite();
			break;
		case 4:
			break;
		default:
			break;
		};
	glPopMatrix();
	glutSwapBuffers ();
}




void keyboard (unsigned char key, int x, int y)
{
	switch (key) {
	case 'p':
	case 'P':
		glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
		break;			
	case 'w':
	case 'W':
		glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
		break;			
	case 'v':
	case 'V':
		glPolygonMode(GL_FRONT_AND_BACK,GL_POINT);
		break;			
	case 's':
	case 'S':
		m_Smooth = !m_Smooth;
		break;
	case 'h':
	case 'H':
		m_Highlight = !m_Highlight;
		break;

	case '1':
	case '2':
	case '3':
	case '4':
	case '5':
		current_object = key - '1';
		break;

	case 'Q':
	case 'q':
		exit(0);
	break;

	default:
	break;
	}

	glutPostRedisplay();
}



void
mouse(int button, int state, int x, int y)
{
  if (state == GLUT_DOWN) {
	mouseButton = button;
    moving = 1;
    startx = x;
    starty = y;
  }
  if (state == GLUT_UP) {
	mouseButton = button;
    moving = 0;
  }
}

void motion(int x, int y)
{
  if (moving) {
	if(mouseButton==GLUT_LEFT_BUTTON)
	{
		angle = angle + (x - startx);
		angle2 = angle2 + (y - starty);
	}
	else zoom += ((y-starty)*0.001);
    startx = x;
    starty = y;
	glutPostRedisplay();
  }
  
}

int main(int argc, char **argv)
{
	cout<<"CS3241 Lab 3"<< endl<< endl;

	cout << "1-4: Draw different objects"<<endl;
	cout << "S: Toggle Smooth Shading"<<endl;
	cout << "H: Toggle Highlight"<<endl;
	cout << "W: Draw Wireframe"<<endl;
	cout << "P: Draw Polygon"<<endl;
	cout << "V: Draw Vertices"<<endl;
	cout << "Q: Quit" <<endl<< endl;

	cout << "Left mouse click and drag: rotate the object"<<endl;
	cout << "Right mouse click and drag: zooming"<<endl;

	glutInit(&argc, argv);
	glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize (600, 600);
	glutInitWindowPosition (50, 50);
	glutCreateWindow ("CS3241 Assignment 3");
	glClearColor (1.0,1.0,1.0, 1.0);
	glutDisplayFunc(display);
	glutMouseFunc(mouse);
	glutMotionFunc(motion);
	glutKeyboardFunc(keyboard);
	setupLighting();
	glDisable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST); 
	glDepthMask(GL_TRUE);

    glMatrixMode(GL_PROJECTION);
    gluPerspective( /* field of view in degree */ 40.0,
  /* aspect ratio */ 1.0,
    /* Z near */ 1.0, /* Z far */ 80.0);
	glMatrixMode(GL_MODELVIEW);
	glutMainLoop();

	return 0;
}
