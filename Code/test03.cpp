// test00.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <GL/glut.h>

void myDisplay();
void myKeyboard(unsigned char key, int x, int y);
void myReshape(GLint w, GLint h);


struct mycolor
{float R;float G;float B;};

struct mycolor MyColor;
 

int main(int argc, char** argv)
{
	
	MyColor.R=1.0; MyColor.G=1.0; MyColor.B=1.0;

	glutCreateWindow("สตั้2");     
	
	glutDisplayFunc(myDisplay);  
	glutKeyboardFunc(&myKeyboard);
	glutReshapeFunc(&myReshape);


	glutMainLoop();
}




void myDisplay()
{
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f); 
	glClear(GL_COLOR_BUFFER_BIT); 
	

	 glColor3f(	MyColor.R, MyColor.G, MyColor.B);

	glBegin(GL_POLYGON);        
		glVertex2f(-0.5, -0.5);        
		glVertex2f(-0.5, 0.5);        
		glVertex2f(0.5, 0.5);        
		glVertex2f(0.5, -0.5);    
	glEnd();


	glFlush(); 
}




void myKeyboard(unsigned char key, int x, int y)
{


	switch (key)
		{
		case'R':    
		case 'r':
			MyColor.R=1.0;
			MyColor.G=0.0;
			MyColor.B=0.0;
			break;
				
		case'G':    
		case 'g':
			MyColor.R=0.0;
			MyColor.G=1.0;
			MyColor.B=0.0;
			break;

		case'B':    
		case 'b':
			MyColor.R=0.0;
			MyColor.G=0.0;
			MyColor.B=1.0;
			break;
		case'Q':    
		case 'q':
			exit(0);
	}

	myDisplay();
	
}


void myReshape(GLint w, GLint h)
{

	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if(w<=h)
		gluOrtho2D(-2.0, 2.0, -2.0*(GLfloat)h/(GLfloat)w,
		2.0*(GLfloat)h/(GLfloat)w);
	else gluOrtho2D(-2.0*(GLfloat)w/(GLfloat)h,
		2.0*(GLfloat)w/(GLfloat)h, -2.0, 2.0);
	glMatrixMode(GL_MODELVIEW);

}