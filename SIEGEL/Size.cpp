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

double Size::GetMinParentSize(double maxParentSize, Position const& position, std::forward_list<GO*> const& children) {
	return SizeToParentSize(_size, maxParentSize, position, children);
}

double Size::SizeToParentSize(double size, double maxParentSize, Position const& position, std::forward_list<GO*> const& children) {
	double minBound1 = (size * position.GetProportionalOrigin() - position.GetShift()) / position.GetProportionalParentOrigin();
	double minBound2 = (size * (1 - position.GetProportionalOrigin()) + position.GetShift()) / (1 - position.GetProportionalParentOrigin());
	return fmax(minBound2, minBound1);
}
