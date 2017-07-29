#version 450 core

out vec4 color;

subroutine vec4 getColor();
layout (index = 2)
subroutine(getColor)
vec4 getColor1() {
  return vec4(1.0f, 0.0f, 0.0f, 1.0f);
}
layout (index = 1)
subroutine(getColor)
vec4 getColor2() {
  return vec4(0.0f, 1.0f, 0.0f, 1.0f);
}

subroutine uniform getColor getColorUnif; 

void main(void) {
  color = getColorUnif;
}