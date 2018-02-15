#pragma once
#define GFM_LOGGER_LEVEL GFM_LOG_LEVEL_INFORMATION
#include <iostream>
#include <cmath>
#include <chrono>
#include "Math/Vector.h"
#include "GPUApi/GraphicCommandHandler.h"
#include "Math/MathCalc.h"
#include "Application.h"
#include "Math/Matrix.h"
#include "Graphic/Rectangle.h"
#include "Math/Vector.h"
#include "Memory/MemoryAllocator.h"
#include "UnitTest/UnitTest.h"
#include "Comparison/CompareNewMemoryAllocator.h"
#include "DataStructures/List.h"
#include "Macro/Assertions.h"
#include "GPUApi/IndexBuffer.h"
#include "GPUApi/VertexBuffer.h"
#include "GPUApi/GL/GLPipeline.h"
#include "GPUApi/GL/GLVertexBuffer.h"
#include "GPUAPI/GL/GLPipelineLayout.h"
#include "GPUApi/GraphicObjectFactory.h"
#include "GPUApi/Shader.h"
#include "Memory/UniquePointer.h"
#include "GPUApi/PipelineManager.h"
#include "Math/Convertions.h"
#include "Graphic/Color.h"
#include "Graphic/RectangleRenderer.h"
#include "Graphic\CircleRenderer.h"
#include "GPUApi/GL/GLUniformBuffer.h"
#include "Graphic\Circle.h"
#include "GPUApi/GL/GLTexture2D.h"
//WINDOW CLASS FOR EVERY PLATFORM
//BASIC KLASSE GFM OBJECT
//MORE FILES MACRO
//MATH OPERATORS !!
//TODO MAKE SHADER SPELL THERE NAME ON ERROR
//LOGGER VON OPENGL STUFF BEFREIEN
//OS LIB
//complete matrix and vector classes and change matrix to colum major
//add template matricies and vectors
//NET LIB
//random LIB
//TIMER
//VFS SYSTEM
//BINARY TREE, DICTIONARY, HASDICTIONARY
//SHAREDPTR
//ALLOCATORS
//WINDOW FUNCTION SET TITLE
//APP GETFPS
//CONTEXT CLASS
//PIPELINELAYOUT CLASS (VERTEX ARRAY WITH OPENGL)
//DEVICE CLASS
//ABSTRACT CLASS MESSAGEABLE AND UPDATEABLE
//vertexbuffer uploadData template un größe berechnen and überladen für list
//OVERRIDE GLOBAL OPERATORS AND KEEP TRACK OF HEAP ALLOCATIONS
//KONVENTIONEN ÄNDERN
//DICTIONARY
//UNIFORM FOR ALL DATATYPES
//RECTANGLE ROTATE AND OPERATORS
//BASE THREAD
// THREAD POOL
//CIRCLE RENDERER CHECK MAX UBO SIZE AND MAKE MULTIPLE IF NEEDED FOR 64kb
//TODO: CUSTOM EXCEPTIONS !!!
//TODO: ASSET SERVER WHO CACHES TEXTURES ETC
//https://stackoverflow.com/questions/1010106/how-to-debug-heap-corruption-errors
//https://stackoverflow.com/questions/1169858/global-memory-management-in-c-in-stack-or-heap

using namespace gfm::INTERNAL::gpu;
using namespace gfm::INTERNAL::gpu::GL;
using namespace gfm::graphic;
using namespace gfm::math;

//_CrtSetDbgFlag(_CRTDBG_CHECK_ALWAYS_DF);
//#define HPASSERT GFM_DEBUG_ASSERT(_CrtCheckMemory(), GFM_STRING(""));
void main() {
	gfm::Application* app = nullptr;
	{
		gfm::utils::Logger::Initialize("LogFile.txt", gfm::utils::LogOutput::eFILE | gfm::utils::LogOutput::eCOUT);
		app = &gfm::Application::Initialize("Test ", 600, 600, true, true);
		auto& gpmgr = GraphicObjectFactory::Initialize(GraphicAPI::eOPENGL);
		gfm::List<Circle> circels;
		gfm::List<Rectangle> angles;
		gfm::INTERNAL::gpu::GL::GLTexture2D tex(GFM_STRING("C:/ogl_sm.jpg"));
		int row = 0;
		int col = 0;
		//circels.Reserve(250);
		for (int i = 25; i < 600; i += 75)
		{
			for (int j = 25; j < 600; j += 75)
			{
				circels.AppendInPlace((float)i , (float)j , 25.0f, Vec4{1.0f, 0.0f, 0.0f, 1.0f});
				angles.AppendInPlace((float)i - 25.0f, (float)j - 25.0f, 33.0f, 33.0f, Vec4(0.0f, 1.0f, 0.0f, 1.0f));
			}
		}
		//circ.SetRadius(200.0f);
		while(app->KeepAlive()) {
			app->ClearScreen();
			app->Update();
		}
		app->Destroy();
		_CrtDumpMemoryLeaks();
	}
}

