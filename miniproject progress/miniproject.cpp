#include "glut.h" 
#define WIN_POSX    400
#define WIN_POSY    400
#define WIN_WIDTH   400
#define WIN_HEIGHT  300

float angle = 0.0f;
float angle_1 = 0.0f;
float angle_2 = 0.0f;

void init( ) {
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glEnable(GL_DEPTH_TEST);
}

void reshape(GLsizei width, GLsizei height) {

	glViewport(0, 0, (GLsizei)width, (GLsizei)height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(120, 1, 2.0, 50);
	glMatrixMode(GL_MODELVIEW);
}

void display() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	glPushMatrix();
	glColor3f(1.0, 0.1, 0.1);
	glTranslatef(0.0, 1.0, -6.0);
	glRotatef(30, 0.0, 1.0, 0.0);
	glRotatef(angle, 0.0, 0.0, 1.0);
	glBegin(GL_POLYGON);
	glVertex3f(0.0, 0.0, 0.0);
	glVertex3f(0.0, 2.0, 0.0);
	glVertex3f(-1.0, 2.0, 0.0);
	glVertex3f(0.0, 0.0, 0.0);
	glVertex3f(-2.23, -0.13, 0.0);
	glVertex3f(-1.32, -1.86, 0.0);
	glVertex3f(0.0, 0.0, 0.0);
	glVertex3f(1.23, -1.86, 0.0);
	glVertex3f(2.23, -0.13, 0.0);
	glVertex3f(0.0, 0.0, 0.0);
	glVertex3f(1.0, 2.0, 0.0);
	glVertex3f(0.0, 2.0, 0.0);
	glEnd();

	glColor3f(0.1, 1.0, 0.1);
	glBegin(GL_POLYGON);
	glVertex3f(0.0, 0.0, 0.2);
	glVertex3f(0.0, 2.0, 0.2);
	glVertex3f(-1.0, 2.0, 0.2);
	glVertex3f(0.0, 0.0, 0.2);
	glVertex3f(-2.23, -0.13, 0.2);
	glVertex3f(-1.32, -1.86, 0.2);
	glVertex3f(0.0, 0.0, 0.2);
	glVertex3f(1.23, -1.86, 0.2);
	glVertex3f(2.23, -0.13, 0.2);
	glVertex3f(0.0, 0.0, 0.2);
	glVertex3f(1.0, 2.0, 0.2);
	glVertex3f(0.0, 2.0, 0.2);
	glEnd();
	glPopMatrix();
	glDisable(GL_LINE_SMOOTH);

	glPushMatrix();
	glTranslatef(0.0, 1.0, -8);
	glRotatef(30.0, 0.0, 1.0, 0.0);
	glRotatef(angle_1, 0.0, 1.0, 0.0);
	glBegin(GL_QUADS);
	glColor3f(0.5, 0.5, 1.0);
	
	glVertex3f(0.2, 0.0, 0.0);
	glVertex3f(-0.2, 0.0, 0.0);
	glVertex3f(-0.3, -5.0, 0.0);
	glVertex3f(0.3, -5.0, 0.0);

	glVertex3f(0.2, 0.0, -0.2);
	glVertex3f(0.3, -5.0, -0.3);
	glVertex3f(-0.3, -5.0, -0.3);
	glVertex3f(-0.2, 0.0, -0.2);

	glVertex3f(0.2, 0.0, 0.0);
	glVertex3f(0.2, 0.0, -0.2);
	glVertex3f(0.3, -5.0, -0.3);
	glVertex3f(0.3, -5.0, 0.0);

	glVertex3f(-0.2, 0.0, 0.0);
	glVertex3f(-0.2, 0.0, -0.2);
	glVertex3f(-0.3, -5.0, -0.3);
	glVertex3f(-0.3, -5.0, 0.0);
	glEnd();

	glPushMatrix();
	glRotatef(30.0, 0.0, 1.0, 0.0);
	glRotatef(angle_2, 0.0, 1.0, 0.0);
	glBegin(GL_QUADS);
	glColor3f(1.0, 0.5, 0.5);
	glVertex3f(1, -5.1, -1.0);
	glVertex3f(-1, -5.1, -1.0);
	glVertex3f(-1, -7.0, -1.0);
	glVertex3f(1, -7.0, -1.0);
	
	glVertex3f(1, -5.10, 1.0);
	glVertex3f(-1, -5.10,1.0);
	glVertex3f(-1, -7.0, 1.0);
	glVertex3f(1, -7.0, 1.0);
	
	glVertex3f(1, -5.10, 1.0);
	glVertex3f(1, -5.10, -1.0);
	glVertex3f(1, -7.0, -1.0);
	glVertex3f(1, -7.0, 1.0);
	
	glVertex3f(-1, -5.10, 1.0);
	glVertex3f(-1, -5.10, -1.0);
	glVertex3f(-1, -7.0, -1.0);
	glVertex3f(-1, -7.0, 1.0);

	glVertex3f(1, -5.1, -1.0);
	glVertex3f(-1, -5.1, -1.0);
	glVertex3f(1, -5.10, 1.0);
	glVertex3f(-1, -5.10, 1.0);
	glEnd();
	glPopMatrix();
	glutSwapBuffers();
	
	angle_1 += 5.0f;
	angle_2 += 1.0f;

	if (angle <= 360) {
		angle += 5.0f;
	}

	else if(angle<=720)
	{
		angle += 1.0f;
	}
	else {
		angle += 10.0f;
	}
}


int main(int argc, char** argv) {           
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowPosition(WIN_POSX, WIN_POSY);      							  
	glutInitWindowSize(WIN_WIDTH, WIN_HEIGHT);
	glutCreateWindow("miniproject progress");
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	init();
	glutIdleFunc(display);
	glutMainLoop();           
	return 0;
}
