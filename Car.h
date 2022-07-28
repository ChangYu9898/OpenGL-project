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
	// �����
	Car(float length, float width, float height);

	// ����
	void Draw();

	void SetBodyColor(Color color);

	void SetWheelColor(Color color);

	void SaveDataFile(std::string filename);

private:

	float length, width, height; // �����
	Color bodyColor, wheelColor; // ������ɫ��������ɫ

	// ��ԭ�����һ����
	void DrawAtOrigin();
};

