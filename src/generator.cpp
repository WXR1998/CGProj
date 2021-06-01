#include <cstdio>
#include <cstring>
#include <ctime>

#include "utils.hpp"

using namespace std;

int main(int argc, char **argv){
    srand(time(0));

    freopen("./data/1.in", "w", stdout);

    int n = 200;
    printf("%d\n", n);
    for (int i = 0; i < n; ++i){
        Point p = randPoint();
        printf("%d %d\n", p.x, p.y);
    }

    return 0;
}