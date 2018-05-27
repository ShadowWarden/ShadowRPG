#version 120
// These are outputs from the Vertex Shader
varying vec2 UV;
varying vec3 Position_worldspace;
varying vec3 EyeDirection_cameraspace;
varying vec3 LightDirection_cameraspace;

uniform sampler2D TextureSampler;
uniform sampler2D NormalTextureSampler;

uniform vec3 LightPosition_worldspace;
uniform mat4 V;
uniform mat4 M;
uniform mat3 mv3x3;

void main(){
	vec3 LightColor = vec3(1,1,1);
	float LightPower = 50.0f;

	// Material Properties
	vec3 MaterialDiffuseColor = texture2D(TextureSampler, UV).rgb;
	vec3 MaterialAmbientColor = vec3(0.1,0.1,0.1) * MaterialDiffuseColor;
	vec3 MaterialSpecularColor = vec3(0.3,0.3,0.3);


	// Compute Distance
	float distance = length(LightPosition_worldspace - Position_worldspace);

	vec4 NC = V*M*vec4(normalize(texture2D(NormalTextureSampler,UV).rgb*2.0 -1.0),0.0);
	
	// Compute normal in cameraspace
	vec3 n = normalize(NC.xyz);
	vec3 l = normalize(LightDirection_cameraspace);

	float cosTheta = clamp(dot(n,l),0,1);

	vec3 E = normalize(EyeDirection_cameraspace);
	vec3 R = reflect(-l,n);

	float cosAlpha = clamp(dot(E,R),0,1);

	gl_FragColor.rgb = MaterialAmbientColor + 
		MaterialDiffuseColor*LightColor*LightPower*cosTheta/(distance*distance) +
		MaterialSpecularColor*LightColor*LightPower*pow(cosAlpha,5)/(distance*distance);
	// gl_FragColor = vec4(1,1,0,1);

}
