R"(
#version 330 core
#extension GL_ARB_explicit_uniform_location : enable
#extension GL_ARB_separate_shader_objects : enable

layout(location = 0) in vec2 vertexPosition;
layout(location = 1) in vec4 color;

layout(location = 0) out vec4 vertColor;

uniform mat4 u_projectionMatrix = mat4(1.0f); 
uniform mat4 u_viewMatrix = mat4(1.0f);
uniform mat4 modelMatrix = mat4(1.0f);
void main()
{
	gl_Position =  u_projectionMatrix * u_viewMatrix *  vec4(vertexPosition, 0.0f, 1.0f);
	vertColor = color;
}
)";