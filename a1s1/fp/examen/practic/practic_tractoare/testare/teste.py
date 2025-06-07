from bussiness.service_tractoare import ServiceTractoare
from domain.tractor import Tractor
from persistenta.file_repo_tractoare import FileRepoTractoare
from validare.validator_tractoare import ValidatorTractor
from erori.repo_error import RepoError

class Teste:

    def setUp(self):
        self.__tractor1 = Tractor(1,"Tractor1",1,"Model1","01.01.2001")

    def __test_domeniu(self):
        assert self.__tractor1.get_id_tractor() == 1
        assert self.__tractor1.get_denumire() == "Tractor1"
        assert self.__tractor1.get_pret() == 1
        assert self.__tractor1.get_model() == "Model1"
        assert self.__tractor1.get_data() == "01.01.2001"

    def __test_repo(self):
        f = open("tractoare_test.txt", "r+")
        f.truncate(0)
        self.__repo = FileRepoTractoare("tractoare_test.txt")
        assert self.__repo.size() == 0
        self.__repo.adauga_tractor(self.__tractor1)
        assert self.__repo.size() == 1
        try:
            self.__repo.adauga_tractor(Tractor(1,"Tractor11",25000,"Model11","12.09.2003"))
            assert False
        except RepoError as ve:
            assert str(ve) == "tractor existent!"
        self.__repo.sterge_tractor(1)
        assert self.__repo.size() == 0
        try:
            self.__repo.cauta_tractor(1)
            assert False
        except RepoError as ve:
            assert str(ve) == "tractor inexistent!"

    def __test_service(self):
        f = open("tractoare_test.txt", "r+")
        f.truncate(0)
        self.__repo = FileRepoTractoare("tractoare_test.txt")
        self.__validator = ValidatorTractor()
        self.__service = ServiceTractoare(self.__repo,self.__validator)
        self.__service.adauga_tractor(100,"Tractor100",100000,"Model100","26.03.2023")
        assert self.__repo.size() == 1
        self.__service.adauga_tractor(102,"Tractor102",102000,"Model102","20.07.2021")
        self.__service.sterge_tractoare(1)
        assert self.__repo.size() == 0
        self.__service.adauga_tractor(100, "Tractor100", 100000, "Model100", "26.03.2023")
        self.__service.adauga_tractor(102, "Tractor102", 200000, "Model102", "20.07.2021")
        self.__service.sterge_tractoare(1)
        assert self.__repo.size() == 1
        self.__service.adauga_tractor(100, "Tractor100", 100000, "Model100", "26.03.2023")
        assert self.__service.filtrare_tractoare("Tract", 150000) == "100, Tractor100, 100000, Model100, 26.03.2023\n"
        assert self.__service.filtrare_tractoare("Tract",-1) == "102, Tractor102, 200000, Model102, 20.07.2021\n100, Tractor100, 100000, Model100, 26.03.2023\n"

    def ruleaza_toate_testele(self):
        self.__test_domeniu()
        self.__test_repo()
        self.__test_service()