#pragma once

#include "GO.h"
#include "Canvas.h"
#include <forward_list>
#include "Rectangle.h"

namespace siegel {
	class Canvas;
	class Layout : public GO {
	protected:
		forward_list<GO*> _children;
		Rectangle _border;
		double _borderThickness;
		double _cornerRadius;
		sf::Color _outlineColor;
	protected:
		void Initialize();
		virtual void Emplace(Vector2f& horizontalParentBounds, Vector2f& verticalParentBounds);
		virtual void EmplaceBorder(Vector2f& horizontalParentBounds, Vector2f& verticalParentBounds);
		virtual forward_list<GO*> GetChildren();
		virtual void EmplaceChildren(Vector2f& horizontalParentBounds, Vector2f& verticalParentBounds);
	public:
		Layout();
		void SetOutlineColor(Color& c);
		Color GetOutlineColor() const;
		void AddChild(GO* child);
		virtual void Render() const;
		void SetHorizontalPadding(Vector2f margin);
		void SetVerticalPadding(Vector2f margin);
		virtual Vector2f &GetHorizontalPadding();
		virtual Vector2f &GetVerticalPadding();
		void SetBorderThickness(double thickness);
		virtual double GetBorderThickness();
		void SetCornerRadius(double radius);
		double GetCornerRadius();
	};
}