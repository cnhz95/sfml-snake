/*
 * Projekt, DT079G Programmeringsmetodik
 * Christian Hernandez
 */

#ifndef GAME_H
#define GAME_H

#include "Constants.h"
#include "Fruit.h"
#include "Score.h"
#include "Snake.h"
#include "World.h"
#include <SFML/Graphics.hpp>
#include <algorithm>
#include <iterator>
#include <memory>

/**
 * Enum class for the different states the game can be in.
 */
enum class Game_state { main_menu, playing, game_over };

/**
 * Class for the game engine responsible for the movement of the snake, checking
 * for collisions, spawning of the fruit, updating the score, etc.
 */
class Game : public sf::Drawable {
public:
	/**
	 * Default constructor. Creates the game object and puts it in the main menu
	 * state. Instantiates the world, snake, fruit and score managed objects.
	 * Sets the snake's start direction to the right and the time step to default.
	 * Initializes the iterators pointing to it's head and it's tail.
	 */
	Game();

	/**
	 * Performs all the actions needed in the progression of the game. Updates
	 * the game every time delta_time has accumlated beyond the games time step
	 * so that it isn't updated on every tick of the game loop.
	 * @param delta_time The game loop's time per frame.
	 */
	void update_game(float delta_time);

	/**
	 * Moves the snake in the direction it is currently desired to move in.
	 */
	void move_snake();

	/**
	 * Getter for the game's state.
	 * @return const Game_state& The state the game is currently in.
	 */
	const Game_state& get_state() const;

	/**
	 * Updates the state the game is currently in.
	 * @param new_state The new state to put the game in.
	 */
	void set_state(const Game_state& new_state);

	/**
	 * Updates the direction the snake moves in if it isn't the opposite nor the same
	 * of the current one.
	 * @param new_direction The direction the player wants the snake to move in.
	 */
	void set_direction(const Direction& new_direction);

private:
	/**
	 * Controls whether the bounding box of any two shapes intersect with each other.
	 * @param shape_a The first shape to compare.
	 * @param shape_b The second shape to compare.
	 * @tparam T type of the first shape.
	 * @tparam U Type of the second shape.
	 * @return bool Indicates if the two shapes intersect each other.
	 */
	template<typename T, typename U>
	bool collides(const T& shape_a, const U& shape_b) const {
		return shape_a.getGlobalBounds().intersects(shape_b.getGlobalBounds());
	}

	/**
	 * Functor that changes the color of the snake when the game is over.
	 * @param square The current square to change the color to.
	 */
	struct Dead_snake {
		void operator()(sf::RectangleShape& square) {
			square.setFillColor(sf::Color(192, 192, 192));
		}
	};

	/**
	 * Controls whether the snake collides with the border.
	 */
	void check_border_collision();

	/**
	 * Controls whether the snake collides with itself.
	 */
	void check_self_collision();

	/**
	 * Controls whether the head of the snake and the fruit are situated at the same position.
	 * If that's the case, the time step is decreased, the score is updated, the snake grows
	 * and the fruit is respawned at a random location where the snake isn't situated.
	 */
	void encounters_fruit();

	/**
	 * Changes the color of the snake whenever it collides with itself or the border.
	 * If a new high score is attained it is updated.
	 */
	void game_over();

	/**
	 * Updates the iterators to point to the head and to the tail.
	 */
	void update_iterators();

	/**
	 * Controls whether the new direction is the opposite of the current direction.
	 * @param current_direction The direction the snake is currently moving in.
	 * @param new_direction The direction the player wants the snake to move in.
	 * @return bool Indicates if the directions are the opposite of each other.
	 */
	bool is_opposite_direction(const Direction& current_direction, const Direction& new_direction) const;

	/**
	 * Draws the game to the render target.
	 * @param target Render target to draw to.
	 * @param states Render states to use for drawing.
	 */
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	const float M_FACTOR = 0.95f;

	float m_time_step;
	float m_time_elapsed{};
	Game_state m_game_state;
	Direction m_current_direction;

	std::unique_ptr<World> m_world;
	std::unique_ptr<Snake> m_snake;
	std::unique_ptr<Fruit> m_fruit;
	std::unique_ptr<Score> m_score;

	std::vector<sf::RectangleShape>::iterator m_head_it;
	std::vector<sf::RectangleShape>::iterator m_tail_it;
};

#endif