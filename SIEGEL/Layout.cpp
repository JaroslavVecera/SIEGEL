#include "Layout.h"
#include "Size.h"
#include "Go.h"
#include "Canvas.h"

using namespace siegel;

Layout::Layout() : GO() {
	Initialize();
}

void Layout::Initialize() {
	_border.SetBorderColor(Color::Green);
	_border.SetColor(Color::Transparent);
	SetBorderThickness(2);
}

void Layout::SetCornerRadius(double radius) {
	_cornerRadius = radius;
}

double Layout::GetCornerRadius() {
	return _cornerRadius;
}

void Layout::SetOutlineColor(Color& c) {
	_outlineColor = c;
}

Color Layout::GetOutlineColor() const {
	return _outlineColor;
}

void Layout::Emplace(Vector2f& horizontalParentBounds, Vector2f& verticalParentBounds) {
	GO::Emplace(horizontalParentBounds, verticalParentBounds);
	if (_borderThickness > 0)
		EmplaceBorder(horizontalParentBounds, verticalParentBounds);
	EmplaceChildren(horizontalParentBounds, verticalParentBounds);
}

void Layout::EmplaceChildren(Vector2f& horizontalParentBounds, Vector2f& verticalParentBounds) {
	for (GO* child : _children) {
		Vector2f horizontalBounds = Vector2f(_canvasHorizontalBounds.x + _horizontalMargin.x + GetBorderThickness() + GetHorizontalPadding().x, _canvasHorizontalBounds.y - _horizontalMargin.y - GetBorderThickness() - GetHorizontalPadding().y);
		Vector2f verticalBounds = Vector2f(_canvasVerticalBounds.x + _verticalMargin.x + GetBorderThickness() + GetVerticalPadding().x, _canvasVerticalBounds.y - _verticalMargin.y - GetBorderThickness() - GetVerticalPadding().y);
		child->Emplace(horizontalBounds, verticalBounds);
	}
}

void Layout::EmplaceBorder(Vector2f& horizontalParentBounds, Vector2f& verticalParentBounds) {
	_border.SetBorderColor(_outlineColor);
	_border.SetBorderThickness(_borderThickness);
	_border.SetRadius(_cornerRadius);
	_border.SetHorizontalPosition(_horizontalPosition);
	_border.SetVerticalPosition(_verticalPosition);
	_border.SetHorizontalSize(_horizontalSize);
	_border.SetVerticalSize(_verticalSize);
	_border.SetHorizontalMargin(_horizontalMargin);
	_border.SetVerticalMargin(_verticalMargin);
	_border.Emplace(horizontalParentBounds, verticalParentBounds);
}

void Layout::AddChild(GO* child) {
	_children.push_front(child);
}

void Layout::Render() const {
	for (GO* child : _children)
		child->Render();
	if (_borderThickness > 0)
		_border.Render();
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
