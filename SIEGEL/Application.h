#pragma once

#include <SFML/Graphics.hpp>
#include "ApplicationSettings.h"
#include "TextureManager.h"
#include "Canvas.h"
#include <string>
#include "EllipseShape.h"
#include <functional>

using namespace std;

namespace siegel {
	class Application {
		Canvas* _window;
		static Application* _instance;
		string _name;
		TextureManager _textureManager;
		Font _font;
		std::function<void(const Time)> _updateCallback;
		static ApplicationSettings* _settings;

		Application(ApplicationSettings settings);

		void HandleEvents();
		void Update(const Time elapsedTime);
		void Render() const;
		void UpdateView(const Event e);
		void CreateWindows(const int, const int);
		void LoadTextures();
		void SetName(const string name);
	public:
		~Application();
		Canvas& GetWindow() const;
		void Run(const string name);
		static Application& GetInstance();
		static void SetSettings(ApplicationSettings settings);
		void SetUpdateCallback(std::function<void(const Time)> updateCallback);
	};
}