// CS3241Lab1.cpp : Defines the entry point for the console application.
#include <cmath>
#include <iostream>
#include "GL/glut.h"
#include <time.h> 

using namespace std;

#define numStars 100
#define numPlanets 9

class planet
{
public:
	float distFromRef;
	float angularSpeed;
	GLfloat color[3];
	float size;
	float angle;

	planet()
	{
		distFromRef = 0;
		angularSpeed = 0;
		color[0] = color[1] = color[2] = 0;
		size = 0;
		angle = 0;
	}
};


GLfloat M_PI = 3.14;
float alpha = 0.0, k=1;
float tx = 0.0, ty=0.0;
planet planetList[numPlanets];
int init_star=0;
double star_x[40];
double star_y[40];
double star_size[40];
bool clock_mode = 0;

void drawArc(double cx, double cy, float r,float rx, float ry, int startDeg, int endDeg)
{
	//oval
	int i;
	for(i=startDeg;i<=endDeg;i++)
		glVertex2f(cx+r*rx*cos(2.0*M_PI*i/360.0),
	cy+r*ry*sin(2.0*M_PI*i/360.0));
}

void drawSpiral()
{
	int i;
	double theta, nextTheta;
	double x1,y1;
	double x2,y2;
	glColor3f(1, 0.46, 0.75); // pink color
	glBegin(GL_POLYGON);
	for(i=0;i<180;i++) // angle in degree
	{
		theta = (3.141592654/180)*i; // convert degree to radian
		nextTheta = (3.141592654/180)*(i+1);
		x1 = sin(theta); y1 = cos(theta);
		x2 = sin(nextTheta); y2 = cos(nextTheta);
		glVertex2f( (i/360.0)*x1, (i/360.0)*y1);
		glVertex2f( ((i+1)/360.0)*x2, ((i+1)/360.0)*y2);
	}
	glEnd();
}

void drawWholeSpiral()
{
	drawSpiral();
	glScalef(-1,1,1);
	drawSpiral();
}


void drawArm()
{
	//arm
	glBegin(GL_POLYGON);
	glColor3f(1,1,0);
	glVertex2f(0,0);
	glVertex2f(3,0);
	glVertex2f(3,2);
	glVertex2f(0,2);
	glVertex2f(0,0);
	glEnd();

	glBegin(GL_LINE_STRIP);
	glColor3f(0,0,0);
	glVertex2f(0,0);
	glVertex2f(3,0);
	glVertex2f(3,2);
	glVertex2f(0,2);
	glVertex2f(0,0);
	glEnd();
}

void drawLeftHand()
{
	//hand
	glBegin(GL_POLYGON);
	glColor3f(1,1,1);
	glVertex2f(3,0);
	glVertex2f(4,0);
	glColor3f(1,1,1);
	drawArc(4, 1, 1, 1, 1, -90, 90);
	drawArc(3.5, 2, 0.5, 1, 1, 0, 180);
	glEnd();

	glBegin(GL_LINE_STRIP);
	glColor3f(0,0,0);
	glVertex2f(3,0);
	glVertex2f(4,0);
	drawArc(4, 1, 1, 1, 1, -90, 90);
	drawArc(3.5, 2, 0.5, 1, 1, 0, 180);
	glVertex2f(3,0);
	glEnd();
}
void drawRightHand()
{
	//hand
	glBegin(GL_POLYGON);
	glColor3f(1,1,1);
	glVertex2f(-3,0);
	drawArc(-3.5, 2, 0.5, 1, 1, 0, 180);
	drawArc(-4, 1, 1, 1, 1, 90, 270);
	glVertex2f(-3,0);
	glEnd();

	glBegin(GL_LINE_STRIP);
	glColor3f(0,0,0);
	glVertex2f(-3,0);
	drawArc(-3.5, 2, 0.5, 1, 1, 0, 180);
	drawArc(-4, 1, 1, 1, 1, 90, 270);
	glVertex2f(-3,0);
	glEnd();
}
void drawWing()
{
	glRotatef(360/30,0,0,1);
	glBegin(GL_POLYGON);
	glColor3f(1,1,1);
	drawArc(4.3, -2.4, 1.8, 3, 1, 0, 360);
	glEnd();

	glRotatef(-360/60,0,0,1);
	
	glBegin(GL_POLYGON);
	glColor3f(1,1,1);
	drawArc(4.1, -3.4, 1.5, 3, 1, 0, 360);
	glEnd();

	glRotatef(-360/30,0,0,1);

	glBegin(GL_POLYGON);
	glColor3f(1,1,1);
	drawArc(4.3, -3.6, 1.2, 3, 1, 0, 360);
	glEnd();
	glRotatef(360/60,0,0,1);

	glRotatef(360/30,0,0,1);
	glBegin(GL_LINE_STRIP);
	glColor3f(0,0,0);
	drawArc(4.3, -2.4, 1.8, 3, 1, -60, 260);
	glEnd();

	glRotatef(-360/60,0,0,1);
	
	glBegin(GL_LINE_STRIP);
	glColor3f(0,0,0);
	drawArc(4.1, -3.4, 1.5, 3, 1, -55, 30);
	glEnd();

	glRotatef(-360/30,0,0,1);

	glBegin(GL_LINE_STRIP);
	glColor3f(0,0,0);
	drawArc(4.3, -3.6, 1.2, 3, 1, -120, 30);
	glEnd();
	glRotatef(360/60,0,0,1);
}

