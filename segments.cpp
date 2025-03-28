#include <iostream>
#include <cmath>

using namespace std;

// A structure to represent a point
struct Point {
    double x, y;
    Point(double _x, double _y) : x(_x), y(_y) {}
};

// Function to find orientation of the ordered triplet (p, q, r).
// 0 -> p, q and r are collinear
// 1 -> Clockwise
// 2 -> Counterclockwise
int orientation(Point p, Point q, Point r) {
    double val = (q.y - p.y) * (r.x - q.x) - (q.x - p.x) * (r.y - q.y);
    if (val == 0) return 0;  // collinear
    return (val > 0) ? 1 : 2; // clockwise or counterclockwise
}

// Function to check if point q lies on line segment pr
bool onSegment(Point p, Point q, Point r) {
    return (q.x <= max(p.x, r.x) && q.x >= min(p.x, r.x) &&
            q.y <= max(p.y, r.y) && q.y >= min(p.y, r.y));
}

// Function to check if two line segments (p1q1) and (p2q2) intersect
bool doIntersect(Point p1, Point q1, Point p2, Point q2) {
    int o1 = orientation(p1, q1, p2);
    int o2 = orientation(p1, q1, q2);
    int o3 = orientation(p2, q2, p1);
    int o4 = orientation(p2, q2, q1);

    // General case
    if (o1 != o2 && o3 != o4) return true;

    // Special cases
    if (o1 == 0 && onSegment(p1, p2, q1)) return true;
    if (o2 == 0 && onSegment(p1, q2, q1)) return true;
    if (o3 == 0 && onSegment(p2, p1, q2)) return true;
    if (o4 == 0 && onSegment(p2, q1, q2)) return true;

    return false; // Doesn't intersect
}

// Function to calculate the length of the line segment AB
double segmentLength(Point a, Point b) {
    return sqrt((b.x - a.x) * (b.x - a.x) + (b.y - a.y) * (b.y - a.y));
}

// Function to calculate the distance from point P to segment AB
double distanceFromPointToSegment(Point p, Point a, Point b) {
    double ABx = b.x - a.x;
    double ABy = b.y - a.y;
    double APx = p.x - a.x;
    double APy = p.y - a.y;

    double AB_AB = ABx * ABx + ABy * ABy;  // Dot product of AB with itself
    double AP_AB = APx * ABx + APy * ABy;  // Dot product of AP with AB
    double t = AP_AB / AB_AB;

    // Project point P onto the line AB and clamp to the segment
    t = max(0.0, min(1.0, t));

    // Find the closest point on the segment
    double closestX = a.x + t * ABx;
    double closestY = a.y + t * ABy;

    // Compute distance from P to the closest point on the segment
    double dx = p.x - closestX;
    double dy = p.y - closestY;

    return sqrt(dx * dx + dy * dy);
}

// Function to calculate the angle between two line segments AB and CD
double angleBetweenSegments(Point A, Point B, Point C, Point D) {
    double ABx = B.x - A.x;
    double ABy = B.y - A.y;
    double CDx = D.x - C.x;
    double CDy = D.y - C.y;

    double dot = ABx * CDx + ABy * CDy;
    double magAB = sqrt(ABx * ABx + ABy * ABy);
    double magCD = sqrt(CDx * CDx + CDy * CDy);

    return acos(dot / (magAB * magCD));  // Angle in radians
}

int main() {
    // Define two line segments: (x1, y1) to (x2, y2) and (x3, y3) to (x4, y4)
    Point p1(1, 1), q1(10, 1);  // Segment 1
    Point p2(1, 2), q2(10, 2);  // Segment 2
    
    // Test: Check if the segments intersect
    if (doIntersect(p1, q1, p2, q2)) {
        cout << "The line segments intersect." << endl;
    } else {
        cout << "The line segments do not intersect." << endl;
    }

    // Test: Calculate the length of the first segment
    cout << "Length of segment 1: " << segmentLength(p1, q1) << endl;

    // Test: Calculate distance from a point to a line segment
    Point p(5, 3);
    cout << "Distance from point (5, 3) to segment 1: " << distanceFromPointToSegment(p, p1, q1) << endl;

    // Test: Calculate the angle between two line segments
    double angle = angleBetweenSegments(p1, q1, p2, q2);
    cout << "Angle between segment 1 and segment 2: " << angle * 180.0 / M_PI << " degrees" << endl;

    return 0;
}
