#include "GraphicAPI.h"

gfm::INTERNAL::gpu::GraphicAPI gfm::INTERNAL::gpu::FindBestGraphicAPI() {
	// SPÄTER WIRD HIER HERAUSGEFUNDEN WELCHE PLATFORM
	// UND DANN HOFFENTLICH ZWISCHEN VULKAN DIRECTX UND OPENGL GEWÄHLT

	static GraphicAPI bestApi = GraphicAPI::eNONE;
	if(bestApi != GraphicAPI::eNONE) {
		return bestApi;
	}
	bestApi = GraphicAPI::eOPENGL; // for now
	return bestApi;
}