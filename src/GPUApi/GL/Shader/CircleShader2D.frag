R"(
#version 330 core
#extension GL_ARB_explicit_uniform_location : enable
#extension GL_ARB_separate_shader_objects : enable

layout (location = 0) out vec4 out_color;

struct PerCircleData {
	vec4 Color;
	vec4 Transformation;
};

in DATA
{
	vec4 position;
	vec4 color;
	vec2 textureCoordinates;
} in_data;

void main()
{
	out_color = in_data.color;
}
)";