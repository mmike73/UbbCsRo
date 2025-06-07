//
// Created by Mihai Moldovan on 18.06.2024.
//

#include "domain.h"
Melodie::Melodie(int id, string titlu, string artist, int rank):
    id{id}, titlu{titlu}, artist{artist}, rank{rank} {}

int Melodie::get_id() const {
    return id;
}
int Melodie::get_rank() const {
    return rank;
}
string Melodie::get_titlu() const {
    return titlu;
}
string Melodie::get_artist() const {
    return artist;
}

void Melodie::set_rank(int rank_nou) {
    rank = rank_nou;
}
void Melodie::set_titlu(string titlu_nou) {
    titlu = titlu_nou;
}
void Melodie::set_artist(string artist_nou) {
    artist = artist_nou;
}

string Melodie::to_string() {
    return std::to_string(id) + ',' + titlu + ',' + artist + ',' + std::to_string(rank) + '\n';
}