#pragma once
#include <set>

class SplayNode{
private:
    int value;
    int max, min, gap;
public:
    SplayNode *lc, *rc, *fa;

    SplayNode(int value, SplayNode *fa=NULL):value(value), fa(fa){
        max = min = value;
        gap = 0;
        lc = rc = NULL;
    }
    void update();
    int getMax();
    int getMin();
    int getMaxGap();
    int getValue();
    void print();
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

    std::pair <bool, std::pair<int, int> > findGapInSubtree(SplayNode *n, int w, int d);
    std::pair <bool, std::pair<int, int> > _findGapInRange_bruteforce(int w, int l, int r, int d);
    std::pair <bool, std::pair<int, int> > _findGapInRange_splay(int w, int l, int r, int d);
    bool _checkPointExistenceInRange_bruteforce(int l, int r);
    bool _checkPointExistenceInRange_splay(int l, int r);
    void _addPoint_bruteforce(int v);
    void _addPoint_splay(int v);

    void splayDelete(SplayNode *n);
    /*
        将节点n旋转到树根，其中如果toRoot为真，则转到树根，否则转到树根的孩子
    */
    void rotate(SplayNode *n, bool toRoot=true);
    void rotateOnce(SplayNode *n);
    /*
        找到大于等于value的第一个节点
        注意value一定要在[-inf, inf]内，否则可能会Runtime Error
    */
    SplayNode* upperBound(SplayNode *n, int value);
    /*
        找到等于value的那个节点
    */
    SplayNode* find(int value);
    void insert(SplayNode *n, int value);
    bool insert(int value);
    /*
        中序遍历中的前一个节点
    */
    SplayNode* pred(SplayNode *n);
    /*
        获得代表区间[l,r]的子树
    */
    SplayNode* getInterval(int l, int r);
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
    int upperBound(int v);
    void addPoint(int v);
    void init();
    void print();
};
