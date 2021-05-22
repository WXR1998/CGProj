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