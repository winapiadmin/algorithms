//Point-in-Polygon (not PIP in python)
#include <iostream>
#include <vector>

using namespace std;

// A structure to represent a point
struct Point {
    int x, y;
    
    Point(int _x, int _y) : x(_x), y(_y) {}
};

// Function to check if a point is on the line segment (p1, p2)
bool onSegment(Point p, Point q, Point r) {
    return (q.x <= max(p.x, r.x) && q.x >= min(p.x, r.x) &&
            q.y <= max(p.y, r.y) && q.y >= min(p.y, r.y));
}

// Function to find orientation of ordered triplet (p, q, r).
// 0 -> p, q and r are collinear
// 1 -> Clockwise
// 2 -> Counterclockwise
int orientation(Point p, Point q, Point r) {
    int val = (q.y - p.y) * (r.x - q.x) - (q.x - p.x) * (r.y - q.y);
    if (val == 0) return 0;  // collinear
    return (val > 0) ? 1 : 2; // clockwise or counterclockwise
}

// Function to check if line segments (p1, q1) and (p2, q2) intersect
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

// Function to check if a point is inside a polygon
bool isInside(const vector<Point>& polygon, Point p) {
    int n = polygon.size();
    if (n < 3) return false;  // Not a polygon

    // Create a point for the ray
    Point extreme(INT_MAX, p.y);

    // Count intersections of the ray with polygon edges
    int count = 0, i = 0;
    do {
        int next = (i + 1) % n;
        if (doIntersect(polygon[i], polygon[next], p, extreme)) {
            if (orientation(polygon[i], p, polygon[next]) == 0)
                return onSegment(polygon[i], p, polygon[next]);
            count++;
        }
        i = next;
    } while (i != 0);

    // If count is odd, return true
    return count % 2 == 1;
}

int main() {
    // Define a polygon (a square)
    vector<Point> polygon = { Point(0, 0), Point(10, 0), Point(10, 10), Point(0, 10) };

    Point testPoint(5, 5);  // Point to test

    if (isInside(polygon, testPoint)) {
        cout << "Point (" << testPoint.x << ", " << testPoint.y << ") is inside the polygon." << endl;
    } else {
        cout << "Point (" << testPoint.x << ", " << testPoint.y << ") is outside the polygon." << endl;
    }

    return 0;
}
