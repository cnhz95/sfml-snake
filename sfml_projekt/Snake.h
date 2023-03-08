/*
 * Projekt, DT079G Programmeringsmetodik
 * Christian Hernandez
 */

#ifndef SNAKE_H
#define SNAKE_H

#include "Constants.h"
#include <SFML/Graphics.hpp>
#include <iterator>

/**
 * Enum class for the directions the snake can move in.
 */
enum class Direction { up, down, left, right };

/**
 * Class for the snake which handles it's movement and increasement in size.
 */
class Snake : public sf::Drawable {
public:
	/**
	 * Default constructor. Creates the snake object with default size starting from the
	 * top left corner of the grid. Initializes the iterators pointing to the head and the tail.
	 */
	Snake();

	/**
	 * Moves the snake by putting the square at the tail on the given
	 * position next to the head.
	 * @param position The position in which to move the snake.
	 */
	void move_snake(const sf::Vector2f& position);

	/**
	 * Increases the size of the snake whenever it encounters fruit.
	 */
	void increase_size();

	/**
	 * Getter for the iterator pointing to the head.
	 * @return const std::vector<sf::RectangleShape>::iterator Iterator pointing to the head.
	 */
	const std::vector<sf::RectangleShape>::iterator get_head() const;

	/**
	 * Getter for the iterator pointing to the tail.
	 * @return const std::vector<sf::RectangleShape>::iterator Iterator pointing to the tail.
	 */
	const std::vector<sf::RectangleShape>::iterator get_tail() const;

private:
	/**
	 * Updates the iterators pointing to the head and to the tail.
	 */
	void update_iterators();

	/**
	 * Creates a new snake square at the given position.
	 * @param position The position in which to place the new square.
	 * @return sf::RectangleShape The newly created square.
	 */
	sf::RectangleShape create_square(const sf::Vector2f& position);

	/**
	 * Draws the squares that the snake is made of.
	 * @param target Render target to draw to.
	 * @param states Render states to use for drawing.
	 */
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	const size_t M_DEFAULT_SIZE = 4;
	const sf::Color M_SNAKE_COLOR = sf::Color(128, 49, 167);

	std::vector<sf::RectangleShape> m_snake;
	std::vector<sf::RectangleShape>::iterator m_head_it;
	std::vector<sf::RectangleShape>::iterator m_tail_it;
};

#endif