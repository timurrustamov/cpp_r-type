#include "t2Vector.hpp"
#include "Geometry.hpp"
#include "World.hpp"
#include <SFML/Graphics.hpp>

int main()
{
    sf::RenderWindow window(sf::VideoMode(400, 400), "SFML works!");

    sf::Clock deltaClock;
    sf::Time dt;
    bool keydown;

    World w(t2Vector<int>(400, 400), true, true);

    Geometry *geo = w.bindPlayerObject(Rectangle<float>(20, 20, 20, 20), 100, 0.1, 5);
    //QuadTree qt(Rectangle<float>(1000, 1000, 300, 300));

    Geometry *rocket = w.newGeometry(Rectangle<float>(100, 100, 250, 250), 100, 0.1, 0.5);

    sf::RectangleShape shape(sf::Vector2f(20, 20));
    sf::RectangleShape rock(sf::Vector2f(100, 100));
    shape.setFillColor(sf::Color::Green);

    sf::Event event;

    while (window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
            window.close();
    }

    while (window.isOpen())
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
            window.close();

        //std::cout << geo->getClockWiseAngle() << std::endl;

        keydown = false;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            geo->addImpulse(t2Vector<float>(-10, 0));
            keydown = true;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            geo->addImpulse(t2Vector<float>(10, 0));
            keydown = true;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
            geo->addImpulse(t2Vector<float>(0, -10));
            keydown = true;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
            geo->addImpulse(t2Vector<float>(0, 10));
            keydown = true;
        }
        if (!keydown) {
            geo->removeImpulse();
        }

        w.tick(dt.asSeconds());


        shape.setPosition(sf::Vector2f(geo->getPosition().getX() - geo->getSize().getX() / 2,
                                       geo->getPosition().getY() - geo->getSize().getY() / 2));
        rock.setPosition(sf::Vector2f(rocket->getPosition().getX() - rocket->getSize().getX() / 2,
                                      rocket->getPosition().getY() - rocket->getSize().getY() / 2));
        window.clear();
        window.draw(shape);
        window.draw(rock);
        window.display();
        dt = deltaClock.restart();
    }

    return 0;
}