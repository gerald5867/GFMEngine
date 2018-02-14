#pragma once
#ifndef GL_SHADER_H
#define GL_SHADER_H
#include "../../Utils/Types.h"
#include "../Shader.h"
namespace gfm {
namespace INTERNAL {
namespace gpu {
namespace GL {

	class GLShader final : public Shader
	{

	public:
		GLShader(const GLShader&)			  = delete;
		GLShader& operator =(const GLShader&) = delete;

		GLShader(GLShader&& other);
		GLShader& operator =(GLShader&& other);
		GLShader(ShaderType type);

		virtual ~GLShader() noexcept;

		virtual void CreateFromFile(const String& filePath) override;
		virtual void CreateFromSource(const String& source) override;
		virtual void CreateFromSource(String&& source) override;

		virtual void Destroy() const noexcept override;
		virtual bool IsCompiled() const noexcept override;
		virtual const String& GetSourceCode() const noexcept override;

		utils::uint32 GetID() const noexcept;
	private:
		void CheckCompileSuccessfull();
		void CreateFromSource();

	private:
		mutable utils::uint32 m_id;
		mutable bool m_isCompiled = false;
		String m_sourceCode;
	};
}//GL
}//gpu
}//INTERNAL
}//gfm
#endif // GL_SHADER_H