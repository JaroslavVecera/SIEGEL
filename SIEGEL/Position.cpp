#include "Position.h"

using namespace siegel;

Position::Position(double shift, double proportionalParentOrigin, double proportionalOrigin) {
	_shift = shift;
	_proportionalOrigin = proportionalOrigin;
	_proportionalParentOrigin = proportionalParentOrigin;
}

Position::Position(double position) : Position(position, 0, 0) { }

Position::Position() : Position(0, 0, 0) { }

double Position::GetShift() const {
	return _shift;
}

double Position::GetProportionalParentOrigin() const {
	return _proportionalParentOrigin;
}

double Position::GetProportionalOrigin() const {
	return _proportionalOrigin;
}

double Position::GetAbsoluteParentOrigin(Vector2f parentBounds) const {
	return parentBounds.x + (parentBounds.y - parentBounds.x) * _proportionalParentOrigin;
}