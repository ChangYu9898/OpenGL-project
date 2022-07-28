
#include <iostream>
#include <string.h>
#include <vector>
#include <memory>
#include <cassert>

#include <stb_image.h>

#include <TTexture.h>
#include "MyGLUtil.h"

// 需要位于stdio.h等头文件的后面
#include <GL/glut.h>

#include "Car.h"

#pragma comment(lib,"glut32.lib")

using namespace std;
using namespace glm;

/* --------------- 全局变量 --------------- */
float W = 800.0f, H = 600.0f;
Car *car;

const float a = 5.0f; // 小车的加速度
float carTrackLength = 60; // 小车运动轨迹总长
float t = 0; // 小车运动的时刻

std::unique_ptr<TTexture> texBg;

/* --------------- 全局变量结束 --------------- */

void SetProjection();
void SetLight();
void OnMenuClicked(int value);

// 初始化
void Init()
{
	glEnable(GL_DEPTH_TEST); // 启用深度测试

	glEnable(GL_NORMALIZE);

	glClearColor(0.1, 0.1, 0.1, 1); // 设置清零颜色
	SetProjection(); // 设置透视矩阵
	SetLight(); // 设置灯光

	texBg.reset(new TTexture("resource/track.jpg"));
}

//receive ASCII key
void keyInput(unsigned char key, int x, int y)
{
	glutPostRedisplay();
}

//receive non-ASCII key
void OnSpecialKey(int key, int x, int y)
{
	switch (key)
	{
	case GLUT_KEY_UP:
		break;
	case GLUT_KEY_DOWN:
		break;
	}
}

// 设置投影矩阵
void SetProjection()
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0, (float)W / (float)H, 0.1, 1000.0);
}

// 设置view矩阵
void SetView()
{
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0, 50, 40, 0, 1, 0, 0, 1, 0);
}

// 设置灯光
void SetLight()
{
	// 启用灯光0
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);

	// 设置灯光
	float ambientValue = 0.01;
	float diffuseValue = 0.5;
	float specularValue = 0.1;
	float ambient[4] = { ambientValue,ambientValue,ambientValue,1.0 };
	float diffuse[4] = { diffuseValue,diffuseValue,diffuseValue,1.0f };
	float specular[4] = { specularValue,specularValue,specularValue,1.0f };
	float position[4] = { 5,5,5,0 };
	float position1[4] = { -5,0,5,0 };
	GLfloat shininess = 128.0f;

	glLightfv(GL_LIGHT0, GL_POSITION, position);
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, specular);

	glLightfv(GL_LIGHT1, GL_POSITION, position1);
	glLightfv(GL_LIGHT1, GL_AMBIENT, ambient);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, diffuse);
	glLightfv(GL_LIGHT1, GL_SPECULAR, specular);

	// 设置材质
	glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, &shininess);

	// 让glColor时可以更改diffuse颜色
	glColorMaterial(GL_FRONT, GL_DIFFUSE);
	glEnable(GL_COLOR_MATERIAL);
}

void DrawCar(float dt)
{
	// 小车的x坐标
	float carX = -carTrackLength / 2.0f;

	// 小车运动路程，从0开始计算
	float s = 0;

	// 加减速切换的时刻
	float t1 = sqrt(carTrackLength / a);

	// 运动终止的时刻
	float tEnd = 2 * t1;

	if (t < t1) // 处于加速阶段
	{
		s = a * t * t / 2.0f;
		cout << "正在加速：v=" << a * t << " m/s" << endl;
	}
	else
	{
		// 处于减速阶段
		s = 2.0f * a * t1 * t - a * t * t / 2.0f - a * t1 * t1;
		cout << "正在减速：v=" << (2.0f*a*t1-a*t) << " m/s" << endl;
	}
	carX += s;

	glPushMatrix();
	glTranslatef(carX, 0,0);
	car->Draw();

	glPopMatrix();

	t += dt;
	if (t > tEnd) // 超出加减速结束时刻，时间归零
	{
		t = 0;
	}
}

// 主绘制事件
void drawScene()
{
	static float prev_ms = glutGet(GLUT_ELAPSED_TIME);
	float ms = glutGet(GLUT_ELAPSED_TIME);
	float dt = (ms - prev_ms) / 1000.0f;

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// 设置view矩阵
	SetView();

	// 绘制跑道
	glEnable(GL_TEXTURE_2D);
	glColor3f(1, 1, 1);
	texBg->Bind();
	glPushMatrix();
	glRotatef(180, 0, 1, 0);
	glScalef(100, 100, 70);
	DrawXZPlane();
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);

	// 绘制汽车
	DrawCar(dt);

	//glutSolidTeapot(2);

	glutSwapBuffers();

	prev_ms = ms;
}

// 重设窗口大小事件
void resize(int w, int h)
{
	W = w; H = h;
	glViewport(0, 0, w, h);
}

// 定时器事件
void OnTimer(int value)
{
	glutPostRedisplay();
	glutTimerFunc(10, OnTimer, 0);
}

int main(int argc, char **argv)
{
	car = new Car(5, 2, 1.8);

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(W, H);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Car");

	Init();

	glutDisplayFunc(drawScene);
	glutTimerFunc(10, OnTimer, 0);
	glutReshapeFunc(resize);
	glutKeyboardFunc(keyInput);
	glutSpecialFunc(OnSpecialKey);

	glutMainLoop();

	delete car;
	return 0;
}