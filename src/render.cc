#include <render.hpp>

Renderer::Renderer()
{
    sf::ContextSettings contextSettings;
        contextSettings.depthBits = 24;
        contextSettings.stencilBits = 8;
        contextSettings.antialiasingLevel = 0;
        contextSettings.majorVersion = 3;
        contextSettings.minorVersion = 3;

        m_window.create(sf::VideoMode::getDesktopMode(),
                        "MazeSolver");
            m_window.display();
}

void
Renderer::draw(const sf::Drawable& d)
{

}
