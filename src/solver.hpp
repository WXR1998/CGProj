#pragma once
#include <vector>

#include "utils.hpp"

class AnnulusSolver{
protected:
    std::vector<Point> p;
    Annulus maxWidthXInterval();
    Annulus maxWidthLShape();
    Annulus maxWidthOfSpecialConditions();
public:
    AnnulusSolver(std::vector<Point> p);
    virtual Annulus solve() = 0;
    // 将点集中所有点旋转角度
    void rotate(int t=1);
};

class SquareAnnulusSolver: AnnulusSolver{
public:
    SquareAnnulusSolver(std::vector<Point> p):AnnulusSolver(p){}
    Annulus solve();
};

class RectAnnulusSolver: AnnulusSolver{
public:
    RectAnnulusSolver(std::vector<Point> p):AnnulusSolver(p){}
    Annulus solve();
};