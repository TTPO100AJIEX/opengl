#pragma once

#include <string>

class Texture
{
private:
	unsigned int id;
	std::string filepath;
	unsigned char* LocalBuffer;
	int width, height, BPP;
public:
	Texture(const std::string& path);
	~Texture();
	
	void Bind(unsigned int slot = 0);
	void Unbind();

	inline int GetWidth()
	{
		return(width);
	}
	inline int GetHeight()
	{
		return(height);
	}
};