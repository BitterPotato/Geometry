#version 420 core                             
                                              
layout(location=0) in vec4 in_color;                         
out vec4 out_color;                           
                                              
void main(void)                               
{                                             
    if(gl_InstanceID % 4 == 1) 
      gl_Position = vec4(0.0, 0.0, 0.0, 1.0);
    else if(gl_InstanceID % 4 == 2) 
      gl_Position = vec4(-0.5, 0.5, 0.0, 1.0);
    else if(gl_InstanceID % 4 == 3) 
      gl_Position = vec4(0.5, 0.5, 0.0, 1.0);
    else
      gl_Position = vec4(0.5, -0.5, 0.0, 1.0);
       
    out_color = in_color;                     
    gl_PointSize = 10.0f;                    
}                                             