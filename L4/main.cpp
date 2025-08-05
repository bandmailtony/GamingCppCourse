#include <SFML/Graphics.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <cmath>
#include <iostream>

// THIS IS THE BASIC FRAMEWORK OF ANY VIDEO GAME

class AShape
{
    public:
    sf::CircleShape circle;
    sf::RectangleShape rect;
    float speedX, speedY;

};

int main(int argc, char * argv[])
{
    srand(time(0));
    const int wWidth = 1280;
    const int wHeight = 720;
    sf::RenderWindow window(sf::VideoMode(wWidth, wHeight),"SFML works!");
    window.setFramerateLimit(60);

    int r = 75;
    int g = 145;
    int b = 255;


    sf::CircleShape circle(50);
    circle.setFillColor(sf::Color(r, g, b));
    circle.setPosition(300.0f, 300.0f);
    float circleMoveSpeed = 0.5f;

    sf::Font myFont;

    if (!myFont.loadFromFile("Mozilla_Headline/MozillaHeadline-VariableFont_wdth,wght.ttf"))
    {
        // if we can't load the fontr, print an error to the console and exit
        std::cerr << "Could not load font!\n";
        exit(-1);
    }

    // set up the text object that will be drawn to the screen
    sf::Text text("You can do this! Keep going :)", myFont, 24 );


    std::vector<sf::CircleShape> circles;
    circles.push_back(circle);

    std::vector<sf::RectangleShape> rectangles;
    
    for (int x = 0; x < 5; x++)
    {for(int y = 0; y < 5; y++)
    {
        sf::RectangleShape rect(sf::Vector2f(15,15));
        rect.setFillColor(sf::Color(100, 150, 200));
        rect.setPosition(x*20, y*20);
        rectangles.push_back(rect);
        
    }
    }

    float rectMoveSpeed = 7.0f;
    //this puts the text in the bottom left of the window- x pos is 0, y position is 'height' (y height increases down, like an array) minus the font size (1 size = 1 pixel)
    text.setPosition(0, wHeight - (float)text.getCharacterSize()-5);
    
    //MAIN LOOP - CONTINUES FOR EACH FRAME WHILE WINDOW IS OPEN
    sf::Clock clock;
    sf::Vector2f position;
    sf::Vector2f velocity;
    float maxSpeed = 1000.0f; // Pixels per second
    float acceleration = 400.0f;
    while(window.isOpen())
    {
        sf::Time deltaTime = clock.restart(); // Get elapsed time and reset the clock
        float dt = deltaTime.asSeconds(); // Convert to seconds for calculation

        //event handling
        sf::Event event;
        while(window.pollEvent(event))
        {
            //this event triggers when the window is closed
            if(event.type == sf::Event::Closed)
            {
                window.close();
            }

                    }

            /*MOVEMENT BLOCK*/
            // Horizontal movement
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
                velocity.x -= acceleration * dt; // Accelerate left
            } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
                velocity.x += acceleration * dt; // Accelerate right
            } else {
            // Decelerate (apply some friction or damping)
                velocity.x *= 0.935f; // Adjust this value for desired deceleration
            }

            // Vertical movement
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
                velocity.y -= acceleration * dt; // Accelerate up (y-axis is inverted in SFML)
            } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
                velocity.y += acceleration * dt; // Accelerate down
            } else {
            // Decelerate
                velocity.y *= 0.935f;
            }

            // Limit the speed
        float currentSpeed = sqrt( (velocity.x * velocity.x) + (velocity.y * velocity.y) );
            if (currentSpeed > maxSpeed) {
            velocity = velocity / currentSpeed * maxSpeed;
            }

            // Update position
            position += velocity * dt;
            for(auto& rect : rectangles)
            {
            rect.move(velocity * dt);
            }
            
            
        /*ANIMATION BLOCK*/
        
        // basic rendering function calls
        window.clear();                     // clear the window of anything previously drawn
        

       for(auto& rect : rectangles)
       {
            window.draw(rect);
       }
        window.draw(text);        // draw the text
        window.display();                  // call the window display function
    }
            
    
    return 0;
}