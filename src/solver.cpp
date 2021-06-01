#include <cstdio>
#include <cassert>
#include <cstdlib>
#include <vector>
#include <map>
#include <algorithm>
#include <iostream>

#include "utils.hpp"
#include "solver.hpp"
#include "bst.hpp"


AnnulusSolver::AnnulusSolver(std::vector<Point> p){
    this->p = p;
    assert(p.size() > 1);
}
void AnnulusSolver::rotate(int t){
    for (int i = 0, l = p.size(); i < l; ++i)
        p[i].rotate(t);
}
Annulus AnnulusSolver::maxWidthXInterval(){
    Point p1, p2;
    Annulus ans;
    sort(this->p.begin(), this->p.end());
    p1 = this->p[0]; p2 = this->p[1];
    for (int i = 1, l = this->p.size(); i < l - 1; ++i)
        if (abs(this->p[i+1].x - this->p[i].x) > abs(p1.x - p2.x))
            p1 = this->p[i+1], p2 = this->p[i];
    ans.setPoints(p1, p2);
    return ans;
}
Annulus AnnulusSolver::maxWidthLShape(){
    Annulus annulus, tmp;
    Bst bst;
    std::vector <int> vx, vy;
    // 给定坐标，求该坐标上的点在p中的下标
    std::map <std::pair<int, int>, int> idx;
    // ans[lx][ly] 表示每个点右上角那个点的x坐标
    int **ans;
    for (auto i: this->p){
        vx.push_back(i.x);
        vy.push_back(i.y);
    }
    uniqueVector(vx);
    uniqueVector(vy);
    for (int i = 0, l = this->p.size(); i < l; ++i)
        idx[std::make_pair(this->p[i].x, this->p[i].y)] = i;
    int lx = vx.size(), ly = vy.size();
    ans = new int*[lx];
    for (int i = 0; i < lx; ++i)
        ans[i] = new int[ly];

    // 从上往下，从左往右放入所有点，同时找x坐标恰好大于这个点的点
    bst.clear();
    for (int j = ly - 1; j >= 0; --j)
        for (int i = 0; i < lx; ++i){
            int x = vx[i], y = vy[j];
            int greater_x = bst.greaterOrEqual(x + 1);
            ans[i][j] = greater_x;
            std::pair<int, int> target = std::make_pair(x, y);
            if (idx.find(target) != idx.end()){
                bst.insert(x);
            }
        }
    // 从右往左，从下往上放入所有点，同时找y坐标恰好大于这个点的点
    bst.clear();
    for (int i = lx - 1; i >= 0; --i)
        for (int j = 0; j < ly; ++j){
            int x = vx[i], y = vy[j];
            int greater_y = bst.greaterOrEqual(y + 1);
            int greater_x = ans[i][j];
            assert((greater_y == inf) == (greater_x == inf));
            if (greater_y != inf && greater_x != inf){
                tmp.setType(SolutionType::L_SHAPED_1);
                int d = std::min(greater_x - x, greater_y - y);
                tmp.setPoints(Point(x, y), Point(x + d, y + d));
                annulus = std::max(annulus, tmp);
            }
            std::pair<int, int> target = std::make_pair(x, y);
            if (idx.find(target) != idx.end())
                bst.insert(y);
        }

    for (int i = 0; i < lx; ++i)
        delete ans[i];
    delete ans;
    return annulus;
}
Annulus AnnulusSolver::maxWidthOfSpecialConditions(){
    Annulus ans, tmp;

    tmp = this->maxWidthXInterval();
    tmp.setType(SolutionType::STRIPE_VERTICAL);
    ans = std::max(ans, tmp);

    this->rotate();
    tmp = this->maxWidthXInterval();
    tmp.rotate(3);
    tmp.setType(SolutionType::STRIPE_HORIZONTAL);
    ans = std::max(ans, tmp);
    this->rotate(3);

    tmp = this->maxWidthLShape();
    tmp.setType(SolutionType::L_SHAPED_1);
    ans = std::max(ans, tmp);

    this->rotate();
    tmp = this->maxWidthLShape();
    tmp.rotate(3);
    tmp.setType(SolutionType::L_SHAPED_2);
    ans = std::max(ans, tmp);

    this->rotate();
    tmp = this->maxWidthLShape();
    tmp.rotate(2);
    tmp.setType(SolutionType::L_SHAPED_3);
    ans = std::max(ans, tmp);

    this->rotate();
    tmp = this->maxWidthLShape();
    tmp.rotate(1);
    tmp.setType(SolutionType::L_SHAPED_4);
    ans = std::max(ans, tmp);

    this->rotate();
    return ans;
}

