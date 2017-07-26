#version 450 core                          

uniform vec4 in_color;

layout(binding = 1) uniform atomic_uint var;
layout(binding = 0, std430) buffer vertices {
  int vertice[24];
};
layout(binding = 2) uniform ColorBlock {
  float alpha;
  vec3 rgb_color;
  mat4 trans_matrix;
  float dummy[4];
} color_block;
                               
out vec4 color;                
                               
void main(void) {              
    color = in_color;          
}                              