/*
void main() {
	gfm::Application* app = nullptr;
	{
		gfm::utils::Logger::Initialize("LogFile.txt", gfm::utils::LogOutput::eFILE | gfm::utils::LogOutput::eCOUT);
		app = &gfm::Application::Initialize("Test ", 600, 600, true, true);
		auto& gpmgr = GraphicObjectFactory::Initialize(GraphicAPI::eOPENGL);
		Rectangle angles[600 / 40][600 / 40];
		srand(0);
		for(auto row = 0U; row < 600 / 40; ++row) {
			for(auto col = 0U; col < 600 / 40; ++col) {
				angles[row][col].SetPosition(row * 40, col * 40);
				angles[row][col].SetSize(40, 40);
				float r = (rand() % 255) / 255.0f;
				float g = (rand() % 255) / 255.0f;
				float b = (rand() % 255) / 255.0f;
				float a = (rand() % 255) / 255.0f;
				angles[row][col].SetColor(Vec4(r, g, b, a));
			}
		}
		auto before = std::chrono::steady_clock::now();
		int lastCol = 0;
		int lastRow = 0;
		while(app->KeepAlive()) {
			app->ClearScreen();
			RectangleRenderer::instance().Update();
			RectangleRenderer::instance().Render();
			app->Update();
			auto now = std::chrono::steady_clock::now();
			auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(now - before).count();
			if(ms >= 10) {
				before = now;
				float r = (rand() % 255) / 255.0f;
				float g = (rand() % 255) / 255.0f;
				float b = (rand() % 255) / 255.0f;
				float a = (rand() % 255) / 255.0f;
				angles[lastRow][lastCol].SetColor(Vec4(r, g, b, a));
				if(++lastRow >= 600 / 40) {
					lastRow = 0;
					if(++lastCol >= 600 / 40) {
						lastCol = 0;
					}
				}
			}
		}
		app->Destroy();
	}
}
*/

/*
void main() {
	gfm::Application* app = nullptr;
	{
		gfm::utils::Logger::Initialize("LogFile.txt", gfm::utils::LogOutput::eFILE | gfm::utils::LogOutput::eCOUT);
		app = &gfm::Application::Initialize("Test ", 600, 600, true, true);
		auto& gpmgr = GraphicObjectFactory::Initialize(GraphicAPI::eOPENGL); // FOR NOW
		
		Rectangle rect(50, 50, 100, 100, Colorb(1.0f, 0.0f, 0.0f, 1.0f));
		GLPipelineLayout pipelayout;
		auto indxbuffer = gpmgr.CreateIndexBuffer(BufferUsage::eSTATIC_DRAW);
		auto vertBuffer = gpmgr.CreateVertexBuffer(BufferUsage::eSTATIC_DRAW);
		unsigned int indexData[] = {
			0, 1, 2,
			2, 3, 0
		};
		auto modelMat = Matrix4x4::Rotation(ToRadians(70.0f), Vec3(0.0f, 0.0f, 1.0f));
		Vec2 leftTop = rect.GetPosition();
		Vec2 leftBottom(rect.GetX(), rect.GetY() + rect.GetHeight());
		Vec2 rightTop(rect.GetX() + rect.GetWidth(), rect.GetY());
		Vec2 rightBottom = rect.GetPosition() + rect.GetSize();
		Vec2 positions[] = {
			leftTop, rightTop, rightBottom, leftBottom
		};
		Vec4 _TopLeft((600.0f / 2.0f) - (rect.GetWidth() / 2.0f), (600.0f / 2.0f) - (rect.GetHeight() / 2.0f), 1.0f, 1.0f);
		Vec4 _BottomLeft((600.0f / 2.0f) - (rect.GetWidth() / 2.0f), (600.0f / 2.0f) + (rect.GetHeight() / 2.0f), 1.0f, 1.0f);
		Vec4 _TopRight((600.0f / 2.0f) + (rect.GetWidth() / 2.0f), (600.0f / 2.0f) - (rect.GetHeight() / 2.0f), 1.0f, 1.0f);
		Vec4 _BottomRight((600.0f / 2.0f) + (rect.GetWidth() / 2.0f), (600.0f / 2.0f) + (rect.GetHeight() / 2.0f), 1.0f, 1.0f);
		auto myort = gfm::math::Matrix4x4::Orthographic(0.0f, 600.0f, 600.0f, 0.0f);
		auto& pipe = PipelineManager::instance().GetPipeline(gfm::INTERNAL::gpu::PipelineType::ePRIMITIVE2D);
		pipe.PushUniform(myort, "projectionMatrix");
		pipe.PushUniform(modelMat, "modelMatrix");
		indxbuffer->UploadData(indexData, 6);
		vertBuffer->UploadData(positions, 8 * sizeof(float));
		pipelayout.AppendBuffer(*vertBuffer.Raw());
		pipelayout.CreateFromPipeline(PipelineType::ePRIMITIVE2D);
		auto myres = gfm::math::Vec4(200.0f, 200.0f, 0.0f, 0.0f) * myort;
		while(app->KeepAlive()) {
			app->ClearScreen();
			GraphicCommandHandler::Instance().DrawIndexed(DrawMode::eTRIANGLES, 6, DrawIndexedType::eUINT);
			app->Update();
		}
	}
	app->Destroy();
}
*/


