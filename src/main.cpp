#include <vector>
#include <cstdio>
#include <algorithm>
#include <ctime>

#include "utils.hpp"
#include "solver.hpp"
#include "bst.hpp"
#include "segment_dragging.hpp"

int main(){
    std::vector <Point> p;
    int n;
    int st = clock();
    freopen("data/1.in", "r", stdin);
    freopen("data/1.out", "w", stdout);
    scanf("%d", &n);
    for (int i = 0; i < n; ++i){
        Point tmp;
        tmp.read();
        p.push_back(tmp);
    }
    // SquareAnnulusSolver sas(p);
    // Annulus square_ans = sas.solve();
    RectAnnulusSolver ras(p);
    Annulus rect_ans = ras.solve();

    // square_ans.print();
    rect_ans.print();
    // Splay splay;
    // splay.debug();
    int ed = clock();
    printf("Time used = %.3f s\n", (double)(ed - st) / CLOCKS_PER_SEC);

    return 0;
}