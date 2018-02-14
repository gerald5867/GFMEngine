#pragma once
#include "GL.h"
#include "GLContext.h"
#include "../../Utils/Logger.h"
#include "../../Input/Window.h"

gfm::INTERNAL::gpu::GL::GLContext::GLContext(GraphicAPI api, input::Window& targetWindow) : 
Context() {
	auto initSuccessfull = glfwInit();
	if(!initSuccessfull) {
		GFM_LOGGER_FATAL_ERROR(GFM_STRING("Can not Initialize glfw Aborting!!!!"));
	}
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);
	targetWindow.Initialize();
	initSuccessfull = glewInit();
	if(initSuccessfull != GLEW_OK) {
		GFM_LOGGER_FATAL_ERROR(GFM_STRING("Can not Initialize glew Abroting!!!!!"));
	}
}

gfm::INTERNAL::gpu::GL::GLContext::~GLContext() {
	glfwPollEvents();
	glfwTerminate();
}