#include <vector>
#include <cstdio>

#include "utils.hpp"
#include "solver.hpp"

int main(){
    std::vector <Point> p;
    int n;
    freopen("data/1.in", "r", stdin);
    freopen("data/1.out", "w", stdout);
    scanf("%d", &n);
    for (int i = 0; i < n; ++i){
        Point tmp;
        tmp.read();
        p.push_back(tmp);
    }
    SquareAnnulusSolver sas(p);
    Annulus square_ans = sas.solve();
    RectAnnulusSolver ras(p);
    Annulus rect_ans = ras.solve();

    square_ans.print();
    // rect_ans.print();

    return 0;
}