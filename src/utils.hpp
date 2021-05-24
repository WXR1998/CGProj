#pragma once
/*
单独处理退化的特殊情况，在实际处理一般情况时，不会使用到无穷点。
*/
const int inf = 0x7fffffff;
const int ninf = 0x80000000;

struct Point{
    int x, y;
    Point();
    Point(int, int);
    void read();
    void print();
    bool operator < (const Point &p) const;
};

struct Rect{
    int x1, y1, x2, y2;                                 // (x1, y1)是矩形左下角的点，(x2, y2)是矩形右上角的点
    Rect();
    Rect(int x1, int y1, int x2, int y2);
    void print();
    bool contains(Rect r);
};

enum SolutionType{
    NORMAL=0,                                           // 一般情况
    STRIPE_HORIZONTAL, STRIPE_VERTICAL,                 // 水平或垂直长条
    L_SHAPED_1, L_SHAPED_2, L_SHAPED_3, L_SHAPED_4      // 四个象限的L形区域
};

struct Annulus{
    Rect inner, outer;
    /*
        L形区域中，a，b两点分别是L内侧和外侧的顶点
        长条区域中，a，b两点分别处在两条平行线上
    */
    Point a, b;
    SolutionType type;
    Annulus();
    void setType(SolutionType type);
    void setRects(Rect inner, Rect outer);
    void setPoints(Point a, Point b);
    void print();
};