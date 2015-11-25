#include <iostream>
#include <unistd.h>
#include "t2Vector.hpp"
#include "Geometry.hpp"
#include <SFML/Graphics.hpp>

int main()
{
    sf::RenderWindow window(sf::VideoMode(400, 400), "SFML works!");
    sf::CircleShape shape(10.f);
    shape.setFillColor(sf::Color::Green);

    float sec = 0;
    sf::Clock deltaClock;
    sf::Time dt;
    bool keydown = false;
    bool r = false;

    Geometry geo(t2Vector<float>(0, 0), t2Vector<int>(1, 1), t2Vector<float>(100, 70), 2, 5);
    Geometry rocket(geo.getPosition(), t2Vector<int>(1, 1), t2Vector<float>(1000, 30), 10, 5);

    sf::RectangleShape rock(sf::Vector2f(5, 5));

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        keydown = false;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        {
            geo.addImpulse(t2Vector<float>(-20, 0));
            keydown = true;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        {
            geo.addImpulse(t2Vector<float>(20, 0));
            keydown = true;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        {
            geo.addImpulse(t2Vector<float>(0, -20));
            keydown = true;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        {
            geo.addImpulse(t2Vector<float>(0, 20));
            keydown = true;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
        {
            rocket.setPosition(geo.getPosition());
            r = true;
            rocket.addImpulse(t2Vector<float>(5, 0));
        }
        if (!keydown)
            geo.removeImpulse();

        //std::cout << dt.asSeconds() << std::endl;
        geo.tick(dt.asSeconds());
        if (r)
        {
            rocket.tick(dt.asSeconds());
            rock.setPosition(sf::Vector2f(rocket.getPosition().getX(), rocket.getPosition().getY()));
        }
        //std::cout << geo.getPosition() << std::endl;
        shape.setPosition(sf::Vector2f(geo.getPosition().getX(), geo.getPosition().getY()));
        window.clear();
        window.draw(shape);
        window.draw(rock);
        window.display();
        dt = deltaClock.restart();
    }

    return 0;
}