#pragma once

#include "GO.h"
#include "Canvas.h"
#include <forward_list>

namespace siegel {
	class Canvas;
	class Layout : public GO {
	protected:
		forward_list<GO*> _children;
		RectangleShape _border;

		void Initialize();
		virtual void Emplace(Vector2f& horizontalParentBounds, Vector2f& verticalParentBounds);
		virtual forward_list<GO*> GetChildren();
	public:
		Layout();

		void SetHorizontalSize(siegel::Size* size);
		void SetVerticalSize(siegel::Size* size);

		void SetOutlineColor(Color& c);
		Color GetOutlineColor() const;

		void AddChild(GO* child);
		virtual void Render();
	};
}