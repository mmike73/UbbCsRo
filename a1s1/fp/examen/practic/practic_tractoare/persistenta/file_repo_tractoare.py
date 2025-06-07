from domain.tractor import Tractor
from persistenta.repository_tractoare import RepoTractoare

class FileRepoTractoare(RepoTractoare):

    def __init__(self,calea_catre_fisier):
        RepoTractoare.__init__(self)
        self.__calea_catre_fisier = calea_catre_fisier

    def __read_all_from_file(self):
        '''
        Citire din fisier
        '''
        with open(self.__calea_catre_fisier,"r") as f:
            lines = f.readlines()
            for line in lines:
                if line != "":
                    line = line.strip()
                    parts = line.split(",")
                    id_tractor = int(parts[0].strip())
                    denumire = parts[1].strip()
                    pret = parts[2].strip()
                    model = parts[3].strip()
                    data = parts[4].strip()
                    tractor = Tractor(id_tractor,denumire,pret,model,data)
                    self._tractoare[id_tractor] = tractor

    def __write_all_to_file(self):
        '''
        Scriere in fisier
        '''
        with open(self.__calea_catre_fisier,"w") as f:
            for tractor in self._tractoare.values():
                f.write(str(tractor))

    def adauga_tractor(self,tractor):
        self.__read_all_from_file()
        RepoTractoare.adauga_tractor(self,tractor)
        self.__write_all_to_file()

    def sterge_tractor(self,id_tractor):
        self.__read_all_from_file()
        RepoTractoare.sterge_tractor(self,id_tractor)
        self.__write_all_to_file()

    def cauta_tractor(self,id_tractor):
        self.__read_all_from_file()
        RepoTractoare.cauta_tractor(self,id_tractor)

    def modifica_tractor(self,tractor):
        self.__read_all_from_file()
        RepoTractoare.modifica_tractor(self,tractor)
        self.__write_all_to_file()

    def get_all_tractoare(self):
        self.__read_all_from_file()
        return RepoTractoare.get_all_tractoare(self)

    def size(self):
        self.__read_all_from_file()
        return RepoTractoare.size(self)