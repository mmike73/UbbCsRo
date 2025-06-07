//
// Created by Mihai Moldovan on 18.06.2024.
//

#ifndef PROJECT_DOMAIN_H
#define PROJECT_DOMAIN_H
#include <string>
using std::string;

class Melodie {
private:
    int id, rank;
    string titlu, artist;

public:
    //constructor
    Melodie(int id, string titlu, string artist, int rank);

    //returneaza id-u melodiei
    int get_id() const;

    //returneaza rankul melodiei
    int get_rank() const;

    //returneaza titlul melodiei
    string get_titlu() const;

    //returneaza artistul melodiei
    string get_artist() const;

    //modifica rankul melodiei
    void set_rank(int rank_nou);

    //modifica titlul melodiei
    void set_titlu(string titlu_nou);

    //modifica artistul melodiei
    void set_artist(string artist_nou);

    string to_string();
};


#endif //PROJECT_DOMAIN_H
