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
	return SizeToParentSize(_size, maxParentSize, object);
}

double Size::SizeToParentSize(double size, double maxParentSize, GO &object) {
	Position& position = GetPosition(object);

	double minBound1 = (size * position.GetProportionalOrigin() - position.GetShift()) / position.GetProportionalParentOrigin();
	double minBound2 = (size * (1 - position.GetProportionalOrigin()) + position.GetShift()) / (1 - position.GetProportionalParentOrigin());
	return fmax(minBound2, minBound1);
}

Position& Size::GetPosition(GO& object) {
	return (_type == SizeType::Horizontal) ? object.GetHorizontalPosition() : object.GetVerticalPosition();
}