void drawWand()
{
	glRotatef(360/10,0,0,1);
	glBegin(GL_LINE_STRIP);
	glColor3f(0,0,0);
	glVertex2f(-4.7,0.6);
	glVertex2f(-4.7,5);
	glEnd();
	glRotatef(-360/10,0,0,1);

	glBegin(GL_POLYGON);
	glColor3f(1,1,0);
	drawArc(-7, 1.5, 1.5, 1, 1, 0, 360);
	glEnd();

	glBegin(GL_POLYGON);
	glColor3f(1,1,1);
	drawArc(-7, 1.5, 1, 1, 1, 0, 360);
	glEnd();

	glBegin(GL_POLYGON);
	glColor3f(1,1,0);
	drawArc(-7, 1.5, 0.5, 1, 1, 0, 360);
	glEnd();

}

void drawBody()
{
	//body
	glBegin(GL_POLYGON);
	glColor3f(1,0,0);
	glVertex2f(-4.5,-5);
	glVertex2f(-2.5,1);
	glVertex2f(2.5,1);
	glVertex2f(4.5,-5);
	glEnd();

	glBegin(GL_POLYGON);
	//glColor3f(1,0.8,0);
	glColor3f(0,1,0);
	drawArc(0, -9, 4, 1.6, 1, 0, 360);
	glEnd();

	glBegin(GL_LINE_STRIP);
	glColor3f(0,0,0);
	drawArc(0, -8, 3, 1.6, 1, 60, 120);
	glVertex2f(-4.5,-5);
	glVertex2f(-2.5,1);
	glVertex2f(2.5,1);
	glVertex2f(4.5,-5);
	glEnd();
	//blouse
	glBegin(GL_POLYGON);
	glColor3f(1,1,0);
	drawArc(0, -0.2, 1.7, 1, 1, 0, 360);
	glEnd();

	glBegin(GL_LINE_STRIP);
	glColor3f(0,0,0);
	drawArc(0, -0.2, 1.7, 1, 1, 0, 360);
	glEnd();

	//foot
	glBegin(GL_POLYGON);
	glColor3f(1,1,1);
	drawArc(3, -4, 1.7, 1, 1.5, 0, 360);
	glEnd();
	
	glBegin(GL_LINE_STRIP);
	glColor3f(0,0,0);
	drawArc(3, -4, 1.7, 1, 1.5, 0, 360);
	glEnd();

	glBegin(GL_POLYGON);
	glColor3f(1,1,1);
	drawArc(-3, -4, 1.7, 1, 1.5, 0, 360);
	glEnd();
	
	glBegin(GL_LINE_STRIP);
	glColor3f(0,0,0);
	drawArc(-3, -4, 1.7, 1, 1.5, 0, 360);
	glEnd();

}

