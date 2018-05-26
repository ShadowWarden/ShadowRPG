#version 120
// These are inputs
attribute vec3 vertex;
attribute vec2 vertexUV;

// These are constants
uniform mat4 mvp;

// These are outputs
varying vec2 UV;

void main(){
	gl_Position = mvp*vec4(vertex, 1.0);
	UV = vertexUV;
}
