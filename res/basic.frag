#version 330 core

layout (location=0) out vec4 out_fragcolor;

in vec3 color;

void main(){
	out_fragcolor = vec4( color, 1.0 );
} 


