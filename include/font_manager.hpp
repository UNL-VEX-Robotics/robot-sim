#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include <unordered_map>

/// @brief Static class to manage fonts in the application, allowing for loading and retrieving fonts by name.
class FontManager
{
private:
    /// @brief Gets the map of all loaded fonts.
    /// @return A reference to the map of fonts.
    static std::unordered_map<std::string, sf::Font>& fonts();

public:
    /// @brief Loads a font from the specified path.
    /// @param name The name to associate with the font.
    /// @param path The path to the font file.
    /// @return True if the font was loaded successfully, false otherwise.
    static bool loadFont(const std::string &name, const std::filesystem::path &path);

    /// @brief Gets a font by name, loading it if necessary.
    /// @param name The name of the font to retrieve.
    /// @param path The path to the font file (used if the font is not already loaded).
    /// @return A reference to the requested font.
    static const sf::Font &getFont(const std::string &name, const std::filesystem::path &path = "");
    
    /// @brief Checks if a font with the specified name is loaded.
    /// @param name The name of the font to check.
    /// @return True if the font is loaded, false otherwise.
    static bool hasFont(const std::string &name);
};