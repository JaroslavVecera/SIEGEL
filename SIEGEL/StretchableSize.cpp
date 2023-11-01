#pragma once

#include "StretchableSize.h"

siegel::StretchableSize::StretchableSize(double size) {
	setSize(size);
}

Vector2f siegel::StretchableSize::GetBounds(Vector2f &parentBounds, GO &object) {
	Position position = GetPosition(object);
	Vector2f& margin = GetMargin(object);
	double wholeSize = _size + margin.x + margin.y;
	double absolutParentOrigin = position.GetAbsoluteParentOrigin(parentBounds);
	double leftSize = wholeSize * position.GetProportionalOrigin();
	double rightSize = wholeSize * (1 - position.GetProportionalOrigin());

	double factor1 = leftSize == 0 ? DBL_MAX :(absolutParentOrigin + position.GetShift() - parentBounds.x) / leftSize;
	double factor2 = rightSize == 0 ? DBL_MAX : (parentBounds.y - (absolutParentOrigin + position.GetShift())) / rightSize;
	double factor = fmax(1, fmin(factor1, factor2));
	double x1 = absolutParentOrigin + position.GetShift() - factor * leftSize;
	double x2 = absolutParentOrigin + position.GetShift() + factor * rightSize;
	return Vector2f(x1, x2);
}