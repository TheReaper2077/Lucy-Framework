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


VertexArray *VertexArray_Create(std::vector<VertexArrayLayout> layouts);
void VertexArray_Bind(VertexArray *vertexarray);
void VertexArray_BindVertexBuffer(VertexArray *vertexarray, VertexBuffer *vertexbuffer, std::size_t stride = 0, std::size_t offset = 0);
void VertexArray_BindIndexBuffer(VertexArray *vertexarray, IndexBuffer *indexbuffer);
void VertexArray_UnBind();
void VertexArray_Destroy(VertexArray *vertexarray);

// #endif

// #ifndef VERTEX_BUFFER	// VertexBuffer


VertexBuffer *VertexBuffer_Create();
void VertexBuffer_Bind(VertexBuffer *vertexbuffer);
void VertexBuffer_UnBind();
void VertexBuffer_Allocate(VertexBuffer *vertexbuffer, std::size_t size);
void VertexBuffer_AddDataDynamic(VertexBuffer *vertexbuffer, void* data, std::size_t size, std::size_t offset = 0);
void VertexBuffer_AddDataStatic(VertexBuffer *vertexbuffer, void* data, std::size_t size);
void VertexBuffer_Destroy(VertexBuffer *vertexbuffer);

// #endif

// #ifndef INDEX_BUFFER	// IndexBuffer


IndexBuffer *IndexBuffer_Create(VertexArray *vertexarray);
void IndexBuffer_Bind(IndexBuffer *Indexbuffer);
void IndexBuffer_UnBind();
void IndexBuffer_Allocate(IndexBuffer *Indexbuffer, std::size_t size);
void IndexBuffer_AddData(IndexBuffer *indexbuffer, unsigned int* data, std::size_t size, std::size_t offset = 0);
void IndexBuffer_Destroy(IndexBuffer *Indexbuffer);

// #endif

// #ifndef UNIFORM_BUFFER


UniformBuffer *UniformBuffer_Create();
void UniformBuffer_Allocate(UniformBuffer *uniformbuffer, std::size_t size);
void UniformBuffer_AddDataDynamic(UniformBuffer *uniformbuffer, void* data, std::size_t size, std::size_t offset = 0);
void UniformBuffer_BindRange(UniformBuffer *uniformbuffer, unsigned int index, std::size_t size, std::size_t offset = 0);
void UniformBuffer_Bind(UniformBuffer *uniformbuffer);
void UniformBuffer_UnBind();

// #endif

// #ifndef SHADER	// Shader


Shader *Shader_Create(const std::string &vs_filename, const std::string &fs_filename);
void Shader_Bind(Shader *shader);
void Shader_UnBind();

void Shader_BindUniformBlock(Shader *shader, std::string name, unsigned int index);
unsigned int Shader_GetUniformLoc(Shader *shader, std::string name);

void Shader_SetUniformi(Shader *shader, std::string uniform, int v0);
void Shader_SetUniformf(Shader *shader, std::string uniform, float v0);
void Shader_SetUniformVec3(Shader *shader, std::string uniform, const float *v);
void Shader_SetUniformVec4(Shader *shader, std::string uniform, const float *v);
void Shader_SetUniformMat4(Shader *shader, std::string uniform, const glm::mat4 &matrix);
void Shader_SetUniformArray(Shader *shader, std::string uniform, std::size_t count, const float *v);

// Texture
Texture *Texture_Create();
Texture *Texture_LoadFile(const char* filename);
void Texture_Bind(Texture *texture);
void Texture_BindUnit(Texture *texture, uint32_t unit);
void Texture_UnBind();
void TextureArray_Bind(Texture *texture);
void TextureArray_UnBind();
SpriteAtlas *Texture_SpriteAtlas_LoadFile(int tilex, int tiley, int tilew, int tileh, const char* filename);

// #endif

#include "Impl.h"
