#version 120
// These are outputs from the Vertex Shader
varying vec2 UV;
uniform sampler2D Texture;

void main(){
	gl_FragColor = texture2D(Texture,UV);
	// gl_FragColor = vec4(1,1,0,1);
}
