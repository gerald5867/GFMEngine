#include "GraphicAPI.h"

gfm::INTERNAL::gpu::GraphicAPI gfm::INTERNAL::gpu::FindBestGraphicAPI() {
	// SP�TER WIRD HIER HERAUSGEFUNDEN WELCHE PLATFORM
	// UND DANN HOFFENTLICH ZWISCHEN VULKAN DIRECTX UND OPENGL GEW�HLT

	static GraphicAPI bestApi = GraphicAPI::eNONE;
	if(bestApi != GraphicAPI::eNONE) {
		return bestApi;
	}
	bestApi = GraphicAPI::eOPENGL; // for now
	return bestApi;
}