#version 450 core

out vec4 color;

vec4 getColor();

void main(void) {
  color = getColor();
}