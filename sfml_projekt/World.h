/*
 * Projekt, DT079G Programmeringsmetodik
 * Christian Hernandez
 */

#ifndef WORLD_H
#define WORLD_H

#include "Constants.h"
#include <SFML/Graphics.hpp>
#include <vector>

/**
 * Enum class for the positions of the borders.
 */
enum Position { top, bottom, left, right };

/**
 * Class for the world which is made of the borders and the grid.
 */
class World : public sf::Drawable {
public:
	/**
	 * Default constructor. Creates the world object. Initializes the
	 * borders and the grid.
	 */
	World();

	/**
	 * Getter for the borders.
	 * @return const std::vector<sf::RectangleShape>& The borders vector.
	 */
	const std::vector<sf::RectangleShape>& get_borders() const;
	
private:
	/**
	 * Initializes the 2-D grid to alternate between two shades of green.
	 */
	void init_grid();

	/**
	 * Initializes the borders.
	 */
	void init_border();

	/**
	 * Draws the squares representing the borders and the grid.
	 * @param target Render target to draw to.
	 * @param states Render states to use for drawing.
	 */
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	const size_t M_TOTAL_BORDERS = 4;

	std::vector<sf::RectangleShape> m_borders;
	std::vector<std::vector<sf::RectangleShape>> m_grid;
};

#endif