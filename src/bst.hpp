#pragma once
#include <ext/pb_ds/tree_policy.hpp>
#include <ext/pb_ds/assoc_container.hpp>

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