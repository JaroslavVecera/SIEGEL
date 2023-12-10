#include "Rectangle.h"

using namespace siegel;

Rectangle::Rectangle() {
	Initialize(0, sf::Color::Blue);
}

Rectangle::Rectangle(double radius, sf::Color color) {
	Initialize(radius, color);
}

void Rectangle::Initialize(double radius, sf::Color color) {
	_roundedShape.SetRadius(radius);
	if (radius < 0.001)
	{
		_shape.setFillColor(color);
		_shape.setOutlineColor(color);
		_shape.setOutlineThickness(15);
	}
	else
	{
		_roundedShape.setFillColor(color);
		_roundedShape.setOutlineColor(color);
		_roundedShape.setOutlineThickness(15);
	}
}

void Rectangle::Render() const {
	if (_radius < 0.001)
		_window->draw(_shape);
	else
		_window->draw(_roundedShape);
}

void Rectangle::SetRadius(double radius) {
	_radius = radius;
}

void Rectangle::SetColor(const Color color) {
	_color = color;
}

double Rectangle::GetRadius() const {
	return _radius;
}

const Color Rectangle::GetBorderColor() const {
	return _borderColor;
}

void Rectangle::SetBorderColor(const Color color) {
	_borderColor = color;
}

const Color Rectangle::GetColor() const {
	return _color;
}

double Rectangle::GetBorderThickness() const {
	return _borderThickness;
}

void Rectangle::SetBorderThickness(double thickness) {
	_borderThickness = thickness;
}

void Rectangle::Emplace(Vector2f& horizontalParentBounds, Vector2f& verticalParentBounds) {
	GO::Emplace(horizontalParentBounds, verticalParentBounds);
	if (_radius < 0.001)
		_shape.setPosition(Vector2f(_canvasTopleft.x + _horizontalMargin.x, _canvasTopleft.y + _verticalMargin.x));
	else
		_roundedShape.setPosition(Vector2f(_canvasTopleft.x + _horizontalMargin.x, _canvasTopleft.y + _verticalMargin.x));
	double sizeH = fmax(0, _canvasSize.x - _horizontalMargin.x - _horizontalMargin.y);
	double sizeV = fmax(0, _canvasSize.y - _verticalMargin.x - _verticalMargin.y);
	double radius = _radius < 0.001 ? 0 : fmin(sizeH / 2, fmin(sizeV / 2, fmax(_borderThickness, _radius)));
	if (_borderThickness > 0) {
		double thickness = fmin(sizeH / 2, fmin(sizeV / 2, _borderThickness));
		if (thickness * 2 < sizeH && thickness * 2 < sizeV)
			EmplaceThickNormal(sizeH - 2 * thickness, sizeV - 2 * thickness, radius, thickness);
		else
			EmplaceThickDegenerate(sizeH, sizeV, thickness);
	}
	else
		EmplaceBorderless(sizeH, sizeV, radius);
	_roundedShape.Recompute();
}

void Rectangle::EmplaceThickNormal(double sizeH, double sizeV, double radius, double thickness) {
	Emplace(sizeH, sizeV, radius, _borderColor, _color, thickness);

	if (_radius < 0.001)
		_shape.move(thickness, thickness);
	else
		_roundedShape.move(thickness, thickness);
}

void Rectangle::EmplaceThickDegenerate(double sizeH, double sizeV, double thickness) {
	Emplace(sizeH, sizeV, thickness, Color::Transparent, _borderColor, 0);
}

void Rectangle::EmplaceBorderless(double sizeH, double sizeV, double radius) {
	Emplace(sizeH, sizeV, radius, Color::Transparent, _color, 0);
}

void Rectangle::Emplace(double sizeH, double sizeV, double radius, Color outlineColor, Color fillColor, double outlineThickness) {
	if (_radius < 0.001)
	{
		_shape.setOutlineThickness(outlineThickness);
		_shape.setFillColor(fillColor);
		_shape.setOutlineColor(outlineColor);
		_shape.setSize(Vector2f(sizeH, sizeV));
	}
	else
	{
		_roundedShape.setOutlineThickness(outlineThickness);
		_roundedShape.setFillColor(fillColor);
		_roundedShape.setOutlineColor(outlineColor);
		_roundedShape.setSize(Vector2f(sizeH, sizeV));
		_roundedShape.SetRadius(radius);
	}
}