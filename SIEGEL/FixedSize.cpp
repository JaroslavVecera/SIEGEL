#include "FixedSize.h"

siegel::FixedSize::FixedSize(double size) {
	setSize(size);
}

Vector2f siegel::FixedSize::GetBounds(Vector2f &parentBounds, GO &object) {
	Position position = GetPosition(object);
	Vector2f& margin = GetMargin(object);
	double wholeSize = _size + margin.x + margin.y;

	double absolutParentOrigin = position.GetAbsoluteParentOrigin(parentBounds);
	double x1 = absolutParentOrigin + position.GetShift() - wholeSize * position.GetProportionalOrigin();
	double x2 = absolutParentOrigin + position.GetShift() + wholeSize * (1 - position.GetProportionalOrigin());
	return Vector2f(x1, x2);
}

