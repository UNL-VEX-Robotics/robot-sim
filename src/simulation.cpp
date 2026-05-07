#include "simulation.hpp"

using json = nlohmann::json;

Simulation::Simulation()
{
    std::ifstream file("config.json");

    if (!file.is_open())
    {
        std::cerr << "Failed to open config.json" << std::endl;
        return;
    }

    json config;
    try
    {
        file >> config;
    }
    catch (const json::parse_error &e)
    {
        std::cerr << "Failed to parse config.json: " << e.what() << std::endl;
        return;
    }

    // Configuration loading with error handling

    if (config.contains("Mode") && config["Mode"].is_string())
        mode = config["Mode"];
    else
        std::cerr << "Mode not found or not a string in config.json" << std::endl;

    if (config.contains("Framerate") && config["Framerate"].is_number_unsigned())
        framerate = config["Framerate"];
    else
        std::cerr << "Framerate not found or not an unsigned number in config.json" << std::endl;

    std::cout << "Simulation initialized with mode: " << mode << "." << std::endl;
}

void Simulation::run()
{
    // Main window
    sf::RenderWindow window(sf::VideoMode::getDesktopMode(), "Robot Simulator", sf::Style::None, sf::State::Fullscreen);
    window.setFramerateLimit(framerate);

    // Fonts
    sf::Font font("assets/fonts/Arial-Rounded.ttf");

    Button button(
        font, 
        "Close X", 
        {200.f, 50.f}, 
        sf::Color::Red, 
        sf::Color::White, 
        sf::Color(200, 0, 0), 
        30, 
        10.f, 
        8
    );

    while (window.isOpen())
    {
        button.isHovered(window.mapPixelToCoords(sf::Mouse::getPosition(window)));

        while (const std::optional<sf::Event> event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
            if (event->is<sf::Event::MouseButtonPressed>() && button.isHovered(window.mapPixelToCoords(sf::Mouse::getPosition(window))))
                window.close();
        }

        window.clear(sf::Color::Black);
        window.draw(button);
        window.display();
    }
}