#include <cstdio>
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

Annulus::Annulus(){
    type = NORMAL;
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
            printf("L_SHAPED ");
            this->a.print();
            this->b.print();
            printf("\n");
            break;
        case STRIPE_HORIZONTAL:
            printf("STRIPE_HORIZONTAL ");
            v1 = this->a.y;
            v2 = this->b.y;
            if (v1 > v2)
                std::swap(v1, v2);
            printf("%d - %d\n", v1, v2);
            break;
        case STRIPE_VERTICAL:
            printf("STRIPE_VERTICAL ");
            v1 = this->a.x;
            v2 = this->b.x;
            if (v1 > v2)
                std::swap(v1, v2);
            printf("%d - %d\n", v1, v2);
            break;
        default:
            printf("NORMAL Annulus\n");
            this->inner.print();
            this->outer.print();
            break;
    }
}