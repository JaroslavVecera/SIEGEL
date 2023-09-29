#pragma once

#include "StretchableSize.h"

siegel::StretchableSize::StretchableSize(double size) {
	setSize(size);
}

Vector2f siegel::StretchableSize::GetBounds(Vector2f const& parentBounds, Position const& position, const forward_list<GO*> const& children) {
	double absolutParentOrigin = position.GetAbsoluteParentOrigin(parentBounds);
	double factor1 = (absolutParentOrigin - parentBounds.x + position.GetShift()) / (_size * position.GetProportionalOrigin());
	double factor2 = (parentBounds.y - absolutParentOrigin - position.GetShift()) / (_size * (1 - position.GetProportionalOrigin()));
	double factor = fmax(1, fmin(factor1, factor2));
	double x1 = absolutParentOrigin + position.GetShift() - _size * factor * position.GetProportionalOrigin();
	double x2 = absolutParentOrigin + position.GetShift() + _size * factor * (1 - position.GetProportionalOrigin());
	return Vector2f(x1, x2);
}