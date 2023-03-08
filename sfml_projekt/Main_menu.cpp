/*
 * Projekt, DT079G Programmeringsmetodik
 * Christian Hernandez
 */

#include "Main_menu.h"

Main_menu::Main_menu() : m_options_text(M_TOTAL_OPTIONS) {
	init_game_text();
	init_options();
}

void Main_menu::init_game_text() {
	if (m_font.loadFromFile(constants::FONT_NAME)) {
		m_title_text = std::move(sf::Text("Snake", m_font, (unsigned int)constants::SQUARE_SIZE * 4));
		m_title_text.setPosition(constants::WINDOW_WIDTH / 2 - m_title_text.getGlobalBounds().width / 2, constants::SQUARE_SIZE * 5);
		m_title_text.setFillColor(sf::Color::Green);
	}
}

void Main_menu::init_options() {
	m_options_text[0] = std::move(sf::Text("Start game", m_font, (unsigned int)constants::SQUARE_SIZE * 2));
	m_options_text[0].setPosition(constants::WINDOW_WIDTH / 2 - m_options_text[0].getGlobalBounds().width / 2, constants::SQUARE_SIZE * 12);
	m_options_text[1] = std::move(sf::Text("Exit", m_font, (unsigned int)constants::SQUARE_SIZE * 2));
	m_options_text[1].setPosition(constants::WINDOW_WIDTH / 2 - m_options_text[1].getGlobalBounds().width / 2, constants::SQUARE_SIZE * 16);
}

const std::vector<sf::Text>& Main_menu::get_options() const {
	return m_options_text;
}

void Main_menu::set_option_text(std::string&& option_name) {
	m_options_text[0].setString(std::move(option_name));
	m_options_text[0].setPosition(constants::WINDOW_WIDTH / 2 - m_options_text[0].getGlobalBounds().width / 2, constants::SQUARE_SIZE * 12);
}

void Main_menu::set_text_color(size_t index, const sf::Color& color) {
	m_options_text[index].setFillColor(color);
}

void Main_menu::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	target.draw(m_title_text);
	std::for_each(m_options_text.begin(), m_options_text.end(), [&](const sf::Text& text) -> void {
		target.draw(text);
	});
}