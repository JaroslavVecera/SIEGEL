#pragma once

#include "GO.h"
#include "Shape.h"
#include "Canvas.h"
#include "RoundedRectangleShape.h"
#include <SFML/Graphics.hpp>

namespace siegel {
	class Rectangle : public Shape {
	protected:
		RoundedRectangleShape _roundedShape;
		sf::RectangleShape _shape;
		double _radius;
		double _borderThickness;
		Color _borderColor;
		Color _color;
	protected:
		void Initialize(double radius, sf::Color color);
		virtual void Emplace(Vector2f& horizontalParentBounds, Vector2f& verticalParentBounds);
		void EmplaceThickNormal(double sizeH, double sizeV, double radius, double thickness);
		void EmplaceThickDegenerate(double sizeH, double sizeV, double thickness);
		void EmplaceBorderless(double sizeH, double sizeV, double radius);
		void Emplace(double sizeH, double sizeV, double radius, Color outlineColor, Color fillColor, double outlineThickness);

		friend class Layout;
	public:
		Rectangle();
		Rectangle(double radius, sf::Color color);

		void SetColor(const Color color);
		const Color GetColor() const;
		void SetBorderColor(const Color color);
		const Color GetBorderColor() const;
		virtual void Render() const;
		void SetRadius(double radius);
		double GetRadius() const;
		void SetBorderThickness(double thickness);
		double GetBorderThickness() const;
	};
}