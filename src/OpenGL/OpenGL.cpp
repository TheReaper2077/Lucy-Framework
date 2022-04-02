#include "OpenGL.h"

std::shared_ptr<OpenGLContext> gl_context;
 
void OpenGL_CreateContext() {
	assert(gl_context == nullptr);

	gl_context = std::make_shared<OpenGLContext>();
}

void OpenGL_DestroyContext() {
	
}
