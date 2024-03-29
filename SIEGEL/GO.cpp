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

siegel::Position& GO::GetHorizontalPosition() {
	return _horizontalPosition;
}

void GO::SetHorizontalPosition(siegel::Position &position) {
	_horizontalPosition = position;
}

siegel::Position& GO::GetVerticalPosition() {
	return _verticalPosition;
}

siegel::Size& GO::GetHorizontalSize() const {
	return *_horizontalSize;
}

void GO::SetVerticalSize(siegel::Size* size) {
	if (_verticalSize == size)
		return;
	if (_verticalSize)
		delete _verticalSize;
	_verticalSize = size;
	_verticalSize->_type = SizeType::Vertical;
}

void GO::SetHorizontalSize(siegel::Size* size) {
	if (_horizontalSize == size)
		return;
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
	_horizontalPadding = Vector2f(0, 0);
	_verticalPadding = Vector2f(0, 0); 
}

void GO::Emplace(Vector2f& horizontalParentBounds, Vector2f& verticalParentBounds) {
	_canvasVerticalBounds = _verticalSize->GetBounds(verticalParentBounds, *this);
	_canvasHorizontalBounds = _horizontalSize->GetBounds(horizontalParentBounds, *this);
	_canvasTopleft = Vector2f(_canvasHorizontalBounds.x, _canvasVerticalBounds.x);
	_canvasSize = Vector2f(_canvasHorizontalBounds.y - _canvasHorizontalBounds.x, _canvasVerticalBounds.y - _canvasVerticalBounds.x);
}


void GO::SetHorizontalMargin(Vector2f margin) {
	_horizontalMargin = margin;
}

void GO::SetVerticalMargin(Vector2f margin) {
	_verticalMargin = margin;
}

Vector2f &GO::GetHorizontalMargin() {
	return _horizontalMargin;
}

Vector2f &GO::GetVerticalMargin() {
	return _verticalMargin;
}

forward_list<GO*> GO::GetChildren() {
	return forward_list<GO*>();
}

double GO::GetBorderThickness() {
	return 0;
}

Vector2f &GO::GetHorizontalPadding() {
	return _horizontalPadding;
}

Vector2f &GO::GetVerticalPadding() {
	return _verticalPadding;
}