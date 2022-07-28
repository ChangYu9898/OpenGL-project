#include "Car.h"

#include "MyGLUtil.h"

#define GLUT_BUILDING_LIB
#include <GL/glut.h>

#include <glm/glm.hpp>

#include <iostream>
#include <fstream>

using namespace glm;
using namespace std;

Color Black = { 0,0,0 };
Color White = { 1,1,1 };
Color Red = { 1,0,0 };
Color Green = { 0,1,0 };
Color Blue = { 0,0,1 };
Color Gray = { 0.5,0.5,0.5 };

Car::Car(float length, float width, float height) :
	length(length), width(width), height(height),
	bodyColor(Red),
	wheelColor(Black)
{
}

void Car::Draw()
{
	DrawAtOrigin();
}

void Car::SetBodyColor(Color color)
{
	bodyColor = color;
}

void Car::SetWheelColor(Color color)
{
	wheelColor = color;
}


void Car::DrawAtOrigin()
{

	/* ----------- 轮子 ----------- */
	glColor3f(wheelColor.r, wheelColor.g, wheelColor.b);
	float r = 0.3 * height;
	float wheelWidth = 0.3f * width;
	float wheelX = 0.5f * length - r-0.5f*r;
	float wheelZ = 0.5f * width-0.5f*wheelWidth+0.1f*wheelWidth;

	{
		glPushMatrix();
		glTranslatef(wheelX, r, wheelZ);
		glRotatef(90, 1, 0, 0);
		MySolidCylinder(r, wheelWidth);
		glPopMatrix();

		glPushMatrix();
		glTranslatef(-wheelX, r, wheelZ);
		glRotatef(90, 1, 0, 0);
		MySolidCylinder(r, wheelWidth);
		glPopMatrix();

		{
			glPushMatrix();
			glRotatef(180, 0, 1, 0);

			glPushMatrix();
			glTranslatef(wheelX, r, wheelZ);
			glRotatef(90, 1, 0, 0);
			MySolidCylinder(r, wheelWidth);
			glPopMatrix();

			glPushMatrix();
			glTranslatef(-wheelX, r, wheelZ);
			glRotatef(90, 1, 0, 0);
			MySolidCylinder(r, wheelWidth);
			glPopMatrix();

			glPopMatrix();
		}
	}
	/* ----------- 轮子结束 ----------- */

	// 车身
	glColor3f(bodyColor.r, bodyColor.g, bodyColor.b);

	glPushMatrix();
	glTranslatef(0,height*0.5+ 0.15 * height, 0);
	glScalef(length, height * 0.5, width);
	glutSolidCube(1);

	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, height+ 0.15 * height, 0);
	glScalef(length*0.5, height * 0.5, width);
	glutSolidCube(1);

	glPopMatrix();
}
