/* Your code here! */
#include "dsets.h"
#include <iostream>
using namespace std;

DisjointSets::DisjointSets() {
}

void DisjointSets::addelements(int num) {
    if (num <= 0) {
        return;
    }
    for (int i = 0 ; i < num ; i++) {
        elem_.push_back(-1);
    }
}

int DisjointSets::find(int elem) {
    if (elem_[elem] == elem) {
        return elem;
    }
    if (elem_[elem] < 0) {
        return elem;
    }
    elem_[elem] = find(elem_[elem]);
    return elem_[elem];
}

void DisjointSets::setunion(int a, int b) {
    if (find(a) == find(b)) {
        return;
    }

    int find_a = find(a);
    int find_b = find(b);
    int temp = -1;

    if (elem_[find_a] < elem_[find_b]) {
        temp = elem_[find_b];
        elem_[find_b] = find_a;
        elem_[find_a] += temp;
        return;
    }

    temp = elem_[find_a];
    elem_[find_a] = find_b;
    elem_[find_b] += temp;
    return;

}

int DisjointSets::size(int elem) {
    return -1 * elem_[find(elem)];
}
