#version 450 core

out vec4 color;

in VS_COLOR {
  vec4 m_color;
} fs_in;

void main(void) {
  color = fs_in.m_color;
}