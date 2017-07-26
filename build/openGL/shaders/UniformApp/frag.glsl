#version 420 core                          
                                           
layout(location = 2) uniform vec4 in_color;
// uniform ColorBlock {
// 	float alpha;
// 	vec3 rgb_color;
// 	mat4 trans_matrix;
// } color_block;
                               
out vec4 color;                
                               
void main(void) {              
    color = in_color;          
}                              