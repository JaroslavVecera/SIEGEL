#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include "GO.h"

using namespace sf;

namespace siegel {
	class Canvas : public sf::RenderWindow {
	private:
		GO* _object = nullptr;
		sf::Color _background;
	public:
		Canvas(VideoMode mode, const String& title, Uint32 style = Style::Default, const ContextSettings& settings = ContextSettings(), sf::Color background = sf::Color::Black);

		void SetObject(GO* obj);
		GO* GetObject() const;
		void Clear();
		void Render() const;
		void Emplace();

		void DrawCut(const sf::Drawable& target, const sf::FloatRect cut) {
			glEnable(GL_SCISSOR_TEST);
			glScissor(cut.left + cut.width, cut.top + cut.height, cut.width, cut.height);
			this->draw(target);
			glDisable(GL_SCISSOR_TEST);
		}
	};
}