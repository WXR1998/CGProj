#pragma once
#include <vector>

#include "utils.hpp"

class AnnulusSolver{
protected:
    std::vector<Point>& p;
    Annulus maxWidthXInterval();
    Annulus maxWidthLShape();
    Annulus maxWidthOfSpecialConditions();
public:
	AnnulusSolver(std::vector<Point>& _p) :
		p(_p) { }
    virtual Annulus solve() = 0;
    // 将点集中所有点旋转角度
    void rotate(int t=1);
};

class SquareAnnulusSolver: AnnulusSolver{
private:
    Annulus maxWidthSquareAnnulus();
public:
    SquareAnnulusSolver(std::vector<Point>& p):AnnulusSolver(p){}
    Annulus solve();
};

class RectAnnulusSolver: AnnulusSolver{
private:
    Annulus maxWidthRectAnnulus();
public:
    RectAnnulusSolver(std::vector<Point> p):AnnulusSolver(p){}
    Annulus solve();
};