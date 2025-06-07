//
// Created by Mihai Moldovan on 19.04.2024.
//

#ifndef LAB6_7_ACTIUNE_UNDO_H
#define LAB6_7_ACTIUNE_UNDO_H

#include "repo.h"
#include "domain.h"

class ActiuneUndo {
public:
    virtual void doUndo() = 0;
    virtual ~ActiuneUndo() = default;
};

class UndoAdauga: public ActiuneUndo {
    int id;
    RepoInterface& repo;
public:
    UndoAdauga(RepoInterface& repo, int id): repo{repo}, id{id} {}
    void doUndo() override {
        repo.sterge_produs_dupa_id_repo(id);
    }
};

class UndoSterge: public ActiuneUndo {
    Produs prod_sters;
    RepoInterface& repo;
public:
    UndoSterge(RepoInterface& repo, Produs produs): repo{repo}, prod_sters{produs} {};
    void doUndo() override {
        repo.adauga_produs_repo(prod_sters);
    }
};

class UndoModifica: public ActiuneUndo {
    Produs prod_nemodificat;
    RepoInterface& repo;
public:
    UndoModifica(RepoInterface& repo, Produs produs): repo{repo}, prod_nemodificat{produs} {};
    void doUndo() override {
        repo.modifica_produs_repo(prod_nemodificat.get_id(), prod_nemodificat);
    }
};


#endif //LAB6_7_ACTIUNE_UNDO_H
