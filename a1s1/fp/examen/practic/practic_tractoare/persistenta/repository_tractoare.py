from erori.repo_error import RepoError

class RepoTractoare:

    def __init__(self):
        self._tractoare = {}

    def adauga_tractor(self,tractor):
        '''
        Adauga tractor dupa id
        '''
        if tractor.get_id_tractor() in self._tractoare:
            raise RepoError("tractor existent!")
        self._tractoare[tractor.get_id_tractor()] = tractor

    def sterge_tractor(self,id_tractor):
        '''
        Sterge tractor dupa id
        '''
        if id_tractor not in self._tractoare:
            raise RepoError("tractor inexistent!")
        del self._tractoare[id_tractor]

    def cauta_tractor(self,id_tractor):
        '''
        Cauta tractor dupa id
        '''
        if id_tractor not in self._tractoare:
            raise RepoError("tractor inexistent!")
        return self._tractoare[id_tractor]

    def modifica_tractor(self,tractor):
        '''
        Modifica tractor dupa id
        '''
        if tractor.get_id_tractor() not in self._tractoare:
            raise RepoError("tractor inexistent!")
        self._tractoare[tractor.get_id_tractor()] = tractor

    def get_all_tractoare(self):
        '''
        Obtinerea unei liste cu toate tractoarele
        '''
        tractoare = []
        for id_tractor in self._tractoare:
            tractoare.append(self._tractoare[id_tractor])
        return tractoare

    def size(self):
        '''
        Numarul de tractoare
        '''
        return len(self._tractoare)