#include "Layout.h"
#include "Size.h"
#include "Go.h"
#include "Canvas.h"

using namespace siegel;

Layout::Layout() : GO() {
	Initialize();
}

void Layout::Initialize() {
	_border.setOutlineColor(Color::Green);
	_border.setFillColor(Color::Transparent);
	SetBorderThickness(2);
}

void Layout::SetVerticalSize(siegel::Size* size) {
	if (_verticalSize)
		delete _verticalSize;
	_verticalSize = size;
}

void Layout::SetHorizontalSize(siegel::Size* size) {
	if (_horizontalSize)
		delete _horizontalSize;
	_horizontalSize = size;
}

void Layout::SetOutlineColor(Color& c) {
	_outlineColor = c;
}

Color Layout::GetOutlineColor() const {
	return _outlineColor;
}

void Layout::Emplace(Vector2f& horizontalParentBounds, Vector2f& verticalParentBounds) {
	GO::Emplace(horizontalParentBounds, verticalParentBounds);
	EmplaceBorder();
	for (GO* child : _children)
	{
		Vector2f horizontalBounds = Vector2f(_canvasHorizontalBounds.x + _horizontalMargin.x + GetBorderThickness() + GetHorizontalPadding().x, _canvasHorizontalBounds.y - _horizontalMargin.y - GetBorderThickness() - GetHorizontalPadding().y);
		Vector2f verticalBounds = Vector2f(_canvasVerticalBounds.x + _verticalMargin.x + GetBorderThickness() + GetVerticalPadding().x, _canvasVerticalBounds.y - _verticalMargin.y - GetBorderThickness() - GetVerticalPadding().y);
		child->Emplace(horizontalBounds, verticalBounds);
	}
}

void Layout::EmplaceBorder() {
	double positionX = _canvasTopleft.x + _horizontalMargin.x + GetBorderThickness();
	double positionY = _canvasTopleft.y + _verticalMargin.x + GetBorderThickness();
	double sizeH = _canvasSize.x - _horizontalMargin.x - _horizontalMargin.y - 2 * GetBorderThickness();
	double sizeV = _canvasSize.y - _verticalMargin.x - _verticalMargin.y - 2 * GetBorderThickness();
	if (sizeH <= 0 || sizeV <= 0)
	{
		_border.setOutlineThickness(0);
		_border.setFillColor(GetOutlineColor());
		_border.setOutlineColor(sf::Color::Transparent);
		_border.setPosition(Vector2f(positionX - GetBorderThickness(), positionY - GetBorderThickness()));
		_border.setSize(Vector2f(GetBorderThickness() * 2 + sizeH, GetBorderThickness() * 2 + sizeV));
	}
	else {
		_border.setOutlineThickness(GetBorderThickness());
		_border.setFillColor(sf::Color::Transparent);
		_border.setOutlineColor(GetOutlineColor());
		_border.setPosition(Vector2f(positionX, positionY));
		_border.setSize(Vector2f(sizeH, sizeV));
	}

}

void Layout::AddChild(GO* child) {
	_children.push_front(child);
}

void Layout::Render() const {
	for (GO* child : _children)
		child->Render();
	_window->draw(_border);
}

void Layout::SetHorizontalPadding(Vector2f padding) {
	_horizontalPadding = padding;
}

void Layout::SetVerticalPadding(Vector2f padding) {
	_verticalPadding = padding;
}

Vector2f &Layout::GetHorizontalPadding() {
	return _horizontalPadding;
}

Vector2f &Layout::GetVerticalPadding() {
	return _verticalPadding;
}

double Layout::GetBorderThickness() {
	return _borderThickness;
}

void Layout::SetBorderThickness(double thickness) {
	_borderThickness = thickness;
}

forward_list<GO*> Layout::GetChildren() {
	return _children;
}
