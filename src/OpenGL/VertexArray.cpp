#pragma once

#include "OpenGL.h"

extern std::shared_ptr<OpenGLContext> gl_context;

VertexArray *VertexArray_Create(std::vector<VertexArrayLayout> layouts) {
	assert(gl_context != nullptr);

	auto vertexarray = std::make_shared<VertexArray>();
	gl_context->vertex_array_store.push_back(vertexarray);

	glGenVertexArrays(1, &vertexarray->id);
	VertexArray_Bind(vertexarray.get());

	uint32_t relativeoffset = 0;

	for (auto& attrib: layouts) {
		glVertexArrayAttribFormat(vertexarray->id, attrib.idx, attrib.size, attrib.type, false, relativeoffset);
		glVertexArrayAttribBinding(vertexarray->id, attrib.idx, 0);
		glEnableVertexArrayAttrib(vertexarray->id, attrib.idx);

		switch(attrib.type) {
			case GL_FLOAT:
				relativeoffset += sizeof(GLfloat)*attrib.size;
				break;
			
			case GL_FIXED:
				relativeoffset += sizeof(GLfixed)*attrib.size;
				break;
			
			case GL_BYTE:
				relativeoffset += sizeof(GLbyte)*attrib.size;
				break;
			
			case GL_UNSIGNED_BYTE:
				relativeoffset += sizeof(GLubyte)*attrib.size;
				break;
			
			default:
				assert(false);
		}
	}

	vertexarray->stride = relativeoffset;

	return vertexarray.get();
}

void VertexArray_Bind(VertexArray *vertexarray) {
	if (gl_context->binding_vertexarray == vertexarray->id) return;
	gl_context->binding_vertexarray = vertexarray->id;
	glBindVertexArray(vertexarray->id);
}

void VertexArray_UnBind() {
	gl_context->binding_vertexarray = 0;
	glBindVertexArray(0);
}

void VertexArray_BindVertexBuffer(VertexArray *vertexarray, VertexBuffer *vertexbuffer, std::size_t stride, std::size_t offset) {
	glVertexArrayVertexBuffer(vertexarray->id, 0, vertexbuffer->id, offset, (stride == 0) ? stride : vertexarray->stride);
}

void VertexArray_BindIndexBuffer(VertexArray *vertexarray, IndexBuffer *indexbuffer) {
	glVertexArrayElementBuffer(vertexarray->id, indexbuffer->id);
}