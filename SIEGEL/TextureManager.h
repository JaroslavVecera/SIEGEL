#pragma once

#include <SFML/Graphics.hpp>
#include <unordered_map>

using namespace sf;
using namespace std;

namespace siegel {
	enum TextureName {
		Test1,
		Test2,
		Test3
	};

	class TextureManager {
	private:
		unordered_map<TextureName, Texture*>* _pairs;
	private:
		Texture* LoadTexture(string);
	public:
		TextureManager();
		~TextureManager();

		void AddTexture(TextureName, string);
		Texture* GetTexture(TextureName);
		Texture* operator[](TextureName name);
	};
}
