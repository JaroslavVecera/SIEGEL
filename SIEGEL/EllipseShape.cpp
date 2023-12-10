#include "EllipseShape.h"
#include <cmath>

using namespace siegel;

    EllipseShape::EllipseShape()
    {
        EllipseShape(Vector2f(1, 1));
    }

    EllipseShape::EllipseShape(const Vector2f& radius) :
        m_radius(radius)
    {
        update();
    }

    void EllipseShape::setRadius(const sf::Vector2f& radius)
    {
        m_radius = radius;
        update();
    }

    const sf::Vector2f& EllipseShape::getRadius() const
    {
        return m_radius;
    }

    std::size_t EllipseShape::getPointCount() const
    {
        double r = (m_radius.x + m_radius.y) / 2;
        double z = (1 - 0.25 / r);
        double th = std::acos(2 * z * z - 1);
        return std::ceil(2 * std::acos(-1) / th);
    }

    sf::Vector2f EllipseShape::getPoint(std::size_t index) const
    {
        static const float pi = 3.141592654f;

        float angle = index * 2 * pi / getPointCount() - pi / 2;
        float x = std::cos(angle) * m_radius.x;
        float y = std::sin(angle) * m_radius.y;

        return sf::Vector2f(m_radius.x + x, m_radius.y + y);
    }