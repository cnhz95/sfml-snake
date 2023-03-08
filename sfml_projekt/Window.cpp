/*
 * Projekt, DT079G Programmeringsmetodik
 * Christian Hernandez
 */

#include "Window.h"

Window::Window(std::string&& title) : m_window(sf::VideoMode((unsigned int)constants::WINDOW_WIDTH, (unsigned int)constants::WINDOW_HEIGTH),
    std::move(title), sf::Style::Titlebar | sf::Style::Close), m_game(std::make_unique<Game>()), m_main_menu(std::make_unique<Main_menu>()) {
    m_window.setFramerateLimit(60);
    init_text();
}

void Window::run() {
    sf::Clock clock;
    while (m_window.isOpen()) {
        m_time_since_last_update += clock.restart().asSeconds();
        while (m_time_since_last_update > M_TIME_PER_FRAME) {
            m_time_since_last_update -= M_TIME_PER_FRAME;
            handle_event();
            m_window.clear();
            switch (m_game->get_state()) {
            case Game_state::main_menu:
                m_window.draw(*m_main_menu);
                break;
            case Game_state::playing:
                m_game->update_game(M_TIME_PER_FRAME);
                m_window.draw(*m_game);
                break;
            case Game_state::game_over:
                sf::sleep(sf::seconds(1.f));
                m_game.reset(); // Destroys the currently managed object.
                m_game = std::make_unique<Game>();
                m_main_menu->set_option_text("New game");
                m_game->set_state(Game_state::main_menu);
                break;
            }
            m_window.display();
        }
    }
}

void Window::handle_event() {
    while (m_window.pollEvent(m_event)) {
        if (m_event.type == sf::Event::Closed) {
            m_window.close();
        }
        switch (m_game->get_state()) {
        case Game_state::main_menu:
            handle_menu_input(m_event);
            break;
        case Game_state::playing:
            handle_game_input(m_event);
            break;
        }
    }
}

void Window::handle_menu_input(const sf::Event& event) {
    auto& menu_options = m_main_menu->get_options();
    sf::Vector2f mouse_position(sf::Mouse::getPosition(m_window));
    // Updates the color of the options text if they are hovered by the mouse.
    for (size_t option = 0; option < menu_options.size(); option++) {
        menu_options[option].getGlobalBounds().contains(mouse_position) ?
        m_main_menu->set_text_color(option, sf::Color::Blue) : m_main_menu->set_text_color(option, sf::Color::White);
    }
    if (event.type == sf::Event::MouseButtonReleased) {
        if (menu_options[0].getGlobalBounds().contains(mouse_position) && event.mouseButton.button == sf::Mouse::Left) {
            start_countdown();
            m_game->set_state(Game_state::playing);
        }
        if (menu_options[1].getGlobalBounds().contains(mouse_position) && event.mouseButton.button == sf::Mouse::Left) {
            m_window.close();
        }
    }
}

void Window::handle_game_input(const sf::Event& event) {
    if (event.type == sf::Event::KeyPressed) {
        switch (event.key.code) {
        case sf::Keyboard::W:
        case sf::Keyboard::Up:
            m_game->set_direction(Direction::up);
            break;
        case sf::Keyboard::S:
        case sf::Keyboard::Down:
            m_game->set_direction(Direction::down);
            break;
        case sf::Keyboard::A:
        case sf::Keyboard::Left:
            m_game->set_direction(Direction::left);
            break;
        case sf::Keyboard::D:
        case sf::Keyboard::Right:
            m_game->set_direction(Direction::right);
            break;
        case sf::Keyboard::Escape:
            m_window.close();
            break;
        case sf::Keyboard::P: // Paused
            m_main_menu->set_option_text("Continue");
            m_game->set_state(Game_state::main_menu);
            break;
        }
        m_game->update_game(constants::GAME_UPDATE_RATE); // Forces the game to update.
    }
}

void Window::init_text() {
    if (m_font.loadFromFile(constants::FONT_NAME)) {
        m_countdown_text = std::move(sf::Text("", m_font, (unsigned int)constants::SQUARE_SIZE * 5));
        m_countdown_text.setFillColor(sf::Color(249, 101, 21));
        m_countdown_text.setOutlineColor(sf::Color::White);
        m_countdown_text.setOutlineThickness(2.f);
    }
}

void Window::start_countdown() {
    size_t countdown = 3;
    while (countdown) {
        m_window.clear();
        m_countdown_text.setString(std::to_string(countdown--));
        m_countdown_text.setPosition(constants::WINDOW_WIDTH / 2 - m_countdown_text.getGlobalBounds().width / 2,
            constants::WINDOW_HEIGTH / 2 - m_countdown_text.getGlobalBounds().height * 2);
        m_window.draw(m_countdown_text);
        m_window.display();
        sf::sleep(sf::seconds(1.f));
    }
}