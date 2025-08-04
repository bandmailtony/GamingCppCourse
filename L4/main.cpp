#include <SFML/Graphics.hpp>
#include <iostream>

int main(int argc, char * argv[])
{
    std::cout << "Testing SFML in another folder location!\n";
 sf::RenderWindow window(sf::VideoMode(400, 400), "SFML works AGAIN!");
    sf::CircleShape shape(73.f);
    shape.setFillColor(sf::Color::Green);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.draw(shape);
        window.display();
    }

    return 0;
}