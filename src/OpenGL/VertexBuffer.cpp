#pragma once

#include "OpenGL.h"

extern std::shared_ptr<OpenGLContext> context;

namespace vertexbuffer {
	VertexBuffer* Create() {
		assert(context != nullptr);

		auto vertexbuffer = std::make_shared<VertexBuffer>();

		glGenBuffers(1, &vertexbuffer->id);
		vertexbuffer->type = BufferType::DYNAMIC;
		vertexbuffer->size = 0;

		context->vertex_buffer_store.push_back(vertexbuffer);

		return vertexbuffer.get();
	}

	void Bind(VertexBuffer * vertexbuffer) {
		if (context->binding_vertexbuffer == vertexbuffer->id) return;
		context->binding_vertexbuffer = vertexbuffer->id;
		glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer->id);
	}

	void UnBind() {
		context->binding_vertexbuffer = 0;
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	void Destroy(VertexBuffer * vertexbuffer) {
		glDeleteBuffers(1, &vertexbuffer->id);
		free(vertexbuffer);
		vertexbuffer = nullptr;
	}

	void Allocate(VertexBuffer * vertexbuffer, std::size_t size) {
		if (vertexbuffer->size > size && size == 0) return;

		Bind(vertexbuffer);
		if (vertexbuffer->type == DYNAMIC) glBufferData(GL_ARRAY_BUFFER, size, nullptr, GL_DYNAMIC_DRAW);
		if (vertexbuffer->type == STATIC) glBufferData(GL_ARRAY_BUFFER, size, nullptr, GL_STATIC_DRAW);
		vertexbuffer->size = size;
	};

	void AddDataStatic(VertexBuffer * vertexbuffer, void* data, std::size_t size) {
		if (size == 0) return;
		Bind(vertexbuffer);
		if (vertexbuffer->type == DYNAMIC) glBufferData(GL_ARRAY_BUFFER, size, data, GL_DYNAMIC_DRAW);
		if (vertexbuffer->type == STATIC) glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
		vertexbuffer->size = size;
	}

	void AddDataDynamic(VertexBuffer * vertexbuffer, void* data, std::size_t size, std::size_t offset) {
		if (size == 0) return;
		assert(offset + size <= vertexbuffer->size);

		Bind(vertexbuffer);
		glBufferSubData(GL_ARRAY_BUFFER, offset, size, data);
		vertexbuffer->size = size;
	}
}
