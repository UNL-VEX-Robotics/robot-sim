#pragma once

#include <fstream>
#include <iostream>
#include <nlohmann/json.hpp>
#include <SFML/Graphics.hpp>

class Simulation
{
private:
    std::string mode;
    unsigned int framerate;
public:
    Simulation();

    void run();
};