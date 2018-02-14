#pragma once
#ifndef SHADER_H
#define SHADER_H
#include "UniformAttribute.h"
#include "ShaderType.h"
#include "../DataStructures/String.h"
#include "../DataStructures/List.h"
#include "../Utils/Types.h"
namespace gfm {
namespace INTERNAL {
namespace gpu {

	/*
	TODO: PARSE THE UNIFORMS !! 
	*/

	class Shader
	{
		public:
		static constexpr const String::CharType* const GLSLDataTypes[] = {
			GFM_STRING("bool"), GFM_STRING("int"), GFM_STRING("uint"),
			GFM_STRING("float"), GFM_STRING("double"),
			GFM_STRING("vec2"), GFM_STRING("vec3"), GFM_STRING("vec4"),
			GFM_STRING("bvec2"), GFM_STRING("bvec3"), GFM_STRING("bvec4"),
			GFM_STRING("uvec2"), GFM_STRING("uvec3"), GFM_STRING("uvec4"),
			GFM_STRING("ivec2"), GFM_STRING("ivec3"), GFM_STRING("ivec4"),
			GFM_STRING("dvec2"), GFM_STRING("dvec3"), GFM_STRING("dvec4"),
			GFM_STRING("mat2"), GFM_STRING("mat3"), GFM_STRING("mat4"),
			GFM_STRING("mat2x2"), GFM_STRING("mat3x3"), GFM_STRING("mat4x4"),
			GFM_STRING("mat2x3"), GFM_STRING("mat2x4"),
			GFM_STRING("mat3x2"), GFM_STRING("mat4x2"),
			GFM_STRING("mat4x3"), GFM_STRING("mat3x4"),
			GFM_STRING("mat3x2"), GFM_STRING("mat4x2"),
		};
		static constexpr const String::CharType* const GLSLAllowedVertexAttributeTypes[] = {
			GFM_STRING("bool"), GFM_STRING("int"), GFM_STRING("uint"),
			GFM_STRING("float"), GFM_STRING("double"),
			GFM_STRING("vec2"), GFM_STRING("vec3"), GFM_STRING("vec4"),
			GFM_STRING("mat2"), GFM_STRING("mat3"), GFM_STRING("mat4")
		};

		protected:
			Shader(ShaderType type) : m_type(type) {}
			Shader(const Shader&)			  = delete;
			Shader& operator =(const Shader&) = delete;
			
		public:
			Shader(Shader &&)			 = default;
			Shader& operator =(Shader&&) = default;
			virtual ~Shader() noexcept   = default;
	
			virtual void CreateFromFile(const String& filePath)  = 0;
			virtual void CreateFromSource(const String& source)  = 0;
			virtual void CreateFromSource(String&& source)       = 0;
			virtual const String& GetSourceCode() const noexcept = 0;

			virtual void Destroy() const noexcept    = 0;
			virtual bool IsCompiled() const noexcept = 0;
			
			void AppendUniformAttribute(const UniformAttribute& attr) { m_uniformAttributes.Append(attr); }

			GFM_BEST_INLINE ShaderType GetType() const noexcept { return m_type; }
			GFM_BEST_INLINE const List<UniformAttribute>& GetUniformAttributes() const noexcept { return m_uniformAttributes; }

		protected:
			List<UniformAttribute> m_uniformAttributes;
			ShaderType m_type;
	};

}//INTERNAL
}//graphic
}//gfm
#endif //SHADER_H