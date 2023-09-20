#include "TextureManager.h"

using namespace siegel;

TextureManager::TextureManager() {
	_pairs = new unordered_map<TextureName, Texture*>();
}

TextureManager::~TextureManager() {
	delete _pairs;
}

void TextureManager::AddTexture(TextureName name, string path) {
	Texture *t = LoadTexture(path);
	if (t == nullptr)
		return;
	(*_pairs)[name] = t;
}

Texture *TextureManager::GetTexture(TextureName name) {
	return (*_pairs)[name];
}

Texture *TextureManager::LoadTexture(string path) {
	Texture *texture = new Texture();
	if (!texture->loadFromFile(path))
		return nullptr;
	return texture;
}

Texture* TextureManager::operator[](TextureName name) {
	return GetTexture(name);
}