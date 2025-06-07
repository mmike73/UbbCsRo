from domain.jucator import Jucator

class ServiceJucatori:
    def __init__(self, repo_jucatori, validare_jucatori):
        self.__repo = repo_jucatori
        self.__valid = validare_jucatori

    def creaza_jucator(self, id, nume, prenume, inaltime, post):
        """
        creeaza obiectuld e tip jucator din parametri transmisi
        :param id: int - unic
        :param nume: str - max 20 de carcatere
        :param prenume: str - max 20 de caractere
        :param inaltime: int > 140
        :param post: Funcad, Pivot, Extrema
        :return: obiectul de tip jucator
        :raises: error - daca datele sunt invalide
        """
        player = Jucator(id, nume, prenume, inaltime, post)
        self.__valid.valideaza_jucator(player)
        return player

    def adauga_jucator(self, jucator):
        """
        adauga jucatorul in repositoru si in fisier
        :param jucator: de tip jucator
        :raises: error, daca jucatorul deja exista
        """
        self.__repo.adauga_jucator(jucator)

    def modifica_inaltime(self, valoare):
        """
        se modifica inaltimea tuturor jucatorilor adaugand valoarea transmisa
        modificarea se face si in fisier
        :param valoare: int
        """
        jucatori = self.__repo.get_all()
        for i in jucatori:
            h = i.get_inaltime()
            if h + valoare <= 140:
                print(f"Nu se poate face modificarea pentru {i.get_nume()} {i.get_prenume()}")
            else:
                i.set_inaltime(h + valoare)
        for i in jucatori:
            self.__repo.modifica_jucator(i)



    def formeaza_echipe(self):
        """
        frmeaza o echipa din jucatorii cu media de intaltime ceea mai mare - back
        :return:
        """

    def importa_jucatori_din_fisier(self, nume_fisier):
        """
        preia nume si prenume din fisier si le genereaza celelalte caracteristici, jucatorii astfel
        creati sunt adaugati in repo
        :param nume_fisier: nume de fisier
        """
        id_de_incaeput = self.__repo.cel_mai_mare_id() + 1
        print(id_de_incaeput)
        #try:
        with open(nume_fisier, 'r') as f:
            lines = f.readlines()
            if len(lines) != 0:
                for line in lines:
                    line = line.strip()
                    if line != "":
                        line = line.split()
                        if len(line) == 2:
                            nume = line[0]
                            prenume = line[1]
                            print(nume, prenume)

                            #jucator = Jucator()
        #except:
          #  raise Exception("Nu exista fisierul transmis!!!")