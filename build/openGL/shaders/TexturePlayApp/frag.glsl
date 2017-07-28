#version 450 core

uniform sampler2DArray texs;

// in int pos;
out vec4 color;

void main(void) {
  color = texture(texs, vec3(gl_FragCoord.xy / textureSize(texs, 0).xy, 1.0f));
}