#include "RoundedRectangleShape.h"
#include <cmath>

using namespace siegel;

RoundedRectangleShape::RoundedRectangleShape() {
	_size = Vector2f(20, 20);
	_radius = 30;
}

RoundedRectangleShape::RoundedRectangleShape(const Vector2f& size, double radius) {
	_size = size;
	_radius = radius;
}

void RoundedRectangleShape::SetRadius(double radius) {
	_radius = radius;
}

void RoundedRectangleShape::setSize(const Vector2f& size) {
	_size = size;
}

void RoundedRectangleShape::Recompute() {
	update();
}

double RoundedRectangleShape::GetRadius() const {
	return _radius;
}

std::size_t RoundedRectangleShape::getPointCount() const {
	double radius = _radius + getOutlineThickness();
	if (radius < 0.001)
		return _pointCount = 4;
	double error = fmin(0.25, radius / 3);
	double z = (1 - error / radius);
	_pointCount = (std::ceil(std::acos(-1) / std::acos(z) / 4) + 1) * 4;
	return _pointCount;
}

sf::Vector2f RoundedRectangleShape::getPoint(std::size_t index) const {
	double innerRadius = max(0.1, _radius - getOutlineThickness());
	double occ = _pointCount / 4;
	int q = floor(index / occ);
	double arg = std::acos(-1) / 2 * (q + (index - (double)q * occ) / (occ - 1));
	double x = innerRadius * cos(arg);
	double y = innerRadius * sin(arg);
	switch (q) {
	case 0:
		x += _size.x - innerRadius;
		y += _size.y - innerRadius;
		break;
	case 1:
		x += innerRadius;
		y += _size.y - innerRadius;
		break;
	case 2:
		x += innerRadius;
		y += innerRadius;
		break;
	case 3:
		x += _size.x - innerRadius;
		y += innerRadius;
		break;
	}
	return Vector2f(x, y);
}
