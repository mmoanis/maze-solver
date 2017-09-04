#pragma once
#include <SFML/Graphics.hpp>
namespace sf
{
    class Drawable;
    class RenderWindow;
}

class Renderer;

class Renderer
{
public:
    Renderer();
    virtual void draw(const sf::Drawable&);
protected:
    sf::RenderWindow m_window;
};
