#include "OpenGL.h"

extern std::shared_ptr<OpenGLContext> gl_context;

Texture *Texture_Create() {
	assert(gl_context != nullptr);

	auto texture = std::make_shared<Texture>();
	glGenTextures(1, &texture->id);
	
	gl_context->texture_store.push_back(texture);

	return texture.get();
}

Texture *Texture_LoadFile(const char* filename) {
	assert(gl_context != nullptr);

	auto* texture = Texture_Create();
	
	Texture_Bind(texture);
	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glGenerateMipmap(texture->id);

	int width, height, channels;
	unsigned char* data = stbi_load(filename, &width, &height, &channels, 0);

	assert(data);

	if (channels == 4)
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
	if (channels == 3)
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
	
	stbi_image_free(data);

	Texture_UnBind();

	texture->channels = channels;
	texture->width = width;
	texture->height = height;

	return texture;
}

void Texture_Bind(Texture *texture) {
	glBindTexture(GL_TEXTURE_2D, texture->id);
}

void Texture_BindUnit(Texture *texture, uint32_t unit) {
	glBindTextureUnit(unit, texture->id);
}

void Texture_UnBind() {
	glBindTexture(GL_TEXTURE_2D, 0);
}

void TextureArray_Bind(Texture *texture) {
	glBindTexture(GL_TEXTURE_2D_ARRAY, texture->id);
}

void TextureArray_UnBind() {
	glBindTexture(GL_TEXTURE_2D_ARRAY, 0);
}