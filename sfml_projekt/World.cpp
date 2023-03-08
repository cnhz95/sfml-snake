/*
 * Projekt, DT079G Programmeringsmetodik
 * Christian Hernandez
 */

#include "World.h"

World::World() : m_borders(M_TOTAL_BORDERS), m_grid((size_t)constants::SQUARES - 2, std::vector<sf::RectangleShape>((size_t)constants::SQUARES - 2)) {
	init_border();
	init_grid();
}

void World::init_border() {
	for (size_t border = 0; border < M_TOTAL_BORDERS; border++) {
		// Sets each border at it's respective position with it's given size.
		auto set_properties = [&](const sf::Vector2f& position, const sf::Vector2f& size) -> void {
			m_borders[border].setPosition(position);
			m_borders[border].setSize(size);
			m_borders[border].setOutlineThickness(constants::SQUARE_SIZE);
			m_borders[border].setOutlineColor(sf::Color(0, 110, 51));
		};
		switch (border) {
		case Position::top:
			set_properties(sf::Vector2f(0.f, 0.f), sf::Vector2f(constants::WINDOW_WIDTH, 0.f));
			break;
		case Position::right:
			set_properties(sf::Vector2f(constants::WINDOW_WIDTH, constants::SQUARE_SIZE),
				sf::Vector2f(0.f, constants::WINDOW_HEIGTH - 2 * constants::SQUARE_SIZE));
			break;
		case Position::bottom:
			set_properties(sf::Vector2f(0.f, constants::WINDOW_HEIGTH), sf::Vector2f(constants::WINDOW_WIDTH, 0.f));
			break;
		case Position::left:
			set_properties(sf::Vector2f(0.f, constants::SQUARE_SIZE),
				sf::Vector2f(0.f, constants::WINDOW_HEIGTH - 2 * constants::SQUARE_SIZE));
			break;
		}
	}
}

void World::init_grid() {
	bool shift_color = 0;
	int row_index = 1;
	std::for_each(m_grid.begin(), m_grid.end(), [&](std::vector<sf::RectangleShape>& row) -> void {
		int col_index = 1;
		std::for_each(row.begin(), row.end(), [&](sf::RectangleShape& square) -> void {
			shift_color ? square.setFillColor(sf::Color(0, 154, 23)) : square.setFillColor(sf::Color(120, 190, 33));
			square.setSize(sf::Vector2f(constants::SQUARE_SIZE, constants::SQUARE_SIZE));
			square.setPosition(constants::SQUARE_SIZE * (float)col_index, constants::SQUARE_SIZE * (float)row_index);
			shift_color ^= 1;
			col_index++;
		});
		row_index++;
	});
}

const std::vector<sf::RectangleShape>& World::get_borders() const {
	return m_borders;
}

void World::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	std::for_each(m_grid.begin(), m_grid.end(), [&](const std::vector<sf::RectangleShape>& row) -> void {
		std::for_each(row.begin(), row.end(), [&](const sf::RectangleShape& square) -> void {
			target.draw(square, states);
		});
	});
	std::for_each(m_borders.begin(), m_borders.end(), [&](const sf::RectangleShape& border) -> void {
		target.draw(border, states);
	});
}