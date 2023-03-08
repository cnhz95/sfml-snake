/*
 * Projekt, DT079G Programmeringsmetodik
 * Christian Hernandez
 */

#include "Snake.h"

Snake::Snake() : m_snake(M_DEFAULT_SIZE), m_tail_it(m_snake.begin()), m_head_it(std::prev(m_snake.end())) {
	size_t index = 1;
	std::for_each(m_tail_it, std::next(m_head_it), [&](sf::RectangleShape& square) -> void {
		square = std::move(create_square(sf::Vector2f(constants::SQUARE_SIZE * index++, constants::SQUARE_SIZE)));
	});
}

void Snake::move_snake(const sf::Vector2f& position) {
	m_tail_it->setPosition(m_head_it->getPosition() + position);
	m_snake.push_back(std::move(*m_tail_it));
	m_snake.erase(m_snake.begin());
	update_iterators();
}

void Snake::increase_size() {
	sf::RectangleShape new_square = std::move(create_square(m_tail_it->getPosition()));
	m_snake.insert(m_snake.begin(), new_square);
	update_iterators();
}

sf::RectangleShape Snake::create_square(const sf::Vector2f& position) {
	sf::RectangleShape square(sf::Vector2f(constants::SQUARE_SIZE, constants::SQUARE_SIZE));
	square.setFillColor(M_SNAKE_COLOR);
	square.setPosition(position);
	return square;
}

void Snake::update_iterators() {
	m_tail_it = m_snake.begin();
	m_head_it = std::prev(m_snake.end());
}

const std::vector<sf::RectangleShape>::iterator Snake::get_head() const {
	return m_head_it;
}

const std::vector<sf::RectangleShape>::iterator Snake::get_tail() const {
	return m_tail_it;
}

void Snake::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	std::for_each(m_tail_it, std::next(m_head_it), [&](const sf::RectangleShape& square) -> void {
		target.draw(square, states);
	});
}