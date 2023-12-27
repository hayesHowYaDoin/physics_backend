#include <SFML/Graphics.hpp>
#include <string>

int main(int argc, char **argv) {
    sf::RenderWindow window;
    std::string test("Hello World!");
    window.setTitle(test);
    return 0;
}