#pragma once

#define OPENGL_API

#include "../define.h"

typedef unsigned int VertexArrayId;
typedef unsigned int VertexBufferId;
typedef unsigned int IndexBufferId;
typedef unsigned int UniformBufferId;
typedef unsigned int ShaderId;
typedef unsigned int TextureId;
typedef unsigned int SpriteAtlasId;
typedef unsigned int SpriteId;

// OpenGLContext
struct OpenGLContext;

struct VertexArrayLayout;
struct VertexArray;

struct VertexBuffer;
struct IndexBuffer;
struct UniformBuffer;

struct Shader;

struct Texture;
struct SpriteAtlas;

void OpenGL_CreateContext();
void OpenGL_DestroyContext();

// #ifndef VERTEX_ARRAY	// VertexArray

namespace vertexarray {
	VertexArray *Create(std::vector<VertexArrayLayout> layouts);
	void Bind(VertexArray *vertexarray);
	void BindVertexBuffer(VertexArray *vertexarray, VertexBuffer *vertexbuffer, std::size_t stride = 0, std::size_t offset = 0);
	void BindIndexBuffer(VertexArray *vertexarray, IndexBuffer *indexbuffer);
	void UnBind();
	void Destroy(VertexArray *vertexarray);
}
// #endif

// #ifndef VERTEX_BUFFER	// VertexBuffer

namespace vertexbuffer {
	VertexBuffer* Create();
	void Bind(VertexBuffer* vertexbuffer);
	void UnBind();
	void Allocate(VertexBuffer* vertexbuffer, std::size_t size);
	void AddDataDynamic(VertexBuffer* vertexbuffer, void* data, std::size_t size, std::size_t offset = 0);
	void AddDataStatic(VertexBuffer* vertexbuffer, void* data, std::size_t size);
	void Destroy(VertexBuffer* vertexbuffer);
}
// #endif

// #ifndef INDEX_BUFFER	// IndexBuffer

namespace indexbuffer {
	IndexBuffer* Create(VertexArray* vertexarray);
	void Bind(IndexBuffer* Indexbuffer);
	void UnBind();
	void Allocate(IndexBuffer* Indexbuffer, std::size_t size);
	void AddData(IndexBuffer* indexbuffer, unsigned int* data, std::size_t size, std::size_t offset = 0);
	void Destroy(IndexBuffer* Indexbuffer);
}

// #endif

// #ifndef UNIFORM_BUFFER


namespace uniformbuffer {
	UniformBuffer* Create();
	void Allocate(UniformBuffer* uniformbuffer, std::size_t size);
	void AddDataDynamic(UniformBuffer* uniformbuffer, void* data, std::size_t size, std::size_t offset = 0);
	void BindRange(UniformBuffer* uniformbuffer, unsigned int index, std::size_t size, std::size_t offset = 0);
	void Bind(UniformBuffer* uniformbuffer);
	void UnBind();
}

// #endif

// #ifndef SHADER	// Shader

namespace shaderprogram {
	Shader* Create(const std::string& vs_filename, const std::string& fs_filename);
	void Bind(Shader* shader);
	void UnBind();

	void BindUniformBlock(Shader* shader, std::string name, unsigned int index);
	unsigned int GetUniformLoc(Shader* shader, std::string name);

	void SetUniformi(Shader* shader, std::string uniform, int v0);
	void SetUniformf(Shader* shader, std::string uniform, float v0);
	void SetUniformVec3(Shader* shader, std::string uniform, const float* v);
	void SetUniformVec4(Shader* shader, std::string uniform, const float* v);
	void SetUniformMat4(Shader* shader, std::string uniform, const glm::mat4& matrix);
	void SetUniformArray(Shader* shader, std::string uniform, std::size_t count, const float* v);
}

// Texture
namespace texture {
	Texture* Create();
	Texture* LoadFile(const char* filename);
	void Bind(Texture* texture);
	void BindUnit(Texture* texture, uint32_t unit);
	void UnBind();
}

void TextureArray_Bind(Texture *texture);
void TextureArray_UnBind();
SpriteAtlas *Texture_SpriteAtlas_LoadFile(int tilex, int tiley, int tilew, int tileh, const char* filename);

// #endif

#include "Impl.h"
