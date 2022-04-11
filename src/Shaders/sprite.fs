#version 400 core

in vec3 f_attr;

uniform sampler2D u_textures0;

void main() {
	gl_FragColor = texture(u_textures0, f_attr.xy) * vec4(1);
}
