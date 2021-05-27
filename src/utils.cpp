#include <cstdio>
#include <cassert>
#include <algorithm>

#include "utils.hpp"

void printCoordinate(int x){
    if (x == inf)
        printf("inf");
    else if (x == -inf)
        printf("-inf");
    else
        printf("%d", x);
}

Point::Point(){
    x = y = 0;
}
Point::Point(int x, int y): x(x), y(y){}
void Point::print(){
    printf("(");
    printCoordinate(x);
    printf(", ");
    printCoordinate(y);
    printf(") ");
}
void Point::read(){
    scanf("%d%d", &x, &y);
}
bool Point::operator < (const Point &a) const{
    return x == a.x ? y < a.y : x < a.x;
}
void Point::rotate(int t){
    switch (t){
        case 1:
            std::swap(this->x, this->y);
            this->x = -this->x;
            break;
        case 2:
            this->x = -this->x;
            this->y = -this->y;
            break;
        case 3:
            std::swap(this->x, this->y);
            this->y = -this->y;
            break;
    }
}

bool sortPointsByX(const Point &a, const Point &b){
    return a.x == b.x ? a.y < b.y : a.x < b.x;
}
bool sortPointsByY(const Point &a, const Point &b){
    return a.y == b.y ? a.x < b.x : a.y < b.y;
}

Rect::Rect(){
    x1 = y1 = x2 = y2 = 0;
}
Rect::Rect(int x1, int y1, int x2, int y2){
    if (x1 > x2)
        std::swap(x1, x2);
    if (y1 > y2)
        std::swap(y1, y2);
    this->x1 = x1;
    this->y1 = y1;
    this->x2 = x2;
    this->y2 = y2;
}
bool Rect::contains(Rect r){
    return  r.x1 >= this->x1 && r.y1 >= this->y1 &&
            r.x2 <= this->x2 && r.y2 <= this->y2;
}
void Rect::print(){
    if (y2 - y1 == x2 - x1)
        printf("Square ");
    else
        printf("Rectangle ");
    Point(x1, y1).print();
    printf("- ");
    Point(x2, y2).print();
    printf("\n");
}
void Rect::rotate(int t){
    int nx1, nx2, ny1, ny2;
    switch (t){
        case 1:
            nx1 = -y2, ny1 = x1, nx2 = -y1, ny2 = x2;
            x1 = nx1; y1 = ny1; x2 = nx2; y2 = ny2;
            break;
        case 2:
            nx1 = -x2, ny1 = -y2, nx2 = -x1, ny2 = -y1;
            x1 = nx1; y1 = ny1; x2 = nx2; y2 = ny2;
            break;
        case 3:
            nx1 = y1, ny1 = -x2, nx2 = y2, ny2 = -x1;
            x1 = nx1; y1 = ny1; x2 = nx2; y2 = ny2;
            break;
    }
}

Annulus::Annulus(){
    this->type = NORMAL;
    this->inner = Rect();
    this->outer = Rect();
}
void Annulus::setType(SolutionType type){
    this->type = type;
}
void Annulus::setRects(Rect inner, Rect outer){
    assert(outer.contains(inner));
    this->inner = inner;
    this->outer = outer;
}
void Annulus::setPoints(Point a, Point b){
    this->a = a;
    this->b = b;
}
void Annulus::print(){
    int v1, v2;
    switch (this->type){
        case L_SHAPED_1:
        case L_SHAPED_2:
        case L_SHAPED_3:
        case L_SHAPED_4:
            printf("L_SHAPED %d\n", this->width());
            this->a.print();
            printf("\n");
            this->b.print();
            printf("\n");
            break;
        case STRIPE_HORIZONTAL:
            printf("STRIPE_HORIZONTAL %d\n", this->width());
            v1 = this->a.y;
            v2 = this->b.y;
            if (v1 > v2)
                std::swap(v1, v2);
            printf("%d\n%d\n", v1, v2);
            break;
        case STRIPE_VERTICAL:
            printf("STRIPE_VERTICAL %d\n", this->width());
            v1 = this->a.x;
            v2 = this->b.x;
            if (v1 > v2)
                std::swap(v1, v2);
            printf("%d\n%d\n", v1, v2);
            break;
        default:
            printf("NORMAL %d\n", this->width());
            this->inner.print();
            this->outer.print();
            break;
    }
}
int Annulus::width() const{
    int dx, dy;
    switch (this->type){
        case L_SHAPED_1:
        case L_SHAPED_2:
        case L_SHAPED_3:
        case L_SHAPED_4:
            dx = abs(this->a.x - this->b.x);
            dy = abs(this->a.y - this->b.y);
            return std::min(dx, dy);
        case STRIPE_HORIZONTAL:
            dy = abs(this->a.y - this->b.y);
            return dy;
        case STRIPE_VERTICAL:
            dx = abs(this->a.x - this->b.x);
            return dx;
        default:
            int u = this->outer.y2 - this->inner.y2;
            int b = this->inner.y1 - this->outer.y1;
            int l = this->inner.x1 - this->outer.x1;
            int r = this->outer.x2 - this->inner.x2;
            return std::min(std::min(u, b), std::min(l, r));
    }
}
bool Annulus::operator <(const Annulus &a) const{
    return this->width() < a.width();
}
void Annulus::rotate(int t){
    this->a.rotate(t);
    this->b.rotate(t);
    this->inner.rotate(t);
    this->outer.rotate(t);
    for (int i = 0; i < t; ++i)
        switch (this->type){
            case L_SHAPED_1:
                this->type = L_SHAPED_2;
                break;
            case L_SHAPED_2:
                this->type = L_SHAPED_3;
                break;
            case L_SHAPED_3:
                this->type = L_SHAPED_4;
                break;
            case L_SHAPED_4:
                this->type = L_SHAPED_1;
                break;
            case STRIPE_HORIZONTAL:
                this->type = STRIPE_VERTICAL;
                break;
            case STRIPE_VERTICAL:
                this->type = STRIPE_HORIZONTAL;
                break;
            default:
                break;
        }
}

int randInt(){
    return ((long long)rand() * rand()) % mod - mod / 2;
}

Point randPoint(){
    return Point(randInt(), randInt());
}