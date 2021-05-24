#include <cstdio>
#include <cstdlib>
#include <vector>
#include <map>
#include <algorithm>
#include <iostream>

#include "utils.hpp"
#include "solver.hpp"

AnnulusSolver::AnnulusSolver(std::vector<Point> p){
    this->p = p;
}

Annulus SquareAnnulusSolver::solve(){
    printf("Square Solver\n");
}

Annulus RectAnnulusSolver::solve(){
    printf("Rect Solver\n");
}