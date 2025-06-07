#include <iostream>
#include <map>
#include <vector>
#include <exception>
#include <assert.h>
using std::map;
using std::vector;
using std::exception;
using namespace std;

int f(vector<int> l) {
    if(l.size() < 1) throw runtime_error("Illegal argument");
    map<int,int> m;
    for(auto e:l) {
        m[e]++;
    }
    int rez{0};
    for(auto e:m) {
        if(e.second > 1) rez++;
    }
    return rez;
}

void test_f() {
    vector<int> l;
    try {
        f(l);
    } catch (exception &e) {
        assert(string(e.what()) == "Illegal argument");
    }
    l.push_back(1);
    assert(f(l) == 0);
    vector<int> l1 = {1, 2, 2, 3, 3, 3, 4, 4, 4, 4, 5, 5, 5, 5, 5, 6, 6, 6, 6, 6, 6};
    assert(f(l1) == 5);
    l1 = {1,2,3,4,5,6};
    assert(f(l1) == 0);
}

int main() {
    test_f();
}
