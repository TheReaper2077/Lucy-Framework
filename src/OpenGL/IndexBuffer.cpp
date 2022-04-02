#include "OpenGL.h"

extern std::shared_ptr<OpenGLContext> context;

namespace indexbuffer {
	IndexBuffer* Create(VertexArray * vertexarray) {
		assert(context != nullptr);

		auto indexbuffer = std::make_shared<IndexBuffer>();

		glGenBuffers(1, &indexbuffer->id);
		indexbuffer->size = 0;
		indexbuffer->vertexarray = vertexarray;

		context->index_buffer_store.push_back(indexbuffer);

		return indexbuffer.get();
	}

	void Bind(IndexBuffer * indexbuffer) {
		vertexarray::Bind(indexbuffer->vertexarray);
		if (context->binding_indexbuffer == indexbuffer->id) return;
		context->binding_indexbuffer = indexbuffer->id;
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexbuffer->id);
	}

	void UnBind() {
		context->binding_indexbuffer = 0;
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}


	void Destroy(IndexBuffer * indexbuffer) {
		glDeleteBuffers(1, &indexbuffer->id);
		free(indexbuffer);
		indexbuffer = nullptr;
	}

	void Allocate(IndexBuffer * indexbuffer, std::size_t size) {
		if (indexbuffer->size > size) return;

		Bind(indexbuffer);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, nullptr, GL_DYNAMIC_DRAW);
		indexbuffer->size = size;
	};

	void AddData(IndexBuffer * indexbuffer, unsigned int* data, std::size_t size, std::size_t offset) {
		if (offset == 0 && size > indexbuffer->size) {
			Bind(indexbuffer);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, GL_DYNAMIC_DRAW);
			indexbuffer->size = size;
			return;
		}

		assert(offset + size <= indexbuffer->size);

		Bind(indexbuffer);
		glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, offset, size, data);
		indexbuffer->size = size;
	}
}
