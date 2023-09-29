#include "Ellipse.h"

using namespace siegel;

Ellipse::Ellipse() {
	Vector2f r = Vector2f(60.f, 120.f);
	Initialize(r, sf::Color::Blue);
}

Ellipse::Ellipse(const sf::Vector2f &radius, sf::Color color) {
	Initialize(radius, color);
}

void Ellipse::Initialize(const sf::Vector2f& radius, sf::Color color) {
	_shape.setRadius(radius);
	_shape.setFillColor(color);
}

void Ellipse::Render() const {
	_window->draw(_shape);
}

void Ellipse::SetRadius(const sf::Vector2f& radius) {
	_shape.setRadius(radius);
}

void Ellipse::SetColor(const Color color) {
	_shape.setFillColor(color);
}

const sf::Vector2f& Ellipse::GetRadius() const {
	return _shape.getRadius();
}

const FloatRect Ellipse::GetLocalBounds() const {
	return _shape.getLocalBounds();
}

const FloatRect Ellipse::GetGlobalBounds() const {
	return _shape.getGlobalBounds();
}

const Color Ellipse::GetColor() const {
	return _shape.getFillColor();
}

void Ellipse::Emplace(Vector2f& horizontalParentBounds, Vector2f& verticalParentBounds) {
	GO::Emplace(horizontalParentBounds, verticalParentBounds);
	_shape.setPosition(_canvasTopleft);
	_shape.setRadius(Vector2f(_canvasSize.x / 2, _canvasSize.y / 2));
}