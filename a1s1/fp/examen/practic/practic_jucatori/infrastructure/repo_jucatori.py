from domain.jucator import Jucator
class RepoJucatori:
    def __init__(self):
        self._repo = {}

    def adauga_jucator(self, jucator):
        """
        adauga jucatorul in repo
        daca jucatorul deja exista, va aparea eroare
        :param jucator: se tip Jucator
        """
        if jucator.get_id() in self._repo:
            raise Exception("Jucatorul deja exista!!!")
        for i in self._repo:
            if self._repo[i].get_nume() == jucator.get_nume() and self._repo[i].get_prenume() == jucator.get_prenume():
                raise Exception("Jucatorul deja exista!!!")
        self._repo[jucator.get_id()] = jucator


    def modifica_jucator(self, jucator):
        """
        plaseaza jucatorul modificat il locul celui curent
        :param jucator:
        :return:
        """
        self._repo[jucator.get_id()] = jucator


    def get_all(self):
        """
        preta toti jucatorii din repo si ii transmite
        :return: lista de jucatori
        """
        return [self._repo[x] for x in self._repo]
class FileRepoJucatori:
    def __init__(self, cale_fisier):
        self.__cale_fisier = cale_fisier
        RepoJucatori.__init__(self)

    def adauga_jucator(self, jucator):
        """
        imcarca in repo si in fisier jucatorul
        :param jucator: de tip jucator
        """
        self.__read_all_from_file()
        RepoJucatori.adauga_jucator(self,jucator)
        self.__append_to_file(jucator)

    def modifica_jucator(self, jucator):
        """
        pune obiectul modificat in repo
        """
        self.__read_all_from_file()
        RepoJucatori.modifica_jucator(self, jucator)
        self.__rewrite_to_file()


    def __append_to_file(self, jucator):
        """
        scrie un jucatior in fisier
        """
        with open(self.__cale_fisier, "a") as f:
            f.write(str(jucator))

    def __rewrite_to_file(self):
        """
        rescrrie tot repo in fisier
        """
        open(self.__cale_fisier,"w").close()
        for i in self._repo:
            self.__append_to_file(str(self._repo[i]))

    def __read_all_from_file(self):
        """
        citeste toate inregistrarile de jucatori din fisier
        """
        with open(self.__cale_fisier, "r") as f:
            lines = f.readlines()
            if len(lines) != 0:
                for line in lines:
                    l = line.strip()
                    if l != "":
                        l = l.split(',')
                        id_jucator = int(l[0])
                        nume = str(l[1])
                        prenume = str(l[2])
                        inaltime = int(l[3])
                        post = str(l[4])
                        jucator = Jucator(id_jucator, nume, prenume, inaltime, post)
                        self._repo[id_jucator] = jucator



    def get_all(self):
        """
        incarca toti jucatorii din fisier in repo si
        preta toti jucatorii din repo si ii transmite
        :return: lista de jucatori
        """
        self.__read_all_from_file()
        return RepoJucatori.get_all(self)

    def remove(self, x):
        self._repo.pop(x)
        self.__rewrite_to_file()

