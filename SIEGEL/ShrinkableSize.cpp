#include "ShrinkableSize.h"

using namespace siegel;

siegel::ShrinkableSize::ShrinkableSize(double size) {
	setSize(size);
}

Vector2f siegel::ShrinkableSize::GetBounds(Vector2f const& parentBounds, Position const& position, const forward_list<GO*> const& children) {
	double minSize = GetMinSize(parentBounds.y - parentBounds.x, position, (forward_list<GO*>&)children);
	double absolutParentOrigin = position.GetAbsoluteParentOrigin(parentBounds);
	double x1 = absolutParentOrigin + position.GetShift() - minSize * position.GetProportionalOrigin();
	double x2 = absolutParentOrigin + position.GetShift() + minSize * (1 - position.GetProportionalOrigin());
	return Vector2f(x1, x2);
}

double siegel::ShrinkableSize::GetMinSize(double maxParentSize, Position const& position, std::forward_list<GO*> const& children) {
	double minSize = 0;
	for (GO* child : children) {
		if (_type == SizeType::Horizontal)
			minSize = fmax(minSize, child->_horizontalSize->GetMinParentSize(_size, child->_horizontalPosition, child->GetChildren()));
		else
			minSize = fmax(minSize, child->_verticalSize->GetMinParentSize(_size, child->_verticalPosition, child->GetChildren()));
	}
	minSize = fmin(minSize, _size);
	return minSize;
}


double siegel::ShrinkableSize::GetMinParentSize(double maxParentSize, Position const& position, std::forward_list<GO*> const& children) {
	double minSize = GetMinSize(maxParentSize, position, children);

	return SizeToParentSize(minSize, maxParentSize, position, children);
}