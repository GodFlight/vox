// #include "Render/Objects.h"
// #include "Engine/Log.h"
#include <GL/glew.h>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include "Render/Texture.h"
#include "Utilities/Log.h"

Texture::Texture() {};

Texture::~Texture() {
	if (_loaded) {
		glDeleteTextures(1, &_id);
	}
};

void Texture::Load(std::string path) {
	uint channels, width, height;

	stbi_set_flip_vertically_on_load(1);
	uint8* data = stbi_load(path.c_str(), (int*)&width, (int*)&height, (int*)&channels, 4);
	if (!data) {
		stbi_image_free(data);
		return;
	}
	glGenTextures(1, &_id);
	glBindTexture(GL_TEXTURE_2D, _id);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
	glGenerateMipmap(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D, 0);
	stbi_image_free(data);
	_loaded = true;
};

bool Texture::IsLoaded() {return _loaded;};

void Texture::Use() {
	glBindTexture(GL_TEXTURE_2D, _id);
};