#include "ShrinkableSize.h"

using namespace siegel;

siegel::ShrinkableSize::ShrinkableSize(double size) {
	setSize(size);
}

Vector2f siegel::ShrinkableSize::GetBounds(Vector2f& parentBounds, GO &object) {
	Position position = GetPosition(object);

	double minSize = GetMinSize(parentBounds.y - parentBounds.x, object);
	double absolutParentOrigin = position.GetAbsoluteParentOrigin(parentBounds);
	double x1 = absolutParentOrigin + position.GetShift() - minSize * position.GetProportionalOrigin();
	double x2 = absolutParentOrigin + position.GetShift() + minSize * (1 - position.GetProportionalOrigin());
	return Vector2f(x1, x2);
}

double siegel::ShrinkableSize::GetMinSize(double maxParentSize, GO &object) {
	Vector2f& margin = GetMargin(object);
	Vector2f& padding = GetPadding(object);
	double minContentSize = 0;
	for (GO* child : object.GetChildren()) {
		Size* childSize = (_type == SizeType::Horizontal) ? child->_horizontalSize : child->_verticalSize;
		minContentSize = fmax(minContentSize, childSize->GetMinParentSize(_size, *child));
	}
	minContentSize = fmin(minContentSize, _size);
	return minContentSize + margin.x + margin.y + 2 * object.GetBorderThickness() + padding.x + padding.y;
}


double siegel::ShrinkableSize::GetMinParentSize(double maxParentSize, GO &object) {
	double minSize = GetMinSize(maxParentSize, object);
	return SizeToParentSize(minSize, maxParentSize, object);
}