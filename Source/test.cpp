#include "GameEngine/t2Vector.hpp"
#include "GameEngine/Geometry.hpp"
#include "GameEngine/World.hpp"
#include <SFML/Graphics.hpp>

int main()
{
    sf::RenderWindow window(sf::VideoMode(400, 400), "SFML works!");

    sf::Clock deltaClock;
    sf::Time dt;
    bool keydown;

    World w(t2Vector<int>(400, 400), true, true);

    Geometry *geo = w.bindPlayerObject(Rectangle<float>(20, 100, 20, 200), 300, 0.1, 5);
    Geometry *geo2 = w.bindPlayerObject(Rectangle<float>(20, 100, 350, 200), 300, 0.1, 5);

    Geometry *rocket = w.newGeometry(Rectangle<float>(10, 10, 250, 250), 400, 0.1, 0.5);

    sf::RectangleShape shape(sf::Vector2f(20, 100));
    sf::RectangleShape shape2(sf::Vector2f(20, 100));
    sf::RectangleShape rock(sf::Vector2f(10, 10));
    shape.setFillColor(sf::Color::Green);
    shape2.setFillColor(sf::Color::Green);

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

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
            geo->addImpulse(t2Vector<float>(-10, 0));
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
            geo->addImpulse(t2Vector<float>(10, 0));
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
            geo->addImpulse(t2Vector<float>(0, -10));
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
            geo->addImpulse(t2Vector<float>(0, 10));
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
            geo2->addImpulse(t2Vector<float>(-10, 0));
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
            geo2->addImpulse(t2Vector<float>(10, 0));
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
            geo2->addImpulse(t2Vector<float>(0, -10));
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
            geo2->addImpulse(t2Vector<float>(0, 10));

        w.tick(dt.asSeconds());

        shape.setPosition(sf::Vector2f(geo->getPosition().getX() - geo->getSize().getX() / 2,
                                       geo->getPosition().getY() - geo->getSize().getY() / 2));
        shape2.setPosition(sf::Vector2f(geo2->getPosition().getX() - geo2->getSize().getX() / 2,
                                       geo2->getPosition().getY() - geo2->getSize().getY() / 2));
        rock.setPosition(sf::Vector2f(rocket->getPosition().getX() - rocket->getSize().getX() / 2,
                                      rocket->getPosition().getY() - rocket->getSize().getY() / 2));
        window.clear();
        window.draw(shape);
        window.draw(shape2);
        window.draw(rock);
        window.display();
        dt = deltaClock.restart();
    }

    return 0;
}