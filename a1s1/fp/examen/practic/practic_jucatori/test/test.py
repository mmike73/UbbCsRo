from business.service_jucaori import ServiceJucatori
from infrastructure.repo_jucatori import FileRepoJucatori
from validare.validare import ValidareJucator
from domain.jucator import Jucator


class Test:
    def __init__(self):
        self.__valid_jucatori = ValidareJucator()
        self.__repo_jucatori = FileRepoJucatori("/Users/mihaimoldovan/Desktop/proiect_practic/test/test_adaugare")
        self.__service_jucatori = ServiceJucatori(self.__repo_jucatori, self.__valid_jucatori)


    def teste_repo(self):
        """
        testeaza:
        - get_all
        - scrirerea in fisier
        - adauga
        """
        jucatori = self.__repo_jucatori.get_all()
        l = len(jucatori)
        id_player = 3
        nume = "Dan"
        prenume = "Coman"
        inaltime = 150
        post = "Fundas"
        player = Jucator(id_player, nume, prenume, inaltime, post)
        self.__repo_jucatori.adauga_jucator(player)
        jucatori = self.__repo_jucatori.get_all()
        l += 1
        assert l == len(jucatori)
        self.__repo_jucatori.remove(3)



    def teste_service(self):
        """
        testeaza
        - get_all
        - adaugare
        - modificare
        -
        """

    def teste_validare(self):
        """
        testeaza validarea unui jucator
        """
        id_player = 1
        nume = "Dan"
        prenume = "Coman"
        inaltime = 150
        post = "Fundas"
        player = Jucator(id_player, nume, prenume, inaltime, post)
        try:
            self.__valid_jucatori.valideaza_jucator(player)
            assert True
        except:
            assert False
        player = Jucator(-1, nume, prenume, inaltime, post)
        try:
            self.__valid_jucatori.valideaza_jucator(player)
            assert False
        except:
            assert True
        player = Jucator(id_player, "", "", inaltime, post)
        try:
            self.__valid_jucatori.valideaza_jucator(player)
            assert False
        except:
            assert True
        player = Jucator(id_player, nume, prenume, 120, post)
        try:
            self.__valid_jucatori.valideaza_jucator(player)
            assert False
        except:
            assert True
        player = Jucator(id_player, nume, prenume, inaltime, "rezerva")
        try:
            self.__valid_jucatori.valideaza_jucator(player)
            assert False
        except:
            assert True

    def teste_domain(self):
        """
        testeaza getteri, setteri, __eq__
        """
        id_player = 1
        nume = "Dan"
        prenume = "Coman"
        inaltime = 150
        post = "Fundas"
        player = Jucator(id_player, nume, prenume, inaltime, post)



    def run_all_tests(self):
        """
        ruleaza toate testele
        :raises: errors cand ceva nu finctioneaza ca intentioat
        """
        self.teste_validare()
        self.teste_repo()
