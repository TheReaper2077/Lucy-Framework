#version 400 core

in vec3 f_attr;

uniform sampler3D u_texture3d;

void main() {
	gl_FragColor = texture(u_texture3d, f_attr) * vec4(1);
}
