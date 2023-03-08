/*
 * Projekt, DT079G Programmeringsmetodik
 * Christian Hernandez
 */

#include "Game.h"

Game::Game() : m_world(std::make_unique<World>()), m_snake(std::make_unique<Snake>()), m_fruit(std::make_unique<Fruit>()),
	m_score(std::make_unique<Score>()), m_game_state(Game_state::main_menu), m_current_direction(Direction::right),
	m_tail_it(m_snake->get_tail()), m_head_it(m_snake->get_head()), m_time_step(constants::GAME_UPDATE_RATE) {}

void Game::update_game(float delta_time) {
	m_time_elapsed += delta_time; // Increased on every iteration of the game's loop.
	// The game is only updated after m_time_step seconds.
	if (m_time_elapsed > m_time_step) {
		move_snake();
		update_iterators();
		check_border_collision();
		check_self_collision();
		encounters_fruit();
		m_time_elapsed = 0.f;
	}
}

void Game::move_snake() {
	switch (m_current_direction) {
	case Direction::up:
		m_snake->move_snake(sf::Vector2f(0.f, -constants::SQUARE_SIZE));
		break;
	case Direction::down:
		m_snake->move_snake(sf::Vector2f(0.f, constants::SQUARE_SIZE));
		break;
	case Direction::left:
		m_snake->move_snake(sf::Vector2f(-constants::SQUARE_SIZE, 0.f));
		break;
	case Direction::right:
		m_snake->move_snake(sf::Vector2f(constants::SQUARE_SIZE, 0.f));
		break;
	}
}

void Game::check_border_collision() {
	auto& borders = m_world->get_borders();
	std::for_each(borders.begin(), borders.end(), [&](const sf::RectangleShape& border) -> void {
		if (collides(*m_head_it, border)) {
			game_over();
		}
	});
}

void Game::check_self_collision() {
	std::for_each(m_tail_it, m_head_it, [&](const sf::RectangleShape& square) -> void {
		if (collides(*m_head_it, square)) {
			game_over();
		}
	});
}

void Game::encounters_fruit() {
	auto& fruit = m_fruit->get_fruit();
	if (collides(*m_head_it, fruit)) {
		m_time_step *= M_FACTOR; // Increases the game's update rate.
		m_score->update_score();
		m_snake->increase_size();
		update_iterators();
		// Controls if the fruit was respawned on top of the snake.
		auto spawned_on_snake = [&]() -> bool {
			auto it = std::find_if(m_tail_it, std::next(m_head_it), [&](const sf::RectangleShape& square) -> bool {
				return collides(square, fruit);
			});
			return it != std::next(m_head_it);
		};
		do {
			m_fruit->respawn();
		} while (spawned_on_snake());
	}
}

void Game::game_over() {
	std::for_each(m_tail_it, std::next(m_head_it), Dead_snake());
	m_score->update_high_score();
	m_game_state = Game_state::game_over;
}

void Game::update_iterators() {
	m_tail_it = m_snake->get_tail();
	m_head_it = m_snake->get_head();
}

const Game_state& Game::get_state() const {
	return m_game_state;
}

void Game::set_state(const Game_state& new_state) {
	m_game_state = new_state;
}

void Game::set_direction(const Direction& new_direction) {
	if (!is_opposite_direction(m_current_direction, new_direction) && m_current_direction != new_direction) {
		m_current_direction = new_direction;
	}
}

bool Game::is_opposite_direction(const Direction& current_direction, const Direction& new_direction) const {
	if ((current_direction == Direction::up && new_direction == Direction::down) ||
		(current_direction == Direction::down && new_direction == Direction::up) ||
		(current_direction == Direction::left && new_direction == Direction::right) ||
		(current_direction == Direction::right && new_direction == Direction::left)) {
		return true;
	}
	return false;
}

void Game::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	target.draw(*m_world, states);
	target.draw(*m_snake, states);
	target.draw(*m_fruit, states);
	target.draw(*m_score, states);
}