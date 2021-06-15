#include <cstdio>
#include <vector>
#include <algorithm>

#include "utils.hpp"
#include "segment_dragging.hpp"

void SegmentDragging::preprocess(){
    int n = p.size(), k;
    Point candidate;
    r.resize(n);
    for (int i = 0; i < n; ++i){
        switch (dir){
            case D1:
                for (int j = i + 1; j < n; ++j){
                    // 在原点左半边平面的点、在原点右侧x轴上的点都不应考虑
                    if (p[j].x < p[i].x || p[j].y == p[i].y)
                        continue;
                    // 对于同一条水平线上的点，只应考虑最左边的那个
                    k = j;
                    candidate = p[j];
                    while (k+1 < n && p[j].y == p[k+1].y){
                        ++k;
                        if (p[k].x >= p[i].x)
                            candidate = std::min(candidate, p[k]);
                    }
                    if (r[i].empty() || r[i].back().x > candidate.x)
                        r[i].push_back(candidate);
                    j = k;
                }
                break;
            case D2:
                for (int j = i + 1; j < n; ++j){
                    // 在原点右半边平面的点、在原点左侧x轴上的点都不应考虑
                    if (p[j].x > p[i].x || p[j].y == p[i].y)
                        continue;
                    // 对于同一条水平线上的点，只应考虑最右边的那个
                    k = j;
                    candidate = p[j];
                    while (k+1 < n && p[j].y == p[k+1].y){
                        ++k;
                        if (p[k].x <= p[i].x)
                            candidate = std::max(candidate, p[k]);
                    }
                    if (r[i].empty() || r[i].back().x < candidate.x)
                        r[i].push_back(candidate);
                    j = k;
                }
                break;
            case D3:
                for (int j = i - 1; j >= 0; --j){
                    // 在原点右半边平面的点、在原点左侧x轴上的点都不应考虑
                    if (p[j].x > p[i].x || p[j].y == p[i].y)
                        continue;
                    // 对于同一条水平线上的点，只应考虑最右边的那个
                    k = j;
                    candidate = p[j];
                    while (k-1 >= 0 && p[j].y == p[k-1].y){
                        --k;
                        if (p[k].x <= p[i].x)
                            candidate = std::max(candidate, p[k]);
                    }
                    if (r[i].empty() || r[i].back().x < candidate.x)
                        r[i].push_back(candidate);
                    j = k;
                }
                break;
            case D4:
                for (int j = i - 1; j >= 0; --j){
                    // 在原点左半边平面的点、在原点右侧x轴上的点都不应考虑
                    if (p[j].x < p[i].x || p[j].y == p[i].y)
                        continue;
                    // 对于同一条水平线上的点，只应考虑最左边的那个
                    k = j;
                    candidate = p[j];
                    while (k-1 >= 0 && p[j].y == p[k-1].y){
                        --k;
                        if (p[k].x >= p[i].x)
                            candidate = std::min(candidate, p[k]);
                    }
                    if (r[i].empty() || r[i].back().x > candidate.x)
                        r[i].push_back(candidate);
                    j = k;
                }
                break;
        }
    }
}
Point SegmentDragging::drag(int origin_idx, int w){
    int left, right, pivot;
    std::vector <Point> &vec = r[origin_idx];
    Point origin = p[origin_idx];
    switch (dir){
        case D1:
        case D2:
            if (vec.empty() || origin.y + w <= vec[0].y)
                if (dir == D1)
                    return Point(inf, origin.y);
                else
                    return Point(-inf, origin.y);
            left = 0, right = vec.size() - 1;
            while (left < right){
                pivot = (left + right + 1) / 2;
                if (origin.y + w <= vec[pivot].y)
                    right = pivot - 1;
                else
                    left = pivot;
            }
            return vec[left];
        case D3:
        case D4:
            if (vec.empty() || origin.y - w >= vec[0].y)
                if (dir == D4)
                    return Point(inf, origin.y);
                else
                    return Point(-inf, origin.y);
            left = 0, right = vec.size() - 1;
            while (left < right){
                pivot = (left + right + 1) / 2;
                if (origin.y - w >= vec[pivot].y)
                    right = pivot - 1;
                else
                    left = pivot;
            }
            return vec[left];
    }
}