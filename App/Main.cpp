#include <Core/Application.h>
#include "Source/SimulationLayer.h"

int main() {
	Core::ApplicationSpecification appSpec;
	appSpec.Name = "Solar System Simulation";
	appSpec.WindowSpec.Width = 1920;
	appSpec.WindowSpec.Height = 1080;

	Core::Application application(appSpec);
	application.PushLayer<SimulationLayer>();
	application.Run();

    return 0;
}