void drawAcce()
{
	glLineWidth(3);
	//mouse
	glBegin(GL_POLYGON);
	glColor3f(1,0,0);
	drawArc(4, 3, 1.1, 1, 1.3, 0, 360);
	glEnd();
	glBegin(GL_LINE_STRIP);
	glColor3f(0,0,0);
	drawArc(4, 3, 1.1, 1, 1.3, 0, 360);
	glEnd();

	//mouse
	glBegin(GL_POLYGON);
	glColor3f(1,0,0);
	drawArc(2, 3, 1.1, 1, 1.3, 0, 360);
	glEnd();
	glBegin(GL_LINE_STRIP);
	glColor3f(0,0,0);
	drawArc(2, 3, 1.1, 1, 1.3, 0, 360);
	glEnd();

	//mouse
	glBegin(GL_POLYGON);
	glColor3f(1,0,0);
	drawArc(2.2, 3, 0.6, 1, 1, 0, 360);
	glEnd();
	glBegin(GL_LINE_STRIP);
	glColor3f(0,0,0);
	drawArc(2.2, 3, 0.6, 1, 1, 0, 360);
	glEnd();
	//mouse
	glBegin(GL_POLYGON);
	glColor3f(1,0,0);
	drawArc(3.8, 3, 0.6, 1, 1, 0, 360);
	glEnd();
	glBegin(GL_LINE_STRIP);
	glColor3f(0,0,0);
	drawArc(3.8, 3, 0.6, 1, 1, 0, 360);
	glEnd();
	
	//mouse
	glBegin(GL_POLYGON);
	glColor3f(1,0,0);
	drawArc(3, 3, 0.9, 1, 1, 0, 360);
	glEnd();
	glBegin(GL_LINE_STRIP);
	glColor3f(0,0,0);
	drawArc(3, 3, 0.9, 1, 1, 0, 360);
	glEnd();
}

void drawFace()
{
	glLineWidth(3);

	//face
	glBegin(GL_POLYGON);
	glColor3f(1,1,1);
	drawArc(0, 0.2, 4.8, 1.3, 1, -40, -30);
	drawArc(0, 0.2, 5.1, 1.2, 1, -30, 30);	
	drawArc(-0.2, 3.5, 5.6, 1, 1, -10, 20);
	drawArc(5.6, -0.1, 5.6, 1, 1, 97, 127);
	drawArc(0, -1, 5.5, 1, 1, 70, 110);
	drawArc(-5.6, -0.1, 5.6, 1, 1, 53, 83);
	drawArc(0.2, 3.5, 5.6, 1, 1, 160, 190);
	drawArc(0, 0.2, 5.1, 1.2, 1, 150, 210);
	drawArc(0, 0.2, 4.8, 1.3, 1, 210, 220);
	drawArc(0, 5.7, 10, 1, 1, 247, 293);
	drawArc(0, 0.2, 4.8, 1.3, 1, -40, -39);
	glEnd();

	glColor3f(0,0,0);
	glBegin(GL_LINE_STRIP);
	drawArc(0, 0.2, 4.8, 1.3, 1, -40, -30);
	drawArc(0, 0.2, 5.1, 1.2, 1, -30, 30);	
	drawArc(-0.2, 3.5, 5.6, 1, 1, -10, 20);
	drawArc(5.6, -0.1, 5.6, 1, 1, 97, 127);
	drawArc(0, -1, 5.5, 1, 1, 70, 110);
	drawArc(-5.6, -0.1, 5.6, 1, 1, 53, 83);
	drawArc(0.2, 3.5, 5.6, 1, 1, 160, 190);
	drawArc(0, 0.2, 5.1, 1.2, 1, 150, 210);
	drawArc(0, 0.2, 4.8, 1.3, 1, 210, 220);
	drawArc(0, 5.7, 10, 1, 1, 247, 293);
	drawArc(0, 0.2, 4.8, 1.3, 1, -40, -39);
	glEnd();


	glColor3f(0,0,0);
	//left-eye
	glBegin(GL_POLYGON);
	drawArc(-3, 0.5, 0.4, 1, 1.5, 0, 360);
	glEnd();


	//right-eye
	glBegin(GL_POLYGON);
	drawArc(3, 0.5, 0.4, 1, 1.5, 0, 360);
	glEnd();

	//mouse
	glBegin(GL_POLYGON);
	glColor3f(1,1,0);
	drawArc(0, -2, 0.4, 1.5, 1, 0, 360);
	glEnd();
	glBegin(GL_LINE_STRIP);
	glColor3f(0,0,0);
	drawArc(0, -2, 0.4, 1.5, 1, 0, 360);
	glEnd();


	
	
	glBegin(GL_LINE_STRIP);
	drawArc(6, -6.5, 6, 1, 1, 80, 97);
	glEnd();

	glBegin(GL_LINE_STRIP);
	drawArc(5, -6.3, 5, 1, 1, 70, 85);
	glEnd();

	glBegin(GL_LINE_STRIP);
	drawArc(4, -6, 4, 1, 1, 50, 78);
	glEnd();

	glBegin(GL_LINE_STRIP);
	drawArc(-6, -6.5, 6, 1, 1, 83, 100);
	glEnd();

	glBegin(GL_LINE_STRIP);
	drawArc(-5, -6.3, 5, 1, 1, 95, 110);
	glEnd();

	glBegin(GL_LINE_STRIP);
	drawArc(-4, -6, 4, 1, 1, 102, 130);
	glEnd();

}


