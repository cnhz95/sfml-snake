/*
 * Projekt, DT079G Programmeringsmetodik
 * Christian Hernandez
 */

#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <string>

/**
 * Namespace for variables required across multiple files.
 */
namespace constants {
	inline constexpr float SQUARES = 27.f;
	inline constexpr float SQUARE_SIZE = 30.f;
	inline constexpr float WINDOW_WIDTH = SQUARES * SQUARE_SIZE;
	inline constexpr float WINDOW_HEIGTH = SQUARES * SQUARE_SIZE;
	inline constexpr float GAME_UPDATE_RATE = 0.1f;
	inline const std::string FONT_NAME = "Fonts/Pacifico-Regular.ttf";
}

#endif