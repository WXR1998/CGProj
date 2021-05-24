#pragma once
#include <vector>

#include "utils.hpp"

class AnnulusSolver{
private:
    std::vector<Point> p;
public:
    AnnulusSolver(std::vector<Point> p);
    virtual Annulus solve() = 0;
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