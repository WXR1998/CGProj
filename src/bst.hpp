#pragma once
#include <ext/pb_ds/tree_policy.hpp>
#include <ext/pb_ds/assoc_container.hpp>
#include <set>

class Bst{
private:
    __gnu_pbds::tree<std::pair<int, int>, 
        __gnu_pbds::null_type, 
        std::less<std::pair<int, int> >, 
        __gnu_pbds::rb_tree_tag, 
        __gnu_pbds::tree_order_statistics_node_update> T;
    int count;
public:
    Bst();
    void clear();
    void insert(int v);
    int greaterOrEqual(int v);
    int lessOrEqual(int v);
};

class SplayNode{
private:
public:
};
class Splay{
private:
    SplayNode *root;
    std::set <int> p;
public:
    Splay();
    /*
        在[l,r]之间找宽度为w的gap。gap的左右边界可以正好是l或r。
        d为0时表示尽可能找靠左的，为1时表示尽可能找靠右的。
    */
    std::pair <bool, std::pair<int, int> > findGapInRange(int w, int l, int r, int d);
    /*
        检查是否有点在[l,r]之间，点落在l或r上也可以。
    */
    bool checkPointExistenceInRange(int l, int r);
    void addPoint(int v);
    void init();
};