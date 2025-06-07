#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include <sstream>

using std::string;
using std::vector;

using std::getline;
using std::stringstream;

class Test {
public:
    Test(string file_path): file_path{file_path} {}

    void read_from_file();

private:
    string file_path;

    string id, varsta;
    string prenume, oras;
};

void Test::read_from_file() {
    //deschide fisier
    std::ifstream fin(file_path);
    //declara variabla in care iei linia curenta
    string line;
    //iei linie cu linie
    while(std::getline(fin,line)) {
        //decalri lienstream care va parsa linia curenta
        stringstream linestream(line);

        std::getline(linestream,id,',');
        std::getline(linestream,prenume,',');
        std::getline(linestream,varsta,',');
        std::getline(linestream,oras,',');

        std::cout << id + " " + prenume + " " + varsta + " " + prenume + " " + oras + "\n";

    }
    

}

