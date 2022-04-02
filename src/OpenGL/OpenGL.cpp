#include "OpenGL.h"

std::shared_ptr<OpenGLContext> context;
 
void OpenGL_CreateContext() {
	assert(context == nullptr);

	context = std::make_shared<OpenGLContext>();
}

void OpenGL_DestroyContext() {
	
}
