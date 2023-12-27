#include <SFML/Graphics.hpp>
#include <iostream>

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "My SFML Window");

    // Main loop
    // while (window.isOpen())
    // {
    //     // Event processing
    //     sf::Event event;
    //     while (window.pollEvent(event))
    //     {
    //         // Close window: exit
    //         if (event.type == sf::Event::Closed)
    //             window.close();
    //     }

    //     // Clear screen
    //     window.clear(sf::Color::Black);

    //     // Draw your GUI here

    //     // Update the window
    //     window.display();
    // }

    return 0;
}