void drawHelloKitty(){
	drawWing();
	glScalef(-1, 1, 1);
	drawWing();

	glTranslatef(0,-1.5,0);

	glRotatef(360/15,0,0,1);
	glTranslatef(0.6,-3.2,0);
	drawArm();
	glTranslatef(-4.6,2.4,0);
	drawArm();
	glTranslatef(3,0.2,0);
	drawRightHand();
	glTranslatef(1,0.6,0);
	glRotatef(-360/15,0,0,1);	

	drawBody();
	
	glTranslatef(0,4,0); 
	drawFace();

	glTranslatef(0,-4,0); 
	glRotatef(360/15,0,0,1);
	glTranslatef(0.6,-3.2,0);
	drawLeftHand();
	glTranslatef(-0.6,3.2,0);
	glRotatef(-360/15,0,0,1);	

	drawWand();


	glTranslatef(0,4,0); 
	glRotatef(-360/15,0,0,1);
	glTranslatef(-1.1,1.7,0); 
	drawAcce();

}
void drawPlanetHelper(planet oneplanet){
	glBegin(GL_POLYGON);
	glColor3f(oneplanet.color[0],oneplanet.color[1],oneplanet.color[2]);
	drawArc(oneplanet.distFromRef*cos(oneplanet.angle), oneplanet.distFromRef*sin(oneplanet.angle), oneplanet.size, 1, 1, 0, 360);
	glEnd();
}
void drawPlanet(){
	planet planet1 = planet();
	planet1.angle = 0;
	planet1.angularSpeed = 60;
	planet1.color[0]= 0;
	planet1.color[1] = 0;
	planet1.color[2] = 1;
	planet1.distFromRef = 6;
	planet1.size = 0.6;

	planet planet2 = planet();
	planet2.angle = 0;
	planet2.angularSpeed = 30;
	planet2.color[0]= 0;
	planet2.color[1] = 1;
	planet2.color[2] = 1;
	planet2.distFromRef = 4;
	planet2.size = 0.7;

	planet planet3 = planet();
	planet3.angle = 30;
	planet3.angularSpeed = 60;
	planet3.color[0]= 0.2f;
	planet3.color[1] = 0.7f;
	planet3.color[2] = 0.5f;
	planet3.distFromRef =8;
	planet3.size = 0.6;

	planet planet2_one = planet();
	planet2_one.angle = 30;
	planet2_one.angularSpeed = 10;
	planet2_one.color[0]= 0.2f;
	planet2_one.color[1] = 0.3f;
	planet2_one.color[2] = 0.4f;
	planet2_one.distFromRef =1.2;
	planet2_one.size = 0.3;

	clock_t seconds = clock();
	double angle1= 360-pow(-1,clock_mode)*(float)seconds/1000/planet1.angularSpeed*360;
	glRotatef(angle1,0,0,1);
	drawPlanetHelper(planet1);
	glRotatef(-angle1,0,0,1);

	double angle2= 360-pow(-1,clock_mode)*(float)seconds/1000/planet2.angularSpeed*360;
	glRotatef(angle2,0,0,1);
	drawPlanetHelper(planet2);
	glTranslatef(planet2.distFromRef*cos(planet2.angle), planet2.distFromRef*sin(planet2.angle), 0);
	double angle2_one= 360-pow(-1,clock_mode)*(float)seconds/1000/planet2_one.angularSpeed*360;
	glRotatef(angle2_one,0,0,1);
	drawPlanetHelper(planet2_one);
	glRotatef(-angle2_one,0,0,1);
	glTranslatef(-planet2.distFromRef*cos(planet2.angle),-planet2.distFromRef*sin(planet2.angle), 0);
	glRotatef(-angle2,0,0,1);
	

	double angle3= 360-pow(-1,clock_mode)*(float)seconds/1000/planet3.angularSpeed*360;
	glRotatef(angle3,0,0,1);
	drawPlanetHelper(planet3);

	glTranslatef(planet3.distFromRef*cos(planet3.angle), planet3.distFromRef*sin(planet3.angle), 0);
	glTranslatef( 0,2.5 + 0.5*cos(angle3), 0);
    glScalef(0.1f, 0.1f, 0.1f);
	drawHelloKitty();
	glScalef(10.0f, 10.0f, 10.0f);
	glTranslatef( 0,-2.5-0.5*cos(angle3), 0);
	glTranslatef(-planet3.distFromRef*cos(planet3.angle), -planet3.distFromRef*sin(planet3.angle), 0);
	glRotatef(-angle3,0,0,1);



}

