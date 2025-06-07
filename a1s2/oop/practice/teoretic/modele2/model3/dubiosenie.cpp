//
// Created by Mihai Moldovan on 22.06.2024.
//
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <map>
using namespace std;

vector<int> f(vector<int> l) {
    if (l.size() == 0)
        throw runtime_error("Illegal argument");
    map<int, int> c;

    for(auto e:l) {
        c[e]++;
    }
    sort(l.begin(), l.end(), [&](int a, int b) {
        return c[a] > c[b]; });
    return l;
}

int main() {
    vector<int> e { 124, 515 ,3553,53,214,4,4,31,42,423,5,5,345,34,2};
    //vector<int> r = ;

    for(auto& i:f(e)) {
        std::cout << i << " ";
    }

}