#pragma once

#include "main.hpp"

class RoundedRectangleShape : public sf::Shape
{
private:
    sf::Vector2f size;
    float radius;
    std::size_t cornerPointCount;

public:
    /// @brief Constructs a new RoundedRectangleShape object.
    /// @param size sf::Vector2f representing the size of the rectangle (width, height)
    /// @param radius float representing the radius of the corners
    /// @param cornerPointCount std::size_t representing the number of points for each corner
    RoundedRectangleShape(
        const sf::Vector2f &size,
        float radius = 0.f,
        std::size_t cornerPointCount = 8);

    /// @brief Sets the size of the rectangle.
    /// @param size sf::Vector2f representing the size of the rectangle (width, height)
    void setSize(const sf::Vector2f &size);

    /// @brief Gets the size of the rectangle.
    /// @return sf::Vector2f representing the size of the rectangle (width, height)
    const sf::Vector2f &getSize() const;

    /// @brief Sets the radius of the corners.
    /// @param radius float representing the radius of the corners
    void setCornersRadius(float radius);

    /// @brief Gets the radius of the corners.
    /// @return float representing the radius of the corners
    float getCornersRadius() const;

    /// @brief Sets the number of points for each corner.
    /// @param count std::size_t representing the number of points for each corner
    void setCornerPointCount(std::size_t count);

    /// @brief Gets the number of points for each corner.
    /// @return std::size_t representing the number of points for each corner
    virtual std::size_t getPointCount() const override;

    /// @brief Gets the position of a point in the shape.
    /// @param index The index of the point.
    /// @return The position of the point.
    virtual sf::Vector2f getPoint(std::size_t index) const override;
};

class Button : public sf::Drawable
{
private:
    RoundedRectangleShape body;

    sf::Text text;

    sf::Color fillColor;
    sf::Color hoverColor;

    bool hovered;

public:
    /// @brief Constructs a new Button object.
    /// @param font const sf::Font & representing the font for the button text
    /// @param text const std::string & representing the text for the button
    /// @param size const sf::Vector2f & representing the size of the button (width, height)
    /// @param fillColor sf::Color representing the fill color of the button
    /// @param textColor sf::Color representing the color of the button text
    /// @param hoverColor sf::Color representing the color of the button when hovered
    /// @param characterSize unsigned int representing the size of the button text
    /// @param radius float representing the radius of the corners
    /// @param cornerPointCount std::size_t representing the number of points for each corner
    Button(
        const sf::Font &font,
        const std::string &text,
        const sf::Vector2f &size,
        sf::Color fillColor,
        sf::Color textColor,
        sf::Color hoverColor = sf::Color::Transparent,
        unsigned int characterSize = 30,
        float radius = 0.f,
        std::size_t cornerPointCount = 8);

    Button(std::string buttonName);

    /// @brief Sets the text for the button.
    /// @param text const std::string & representing the text for the button
    void setText(const std::string &text);

    /// @brief Sets the character size for the button text.
    /// @param size unsigned int representing the size of the button text
    void setCharacterSize(unsigned int size);

    /// @brief Sets the color of the button text.
    /// @param color sf::Color representing the color of the button text
    void setTextColor(sf::Color color);

    /// @brief Sets the fill color of the button.
    /// @param color sf::Color representing the fill color of the button
    void setFillColor(sf::Color color);

    /// @brief Sets the color of the button when hovered.
    /// @param color sf::Color representing the color of the button when hovered
    void setHoverColor(sf::Color color);

    /// @brief Checks if the mouse is hovering over the button.
    /// @param mousePos const sf::Vector2f & representing the position of the mouse
    /// @return bool indicating whether the mouse is hovering over the button
    bool isHovered(const sf::Vector2f &mousePos);

    /// @brief Draws the button on the render target.
    /// @param target The render target to draw on.
    /// @param states The render states.
    virtual void draw(
        sf::RenderTarget &target,
        sf::RenderStates states) const override;
};