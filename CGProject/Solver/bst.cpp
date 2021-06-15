#include <set>
#include <vector>
#include <iostream>
#include <cassert>
#include <algorithm>

#include "bst.hpp"
#include "utils.hpp"

using std::cout;
using std::endl;

void SplayNode::update(){
    max = min = value;
    gap = 0;
    if (lc){
        gap = std::max(std::max(lc->gap, value - lc->max), gap);
        max = std::max(max, lc->max);
        min = std::min(min, lc->min);
    }
    if (rc){
        gap = std::max(std::max(rc->gap, rc->min - value), gap);
        max = std::max(max, rc->max);
        min = std::min(min, rc->min);
    }
}
int SplayNode::getMax(){ return max; }
int SplayNode::getMin(){ return min; }
int SplayNode::getMaxGap(){ return gap; }
int SplayNode::getValue(){ return value; }
void SplayNode::print(){
    if (lc){
        printf("[");
        lc->print();
        printf("]");
    }
    printf("%d", value);
    if (rc){
        printf("[");
        rc->print();
        printf("]");
    }
}

Splay::Splay(){
    root = NULL;
    this->init();
}
void Splay::splayDelete(SplayNode *n){
    if (n){
        splayDelete(n->lc);
        splayDelete(n->rc);
        delete n;
    }
}
void Splay::rotateOnce(SplayNode *n){
    if (!n->fa)
        return;
    if (root == n->fa)
        root = n;
    SplayNode *fa = n->fa;
    if (fa->lc == n){
        fa->lc = n->rc;
        if (n->rc)
            n->rc->fa = fa;
        n->rc = fa;
    }else{
        fa->rc = n->lc;
        if (n->lc)
            n->lc->fa = fa;
        n->lc = fa;
    }
    if (fa->fa)
        if (fa->fa->lc == fa)
            fa->fa->lc = n;
        else
            fa->fa->rc = n;
    n->fa = fa->fa;
    fa->fa = n;
    fa->update();
    n->update();
    if (n->fa)
        n->fa->update();
}
void Splay::rotate(SplayNode *n, bool toRoot){
    SplayNode *goal = toRoot ? NULL : root;
    assert(toRoot || n != root);
    while (n->fa != goal){
        if (n->fa->fa == goal){
            rotateOnce(n);
        }
        else{
            if ((n->fa->fa->lc == n->fa) == (n->fa->lc == n))
                rotateOnce(n->fa);
            rotateOnce(n);
        }
    }
}
SplayNode* Splay::upperBound(SplayNode *n, int value){
    if (value == n->getValue()){
        rotate(n);
        return n;
    }
    if (value > n->getValue())
        if (n->rc)
            return upperBound(n->rc, value);
        else
            return NULL;
    if (value < n->getValue())
        if (n->lc && n->lc->getMax() >= value)
            return upperBound(n->lc, value);
        else{
            rotate(n);
            return n;
        }
}
SplayNode* Splay::find(int value){
    SplayNode *candidate = upperBound(root, value);
    if (candidate && candidate->getValue() == value)
        return candidate;
    return NULL;
}
void Splay::insert(SplayNode *n, int value){
    if (value > n->getValue())
        if (n->rc)
            insert(n->rc, value);
        else
            n->rc = new SplayNode(value, n);
    else
        if (n->lc)
            insert(n->lc, value);
        else
            n->lc = new SplayNode(value, n);
    n->update();
}
bool Splay::insert(int value){
    if (find(value))
        return false;
    insert(root, value);
    return true;
}
SplayNode* Splay::pred(SplayNode *n){
    rotate(n);
    if (!n->lc)
        return NULL;
    n = n->lc;
    while (n->rc)
        n = n->rc;
    return n;
}
SplayNode* Splay::getInterval(int l, int r){
    assert(l <= r);
    SplayNode *nl1 = upperBound(root, l);
    SplayNode *nr = upperBound(root, r + 1);
    SplayNode *nl = pred(nl1);
    rotate(nl);
    rotate(nr, false);
    return root->rc->lc;
}
std::pair <bool, std::pair<int, int> > Splay::findGapInSubtree(SplayNode *n, int w, int d){
    std::pair <bool, std::pair<int, int> > ans;
    ans.first = false;
    if (n->getMaxGap() < w)
        return ans;
    if (d == 0){
        if (n->lc && n->lc->getMaxGap() >= w)
            return findGapInSubtree(n->lc, w, d);
        if (n->lc && n->getValue() - n->lc->getMax() >= w){
            ans.first = true;
            ans.second.first = n->lc->getMax();
            ans.second.second = n->lc->getMax() + w;
            return ans;
        }
        if (n->rc && n->rc->getMin() - n->getValue() >= w){
            ans.first = true;
            ans.second.first = n->getValue();
            ans.second.second = n->getValue() + w;
        }
        if (n->rc && n->rc->getMaxGap() >= w)
            return findGapInSubtree(n->rc, w, d);
    }else{
        if (n->rc && n->rc->getMaxGap() >= w)
            return findGapInSubtree(n->rc, w, d);
        if (n->rc && n->rc->getMin() - n->getValue() >= w){
            ans.first = true;
            ans.second.first = n->getValue();
            ans.second.second = n->getValue() + w;
        }
        if (n->lc && n->getValue() - n->lc->getMax() >= w){
            ans.first = true;
            ans.second.first = n->lc->getMax();
            ans.second.second = n->lc->getMax() + w;
            return ans;
        }
        if (n->lc && n->lc->getMaxGap() >= w)
            return findGapInSubtree(n->lc, w, d);
    }
    return ans;
}

