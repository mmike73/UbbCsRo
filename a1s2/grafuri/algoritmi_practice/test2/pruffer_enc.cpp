#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <queue>

using namespace std;

vector<int> parents;
int v;

vector<int> prufer(){
    vector<int> rez;
    vector<int> grade(v,0);
    priority_queue<int,vector<int>,greater<int>> frunze;
    for (int i=0;i<v;i++){
        grade[i]++;
        if (parents[i]!=-1)
            grade[parents[i]]++;
    }
    for (int i=0;i<v;i++){
        if (grade[i]==1)
            frunze.push(i);
    }
    while (!frunze.empty()){
        int frunza=frunze.top();
        frunze.pop();
        rez.push_back(parents[frunza]);
        grade[parents[frunza]]--;
        if (grade[parents[frunza]]==1&&parents[parents[frunza]]!=-1){
            frunze.push(parents[frunza]);
        }
        grade[frunza]=0;
        }
    return rez;
}

int main(int argc, char * argv[]) {
    if (argc!=3){
        std::cerr << "Usage: ./p1 in out";
        exit(1);
    }
    string path_in=argv[1];
    string path_out=argv[2];
    ifstream f (path_in);
    ofstream f2 (path_out);

    f>>v;
    for (int i=0;i<v;i++) {
        int x;
        f>>x;
        parents.push_back(x);
    }

      vector<int> rez=prufer();
      f2<<rez.size()<<"\n";
      for (auto nod : rez)
          f2<<nod<<" ";

    f.close();
    f2.close();
    return 0;
}
