/*
 * Projekt, DT079G Programmeringsmetodik
 * Christian Hernandez
 */

#include "Fruit.h"

Fruit::Fruit() : m_fruit(M_RADIUS) {
	m_fruit.setFillColor(sf::Color(205, 0, 26));
	m_fruit.setPosition(constants::WINDOW_WIDTH / 2 - 0.5f * constants::SQUARE_SIZE,
		constants::WINDOW_WIDTH / 2 - 0.5f * constants::SQUARE_SIZE); // Window center.
}

void Fruit::respawn() {
	std::uniform_int_distribution<int> uid(1, (int)constants::SQUARES - 2);
	std::mt19937 rng((unsigned int)std::chrono::steady_clock::now().time_since_epoch().count());
	m_fruit.setPosition(uid(rng) * constants::SQUARE_SIZE, uid(rng) * constants::SQUARE_SIZE);
}

const sf::CircleShape& Fruit::get_fruit() const {
	return m_fruit;
}

void Fruit::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	target.draw(m_fruit, states);
}