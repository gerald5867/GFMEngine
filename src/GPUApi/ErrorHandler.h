#pragma once
#include "../DataStructures/String.h"
#include "GraphicAPI.h"
#ifndef ERROR_HANDLER_H
#define ERROR_HANDELR_H
namespace gfm {
namespace INTERNAL {
namespace gpu {

	class ErrorHandler
	{
	
	public:
		static ErrorHandler& Initialize(GraphicAPI api);
		static ErrorHandler& Instance();
		static void Destroy() noexcept;
	
	public:
		virtual bool LogCall(const String::CharType* func, const String::CharType* file, const String::CharType* line) = 0;
		virtual void ClearLastError() const = 0;
		virtual const String& GetLastError() const noexcept = 0;

		virtual ~ErrorHandler() noexcept = default;
	protected:
		ErrorHandler() = default;


	private:
		thread_local static ErrorHandler* mp_instance;
	};

}//gpu
}//INTERNAL
}//gfm
#endif // ERROR_HANDELR_H