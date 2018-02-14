R"(
#version 330 core
#extension GL_ARB_explicit_uniform_location : enable
#extension GL_ARB_separate_shader_objects : enable
#extension GL_ARB_explicit_attrib_location : require

const int CIRCLE_MAXNUM = 300;

layout(location = 0) in vec2 a_vertexPosition;
layout(location = 1) in vec2 a_textureCoordinates;

out DATA {
	vec4 position;
	vec4 color;
	vec2 textureCoordinates;
} out_data;

uniform mat4 u_projectionMatrix = mat4(1.0f); 
uniform mat4 u_viewMatrix = mat4(1.0f);

struct PerCircleData {
	vec4 Color;
	vec2 Position;
	float Radius;
	float Scale;
};

layout(std140) uniform ubo_circle {
	PerCircleData ubo_data[CIRCLE_MAXNUM];
};

void main() {
	float scaleFactor = ubo_data[gl_InstanceID].Scale;
	float radius = ubo_data[gl_InstanceID].Radius;
	vec4 scaleVector = vec4(scaleFactor, scaleFactor, 0.0f, 1.0f);
	vec4 radiusVector = vec4(radius, radius, 0.0f, 1.0f);
	vec4 devicePosition = u_viewMatrix * u_projectionMatrix * vec4(ubo_data[gl_InstanceID].Position, 0.0f, 1.0f);
	vec4 endPosition = devicePosition + radiusVector * scaleVector * vec4(a_vertexPosition, 0.0f, 1.0f);
	gl_Position = endPosition;
	out_data.position = endPosition;
	out_data.color = ubo_data[gl_InstanceID].Color;
	out_data.textureCoordinates = a_textureCoordinates;
}
)";