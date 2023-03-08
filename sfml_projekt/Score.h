/*
 * Projekt, DT079G Programmeringsmetodik
 * Christian Hernandez
 */

#ifndef SCORE_H
#define SCORE_H

#include "Constants.h"
#include <SFML/Graphics.hpp>
#include <fstream>
#include <iostream>

/**
 * Class for the score which manages the scores to be displayed and stored.
 */
class Score : public sf::Drawable {
public:
	/**
	 * Default constructor. Creates the score object. Initializes the
	 * current score and high score text.
	 */
	Score();

	/**
	 * Updates the current score to be displayed as well as the
	 * high score displayed if it is surpassed.
	 */
	void update_score();

	/**
	 * Overwrites the high score in the text file if a higher one
	 * has been achieved.
	 */
	void update_high_score();

private:
	/**
	 * Stores the high score from the text file if it isn't empty.
	 */
	void init_high_score();

	/**
	 * Initializes the text in which the current score and the
	 * high score are displayed.
	 */
	void init_text();

	/**
	 * Draws the text that represents the scores.
	 * @param target Render target to draw to.
	 * @param states Render states to use for drawing.
	 */
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	const std::string M_FILENAME = "high_score.txt";

	sf::Font m_font;
	sf::Text m_score_text;
	size_t m_current_score{};
	size_t m_high_score{};
};

#endif