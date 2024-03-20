#include "GLCore.h"
#include "SandboxLayer.h"
#include "DynamicLayer.h"
#include "RendererLayer.h"

using namespace GLCore;

class Sandbox : public Application
{
public:
	Sandbox()
	{
		//PushLayer(new SandboxLayer());
		//PushLayer(new DynamicLayer());
		PushLayer(new RendererLayer());
	}
};

int main()
{
	std::unique_ptr<Sandbox> app = std::make_unique<Sandbox>();
	app->Run();
}