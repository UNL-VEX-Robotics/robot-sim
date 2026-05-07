#include "simulation.hpp"

int main() 
{
    FontManager::loadFont("DEFAULT_FONT", "assets/fonts/Arial-Rounded.ttf");
    Simulation().run();
}