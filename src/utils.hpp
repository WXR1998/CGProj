#pragma once
#include <vector>
#include <cstdlib>
#include <deque>
const int mod = 10000 * 2;
const int inf = mod * 2;
const int ninf = -mod * 2;

template <typename T>
void uniqueVector(std::vector<T> &v){
    sort(v.begin(), v.end());
    auto pos = unique(v.begin(), v.end());
    v.erase(pos, v.end());
}

struct Point{
    int x, y;
    Point();
    Point(int, int);
    void read();
    void print();
    void rotate(int t=1);
    bool operator < (const Point &p) const;
    bool operator <= (const Point &p) const;
    bool operator == (const Point &p) const;
    Point operator - (const Point &p) const;
};
long long dot(const Point &a, const Point &b);
long long cross(const Point &a, const Point &b);
bool sortPointsByX(const Point &a, const Point &b);
bool sortPointsByY(const Point &a, const Point &b);

struct Rect{
    int x1, y1, x2, y2;                                 // (x1, y1)是矩形左下角的点，(x2, y2)是矩形右上角的点
    Rect();
    Rect(int x1, int y1, int x2, int y2);
    void print();
    void rotate(int t=1);
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
    bool operator <(const Annulus &a) const;
    int width() const;
    void setType(SolutionType type);
    void setRects(Rect inner, Rect outer);
    void setPoints(Point a, Point b);
    void print();
    void rotate(int t=1);
};

class Contour{
    /*
        p是轮廓线上的点
        add可以把一条线段加入轮廓线的计算，注意不同的线段会有不同的计算方式
    */
protected:
    std::vector <Point> p;
    int r;
public:
    Contour(int r): r(r){}
    std::vector <Point>& getPoints();
    void print();
    /*
        计算完所有需要计算的点后，调用finish以将inf点放入轮廓列表
    */
    virtual void finish() = 0;
    virtual void add(Point l) = 0;
};

class ContourTilted: public Contour{
private:
    Point current;      // 当前最右边的在x轴上的点
public:
    ContourTilted(int r): Contour(r){
        current = Point(-inf, 0);
        p.push_back(current);
    }
    void reverseX();
    /*
        这里加入的是斜线和x轴的交点
    */
    void add(Point l);
    void finish();
};

class ContourHorizontal: public Contour{
private:
    std::deque <Point> dq;      // 保存线段右端点的阶梯形状
public:
    ContourHorizontal(int r): Contour(r){
        dq.clear();
        p.push_back(Point(-inf, 0));
    }
    /*
        这里加入的是水平线段的左端点
        注意，对于一个x=x0，只允许插入最低的一条线段，而不允许插入多条
    */
    void add(Point l);
    void finish();
};

int randInt();
/*
    在[-mod/2, mod/2)的坐标范围内产生随机点，且坐标均为偶数
*/
Point randPoint();
/*
    求线段a1a2和b1b2的交点，如果有交点，则返回 <true, 交点>，否则 <false, 零点>
*/
std::pair <bool, Point> intersection(Point a1, Point a2, Point b1, Point b2);