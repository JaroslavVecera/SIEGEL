#include "Application.h"
#include <vector>
#include <array>

using namespace siegel;

Application *Application::_instance = nullptr;
ApplicationSettings* Application::_settings = nullptr;

Application::Application(ApplicationSettings settings) {
    CreateWindows(settings.width, settings.height);
    LoadTextures();

    _font.loadFromFile(settings.fontPath);
}

Application::~Application() {
	delete _window;
}

void Application::Run(const string name) {
    SetName(name);
    Clock clock;
    Time elapsed;
    while (_window->isOpen()) {
        HandleEvents();
        Update(elapsed);
        _window->Emplace();
        elapsed = clock.restart();
        Render();
    }
    delete _instance;
}

void Application::HandleEvents() {
    sf::Event event;
    while (_window->pollEvent(event)) {
        switch (event.type) {
            case sf::Event::Closed:
                _window->close();
                break;
            case sf::Event::Resized:
                UpdateView(event);
                break;
            case sf::Event::TextEntered:
                break;
            case sf::Event::KeyPressed:
                break;
            case sf::Event::KeyReleased:
                break;
            case sf::Event::MouseWheelScrolled:
                break;
            case sf::Event::MouseMoved:
                break;
            default:
                break;
        }
    }
}

void Application::Render() {
    _window->Clear();
    _window->Render();
    _window->display();
}

void Application::Update(const Time elapsedTime) {
    _updateCallback(elapsedTime);
}

void Application::UpdateView(const Event e) {

    FloatRect visibleArea(0, 0, e.size.width, e.size.height);
    _window->setView(View(visibleArea));
}

void Application::SetName(const string name) {
    _name = name;
    _window->setTitle(name);
}

void Application::CreateWindows(const int width, const int height) {
    ContextSettings settings;
    settings.antialiasingLevel = 8;
    _window = new Canvas(sf::VideoMode(300, 200), _name,Style::Default, settings);
}

void Application::LoadTextures() {
    _textureManager.AddTexture(Test1, "C:\\Users\\Jarek\\Desktop\\fotky\\received_messenger\\a.jpeg");
}

Canvas& Application::GetWindow() const {
    return *_window;
}

Application& Application::GetInstance() {
    if (_instance == nullptr)
        _instance = new Application(*_settings);
    return *_instance;
}

void Application::SetSettings(ApplicationSettings settings) {

    _settings = new ApplicationSettings(settings);
}

void Application::SetUpdateCallback(std::function<void(const Time)> updateCallback) {
    _updateCallback = updateCallback;
}