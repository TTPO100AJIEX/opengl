#include "Texture.h"

#include <GL/glew.h>

#include <stb_image/stb_image.h>

Texture::Texture(const std::string& path)
{
	id = 0;
	filepath = path;
	LocalBuffer = nullptr;
	width = 0;
	height = 0;
	BPP = 0;

	stbi_set_flip_vertically_on_load(1);
	LocalBuffer = stbi_load(path.c_str(), &width, &height, &BPP, 4);

	glGenTextures(1, &id);
	glBindTexture(GL_TEXTURE_2D, id);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, LocalBuffer);
	glBindTexture(GL_TEXTURE_2D, 0);

	if (LocalBuffer)
	{
		stbi_image_free(LocalBuffer);
	}
}

Texture::~Texture()
{
	glDeleteTextures(1, &id);
}

void Texture::Bind(unsigned int slot)
{
	glActiveTexture(GL_TEXTURE0 + slot);
	glBindTexture(GL_TEXTURE_2D, id);
}
void Texture::Unbind()
{
	glBindTexture(GL_TEXTURE_2D, 0);
}