#include <catch2/catch_test_macros.hpp>
// #include "tests_helper.h"

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

#include "cs225/PNG.h"
#include "cs225/HSLAPixel.h"

#include "List.h"

using namespace cs225;

int main() {
    List<int> list;

    for (int i = 1; i <= 6; i++)
        list.insertBack(i);

    list.reverseNth(4);
    //123456
    //321654
    for(int i : list) {
        cout << i << endl;
    }
}