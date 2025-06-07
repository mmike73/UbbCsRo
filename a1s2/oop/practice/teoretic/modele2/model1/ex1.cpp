#include <exception>
#include <algorithm>
#include <stack>
#include <assert.h>
using namespace std;

vector<string> g(vector<string> l) {
    if(l.size() == 0) throw runtime_error("Illegal argument");
    std::stack<string> st;
    for(auto& s: l) {
        st.push(s);
    }
    vector<string> r;
    while(!st.empty()) {
        r.push_back(st.top());
        st.pop();
    }
    return r;
}

void test_g() {
    vector<string> l;
    try {
        g(l);
    } catch(exception& e) {
        assert(string(e.what()) == "Illegal argument");
    }
    l.push_back("ab");
    assert(g(l).size() == 1 && g(l)[0] == "ab");
    l.push_back("cd");
    l.push_back("ef");
    vector<string> rez = g(l);
    assert(rez.size() == 3 && rez[0] == "ef" && rez[1] == "cd" && rez[2] == "ab");
}

int main() {
    test_g();
    return 0;
}
