#include "button.hpp"

RoundedRectangleShape::RoundedRectangleShape(
    const sf::Vector2f &size,
    float radius,
    std::size_t cornerPointCount)
    : size(size), 
      radius(radius), 
      cornerPointCount(cornerPointCount)
{
    update();
}

void RoundedRectangleShape::setSize(const sf::Vector2f &size)
{
    this->size = size;
    update();
}

const sf::Vector2f &RoundedRectangleShape::getSize() const
{
    return size;
}

void RoundedRectangleShape::setCornersRadius(float radius)
{
    this->radius = radius;
    update();
}

float RoundedRectangleShape::getCornersRadius() const
{
    return radius;
}

void RoundedRectangleShape::setCornerPointCount(std::size_t count)
{
    cornerPointCount = count;
    update();
}

std::size_t RoundedRectangleShape::getPointCount() const
{
    return cornerPointCount * 4;
}

sf::Vector2f RoundedRectangleShape::getPoint(std::size_t index) const
{
    std::size_t corner = index / cornerPointCount;
    std::size_t i = index % cornerPointCount;

    float angle = i * 90.f / (cornerPointCount - 1);

    sf::Vector2f center;

    switch (corner)
    {
    case 0: // Top-right
        center = {size.x - radius, radius};
        angle -= 90.f;
        break;

    case 1: // Bottom-right
        center = {size.x - radius, size.y - radius};
        break;

    case 2: // Bottom-left
        center = {radius, size.y - radius};
        angle += 90.f;
        break;

    case 3: // Top-left
        center = {radius, radius};
        angle += 180.f;
        break;
    }

    float rad = angle * 3.141592654f / 180.f;

    return {
        center.x + std::cos(rad) * radius,
        center.y + std::sin(rad) * radius};
}

Button::Button(
    const sf::Font& font, 
    const std::string& text,
    const sf::Vector2f &size, 
    sf::Color fillColor,
    sf::Color textColor,
    sf::Color hoverColor,
    unsigned int characterSize,
    float radius,
    std::size_t cornerPointCount)
    : body(RoundedRectangleShape(size, radius, cornerPointCount)), 
      text(font, text, characterSize), 
      fillColor(fillColor),
      hovered(false)
{
    this->body.setFillColor(fillColor);
    this->text.setFillColor(textColor);

    // Check if hover color exists
    if (hoverColor != sf::Color::Transparent)
        this->hoverColor = hoverColor;
    else
        this->hoverColor = fillColor;

    // Text centering
    sf::FloatRect textBounds = this->text.getLocalBounds();

    this->text.setOrigin({
        textBounds.position.x + textBounds.size.x / 2.f,
        textBounds.position.y + textBounds.size.y / 2.f
    });

    this->text.setPosition({
        size.x / 2.f,
        size.y / 2.f
    });
}

Button::Button(std::string buttonName)
: body(RoundedRectangleShape({0.f, 0.f}, 0.f, 0)), 
  text(FontManager::getFont("DEFAULT_FONT"))
{
    using json = nlohmann::json;

    std::ifstream file("elements.json");
    if (!file.is_open())
        throw std::runtime_error("Failed to open elements.json");

    json elements;
    try
    {
        file >> elements;
    }
    catch (const json::parse_error &e)
    {
        throw std::runtime_error("Failed to parse elements.json: " + std::string(e.what()));
    }    

    if (!elements.contains(buttonName) || !elements[buttonName].is_object())
        throw std::runtime_error("Button " + buttonName + " not found or not an object in elements.json");

    // Body configuration
    sf::Vector2f size = {
        elements[buttonName]["Shape"]["Size"]["Width"],
        elements[buttonName]["Shape"]["Size"]["Height"]
    };
    body.setSize(size);
    body.setPosition({
        elements[buttonName]["Shape"]["Position"]["X"].get<float>(),
        elements[buttonName]["Shape"]["Position"]["Y"].get<float>()
    });
    this->fillColor = sf::Color(
        elements[buttonName]["Shape"]["Color"]["R"].get<std::uint8_t>(),
        elements[buttonName]["Shape"]["Color"]["G"].get<std::uint8_t>(),
        elements[buttonName]["Shape"]["Color"]["B"].get<std::uint8_t>()
    );
    this->hoverColor = sf::Color(
        elements[buttonName]["Shape"]["Hover Color"]["R"].get<std::uint8_t>(),
        elements[buttonName]["Shape"]["Hover Color"]["G"].get<std::uint8_t>(),
        elements[buttonName]["Shape"]["Hover Color"]["B"].get<std::uint8_t>()
    );
    body.setCornersRadius(elements[buttonName]["Shape"]["Radius"].get<float>());
    body.setCornerPointCount(elements[buttonName]["Shape"]["Corner Point Count"].get<std::size_t>());

    // Text configuration
    text.setFont(FontManager::getFont(
        elements[buttonName]["Font"]["Name"].get<std::string>(),
        elements[buttonName]["Font"]["Path"].get<std::string>()
    ));
    text.setString(elements[buttonName]["Font"]["Text"].get<std::string>());
    text.setCharacterSize(elements[buttonName]["Font"]["Size"].get<unsigned int>());
    text.setFillColor(sf::Color(
        elements[buttonName]["Font"]["Color"]["R"].get<std::uint8_t>(),
        elements[buttonName]["Font"]["Color"]["G"].get<std::uint8_t>(),
        elements[buttonName]["Font"]["Color"]["B"].get<std::uint8_t>()
    ));

    // Text centering
    sf::FloatRect textBounds = this->text.getLocalBounds();

    this->text.setOrigin({
        textBounds.position.x + textBounds.size.x / 2.f,
        textBounds.position.y + textBounds.size.y / 2.f
    });

    this->text.setPosition({
        size.x / 2.f,
        size.y / 2.f
    });
}

void Button::setText(const std::string &text)
{
    this->text.setString(text);

    // Text centering
    sf::FloatRect textBounds = this->text.getLocalBounds();

    this->text.setOrigin({
        textBounds.position.x + textBounds.size.x / 2.f,
        textBounds.position.y + textBounds.size.y / 2.f
    });
}

void Button::setCharacterSize(unsigned int size)
{
    this->text.setCharacterSize(size);
}

void Button::setTextColor(sf::Color color)
{
    this->text.setFillColor(color);
}

void Button::setFillColor(sf::Color color)
{
    this->fillColor = color;
}

void Button::setHoverColor(sf::Color color)
{
    this->hoverColor = color;
}

bool Button::isHovered(const sf::Vector2f& mousePos)
{

   hovered = this->body.getGlobalBounds().contains(mousePos);
   return hovered;
}

void Button::draw(
    sf::RenderTarget &target, 
    sf::RenderStates states) const
{
    const_cast<RoundedRectangleShape&>(this->body).setFillColor(hovered ? hoverColor : fillColor);
    states.transform *= this->body.getTransform();

    target.draw(this->body, states);
    target.draw(this->text, states);
}
