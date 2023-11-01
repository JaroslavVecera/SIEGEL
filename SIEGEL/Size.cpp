#include "Size.h"

using namespace siegel;


Size::Size(double size) {
	setSize(size);
}

Size::Size() {
	setSize(0);
}

double Size::getSize() {
	return _size;
}

void Size::setSize(double size) {
	_size = size;
}

double Size::GetMinParentSize(double maxParentSize, GO &object) {
	Vector2f& margin = GetMargin(object);
	double wholeSize = _size + margin.x + margin.y;
	return SizeToParentSize(wholeSize, maxParentSize, object);
}

double Size::SizeToParentSize(double size, double maxParentSize, GO &object) {
	Position& position = GetPosition(object);

	if (position.GetProportionalParentOrigin() == 0 || position.GetProportionalParentOrigin() == 1)
		return size;

	double minBound1 = (size * position.GetProportionalOrigin() - position.GetShift()) / position.GetProportionalParentOrigin();
	double minBound2 = (size * (1 - position.GetProportionalOrigin()) + position.GetShift()) / (1 - position.GetProportionalParentOrigin());
	return fmax(minBound2, minBound1);
}

Position& Size::GetPosition(GO& object) {
	return (_type == SizeType::Horizontal) ? object.GetHorizontalPosition() : object.GetVerticalPosition();
}

Vector2f& Size::GetMargin(GO& object) {
	return (_type == SizeType::Horizontal) ? object.GetHorizontalMargin() : object.GetVerticalMargin();
}
