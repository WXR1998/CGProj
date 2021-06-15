#pragma once
#include <vector>
#include <algorithm>

#include "utils.hpp"

enum Direction{
    D1, D2, D3, D4
};

class SegmentDragging{
private:
    Direction dir;
    std::vector <Point> p;
    std::vector <std::vector <Point> > r;
public:
    void preprocess();
    /*
        需确保传入的p是按照sortPointByY排序好的
    */
    SegmentDragging(std::vector <Point> p, Direction dir): dir(dir), p(p){
        preprocess();
    }
    /*
        求按照dir方向，从原点上方或者下方竖直的长为w的线段扫到的第一个点。线段端点扫到的点不算在内。
    */
    Point drag(int origin_idx, int w);
};