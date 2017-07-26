  #version 420 core                       
                                          
  void main(void)                         
  {                                       
      const vec4 vertices[3] = vec4[3](   
          vec4(0.2f, 0.2f, 0.0f, 1.0f),   
          vec4(-0.2f, -0.2f, 0.0f, 1.0f), 
          vec4(0.2f, -0.2f, 0.0f, 1.0f)   
      );                                  
      gl_Position = vertices[gl_VertexID];
  }