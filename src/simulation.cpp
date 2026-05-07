#include "simulation.hpp"

using json = nlohmann::json;

Simulation::Simulation()
{
    std::ifstream file("config.json");

    if (!file.is_open())
    {
        throw std::runtime_error("Failed to open config.json");
    }

    json config;
    try
    {
        file >> config;
    }
    catch (const json::parse_error &e)
    {
        throw std::runtime_error("Failed to parse config.json: " + std::string(e.what()));
    }

    // Configuration loading with error handling

    if (config.contains("Mode") && config["Mode"].is_string())
        mode = config["Mode"];
    else
        throw std::runtime_error("Mode not found or not a string in config.json");

    if (config.contains("Framerate") && config["Framerate"].is_number_unsigned())
    {
        framerate = config["Framerate"];
    }
    else
    {
        std::cerr << "Framerate not found or not a number in config.json, defaulting to 100" << std::endl;
        framerate = 100;
    }

    std::cout << "Simulation initialized with mode: " << mode << " and framerate: " << framerate << "." << std::endl;
}

void Simulation::run()
{
    // Main window
    sf::RenderWindow window(sf::VideoMode::getDesktopMode(), "Robot Simulator", sf::Style::None, sf::State::Fullscreen);
    window.setFramerateLimit(framerate);
    sf::View view(sf::FloatRect({0.f, 0.f}, {1920.f, 1080.f}));
    window.setView(view);

    Button button("Close Button");

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