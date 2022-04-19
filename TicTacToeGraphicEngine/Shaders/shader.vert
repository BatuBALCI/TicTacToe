#version 330                                                                      

// This varaible is not uniform and it may change during process. Location 0 means it reads positions                 
layout(location = 0) in vec3 pos;                                                 

//Location 1 means it reads texture coordinates  
layout(location = 1) in vec2 tex;   

//Location 2 means it reads normals of vertices  
layout(location = 2) in vec3 norm;   

//out variables are used to transform data to other shaders.                      
out vec4 vCol;  
out vec2 texCoord;                       
out vec3 Normal;                                                               
out vec3 FragPos;

//Uniform variable                                                                
uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;                                                               

void main()                                                                       
{                                                                                 
    gl_Position = model*vec4(pos, 1.0);     
    // this code assign colour to the vertex according to its position            
    // clamp function helps to get rid of minus signs to get proper color spectrum
    vCol = vec4(clamp(pos, 0.0f, 1.0f), 1.0f);  
	texCoord = tex;
	
	// Since only the rotation and stretching effect the normal we can only use the 3x3 part of the model 
	// martix because rotation and stretch only affects that portion. In order to handling non-uniform stretching
	// take the transpose of the inverse of the model function.
	Normal = mat3(transpose(inverse(model)))*norm;
	
	//.xyz gets first 3 value from the vector.
	FragPos = (model * vec4(pos, 1.0)).xyz;   
}