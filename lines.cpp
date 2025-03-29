#include <iostream>
#include <cmath>
using namespace std;

// A structure to represent a point
struct Point {
    double x, y;
    Point(double _x, double _y) : x(_x), y(_y) {}
};

// A structure to represent an infinite line in the form ax + by + c = 0
struct Line {
    double a, b, c;
    Line(double _a, double _b, double _c) : a(_a), b(_b), c(_c) {}
};

// Function to find intersection of two lines (if it exists)
bool findIntersection(Line l1, Line l2, Point &intersection) {
    // The determinant (denominator) of the system of equations
    double denominator = l1.a * l2.b - l1.b * l2.a;

    if (denominator == 0) {
        // Lines are parallel or coincident, no unique intersection
        return false;
    }

    // Cramer's rule for solving the system
    double x = (l2.b * l1.c - l1.b * l2.c) / denominator;
    double y = (l1.a * l2.c - l2.a * l1.c) / denominator;

    intersection = Point(x, y);
    return true;
}

// Function to check if two lines are parallel
bool areParallel(Line l1, Line l2) {
    return (l1.a * l2.b == l1.b * l2.a);
}

// Function to check if two lines are perpendicular
bool arePerpendicular(Line l1, Line l2) {
    return (l1.a * l2.a + l1.b * l2.b == 0);
}

// Function to calculate the perpendicular distance from a point (px, py) to an infinite line ax + by + c = 0
double distanceFromPointToLine(Line l, Point p) {
    return fabs(l.a * p.x + l.b * p.y + l.c) / sqrt(l.a * l.a + l.b * l.b);
}

// Function to calculate the angle between two lines
double angleBetweenLines(Line l1, Line l2) {
    // Calculate slopes of the lines
    double slope1 = -l1.a / l1.b;
    double slope2 = -l2.a / l2.b;

    // Angle between the two lines
    double tanTheta = fabs((slope1 - slope2) / (1 + slope1 * slope2));

    return atan(tanTheta);  // Returns the angle in radians
}

int main() {
    // Define two infinite lines: a1x + b1y + c1 = 0 and a2x + b2y + c2 = 0
    Line l1(1, -1, -1);  // Line 1: x - y = 1
    Line l2(1, 1, -1);   // Line 2: x + y = -1

    // Test: Find intersection of two lines
    Point intersection(0, 0);
    if (findIntersection(l1, l2, intersection)) {
        cout << "Intersection at: (" << intersection.x << ", " << intersection.y << ")" << endl;
    } else {
        cout << "The lines do not intersect (parallel)." << endl;
    }

    // Test: Check if the lines are parallel
    if (areParallel(l1, l2)) {
        cout << "The lines are parallel." << endl;
    } else {
        cout << "The lines are not parallel." << endl;
    }

    // Test: Check if the lines are perpendicular
    if (arePerpendicular(l1, l2)) {
        cout << "The lines are perpendicular." << endl;
    } else {
        cout << "The lines are not perpendicular." << endl;
    }

    // Test: Calculate the distance from a point to the line
    Point p(2, 3);
    cout << "Distance from point (2, 3) to line 1: " << distanceFromPointToLine(l1, p) << endl;

    // Test: Calculate the angle between the two lines in degrees
    double angleRad = angleBetweenLines(l1, l2);
    double angleDeg = angleRad * 180.0 / M_PI;  // Convert to degrees
    cout << "Angle between lines 1 and 2: " << angleDeg << " degrees" << endl;

    return 0;
}