std::pair <int, int> checkBelow(Point p, Point q1, Point q2){
    assert(p.x >= q1.x && p.x <= q2.x);
    if (p.x == q1.x){
        if (p.y <= q1.y)
            return std::make_pair(1, 0);
        else if (q1.y == 0)
            return std::make_pair(1, 1);
        else
            return std::make_pair(0, 0);
    }
    if (q1.y == 0 && q2.y == 0)
        return std::make_pair(1, 1);
    double t = (double)(p.x - q1.x) / (q2.x - q1.x);
    int y = (int)(q1.y + (q2.y - q1.y) * t);
    return std::make_pair(p.y <= y, 0);
}
Annulus SquareAnnulusSolver::maxWidthSquareAnnulus(){
    /*
     确定一个上边界上的点，确定一个下边界上的点，然后这个正方形的中心一定在这两个点y坐标的均值的这条线上
     f_i(x): 当中心的坐标为(x, (y1+y2)/2)时，i号点的存在使得这个空环的宽最大为f_i(x)
     */
    std::vector <Point> p_x(this->p), p_y(this->p);   // 按x排序和按y排序的点集
    sort(p_x.begin(), p_x.end(), sortPointsByX);
    sort(p_y.begin(), p_y.end(), sortPointsByY);

    Annulus ans, tmp;
    ans.setRects(Rect(), Rect());
    tmp.setType(SolutionType::NORMAL);
    int n = p_x.size();
    for (int lower_idx = 0; lower_idx < n; ++lower_idx)
        for (int upper_idx = lower_idx + 1; upper_idx < n; ++upper_idx){
            Point lower = p_y[lower_idx], upper = p_y[upper_idx];
            int r = (upper.y - lower.y) / 2;        // 正方形的半径

            ContourTilted contour_asc(r), contour_des(r);
            ContourHorizontal contour_hor(r);
            for (int i = 0; i < n; ++i)
                if (p_x[i].y > lower.y && p_x[i].y < upper.y)
                    contour_asc.add(Point(p_x[i].x - r, 0));
            for (int i = 0; i < n; ++i)
                if (p_x[i].y > lower.y && p_x[i].y < upper.y){
                    Point lowest = Point(p_x[i].x - r, std::min(abs(p_x[i].y - lower.y), abs(p_x[i].y - upper.y)));
                    // 确保对于同一个x，只有y最小的那条线段才能纳入计算
                    int j = i;
                    while (j+1 < n && p_x[j+1].y > lower.y && p_x[j+1].y < upper.y && p_x[j+1].x == p_x[i].x){
                        ++j;
                        lowest = std::min(lowest, 
                            Point(p_x[j].x - r, 
                                std::min(abs(p_x[j].y - lower.y), abs(p_x[j].y - upper.y)))
                        );
                    }
                    contour_hor.add(lowest);
                    i = j;
                }
            for (int i = n-1; i >= 0; --i)
                if (p_x[i].y > lower.y && p_x[i].y < upper.y)
                    contour_des.add(Point(- p_x[i].x - r, 0));
            contour_asc.finish();
            contour_des.finish();
            contour_des.reverseX();
            contour_hor.finish();

            // 至此，三条轮廓线已经计算完毕
            // 接下来需要计算轮廓线两两之间的交点
            std::vector <Point> &p_asc = contour_asc.getPoints();
            std::vector <Point> &p_des = contour_des.getPoints();
            std::vector <Point> &p_hor = contour_hor.getPoints();
            std::vector <Point> candidates;
            candidates.insert(candidates.end(), p_asc.begin(), p_asc.end());
            candidates.insert(candidates.end(), p_des.begin(), p_des.end());
            candidates.insert(candidates.end(), p_hor.begin(), p_hor.end());

            int cur_asc = 0, cur_des = 0, cur_hor = 0;
            int len_asc = p_asc.size() - 1, 
                len_des = p_des.size() - 1, 
                len_hor = p_hor.size() - 1;
            while (cur_asc+1 < len_asc || cur_des+1 < len_des || cur_hor+1 < len_hor){
                Point asc = cur_asc+1 < len_asc ? p_asc[cur_asc+1] : Point(inf, inf);
                Point des = cur_des+1 < len_des ? p_des[cur_des+1] : Point(inf, inf);
                Point hor = cur_hor+1 < len_hor ? p_hor[cur_hor+1] : Point(inf, inf);
                std::pair <bool, Point> res1, res2;
                if (asc <= des && asc <= hor){
                    res1 = intersection(p_asc[cur_asc], p_asc[cur_asc+1], p_des[cur_des], p_des[cur_des+1]);
                    res2 = intersection(p_asc[cur_asc], p_asc[cur_asc+1], p_hor[cur_hor], p_hor[cur_hor+1]);
                    if (res1.first)
                        candidates.push_back(res1.second);
                    if (res2.first)
                        candidates.push_back(res2.second);
                    ++cur_asc;
                }else if (des <= asc && des <= hor){
                    res1 = intersection(p_des[cur_des], p_des[cur_des+1], p_asc[cur_asc], p_asc[cur_asc+1]);
                    res2 = intersection(p_des[cur_des], p_des[cur_des+1], p_hor[cur_hor], p_hor[cur_hor+1]);
                    if (res1.first)
                        candidates.push_back(res1.second);
                    if (res2.first)
                        candidates.push_back(res2.second);
                    ++cur_des;
                }else{
                    res1 = intersection(p_hor[cur_hor], p_hor[cur_hor+1], p_des[cur_des], p_des[cur_des+1]);
                    res2 = intersection(p_hor[cur_hor], p_hor[cur_hor+1], p_asc[cur_asc], p_asc[cur_asc+1]);
                    if (res1.first)
                        candidates.push_back(res1.second);
                    if (res2.first)
                        candidates.push_back(res2.second);
                    ++cur_hor;
                }
            }
            uniqueVector(candidates);
            // 此时candidates就是所有的可能解，逐一判定即可

            cur_asc = 0, cur_des = 0, cur_hor = 0;
            for (auto candidate: candidates){
                if (candidate.x == inf || candidate.x == -inf)
                    continue;
                int x = candidate.x, y = candidate.y;
                if (x > std::min(lower.x, upper.x) + r || x < std::max(lower.x, upper.x) - r)
                    continue;
                while (cur_asc < len_asc && p_asc[cur_asc+1].x < x)
                    ++cur_asc;
                while (cur_des < len_des && p_des[cur_des+1].x <= x)
                    ++cur_des;
                while (cur_hor < len_hor && (p_hor[cur_hor+1].x < x || 
                    p_hor[cur_hor+1].x == x && p_hor[cur_hor+1].y <= p_hor[cur_hor].y))
                    ++cur_hor;
                int count = 0, zero_count = 0;
                std::pair <int, int> res;
                res = checkBelow(candidate, p_asc[cur_asc], p_asc[cur_asc+1]);
                count += res.first;
                zero_count += res.second;
                res = checkBelow(candidate, p_des[cur_des], p_des[cur_des+1]);
                count += res.first;
                zero_count += res.second;
                res = checkBelow(candidate, p_hor[cur_hor], p_hor[cur_hor+1]);
                count += res.first;
                zero_count += res.second;
                if (zero_count < 3 && count == 3){
                    Point center(x, (lower.y + upper.y) / 2);
                    tmp.setRects(Rect(center.x - r + y, center.y - r + y, center.x + r - y, center.y + r - y),
                                 Rect(center.x - r, center.y - r, center.x + r, center.y + r));
                    ans = std::max(ans, tmp);
                }
            }
        }
    return ans;
}
Annulus SquareAnnulusSolver::solve(){
    Annulus ans, tmp;
    ans = std::max(ans, this->maxWidthOfSpecialConditions());

    tmp = this->maxWidthSquareAnnulus();
    tmp.setType(SolutionType::NORMAL);
    ans = std::max(ans, tmp);

    this->rotate();
    tmp = this->maxWidthSquareAnnulus();
    tmp.rotate(3);
    tmp.setType(SolutionType::NORMAL);
    ans = std::max(ans, tmp);

    this->rotate(3);
    return ans;
}

Annulus RectAnnulusSolver::solve(){
    Annulus ans, tmp;
    ans = std::max(ans, this->maxWidthOfSpecialConditions());

    return ans;
}