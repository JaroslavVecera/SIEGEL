#include "Canvas.h"

using namespace siegel;

Canvas::Canvas(VideoMode mode, const String& title, Uint32 style, const ContextSettings& settings, sf::Color background) :
	sf::RenderWindow(mode, title, style, settings) {
	_background = background;
}

GO* Canvas::GetObject() const {
	return _object;
}

void Canvas::SetObject(GO* object) {
	_object = object;
} 

void Canvas::Clear() {
	RenderWindow::clear(_background);
}

void Canvas::Render() const {
	_object->Render();
}

void Canvas::Emplace() {
	Vector2u size = getSize();
	Vector2f h(0, size.x);
	Vector2f v(0, size.y);
	_object->Emplace(h, v);
}