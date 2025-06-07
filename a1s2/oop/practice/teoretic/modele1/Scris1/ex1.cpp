#include <exception>
#include <vector>
#include <algorithm>
#include <stack>
using namespace std;

vector<string> g(vector<string> l) {
    if(l.size() == 0)
        throw exception("Illegal argument");
    
}