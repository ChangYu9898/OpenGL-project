#pragma once
#include <GL/glut.h>
#include <string>

class TFrameBuffer;
class TTexture
{
private:
	std::string filename;
protected:
	unsigned int textureId;
	TTexture() :textureId(0) {}
public:

	//jpg: channels=3; png: channels=4;
	TTexture(std::string in_filename,unsigned int filtering=GL_LINEAR);
	explicit TTexture(unsigned int textureId);
	TTexture(const TTexture& other);

	~TTexture();

	void Bind(int samplerIndex=0) const;

	unsigned int GetId() const;

	friend TFrameBuffer;
	friend class TMultiSampleFrameBuffer;
};

