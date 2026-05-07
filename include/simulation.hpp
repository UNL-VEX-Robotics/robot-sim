#pragma once

#include <fstream>
#include <iostream>
#include <nlohmann/json.hpp>
#include <SFML/Graphics.hpp>

#include "button.hpp"
#include "font_manager.hpp"

class Simulation
{
private:
    std::string mode;
    unsigned int framerate;
public:
    /// @brief Constructs a new Simulation object by reading configuration from a JSON file.
    Simulation();

    /// @brief Runs the simulation based on the loaded configuration.
    void run();
};