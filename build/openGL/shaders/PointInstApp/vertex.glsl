#version 450 core

layout(binding=0, rgba32f) readonly uniform image1D baseColor;
layout(binding=1) uniform sampler1D alphaColor;

int random(int seed, int iterations) {
  int value = seed;
  
  for(int n=0; n<iterations; n++) {
    value = ((value >> 7) ^ (value << 9)) * 15485863;
  }

  return value;
}

// each part is in (-1.0f, 1.0f)
vec3 random_vector(int instId) {
  int x = random(instId, 4);
  int y = random(x, 2);
  int z = random(y, 2);

  return vec3(float(x & 0x3FF) / 1024.0,
              float(y & 0x3FF) / 1024.0,
              float(z & 0x3FF) / 1024.0);

}

// return float in [0, [MAX])
float random_f(int instId, float MAX) {
  int value = random(instId, 4);
  int floor = int(MAX);
  int testFloor = floor * 0x3FF;

  return float(value & testFloor) / 1024.0;
}

// return index in [0, MAX]
int random_index(int instId, int MAX) {
  return int(random_f(instId, MAX));
}

out VS_COLOR {
  vec4 m_color;
} vs_out;

void main(void) {
  // const int BASE_SIZE = imageSize(baseColor);
  // const int ALPHA_SIZE = textureSize(alphaColor, 0);
 //  const float POINT_MAX = 4.0f;

  // gl_Position = vec4(random_vector(gl_InstanceID), 1.0f);
  // gl_PointSize = random_f(gl_InstanceID, POINT_MAX);

  // vs_out.m_color = vec4(imageLoad(baseColor, random_index(gl_InstanceID, BASE_SIZE)).xyz, texture(alphaColor, random_index(gl_InstanceID, ALPHA_SIZE)).a);
  gl_Position = vec4(0.0f, 1.0f, 1.0f, 1.0f);
  // gl_PointSize = 20.0f;
  vs_out.m_color = vec4(1.0f, 1.0f, 1.0f, 1.0f);
}