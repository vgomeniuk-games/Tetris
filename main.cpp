#include <SFML/Graphics.hpp>

const int M = 20;
const int N = 10;

int field[M][N] = {0};

// Buffers with points
struct Point { int x; int y; } buffer_a[4], buffer_b[4];

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

void getCoordinates2d(Point* buffer, int figure) {
    // transform cell's number into 2d coordinates and fill buffer
    for (int cell = 0; cell < 4; ++cell) {
        auto p = (buffer + cell);
        p->x = figures[figure][cell] % 2;
        p->y = figures[figure][cell] / 2;
    }
}

void rotateFigure(Point* buffer) {
    // Rotate figure relatively to 2nd figure's cell
    Point center = buffer[1];  // Center of rotation
    for (int i = 0; i < 4; ++i) {
        int x = buffer[i].y - center.y;
        int y = buffer[i].x - center.x;
        buffer[i].x = center.x - x;
        buffer[i].y = center.y + y;
    }
}

void moveFigure(Point* buffer, int deltaX=0, int deltaY=0) {
    for (int i = 0; i < 4; ++i) {
        buffer[i].x += deltaX;
        buffer[i].y += deltaY;
    }

}

bool canMove(Point* buffer) {
    for (int i = 0; i < 4; ++i) {
        // Overlaping with field edges
        if (buffer[i].x < 0 || buffer[i].x >= N) {
            return false;
        }
        // At the bottom of the field
        if (buffer[i].y >= M) {
            return false;
        }
        // Overlaping with other figures
        if (field[buffer[i].y][buffer[i].x]) {
            return false;
        }
    }
    return true;
}


int main()
{
    sf::RenderWindow window(sf::VideoMode(320, 480), "Tetris");

    // Load textures
    sf::Texture tTiles;
    tTiles.loadFromFile("assets/tiles.png");

    // Create sprites from textures
    sf::Sprite sTiles(tTiles);
    sTiles.setTextureRect(sf::IntRect(0, 0, 18, 18));  // TODO

    // Handle movement / rotation / figure's color
    int dx = 0;
    bool rotate = false;
    int colorNum = 1;

    // Time counters
    sf::Clock clock;
    float timer = 0;
    float tickDelay = 0.3;

    // Init random engine
    srand(time(0));

    // Main loop
    while (window.isOpen()) {
        // Increase timer
        timer += clock.getElapsedTime().asSeconds();
        clock.restart();

        // Process events
        sf::Event e;
        while (window.pollEvent((e))) {
            // Handle closing
            if (e.type == sf::Event::Closed) {
                window.close();
            }
            // Handle movement
            if (e.type == sf::Event::KeyPressed) {
                switch(e.key.code){
                    case sf::Keyboard::Up:
                        rotate = true;
                        break;
                    case sf::Keyboard::Left:
                        dx = -1;
                        break;
                    case sf::Keyboard::Right:
                        dx = 1;
                        break;
                    default:
                        break;
                }
            }
        }
        // Move and rotate
        moveFigure(buffer_a, dx);
        if (rotate) { rotateFigure(buffer_a); }

        // Get figure's coordinates
        if (buffer_a[0].x == 0) {
            getCoordinates2d(buffer_a, 3);
        }

        // Tick
        if (timer > tickDelay) {
            moveFigure(buffer_a, 0, 1);
            timer = 0;
        }

        // Reset movement indicators
        dx = 0;
        rotate = false;

        // TODO: Draw from buffer
        window.clear(sf::Color::White);
        for (int i = 0; i < 4; ++i) {
            sTiles.setPosition(buffer_a[i].x * 18, buffer_a[i].y * 18);
            window.draw(sTiles);
        }

        window.display();
    }

    return 0;
}
