#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <utility>
#include <queue>

using namespace std;


int v;

vector<int> prufer_coded;

vector<int> decoding(){
    vector<int> ap(v,0);
    vector<int> parents(v,-1);
    priority_queue<int,vector<int>,greater<int>  > leaves;
    for (int i=0;i<v-1;i++){
        ap[prufer_coded[i]]++;
    }
    for (int i=0;i<v;i++)
        if (ap[i]==0)
            leaves.push(i);
    int index=0;
    while (index<v-1){
        int nod=leaves.top();
        leaves.pop();
        parents[nod]=prufer_coded[index];
        ap[prufer_coded[index]]--;
        if (ap[prufer_coded[index]]==0)
            leaves.push(prufer_coded[index]);
        index++;
    }
    return parents;
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
    v++;
    for (int i=0;i<v;i++){
        int x;
        f>>x;
        prufer_coded.push_back(x);
    }
    vector<int> res= decoding();
    f2<<res.size()<<"\n";
    for (auto nod : res){
        f2<<nod<<" ";
    }
    f.close();
    f2.close();
    return 0;
}