bool Splay::_checkPointExistenceInRange_splay(int l, int r){
    if (l > r)
        return false;
    SplayNode* n = getInterval(l, r);
    return !!n;
}
void Splay::_addPoint_splay(int v){
    insert(v);
}
std::pair <bool, std::pair<int, int> > Splay::_findGapInRange_splay(int w, int l, int r, int d){
    std::pair <bool, std::pair<int, int> > ans;
    if (l > r){
        ans.first = false;
        return ans;
    }
    SplayNode *interval = getInterval(l, r);
    if (!interval){
        if (r - l >= w){
            ans.first = true;
            if (d == 0){
                ans.second.first = l;
                ans.second.second = l + w;
            }else{
                ans.second.first = r - w;
                ans.second.second = r;
            }
        }
        return ans;
    }
    if (d == 0){
        if (interval->getMin() - l >= w){
            ans.first = true;
            ans.second.first = l;
            ans.second.second = l + w;
            return ans;
        }
        ans = findGapInSubtree(interval, w, d);
        if (r - interval->getMax() >= w){
            ans.first = true;
            ans.second.first = interval->getMax();
            ans.second.second = interval->getMax() + w;
            return ans;
        }
    }else{
        if (r - interval->getMax() >= w){
            ans.first = true;
            ans.second.first = r - w;
            ans.second.second = r;
            return ans;
        }
        ans = findGapInSubtree(interval, w, d);
        if (interval->getMin() - l >= w){
            ans.first = true;
            ans.second.first = interval->getMin() - w;
            ans.second.second = interval->getMin();
            return ans;
        }
    }
    return ans;
}
void Splay::print(){
    root->print();
    printf("\n");
}

std::pair <bool, std::pair<int, int> > Splay::_findGapInRange_bruteforce(int w, int l, int r, int d){
    std::pair <bool, std::pair<int, int> > ans;
    ans.first = false;
    if (r - l < w)
        return ans;
    if (this->p.empty()){
        ans.first = true;
        if (d == 0){
            ans.second.first = l;
            ans.second.second = l + w;
        }else{
            ans.second.first = r - w;
            ans.second.second = r;
        }
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
        if (i < vec.size() - 1 && vec[i] <= l && r <= vec[i+1]){
            ans.first = true;
            if (d == 0){
                ans.second.first = l;
                ans.second.second = l + w;
            }else{
                ans.second.first = r - w;
                ans.second.second = r;
            }
        }
        if (i > 0)
            if (vec[i] - vec[i-1] >= w && l <= vec[i-1] && r >= vec[i]){
                ans.first = true;
                if (d == 0){
                    ans.second.first = vec[i-1];
                    ans.second.second = vec[i-1] + w;
                }else{
                    ans.second.first = vec[i] - w;
                    ans.second.second = vec[i];
                }
                return ans;
            }
        if (d == 0)
            ++i;
        else
            --i;
    }
    return ans;
}
bool Splay::_checkPointExistenceInRange_bruteforce(int l, int r){
    for (auto i: this->p)
        if (i >= l && i <= r)
            return true;
    return false;
}
void Splay::_addPoint_bruteforce(int v){
    if (this->p.find(v) == this->p.end())
        this->p.insert(v);
}
std::pair <bool, std::pair<int, int> > Splay::findGapInRange(int w, int l, int r, int d){
    if (l == -inf) ++l;
    if (r == inf)  --r;
    // auto ans1 = _findGapInRange_bruteforce(w, l, r, d);
    auto ans2 = _findGapInRange_splay(w, l, r, d);
    // assert(ans1.first == ans2.first);
    return ans2;
}
bool Splay::checkPointExistenceInRange(int l, int r){
    // auto ans1 = _checkPointExistenceInRange_bruteforce(l, r);
    auto ans2 = _checkPointExistenceInRange_splay(l, r);
    // assert(ans1 == ans2);
    return ans2;
}
void Splay::addPoint(int v){
    // _addPoint_bruteforce(v);
    _addPoint_splay(v);
}
void Splay::init(){
    this->p.clear();
    splayDelete(root);
    root = new SplayNode(-inf);
    root->rc = new SplayNode(inf, root);
    root->update();
}
int Splay::upperBound(int v){
    if (v > inf)
        v = inf;
    if (v < -inf)
        v = -inf;
    SplayNode* res = upperBound(root, v);
    return res->getValue();
}