#include <iostream>
#include <math.h>
#include <cmath>
#include "gwindow.h"
#include "gobjects.h"
#include "point.h"

using namespace std;

// function prototypes
GPoint addPolar(GPoint start, double length, double angleDegrees);
void drawLeaf(GWindow & w, GPoint center);
void drawBranch(GWindow & w, GPoint start, GPoint end) ;
void drawTree(GWindow & w, int level, GPoint base, double length, double angle) ;


// useful math constants
static const double COS_60 = 0.5;            //the value of cos(60 degrees)
static const double SIN_60 = sqrt(3)*0.5;    //the value of sin(60 degrees)
static const double M_PI = 3.14;             //the value of Pi

// display constants
static const int SCREEN_WIDTH = 600;
static const int SCREEN_HEIGHT = SCREEN_WIDTH;
static const int BASE_Y = SCREEN_HEIGHT*3/4;    // the initial coordinates
static const int BASE_X = SCREEN_WIDTH/2;       // of the bases of the tree

// tree constants
static const double RECESSION = 0.75;       // the reduction ratio of the size of the branch
static const int TRUNK_LENGTH = 100;        // the initial length of the tree trunk
static const int LEAF_RADIUS = 5;           // the radius of tree leaves



int main() {

    int iteration = 10;

    GWindow w(SCREEN_WIDTH, SCREEN_HEIGHT);
    GPoint base(BASE_X, BASE_Y);
    drawTree(w, iteration, base, TRUNK_LENGTH, 90);
    return 0;
}

/**
 * Function: addPolar
 * Usage:addPolar(GPoint start, double length, double angleDegrees)
 * ----------------------------------------------------------------
 * This function draws the starting point of each branch with the
 * specified x and y coordinates
 *
 * @param start - start point of the branch
 * @param length - Lenght of the branch
 * @param angleDegrees - the angle of the branches of a tree
 * @return next - Next top point of the branch
 */
GPoint addPolar(GPoint start, double length, double angleDegrees) {
    double radiansPerDegree = 2 * M_PI / 360;
    double radians = angleDegrees * radiansPerDegree;
    double dx = length * cos(radians);
    double dy = length * sin(radians);
    GPoint next(start.getX() + dx, start.getY() - dy);
    return next;
}

/**
 * Function: drawLeaf
 * Usage: drawLeaf(GWindow & w, GPoint center)
 * -------------------------------------------
 * This function draws a tree leaves of a given color
 * using GOval
 *
 * @param w - GWindow for drawing
 * @param center - Center of the leaf
 */
void drawLeaf(GWindow & w, GPoint center) {
    double x = center.getX() - LEAF_RADIUS;
    double y = center.getY() - LEAF_RADIUS;
    double size = LEAF_RADIUS * 2;
    GOval * leaf = new GOval(x, y, size, size);
    leaf->setColor("#ffff00");
    leaf->setFilled(true);
    w.add(leaf);
}

/**
 * Function: drawBranch
 * Usage: drawBranch(GWindow & w, GPoint start, GPoint end)
 * --------------------------------------------------------
 * This function draws a tree branch set color using the GPoligon
 *
 * @param w - GWindow for drawing
 * @param start - Start Point of the begining of new branch
 * @param end - End Point of the of new branch
 */
void drawBranch(GWindow & w, GPoint start, GPoint end) {
    GPolygon * branch = new GPolygon();
    branch->addVertex(start.getX() - 3, start.getY());
    branch->addVertex(end.getX() - 3, end.getY());
    branch->addVertex(end.getX() + 3, end.getY());
    branch->addVertex(start.getX() + 3, start.getY());
    branch->setColor("#00bfff");
    branch->setFilled(true);
    w.add(branch);
}

/**
 * Function: drawTree
 * Usage: drawTree(GWindow & w, int level, GPoint base, double length, double angle)
 * ---------------------------------------------------------------------------------
 * This function recurcively draws Pythagoras tree. On the last iteration of
 * the function paints the leaves.
 *
 * @param w - GWindow for drawing
 * @param level - Level of recursion
 * @param base - Base of the new branch
 * @param length - Lenght of the new branch
 * @param angle -  Angle of every new branch
 */
void drawTree(GWindow & w, int level, GPoint base, double length, double angle) {
    if(level > 0) {
        GPoint top = addPolar(base, length, angle);
        drawBranch(w, base, top);
        drawTree(w, level - 1, top, length * RECESSION, angle - 25);
        drawTree(w, level - 1, top, length * RECESSION, angle + 45);
    } else {
        drawLeaf(w, base);
    }
}