void drawOneStar(){
	//glVertex3f(-0.2,-0.1,0);
	//glVertex3f(0.2,-0.1,0);
	//glVertex3f(0.2,0.1,0);
	//glVertex3f(-0.2,0.1,0);
	
	glVertex3f(-0.07,-0.07,0);
	glVertex3f(0.07,-0.07,0);
	glVertex3f(0.07,0.07,0);
	glVertex3f(-0.07,0.07,0);
}
void drawStar(){

	clock_t seconds = clock();
	if (init_star==0){
		for (int i = 0; i<40; i++){

			star_x[i] = rand()%100/5.0;
			star_y[i] = rand()%100/5.0;
			star_size[i] = rand()%1000/1000.00;
			cout<<star_x[i]<<endl;
			cout<<star_y[i]<<endl;
			cout<<star_size[i]<<endl;
		}
		init_star = 1;

	}
	glTranslatef( -10, - 10, 0);
	for  (int i = 0; i<40; i++){
		glTranslatef( star_x[i], star_y[i], 0);

		double transparency=   cos(seconds/200 + 15*i);
		glScalef(star_size[i]*1.0f, star_size[i]*1.0f, star_size[i]*1.0f);	    
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glEnable(GL_BLEND);
		glColor4f(1,1,1,transparency);
		glBegin(GL_POLYGON);
		drawOneStar();

		glEnd();
		glScalef(1/star_size[i]*1.0f, 1/star_size[i]*1.0f, 1/star_size[i]*1.0f);
		glTranslatef( -star_x[i], -star_y[i], 0);
	}
	glTranslatef( 10,  10, 0);
}

void drawCenter(){
	glBegin(GL_POLYGON);
	glColor3f(1,1,0);
	drawArc(0, 0, 1.5, 1, 1, 0, 360);
	glEnd();
}

void reshape (int w, int h)
{
	glViewport (0, 0, (GLsizei) w, (GLsizei) h);

	glMatrixMode (GL_PROJECTION);
	glLoadIdentity();

	glOrtho(-10, 10, -10, 10, -10, 10);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void init(void)
{
	glClearColor (0.0, 0.0, 0.3, 1.0);
	glShadeModel (GL_SMOOTH);
	glEnable(GL_BLEND);
	glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	glPushMatrix();

	glScalef(k, k, k);	
	glTranslatef(tx, ty, 0);	
	glRotatef(alpha, 0, 0, 1);

	//draw stuff here!
	drawStar();
	drawCenter();
	drawPlanet();

	glPopMatrix();
	glFlush ();
}

void idle()
{
	//update animation here
	
	glutPostRedisplay();	//after updating, draw the screen again
}

void keyboard (unsigned char key, int x, int y)
{
	//keys to control scaling - k
	//keys to control rotation - alpha
	//keys to control translation - tx, ty
	switch (key) {

		case 'a':
			alpha+=10;
			glutPostRedisplay();
		break;

		case 'd':
			alpha-=10;
			glutPostRedisplay();
		break;

		case 'q':
			k+=0.1;
			glutPostRedisplay();
		break;

		case 'e':
			if(k>0.1)
				k-=0.1;
			glutPostRedisplay();
		break;

		case 'z':
			tx-=0.1;
			glutPostRedisplay();
		break;

		case 'c':
			tx+=0.1;
			glutPostRedisplay();
		break;

		case 's':
			ty-=0.1;
			glutPostRedisplay();
		break;

		case 'w':
			ty+=0.1;
			glutPostRedisplay();
		break;

		case 't':
			clock_mode = 1- clock_mode;
			glutPostRedisplay();
		break;

		default:
		break;
	}
}

int main(int argc, char **argv)
{
	cout<<"CS3241 Lab 2\n\n";
	cout<<"+++++CONTROL BUTTONS+++++++\n\n";
	cout<<"Scale Up/Down: Q/E\n";
	cout<<"Rotate Clockwise/Counter-clockwise: A/D\n";
	cout<<"Move Up/Down: W/S\n";
	cout<<"Move Left/Right: Z/C\n";

	glutInit(&argc, argv);
	glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize (600, 600);
	glutInitWindowPosition (50, 50);
	glutCreateWindow (argv[0]);
	init ();
	glutDisplayFunc(display);
	glutIdleFunc(idle);
	glutReshapeFunc(reshape);	
	//glutMouseFunc(mouse);
	glutKeyboardFunc(keyboard);
	glutMainLoop();

	return 0;
}
