#version 120
// These are inputs
attribute vec3 vertex_modelSpace;
attribute vec2 vertexUV;
attribute vec3 normal_modelSpace;

// These are constants
uniform mat4 mvp;
uniform mat4 M;
uniform mat4 V;
uniform mat3 mv3x3;
uniform vec3 LightPosition_worldspace;

// These are outputs
varying vec2 UV;
varying vec3 Position_worldspace;
varying vec3 EyeDirection_cameraspace;
varying vec3 LightDirection_cameraspace;


void main(){
	gl_Position = mvp*vec4(vertex_modelSpace, 1.0);
	
	Position_worldspace = (M*vec4(vertex_modelSpace,1.0)).xyz;
	vec3 vertexPosition_cameraspace = (V*M*vec4(vertex_modelSpace,1.0)).xyz;
	EyeDirection_cameraspace = vec3(0,0,0) - vertexPosition_cameraspace;

	vec3 LightPosition_cameraspace = (V*vec4(LightPosition_worldspace,1.0)).xyz;
	LightDirection_cameraspace = LightPosition_cameraspace + EyeDirection_cameraspace;

	UV = vertexUV;
}
