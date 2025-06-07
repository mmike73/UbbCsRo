cmake_minimum_required(VERSION 3.26)
project(untitled C)

set(CMAKE_C_STANDARD 11)

add_executable(untitled main.c
        sum_cif.c
        prime_n.c
        reprezentari_suma.c
        insertion_sort.c
        descompunere_f_p.c
        sir_termeni.c
        triunghiul_lui_pascal.c
        expoenet_fact.c
        indicatorul_lui_euler.c
        cmake-build-debug/indocator_nr_divizori.c)
