#include <iostream>
#include "vector_template.h"
#include "domain.h"
using std::cout;

int main() {
    Produs p{1,"da","da",1,"da"};
    Produs q{2,"da","da",1,"da"};
    Produs r{3,"da","da",1,"da"};
    Produs s{4,"da","da",1,"da"};
    Produs t{5,"da","da",1,"da"};
    Produs u{6,"da","da",1,"da"};
    Produs v{7,"da","da",1,"da"};
    Vector<Produs> A;

    Produs b = p;

    A.push_back(p);
    A.push_back(q);
    A.push_back(r);
    A.push_back(s);
    A.push_back(t);
    A.push_back(u);
    A.push_back(v);


    A.erase(4);




    for(int i = 0; i < 10; ++i)
        cout << A[i].get_id() << '\n';

}
