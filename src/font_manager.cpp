#include "font_manager.hpp"

std::unordered_map<std::string, sf::Font>& FontManager::fonts()
{
    static std::unordered_map<std::string, sf::Font> fonts;
    return fonts;
}

bool FontManager::loadFont(const std::string &name, const std::filesystem::path &path)
{
    if (hasFont(name))
        return true; // Font already loaded
        
    try
    {
        fonts()[name] = sf::Font(path);
    }
    catch (const std::exception &e)
    {
        return false;
    }

    return true;
}

const sf::Font &FontManager::getFont(const std::string &name, const std::filesystem::path &path)
{
    if (!hasFont(name))
    {
        if (!loadFont(name, path))
        {
            throw std::runtime_error("Failed to load font: " + name);
        }
    }

    return fonts().at(name);
}

bool FontManager::hasFont(const std::string &name)
{
    return fonts().find(name) != fonts().end();
}