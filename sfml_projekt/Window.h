/*
 * Projekt, DT079G Programmeringsmetodik
 * Christian Hernandez
 */

#ifndef WINDOW_H
#define WINDOW_H

#include "Constants.h"
#include "Game.h"
#include "Main_menu.h"
#include <SFML/Graphics.hpp>
#include <memory>

/**
 * Class for the window in which the game is displayed and the user input in handled.
 */
class Window {
public:
	/**
	 * Default constructor.
	 */
	Window() = delete;

	/**
	 * Parameterized constructor. Creates the window object with the given title and default
	 * witdth and height. Sets the framerate limit to 60 frames per second. Initializes
	 * the game and main menu managed objects as well as the countdown text. 
	 * @param title The title of the window.
	 */
	explicit Window(std::string&& title);

	/*
	 * Game loop. Handles the events, runs and draws the respective window.
	 */
	void run();

private:
	/**
	 * Loads the default font and initializes the countdown's text.
	 */
	void init_text();

	/**
	 * Handles the events that may be in the event queue.
	 */
	void handle_event();

	/**
	 * Handles the mouse input when the game is in the main menu state.
	 * @param event The event containing the mouse input.
	 */
	void handle_menu_input(const sf::Event& event);

	/**
	 * Handles the keyboard input when the game is in the playing state
	 * and uptades the game.
	 * @param event The event containing the keyboard input.
	 */
	void handle_game_input(const sf::Event& event);

	/**
	 * Starts a countdown of 3 seconds.
	 */
	void start_countdown();

	const float M_TIME_PER_FRAME = 1.f / 60.f;

	float m_time_since_last_update{};
	sf::RenderWindow m_window;
	sf::Text m_countdown_text;
	sf::Font m_font;
	sf::Event m_event;

	std::unique_ptr<Game> m_game;
	std::unique_ptr<Main_menu> m_main_menu;
};

#endif