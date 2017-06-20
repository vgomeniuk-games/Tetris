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

void getCoordinates2d(int figure) {
    // transform cell's number into 2d coordinates and fill buffer
    for (int cell = 0; cell < 4; ++cell) {
        buffer_a[cell].x = figures[figure][cell] % 2;
        buffer_a[cell].y = figures[figure][cell] / 2;
    }
}

void newFigure(int& colorNum) {
    // Set new random color
    colorNum = 1 + rand() % 7;

    // Create new random figure
    getCoordinates2d(rand() % 7);
}

bool checkTransform() {
    // Check if current transform action is possible
    for (int i = 0; i < 4; ++i) {
        // Overlaping with field's edges or bottom
        if (buffer_a[i].x < 0 || buffer_a[i].x >= N || buffer_a[i].y >= M) {
            return false;
        }
        // Overlaping with other figures
        if (field[buffer_a[i].y][buffer_a[i].x]) {
            return false;
        }
    }
    return true;
}

bool rotateFigure() {
    // Rotate figure relatively to 2nd figure's cell
    Point center = buffer_a[1];  // Center of rotation
    for (int i = 0; i < 4; ++i) {
        int x = buffer_a[i].y - center.y;
        int y = buffer_a[i].x - center.x;
        buffer_a[i].x = center.x - x;
        buffer_a[i].y = center.y + y;
    }
    if (!checkTransform()) {
        for (int i = 0; i < 4; ++i) { buffer_a[i] = buffer_b[i]; }
        return false;
    }
    return true;
}

bool moveFigure(int delta=0, bool vertical=false, int currentColor=0) {
    for (int i = 0; i < 4; ++i) {
        buffer_b[i] = buffer_a[i];
        vertical ? buffer_a[i].y += delta : buffer_a[i].x += delta;
    }
    if (!checkTransform()) {
        for (int i = 0; i < 4; ++i) {
            if (vertical) { field[buffer_b[i].y][buffer_b[i].x] = currentColor; }
            else { buffer_a[i] = buffer_b[i]; }
        }
        return false;
    }
    return true;
}

void removeSolid() {
    int k = M - 1;
    for (int i = M - 1; i > 0; --i) {
        int count = 0;
        for (int j = 0; j < N; ++j) {
            if (field[i][j]) { ++count; }
            field[k][j] = field[i][j];
        }
        if (count < N) { --k; }
    }
}


int main()
{
    // Create window
    sf::RenderWindow window(sf::VideoMode(320, 480), "Tetris");

    // Load textures and create sprites
    sf::Texture t1, t2, t3;
    t1.loadFromFile("assets/tiles.png");
    t2.loadFromFile("assets/background.png");
    sf::Sprite tile(t1);
    tile.setTextureRect(sf::IntRect(0, 0, 18, 18));  // TODO
    sf::Sprite background(t2);

    // Handle movement / rotation / figure's color
    int deltax = 0;
    bool rotate = false;
    int colorNum = 1;

    // Time counters
    sf::Clock clock;
    float timer = 0;
    float tickDelay = 0.3;

    // Init random engine
    srand(time(0));

    // Create new random figure
    newFigure(colorNum);


    // Main loop
    while (window.isOpen()) {
        // Increase timer
        timer += clock.getElapsedTime().asSeconds();
        clock.restart();

        // Process events
        sf::Event e;
        while (window.pollEvent((e))) {
            // Handle closing
            if (e.type == sf::Event::Closed) { window.close(); }

            // Handle movement
            if (e.type == sf::Event::KeyPressed) {
                switch(e.key.code){
                case sf::Keyboard::Up:
                    rotate = true;
                    break;
                case sf::Keyboard::Left:
                    deltax = -1;
                    break;
                case sf::Keyboard::Right:
                    deltax = 1;
                    break;
                default:
                    break;
                }
            }
        }

        // Increase fall speed
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) { tickDelay = 0.05; }

        // Move and rotate
        moveFigure(deltax);
        if (rotate) { rotateFigure(); }

        // Tick
        if (timer > tickDelay) {
            if (!moveFigure(1, true, colorNum)) {
                newFigure(colorNum);
            }
            timer = 0;
        }

        // Check lines
        removeSolid();

        // Reset movement indicators
        deltax = 0;
        rotate = false;
        tickDelay = 0.3;

        // Draw background
        window.clear(sf::Color::White);
        window.draw(background);

        // Draw field with non-moving figures
        for (int i = 0; i < M; ++i) {
            for (int j = 0; j < N; ++j) {
                if (field[i][j] == 0) { continue; }
                tile.setTextureRect(sf::IntRect(field[i][j] * 18, 0, 18, 18));
                tile.setPosition(j * 18, i * 18);
                tile.move(28, 31);  // Offset
                window.draw(tile);
            }
        }

        // Draw active figure
        for (int i = 0; i < 4; ++i) {
            tile.setTextureRect(sf::IntRect(colorNum * 18, 0, 18, 18));
            tile.setPosition(buffer_a[i].x * 18, buffer_a[i].y * 18);
            tile.move(28, 31);  // Offset
            window.draw(tile);
        }

        window.display();
    }
    return 0;
}
