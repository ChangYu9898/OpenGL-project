#include "MyGLUtil.h"

#define GLUT_BUILDING_LIB
#include <GL/glut.h>

#include <glm/glm.hpp>

using namespace glm;

void DrawXZPlane()
{
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);	glNormal3f(0, 1, 0); glVertex3f(-0.5, 0, -0.5);
	glTexCoord2f(0, 1);	glNormal3f(0, 1, 0); glVertex3f(-0.5, 0, 0.5);
	glTexCoord2f(1, 1);	glNormal3f(0, 1, 0); glVertex3f(0.5, 0, 0.5);
	glTexCoord2f(1, 0);	glNormal3f(0, 1, 0); glVertex3f(0.5, 0, -0.5);
	glEnd();
}

void DrawASector(float radius, float angle, float slices)
{
	glBegin(GL_TRIANGLE_FAN);//扇形连续填充三角形
	glTexCoord2f(0, 0);
	glNormal3f(0, 0, 1);
	glVertex3f(0.0f, 0.0f, 0.0f);
	int times = angle / (360.0f / slices) + 1;
	for (int i = 0; i < times; ++i)
	{
		float p = i * 360.0f / slices;
		glTexCoord2f((sin(radians(p)) + 1.0f) / 2.0f, (cos(radians(p)) + 1.0f) / 2.0f);
		glNormal3f(0, 0, 1);
		glVertex3f(radius * sin(radians(p)), radius * cos(radians(p)), 0.0f);
	}
	glEnd();
}

void MySolidCylinder(float radius, float height, int slices, int stacks)
{
	// 绘制底面
	glPushMatrix();
	glTranslatef(0, -height / 2.0f, 0);
	glRotatef(90, 1, 0, 0);//x方向旋转90度
	DrawASector(radius, 360, slices);
	glPopMatrix();

	// 绘制侧面
	glPushMatrix();
	glRotatef(90, 1, 0, 0);//x方向旋转90度
	glBegin(GL_QUAD_STRIP);//连续填充四边形串
	for (int i = 0; i < slices + 1; ++i) // i: [0,slices]
	{
		float p = i * 360.0f / slices; // p: [0,360]
		glTexCoord2f((float)i / (float)slices, 0);
		glNormal3f(radius * sin(radians(p)), radius * cos(radians(p)), 0);
		glVertex3f(radius * sin(radians(p)), radius * cos(radians(p)), -height / 2.0f);

		glTexCoord2f((float)i / (float)slices, 1);
		glNormal3f(radius * sin(radians(p)), radius * cos(radians(p)), 0);
		glVertex3f(radius * sin(radians(p)), radius * cos(radians(p)), height / 2.0f);
	}
	glEnd();
	glPopMatrix();

	// 绘制顶面
	glPushMatrix();
	glTranslatef(0, height / 2.0f, 0);
	glRotatef(-90, 1, 0, 0);//x方向旋转-90度
	DrawASector(radius, 360, slices);
	glPopMatrix();
}