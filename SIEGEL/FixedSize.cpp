#include "FixedSize.h"

siegel::FixedSize::FixedSize(double size) {
	setSize(size);
}

Vector2f siegel::FixedSize::GetBounds(Vector2f& parentBounds, Position &position, const forward_list<GO*>& children) {
	double absolutParentOrigin = position.GetAbsoluteParentOrigin(parentBounds);
	double x1 = absolutParentOrigin + position.GetShift() - _size * position.GetProportionalOrigin();
	double x2 = absolutParentOrigin + position.GetShift() + _size * (1 - position.GetProportionalOrigin());
	return Vector2f(x1, x2);
}

