#ifndef FIGURE_H
#define FIGURE_H


class Figure
{
public:
    Figure() = delete;
    static Figure& generate();

    bool rotate();
    bool move();

private:
    bool canTransform();

private:
    int color;
    struct Point { int x; int y; } buffer_a[4], buffer_b[4];

};

#endif // FIGURE_H
