#include <iostream>
#include "gwindow.h"
#include <cmath>
using namespace std;



static const int SCREEN_WIDTH = 600;
static const int SCREEN_HEIGHT = SCREEN_WIDTH;

const double SIZE = SCREEN_WIDTH/4*3;
const int ITERATION = 10;

GPoint drawFractalLine(GWindow & gw, GPoint pt, double r, double theta, int level);

int main() {
    GWindow w(SCREEN_WIDTH, SCREEN_HEIGHT);

    double cx = w.getWidth() / 2;
    double cy = w.getHeight() / 2;
    GPoint pt(cx - SIZE / 2, cy + sqrt(3.0) * SIZE / 4);
    pt = drawFractalLine(w, pt, SIZE, 60, ITERATION);
    pt = drawFractalLine(w, pt, SIZE, -60, ITERATION);
    pt = drawFractalLine(w, pt, SIZE, 180, ITERATION);

    return 0;
}

/**
 * Function: drawFractalLine
 * Usage: drawFractalLine(GWindow & gw, GPoint pt, double r, double theta, int level)
 * @param gw - GWindow for drawing
 * @param pt - GPoint for start of the line
 * @param r - size of the line
 * @param theta - the angle of inclination
 * @param level - Level of recursion
 * @return line
 */
GPoint drawFractalLine(GWindow & gw, GPoint pt, double r, double theta, int level) {
    if (level == 0) {
        return gw.drawPolarLine(pt, r, theta);
    } else {
        r = r / 2;
        pt = drawFractalLine(gw, pt, r, theta, level - 1);
        drawFractalLine(gw, pt, r, theta - 120, level - 1);
        return drawFractalLine(gw, pt, r, theta, level - 1);
    }
}
