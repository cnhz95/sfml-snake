/*
 * Projekt, DT079G Programmeringsmetodik
 * Christian Hernandez
 */

#ifndef FRUIT_H
#define FRUIT_H

#include "Constants.h"
#include <SFML/Graphics.hpp>
#include <chrono>
#include <random>

/**
 * Class for the fruit which handles it's spawning.
 */
class Fruit : public sf::Drawable {
public:
	/**
	 * Default constructor. Creates the fruit object, with a given radius,
	 * in the middle of the screen.
	 */
	Fruit();

	/**
	 * Spawns the fruit at a random position within the borders.
	 */
	void respawn();

	/**
	 * Getter for the fruit.
	 * @return const sf::CircleShape& The circle shape representing the fruit.
	 */
	const sf::CircleShape& get_fruit() const;

private:
	/**
	 * Draws the circle that represents the fruit.
	 * @param target Render target to draw to.
	 * @param states Render states to use for drawing.
	 */
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	const float M_RADIUS = constants::SQUARE_SIZE / 2;

	sf::CircleShape m_fruit;
};

#endif