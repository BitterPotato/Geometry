#version 450 core

layout (location = 0) in vec4 in_pos;
layout (location = 1) in vec3 in_color;

out VS_COLOR {
  vec3 m_color;
} vs_out;

void main(void) {
  gl_Position = in_pos;
  vs_out.m_color = in_color;
}