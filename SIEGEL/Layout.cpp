#pragma once

#include "Layout.h"
#include "Size.h"
#include "Go.cpp"

using namespace siegel;

Layout::Layout() : GO() {
	Initialize();
}

void Layout::Initialize() {
	_border.setOutlineColor(Color::Green);
	_border.setFillColor(Color::Transparent);
	_border.setOutlineThickness(2);
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
	_border.setPosition(_canvasTopleft);
	_border.setSize(_canvasSize);
	for (GO* child : _children)
		child->Emplace(_canvasHorizontalBounds, _canvasVerticalBounds);
}

void Layout::AddChild(GO* child) {
	_children.push_front(child);
}

void Layout::Render() {
	for (GO* child : _children)
		child->Render();
	_window->draw(_border);
}


forward_list<GO*> Layout::GetChildren() {
	return _children;
}
