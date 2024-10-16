#include "Text.h"

sf::Font Text::font;

Text::Text() {}
Text::~Text() {}

void Text::init(const char* content, float x, float y) {
	if (!font.loadFromFile("src/font/Movistar Text Regular.ttf")) exit(EXIT_FAILURE);
    text.setFont(font);
    text.setString(content);
    text.setCharacterSize(25);
    text.setFillColor(sf::Color::White);
    text.setPosition(x, y);
    text.setStyle(sf::Text::Bold);
}
