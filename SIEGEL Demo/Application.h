#pragma once

#include "Siegel.h"

namespace demo {
	class Application {
		siegel::ApplicationSettings MakeSettings();
		void BuildGraphics();
		void Update(const Time elapsedTime);

		siegel::GO* _e;
		bool _availableUpdate;
	public:
		Application();
		void Run();
	};
}