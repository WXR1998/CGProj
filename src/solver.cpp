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

template <class T>
void uniqueVector(std::vector<T> &v){
    sort(v.begin(), v.end());
    auto pos = unique(v.begin(), v.end());
    v.erase(pos, v.end());
}

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

Annulus SquareAnnulusSolver::solve(){
    Annulus ans, tmp;
    ans = std::max(ans, this->maxWidthOfSpecialConditions());

    return ans;
}

Annulus RectAnnulusSolver::solve(){
    Annulus ans, tmp;
    ans = std::max(ans, this->maxWidthOfSpecialConditions());

    return ans;
}