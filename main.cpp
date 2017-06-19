#include <SFML/Graphics.hpp>


int main()
{
    sf::RenderWindow window(sf::VideoMode(320, 480), "Tetris");

    // Load textures
    sf::Texture tTiles;
    tTiles.loadFromFile("assets/tiles.png");

    // Create sprites from textures
    sf::Sprite sTiles(tTiles);
    sTiles.setTextureRect(sf::IntRect(0, 0, 18, 18));  // TODO

    // Main loop
    while (window.isOpen()) {
        sf::Event e;
        while (window.pollEvent((e))) {
            if (e.type == sf::Event::Closed) {
                window.close();
            }
        }

        window.clear(sf::Color::White);
        window.draw(sTiles);
        window.display();
    }

    return 0;
}
