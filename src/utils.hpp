const int inf = 0x7fffffff;
const int ninf = 0x80000000;

struct Point{
    int x, y;
    Point();
    Point(int, int);
    void read();
    void print();
    bool operator < (const Point &) const;
};

struct Rect{
    int x1, y1, x2, y2;
    Rect();
    Rect(int, int, int, int);
    void print();
};