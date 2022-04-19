#version 330     

in vec4 vCol;    
in vec2 texCoord;
in vec3 Normal;
in vec3 FragPos;

out vec4 colour; 

struct DirectionalLight
{
	vec3 ambientColour;
	vec3 diffuseColour;
	vec3 direction;
	float ambientIntensity;
	float diffuseIntensity;
};

struct Material
{
	float specularIntensity;
	float shininess;
};

// this sampler reaches the texture itself by its id to use it shader.
uniform sampler2D theTexture;
uniform DirectionalLight directionalLight;
uniform Material material;

// camera position;
uniform vec3 eyePosition;

void main()      
{         
	vec4 ambientColour = vec4(directionalLight.ambientColour, 1.0f) * directionalLight.ambientIntensity;
	
	// dot product of the normal and direction vector gives factor.
	float diffuseFactor = max(dot(normalize(Normal), directionalLight.direction), 0.0f);
	vec4 diffuseColour = vec4(directionalLight.diffuseColour, 1.0f) * diffuseFactor * directionalLight.diffuseIntensity;
    
	vec4 specularColour = vec4(0,0,0,0);
	
	// ın order to have specular light there has to be diffuse lighting.
	if(diffuseFactor>0.0f)
	{
		vec3 fragToEye = normalize(eyePosition - FragPos);
		// reflect the direction according to the normal vector.
		vec3 reflectedVertex = reflect(directionalLight.direction, normalize(Normal));
		float specularFactor = normalize(max(dot(fragToEye, reflectedVertex), 0.0f));
		if(specularFactor>0)
		{
			specularFactor = pow(specularFactor, material.shininess);
			specularColour = vec4(directionalLight.diffuseColour * material.specularIntensity * specularFactor, 1.0f);
		}
	}
	
	colour = texture(theTexture, texCoord) * (ambientColour + diffuseColour + specularColour) + vec4(1.0f, 1.0f, 1.0f, 1.0f);
}