template<typename... args>
void dosome(args&&... arguments) {
	const char* sizes[] = { typeid(decltype(arguments)).name()... };
	char* args[sizeof...(args)] = { reinterpret_cast<char*>(&arguments)... };
	std::cout << *reinterpret_cast<double*>(args[0]) << std::endl;
	std::cout << *reinterpret_cast<double*>(args[1]) << std::endl;
}
/*
void main()
{

	gfm::String testString("HALLO MEIN NAME IST GERALD");
	using namespace gfm::utils;
	gfm::utils::ChangeCoutColor((ConsoleColor)256);
	GFM_DEBUG_ASSERT(false, L"Hallo Ich bin ein Assertion {0}", 100);
	GFM_LOGGER_FATAL_ERROR(L"HALLO ICH BIN EINE INFORMATION");
	char buffer[8192];
	int len = 8192;
	std::cout << "test2" << std::endl;
	//gfm::String::Format("do some", 5, 10.0f);
	using namespace std::chrono;
	auto before = high_resolution_clock::now();
	for (int i = 0; i < 8192 * 3; i++) {
		snprintf(buffer, len, "%s %d %f %s %d %f", "Gerald", 21, 180.0f, "Gerald", 21, 180.0f);
	}
	auto after = duration_cast<milliseconds>(high_resolution_clock::now() - before).count();
	std::cout << after << " SNPRINTF IN MILISECONDS " << std::endl;
	auto before2 = high_resolution_clock::now();
	for (int i = 0; i < 8192 * 3; i++) {
		//auto gerald = gfm::String::Format("{0} {0} a b c {1} {2} {0}", 5, 6, "Gerald");
	}
	auto after2 = duration_cast<milliseconds>(high_resolution_clock::now() - before).count();
	std::cout << after2 << " MY STRING FORMAT IN MILISECONDS " << std::endl;
	double first = 77.0, second = 666.0;
	dosome(first, second);
	struct bz{};
	srand(0);
	class Test {
	public:
		int m_alter;
		std::string m_name;
	public:
		Test();
	public:
		Test(int alter, const std::string& name) :
			m_alter(alter), m_name(name) {

		}
		virtual ~Test() noexcept = default;
	};
	typedef gfm::List<Test, gfm::memory::DefaultAllocator> lst;
	
	lst g;
	gfm::List<int> res;
	for (int i = 0; i < 50; i++) {
		res.Append(i);
	}
	auto rsd = res.Any(577);


	res = res + std::initializer_list<int>{11, 111, 1111};
	for (int i = 0; i < 10; i++) {
		g.Append(Test(1, std::to_string(rand() % 500)));
	}
	for (size_t i = 0; i < res.Length(); i++) {
	}
	//gfm::compareMemoryAllocatorToNewAndDelete();
	/*srand(0);
	using namespace gfm;
	using namespace math;
	float positions[][2]{ {50, 50}, {70, 50}, {300, 300}, {400, 100}, {250, 250 } };
	gfm::Application& app = gfm::Application::Initialize("test", 500, 500, true, true);
	gfm::graphic::Rectangle * angles = new gfm::graphic::Rectangle[5];
	for (int i = 0; i < 5; i++) {
		angles[i].SetPosition(positions[i][0], positions[i][1]);
		angles[i].SetColor({ 0.0f, 1.0f, 0.0f, 1.0f });
		angles[i].SetSize(25.0f, 25.0f);
		angles[i].Show();
	}
	auto start = std::chrono::high_resolution_clock::now();
	int rot = 1;
	while (app.KeepAlive()) {
		glClear(GL_COLOR_BUFFER_BIT);
		app.Update();
		auto now = std::chrono::high_resolution_clock::now();
		if (std::chrono::duration_cast<std::chrono::milliseconds>(now - start).count() > 10.0f) {
			if (rot == 360) {
				rot = 1;
			}
			for (int i = 0; i < 5; i++) {
				angles[i].Rotate(rot += 1);
			}
			start = now;
		}
	}
	app.Destroy();
	std::getchar();
}*/