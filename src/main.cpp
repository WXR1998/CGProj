#include <vector>
#include "utils.hpp"
#include "solver.hpp"

int main(){
    Annulus a;
    a.setType(SolutionType::NORMAL);
    a.setRects(Rect(0, 0, 2, 2), Rect(-1, -1, 3, 3));
    a.print();

    std::vector<Point> p;
    p.push_back(Point(1, 2));
    SquareAnnulusSolver sas(p);
    a = sas.solve();
    a.print();

    return 0;
}