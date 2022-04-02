#include "OpenGL.h"

extern std::shared_ptr<OpenGLContext> context;

namespace uniformbuffer {
	UniformBuffer* Create() {
		assert(context != nullptr);

		auto uniformbuffer = std::make_shared<UniformBuffer>();

		glGenBuffers(1, &uniformbuffer->id);
		uniformbuffer->size = 0;

		context->uniform_buffer_store.push_back(uniformbuffer);

		return uniformbuffer.get();
	}

	void Allocate(UniformBuffer * uniformbuffer, std::size_t size) {
		if (uniformbuffer->size > size) return;

		Bind(uniformbuffer);
		glBufferData(GL_UNIFORM_BUFFER, size, nullptr, GL_DYNAMIC_DRAW);
		uniformbuffer->size = size;
	};

	void AddDataDynamic(UniformBuffer * uniformbuffer, void* data, std::size_t size, std::size_t offset) {
		assert(offset + size <= uniformbuffer->size);

		Bind(uniformbuffer);
		glBufferSubData(GL_UNIFORM_BUFFER, offset, size, data);
	}

	void BindRange(UniformBuffer * uniformbuffer, unsigned int index, std::size_t size, std::size_t offset) {
		Bind(uniformbuffer);
		glBindBufferRange(GL_UNIFORM_BUFFER, index, uniformbuffer->id, offset, size);
	}

	void Bind(UniformBuffer * uniformbuffer) {
		if (context->binding_uniformbuffer == uniformbuffer->id) return;
		context->binding_uniformbuffer = uniformbuffer->id;
		glBindBuffer(GL_UNIFORM_BUFFER, uniformbuffer->id);
	}

	void UnBind() {
		context->binding_uniformbuffer = 0;
		glBindBuffer(GL_UNIFORM_BUFFER, 0);
	}
}
