#include "GameEngine/t2Vector.hpp"
#include "GameEngine/Geometry.hpp"
#include "GameEngine/World.hpp"
#include "GameEngine/Rocket.hpp"
#include <SFML/Graphics.hpp>

int main() {
    sf::RenderWindow window(sf::VideoMode(1280, 720), "SFML works!");

    sf::Clock deltaClock;
    sf::Time dt;

    Timer t;
    t.addNewEvent("reload", 10);
    World w(t2Vector<int>(1280, 720), true, true);

    Object *geo;
    Object *rocket;
    w.createNewPlayer(40, 40, 0);
    Object *geo2;
    w.createNewPlayer(80, 40, 1);
    unsigned int rocketId = w.createNewObject<Rocket>(100, 100);

    //Object *rocket = w.newGeometry(Rectangle<float>(10, 10, 250, 250), 400, 0.1, 0.5);

    sf::RectangleShape rock(sf::Vector2f(10, 10));
    sf::RectangleShape shape(sf::Vector2f(32, 16));
    sf::RectangleShape shape2(sf::Vector2f(32, 16));
    shape.setFillColor(sf::Color::Green);
    shape2.setFillColor(sf::Color::Green);

   // Snapshot *s = w.getSnapshot();
    sf::Event event;

    while (window.isOpen())
    {
        window.clear();

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
            window.close();

        if ((rocket = w.getObject(rocketId)))
        {
            rock.setPosition(sf::Vector2f(rocket->geometry->getPosition().getX() - rocket->geometry->getSize().getX() / 2,
                                          rocket->geometry->getPosition().getY() - rocket->geometry->getSize().getY() / 2));
            window.draw(rock);
        }
//        if (t.eventDone("caca"))
//            std::cout << "done!" << std::endl;
        //std::cout << geo->getClockWiseAngle() << std::endl;

        if ((geo = w.getPlayerObject(1))) {
            shape.setPosition(sf::Vector2f(geo->geometry->getPosition().getX() - geo->geometry->getSize().getX() / 2,
                                           geo->geometry->getPosition().getY() - geo->geometry->getSize().getY() / 2));
            window.draw(shape);
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
                geo->geometry->addImpulse(t2Vector<float>(-10, 0));
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
                geo->geometry->addImpulse(t2Vector<float>(10, 0));
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
                geo->geometry->addImpulse(t2Vector<float>(0, -10));
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
                geo->geometry->addImpulse(t2Vector<float>(0, 10));
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) &&
                (rocket = w.getObject(rocketId)) != NULL) {

                rocket->geometry->setVelocity(t2Vector<int>(0, 0));
                rocket->geometry->removeImpulse().setPosition(
                        geo->geometry->getPosition() +
                        t2Vector<int>(geo->geometry->getSize().getX(), 0)).applyImpulse(
                        t2Vector<int>(20, 0), 5);
            }
        }
        if ((geo2 = w.getPlayerObject(0))) {

            shape2.setPosition(sf::Vector2f(geo2->geometry->getPosition().getX() - geo2->geometry->getSize().getX() / 2,
                                            geo2->geometry->getPosition().getY() - geo2->geometry->getSize().getY() / 2));
            window.draw(shape2);
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
                geo2->geometry->addImpulse(t2Vector<float>(-10, 0));
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
                geo2->geometry->addImpulse(t2Vector<float>(10, 0));
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
                geo2->geometry->addImpulse(t2Vector<float>(0, -10));
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
                geo2->geometry->addImpulse(t2Vector<float>(0, 10));
        }
        w.tick(dt.asSeconds());
        /*if (t.eventDone("reload")) {
            w.loadSnapshot(s);
            t.reset("reload");
        }*/
        window.display();
        dt = deltaClock.restart();

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
    }

    return 0;
}