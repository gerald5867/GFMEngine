#pragma once
#include "..\ErrorHandler.h"
#include "..\..\DataStructures\List.h"
#include "..\..\Utils\Types.h"
#ifndef GL_ERROR_HANDLER_H
#define GL_ERROR_HANDLER_H
namespace gfm {
namespace INTERNAL {
namespace gpu {
namespace GL {

	class GLErrorHandler final : public ErrorHandler 
	{

		public:
			GLErrorHandler() = default;
			virtual ~GLErrorHandler() noexcept = default;

		public:
			virtual bool LogCall(const String::CharType* func, const String::CharType* file, const String::CharType* line) override;
			virtual void ClearLastError() const override;
			virtual const String& GetLastError() const noexcept override;

		private:
			List<utils::uint32> m_errorMessages;
			mutable String m_lastError;
	};

}//GL
}//gpu
}//INTERNAL
}//gfm
#endif //GL_ERROR_HANDLER_H