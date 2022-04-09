#include "OpenGL.h"

#ifndef SHADER_TEXTUREARRAY
#define SHADER_TEXTUREARRAY "u_texturearray"
#endif

#ifndef SHADER_TEXTURES
#define SHADER_TEXTURES "u_textures"
#endif

#ifndef SHADER_LIGHT
#define SHADER_LIGHT
#endif


static std::string read_file(const std::string &filename) {
	std::string line, text;
	std::fstream file(filename);

	while (std::getline(file, line)) text += (line + '\n');

	file.close();

	return text;
}

extern std::shared_ptr<OpenGLContext> gl_context;

void Compile(unsigned int &program, const std::string &filename, unsigned int target, bool file) {
	unsigned int shader = glCreateShader(target);
	std::string text;
	if (file) text = read_file(filename);
	else text = filename;
	const char* src = text.c_str();
	glShaderSource(shader, 1, &src, NULL);
	glCompileShader(shader);

	unsigned int result;
	glGetShaderiv(shader, GL_COMPILE_STATUS, (GLint*)&result);

	if (!result) {
		unsigned int logLength;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, (GLint*)&logLength);
		GLchar* message = (GLchar*)alloca(logLength*sizeof(char));
		glGetShaderInfoLog(shader, logLength, (GLsizei*)&logLength, message);
		std::cout << message << std::endl;
	}

	assert(result);

	glAttachShader(program, shader);
	glDeleteShader(shader);
};

Shader *Shader_Create(const std::string &vs_filename, const std::string &fs_filename, bool file) {
	assert(gl_context != nullptr);

	unsigned int program = glCreateProgram();

	Compile(program, vs_filename, GL_VERTEX_SHADER, file);
	Compile(program, fs_filename, GL_FRAGMENT_SHADER, file);

	glLinkProgram(program);

	auto shader = std::make_shared<Shader>();

	shader->id = program;

	gl_context->shader_store.push_back(shader);
	
	auto* shader_ptr = shader.get();

	Shader_Bind(shader_ptr);

	if (Shader_GetUniformLoc(shader_ptr, SHADER_TEXTUREARRAY)) {
		shader_ptr->texture_array = true;

		// for (int i = 0; i < 32; i++) {
		// 	glActiveTexture(GL_TEXTURE0 + i);
		// 	auto tmp = std::string(SHADER_TEXTUREARRAY) + std::to_string(i);
		// 	Shader_SetUniformi(shader_ptr, tmp, i);
		// }
		glActiveTexture(GL_TEXTURE0);
		Shader_SetUniformi(shader_ptr, SHADER_TEXTUREARRAY, 0);
	}
	if (Shader_GetUniformLoc(shader_ptr, SHADER_TEXTURES)) {
		shader_ptr->textures = true;
		
		for (int i = 0; i < 32; i++) {
			glActiveTexture(GL_TEXTURE0 + i);
			auto tmp = std::string(SHADER_TEXTURES) + std::to_string(i);
			Shader_SetUniformi(shader_ptr, tmp, i);
		}
	}
	if (Shader_GetUniformLoc(shader_ptr, "light")) {
		shader_ptr->light = true;
	}
	if (Shader_GetUniformLoc(shader_ptr, "material")) {
		shader_ptr->material = true;
	}

	return shader_ptr;
}

void Shader_Bind(Shader *shader) {
	if (gl_context->binding_shader == shader->id) return;
	gl_context->binding_shader = shader->id;
	glUseProgram(shader->id);
}

void Shader_UnBind() {
	gl_context->binding_vertexarray = 0;
	glUseProgram(0);
}

void Shader_BindUniformBlock(Shader *shader, std::string name, unsigned int index) {
	glUniformBlockBinding(shader->id, glGetUniformBlockIndex(shader->id, name.c_str()), index);
}

unsigned int Shader_GetUniformLoc(Shader *shader, std::string name) {
	if (shader->uniform_location_map.find(name) == shader->uniform_location_map.end())
		shader->uniform_location_map[name] = glGetUniformLocation(shader->id, name.c_str());
		
	return shader->uniform_location_map[name];
}

void Shader_SetUniformMat4(Shader *shader, std::string uniform, const float* matrix) {
	Shader_Bind(shader);
	glUniformMatrix4fv(Shader_GetUniformLoc(shader, uniform), 1, GL_FALSE, matrix);
}

void Shader_SetUniformi(Shader *shader, std::string uniform, int v0) {
	Shader_Bind(shader);
	glUniform1i(Shader_GetUniformLoc(shader, uniform), v0);
}

void Shader_SetUniformf(Shader *shader, std::string uniform, float v0) {
	Shader_Bind(shader);
	glUniform1f(Shader_GetUniformLoc(shader, uniform), v0);
}

void Shader_SetUniformVec3(Shader *shader, std::string uniform, const float *v) {
	Shader_Bind(shader);
	glUniform3fv(Shader_GetUniformLoc(shader, uniform), 1, v);
}

void Shader_SetUniformVec4(Shader *shader, std::string uniform, const float *v) {
	Shader_Bind(shader);
	glUniform4fv(Shader_GetUniformLoc(shader, uniform), 1, v);
}

void Shader_SetUniformArray(Shader *shader, std::string uniform, std::size_t count, const float *v) {
	Shader_Bind(shader);
	glUniform1fv(Shader_GetUniformLoc(shader, uniform), count, v);
}
