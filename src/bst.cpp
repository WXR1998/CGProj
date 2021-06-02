#include <set>
#include <vector>

#include "bst.hpp"
#include "utils.hpp"

Bst::Bst(){
    this->clear();
}
void Bst::clear(){
    this->count = 0;
    this->T.clear();
}
void Bst::insert(int v){
    this->T.insert(std::make_pair(v, this->count++));
}
int Bst::greaterOrEqual(int v){
    auto ans = this->T.lower_bound(std::make_pair(v, -1));
    if (ans == T.end())
        return inf;
    return ans->first;
}
int Bst::lessOrEqual(int v){
    auto ans = this->T.lower_bound(std::make_pair(v, this->count+1));
    ans--;
    if (ans == T.rend())
        return -inf;
    return ans->first;
}

Splay::Splay(){
    this->init();
}
std::pair <bool, std::pair<int, int> > Splay::findGapInRange(int w, int l, int r, int d){
    std::pair <bool, std::pair<int, int> > ans;
    ans.first = false;
    if (r - l < w)
        return ans;
    if (this->p.empty()){
        ans.first = true;
        ans.second.first = l;
        ans.second.second = l + w;
        return ans;
    }
    std::vector <int> vec;
    vec.assign(this->p.begin(), this->p.end());

    int i = (d == 0 ? 0 : vec.size() - 1);
    while (i >= 0 && i < vec.size()){
        if (i > 0 && vec[i-1] <= l && vec[i] > l || i == 0)
            if (vec[i] - l >= w){
                ans.first = true;
                ans.second.first = l;
                ans.second.second = l + w;
                return ans;
            }
        if (i < vec.size() - 1 && vec[i+1] >= r && vec[i] < r || i == vec.size() - 1)
            if (r - vec[i] >= w){
                ans.first = true;
                ans.second.first = r - w;
                ans.second.second = r;
                return ans;
            }
        if (i > 0)
            if (vec[i] - vec[i-1] >= w && l <= vec[i-1] && r >= vec[i]){
                ans.first = true;
                ans.second.first = vec[i-1];
                ans.second.second = vec[i];
                return ans;
            }
        if (d == 0)
            ++i;
        else
            --i;
    }
    return ans;
}
bool Splay::checkPointExistenceInRange(int l, int r){
    for (auto i: this->p)
        if (i >= l && i <= r)
            return true;
    return false;
}
void Splay::addPoint(int v){
    if (this->p.find(v) == this->p.end())
        this->p.insert(v);
}
void Splay::init(){
    this->p.clear();
}