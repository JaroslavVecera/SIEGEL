#include "GO.h"
#include "Application.h"
#include "Position.h"
#include "FixedSize.h"
#include <memory>

using namespace siegel;

GO::GO() {
	SetWindow();
	Initialize();
}

GO::~GO() {
}

void GO::SetWindow() {
	_window = &Application::GetInstance().GetWindow();
}

siegel::Position GO::GetHorizontalPosition() const {
	return _horizontalPosition;
}

void GO::SetHorizontalPosition(siegel::Position &position) {
	_horizontalPosition = position;
}

siegel::Position GO::GetVerticalPosition() const {
	return _verticalPosition;
}

siegel::Size& GO::GetHorizontalSize() const {
	return *_horizontalSize;
}

void GO::SetVerticalSize(siegel::Size* size) {
	if (_verticalSize)
		delete _verticalSize;
	_verticalSize = size;
	_verticalSize->_type = SizeType::Vertical;
}

void GO::SetHorizontalSize(siegel::Size* size) {
	if (_horizontalSize)
		delete _horizontalSize;
	_horizontalSize = size;
	_horizontalSize->_type = SizeType::Horizontal;
}

siegel::Size& GO::GetVerticalSize() const {
	return *_verticalSize;
}

void GO::SetVerticalPosition(siegel::Position& position) {
	_verticalPosition = position;
}

void GO::Initialize() {
	SetVerticalSize(new FixedSize(50));
	SetHorizontalSize(new FixedSize(50));
}

void GO::Emplace(Vector2f& horizontalParentBounds, Vector2f& verticalParentBounds) {
	_canvasVerticalBounds = _verticalSize->GetBounds(verticalParentBounds, _verticalPosition, GetChildren());
	_canvasHorizontalBounds = _horizontalSize->GetBounds(horizontalParentBounds, _horizontalPosition, GetChildren());
	_canvasTopleft = Vector2f(_canvasHorizontalBounds.x, _canvasVerticalBounds.x);
	_canvasSize = Vector2f(_canvasHorizontalBounds.y - _canvasHorizontalBounds.x, _canvasVerticalBounds.y - _canvasVerticalBounds.x);
}


forward_list<GO*> GO::GetChildren() {
	return forward_list<GO*>();
}