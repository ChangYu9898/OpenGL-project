

//#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#include <cassert>
#include <stdexcept>

#include "TTexture.h"

TTexture::TTexture(std::string in_filename, unsigned int filtering):filename(in_filename)
{
	glGenTextures(1, &textureId);
	glBindTexture(GL_TEXTURE_2D, textureId);

	// 为当前绑定的纹理对象设置环绕、过滤方式
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filtering);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filtering);

	// 加载并生成纹理
	int width, height, nrChannels;
	//stbi_set_flip_vertically_on_load(true);
	unsigned char* data = stbi_load(in_filename.c_str(), &width, &height, &nrChannels, 0);
	if (data)
	{
		int format = (nrChannels == 3) ? GL_RGB : GL_RGBA;
		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
	}
	else
	{
		stbi_image_free(data);
		throw std::runtime_error("Failed to load texture:"+ in_filename);
	}
	stbi_image_free(data);
}

TTexture::TTexture(unsigned int textureId):textureId(textureId)
{
	
}

TTexture::TTexture(const TTexture& other):TTexture(other.filename)
{
}

TTexture::~TTexture()
{
	glDeleteTextures(1, &textureId);
}

void TTexture::Bind(int samplerIndex) const
{
	glBindTexture(GL_TEXTURE_2D, textureId);

#ifdef _DEBUG
	int err = glGetError();
	assert(err == GL_NO_ERROR);
#endif
}

unsigned int TTexture::GetId() const
{
	return textureId;
}
