#pragma once
#include <SFML/Graphics.hpp>

class Text {
	static sf::Font font;
	sf::Text text;

public:
	Text();
	~Text();

	void init(const char* content, float x, float y);
	sf::Text getText() { return text; }
};

