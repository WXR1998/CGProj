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

/*
    Splay需要实现这样的操作：
        - 插入一个点
        - 查询某个区间中，大于等于w的最大gap，解需要尽量靠左或者靠右
    这就需要每个节点维护它子树的 最小值、最大值、该区间中最大的gap
        - 合并两棵子树时，该区间的最大gap即为 两棵子树的gap 和 右子树min-左子树max
        - 查询时，首先把区间[l,r]提取出来，然后依据顺序，看 l到区间最小值、区间最大值到r、区间中的大于等于w的第一个gap
*/
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