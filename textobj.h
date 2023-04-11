#pragma once
#include "settings.h"

class TextObj {
private:
	sf::Font font;
	sf::Text text;

public:
	TextObj(std::string str, sf::Vector2f pos) {
		font.loadFromFile(RES_FOLDER + FONT_FILE_NAME);
		text.setString(str);
		text.setFont(font);
		text.setCharacterSize(CHAR_SIZE);
		text.setPosition(pos);
	}

	void update(std::string str) {
		text.setString(str);
	}

	sf::Text getText() { return text; }

};