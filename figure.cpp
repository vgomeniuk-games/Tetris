#include "figure.h"

//static Figure& Figure::generate() {

//}

bool Figure::rotate() {
    return false;
}

bool Figure::move() {
    // Rotate figure relatively to 2nd figure's cell
    Point center = buffer_a[1];  // Center of rotation
    for (int i = 0; i < 4; ++i) {
        int x = buffer_a[i].y - center.y;
        int y = buffer_a[i].x - center.x;
        buffer_a[i].x = center.x - x;
        buffer_a[i].y = center.y + y;
    }
//    if (!checkTransform()) {
//        for (int i = 0; i < 4; ++i) { buffer_a[i] = buffer_b[i]; }
//        return false;
//    }
    return true;
}

bool Figure::canTransform() {

}
