#include <SFML/Graphics.hpp>

const int M = 20;
const int N = 10;

int field[M][N] = {0};

struct { int x; int y; } buffer_a[4], buffer_b[4];

// Types of figures (cells in 2x4 field)
int figures[7][4] = {
    1, 3, 5, 7,  // I
    2, 4, 5, 7,  // Z
    3, 5, 4, 6,  // S
    3, 5, 4, 7,  // T
    2, 3, 5, 7,  // L
    3, 5, 7, 6,  // J
    2, 3, 4, 5   // O
};


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
