/*
 * Projekt, DT079G Programmeringsmetodik
 * Christian Hernandez
 */

#ifndef MAIN_MENU_H
#define MAIN_MENU_H

#include "Constants.h"
#include <SFML/Graphics.hpp>
#include <vector>

/**
 * Class for the main menu which handles the texts to be dispayed.
 */
class Main_menu : public sf::Drawable {
public:
	/**
	 * Default constructor. Creates the menu object. Sets the default
	 * number of options. Initializes the font and text for the
	 * title and the options to be displayed.
	 */
	Main_menu();

	/**
	 * Getter for the options.
	 * @return const std::vector<sf::Text>& The options text vector.
	 */
	const std::vector<sf::Text>& get_options() const;

	/**
	 * Updates the text displayed as the main menu's first option.
	 */
	void set_option_text(std::string&& option_name);

	/**
	 * Updates the color of the options depending on whether they
	 * are hovered by the mouse.
	 */
	void set_text_color(size_t index, const sf::Color& color);

private:
	/**
	 * Loads the default font and initializes the title's text.
	 */
	void init_game_text();

	/**
	 * Initializes the option's text.
	 */
	void init_options();

	/**
	 * Draws the main menu to the render target.
	 * @param target Render target to draw to.
	 * @param states Render states to use for drawing.
	 */
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	const size_t M_TOTAL_OPTIONS = 2;

	sf::Font m_font;
	sf::Text m_title_text;
	std::vector<sf::Text> m_options_text;
};

#endif