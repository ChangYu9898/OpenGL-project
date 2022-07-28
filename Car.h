#pragma once

#include <string>
#include <glm/glm.hpp>

using Color = glm::vec3;

extern Color Black;
extern Color White;
extern Color Red;
extern Color Green;
extern Color Blue;
extern Color Gray;

class Car
{
public:
	// 长宽高
	Car(float length, float width, float height);

	// 绘制
	void Draw();

	void SetBodyColor(Color color);

	void SetWheelColor(Color color);

	void SaveDataFile(std::string filename);

private:

	float length, width, height; // 长宽高
	Color bodyColor, wheelColor; // 车身颜色，轮子颜色

	// 在原点绘制一个车
	void DrawAtOrigin();
};

