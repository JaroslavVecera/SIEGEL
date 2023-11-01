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
	_border.setOutlineColor(c);
}

Color Layout::GetOutlineColor() const {
	return _border.getOutlineColor();
}

void Layout::Emplace(Vector2f& horizontalParentBounds, Vector2f& verticalParentBounds) {
	GO::Emplace(horizontalParentBounds, verticalParentBounds);
	EmplaceBorder();
	for (GO* child : _children)
	{
		Vector2f horizontalBounds = Vector2f(_canvasHorizontalBounds.x + _horizontalMargin.x + GetBorderThickness(), _canvasHorizontalBounds.y - _horizontalMargin.y - GetBorderThickness());
		Vector2f verticalBounds = Vector2f(_canvasVerticalBounds.x + _verticalMargin.x + GetBorderThickness(), _canvasVerticalBounds.y - _verticalMargin.y - GetBorderThickness());
		child->Emplace(horizontalBounds, verticalBounds);
	}
}

void Layout::EmplaceBorder() {
	_border.setPosition(Vector2f(_canvasTopleft.x + _horizontalMargin.x + GetBorderThickness(), _canvasTopleft.y + _verticalMargin.x + GetBorderThickness()));
	_border.setSize(Vector2f(_canvasSize.x - _horizontalMargin.x - _horizontalMargin.y - 2 * GetBorderThickness(), _canvasSize.y - _verticalMargin.x - _verticalMargin.y - 2 * GetBorderThickness()));
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

Vector2f Layout::GetHorizontalPadding() {
	return _horizontalPadding;
}

Vector2f Layout::GetVerticalPadding() {
	return _verticalPadding;
}

double Layout::GetBorderThickness() {
	return _border.getOutlineThickness();
}

void Layout::SetBorderThickness(double thickness) {
	_border.setOutlineThickness(thickness);
}

forward_list<GO*> Layout::GetChildren() {
	return _children;
}
