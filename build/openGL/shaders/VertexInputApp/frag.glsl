#version 450 core

out vec4 color;

in VS_COLOR {
  vec3 m_color;
} fs_in;

void main(void) {
  color = vec4(fs_in.m_color, 1.0f);
}