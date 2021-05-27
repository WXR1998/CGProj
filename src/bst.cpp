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