#pragma once

#include <SFML/Graphics.hpp>

class RoundedRectangleShape : public sf::Shape
{
private:
    sf::Vector2f size;
    float radius;
    std::size_t cornerPointCount;

public:
    RoundedRectangleShape(
        const sf::Vector2f &size,
        float radius = 0.f,
        std::size_t cornerPointCount = 8);

    void setSize(const sf::Vector2f &size);
    const sf::Vector2f &getSize() const;

    void setCornersRadius(float radius);
    float getCornersRadius() const;

    void setCornerPointCount(std::size_t count);
    virtual std::size_t getPointCount() const override;

    virtual sf::Vector2f getPoint(std::size_t index) const override;
};

class Button : public sf::Drawable
{
private:
    RoundedRectangleShape shape;
    sf::Text text;
    sf::Color fillColor;
    sf::Color hoverColor;
    bool hovered;
public:
    Button(
        const sf::Font& font, 
        const std::string& text,
        const sf::Vector2f &size, 
        sf::Color fillColor,
        sf::Color textColor,
        sf::Color hoverColor = sf::Color::Transparent,
        unsigned int characterSize = 30,
        float radius = 0.f,
        std::size_t cornerPointCount = 8);

    void setText(const std::string& text);
    void setCharacterSize(unsigned int size);
    void setTextColor(sf::Color color);

    void setFillColor(sf::Color color);
    void setHoverColor(sf::Color color);

    bool isHovered(const sf::Vector2f& mousePos);

    virtual void draw(
        sf::RenderTarget& target,
        sf::RenderStates states) const override;
};