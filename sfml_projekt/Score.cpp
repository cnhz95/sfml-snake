/*
 * Projekt, DT079G Programmeringsmetodik
 * Christian Hernandez
 */

#include "Score.h"

#include <iostream>

Score::Score() {
	init_high_score();
	init_text();
}

void Score::init_high_score() {
	std::ifstream file(M_FILENAME);
	if (!file) {
		std::cerr << "The file \"" << M_FILENAME << "\" couldn't be opened!\n";
		return;
	}
	if (file.peek() != std::ifstream::traits_type::eof()) { // The file is not empty.
		file >> m_high_score;
	}
	file.close();
}

void Score::init_text() {
	if (m_font.loadFromFile(constants::FONT_NAME)) {
		m_score_text = std::move(sf::Text("Score: 0\tBest: " + std::to_string(m_high_score), m_font, (unsigned int)constants::SQUARE_SIZE - 3));
		m_score_text.setPosition(constants::WINDOW_WIDTH / 2 - m_score_text.getGlobalBounds().width / 2, 0.f);
		m_score_text.setFillColor(sf::Color::Black);
		m_score_text.setOutlineColor(sf::Color::White);
		m_score_text.setOutlineThickness(2.f);
	}
}

void Score::update_score() {
	if (++m_current_score > m_high_score) {
		m_high_score = m_current_score;
	}
	m_score_text.setString("Score: " + std::to_string(m_current_score) + "\tBest: " + std::to_string(m_high_score));
}

void Score::update_high_score() {
	if (m_current_score > m_high_score) {
		std::ofstream file(M_FILENAME);
		if (!file) {
			std::cerr << "The file \"" << M_FILENAME << "\" couldn't be opened!\n";
			return;
		}
		file << m_high_score;
		file.close();
	}
}

void Score::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	target.draw(m_score_text, states);
}