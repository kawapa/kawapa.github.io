#include <vector>

struct Point {
    int x, y;
};

void drawPoints(std::vector<Point>::iterator start, 
                std::vector<Point>::iterator end) { }


// API renderuje punkty
// A my mamy linie...

struct Line {
    Point start, end;
};

struct LineToPointAdapter {
    using Points = std::vector<Point>;

    LineToPointAdapter(Line& line) {

    }

    virtual Points::iterator begin() { return points.begin(); }
    virtual Points::iterator end() { return points.end(); }
private:
    Points points;
}; 