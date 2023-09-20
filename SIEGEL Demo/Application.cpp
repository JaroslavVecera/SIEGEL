#include "Application.h"
#include <functional>
#include <fstream>
#include <nlohmann/json.hpp>
#include "GraphicBuilder.h"
#include <FileWatch.hpp>

using json = nlohmann::json;
using namespace demo;

demo::Application::Application() {
    _availableUpdate = true;
}

siegel::ApplicationSettings demo::Application::MakeSettings() {
    siegel::ApplicationSettings settings = { };
    settings.width = 300;
    settings.height = 200;
    settings.fontPath = "C:\\Users\\Jarek\\source\\repos\\SFML\\SFML\\res\\Arialn.ttf";
    return settings;
}

void demo::Application::Update(const sf::Time elapsedTime) {
    if (!_availableUpdate)
        return;
    _availableUpdate = false;
    BuildGraphics();
}

void demo::Application::BuildGraphics() {
    std::ifstream f("graphic.json");
    json data = json::parse(f);
    GraphicBuilder b;
    _e = b.BuildGoObject(data);

    siegel::Application::GetInstance().GetWindow().SetObject(_e);
}

void demo::Application::Run() {
    siegel::ApplicationSettings settings = MakeSettings();
    siegel::Application::SetSettings(settings);
    siegel::Application a = siegel::Application::GetInstance();
    filewatch::FileWatch<std::wstring> watch(
        L"graphic.json"s,
        [this](const std::wstring& path, const filewatch::Event change_type) {
            _availableUpdate = true;
        }
    );
    a.SetUpdateCallback(std::bind(&Application::Update, this, std::placeholders::_1));
    a.Run("Test 2");
}