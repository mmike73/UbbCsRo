from erori.repo_error import RepoError
from erori.validation_error import ValidError

class UI:

    def __init__(self,service_tractoare):
        '''
        Initializeaza o clasa de tip consola, care va prelua datele utilizatorului
        :param service_tractoare:face legatura dintre cele doua clase
        '''
        self.__service_tractoare = service_tractoare
        self.__filtru = ["",-1]
        self.__comenzi = {
            "adauga_tractor": self.__ui_adauga_tractor,
            "sterge_tractor_dupa_cifra": self.__ui_sterge_tractoare_dupa_cifra,
            "modifica_filtru": self.__modifica_filtru,
            "filtrare_tractoare": self.__ui_filtrare_tractoare
        }

    def __ui_adauga_tractor(self):
        if len(self.__params) != 5:
            raise ValueError("numar parametrii invalid!")
        id = int(self.__params[0])
        denumire = self.__params[1]
        pret = int(self.__params[2])
        model = self.__params[3]
        data = self.__params[4]
        self.__service_tractoare.adauga_tractor(id,denumire,pret,model,data)
        print("tractor adaugat cu succes!")

    def __ui_sterge_tractoare_dupa_cifra(self):
        if len(self.__params) != 1:
            raise ValueError("numar parametrii invalid!")
        cifra = int(self.__params[0])
        self.__service_tractoare.sterge_tractoare(cifra)
        print("tractoare sterse cu succes!")

    def __modifica_filtru(self):
        if len(self.__params) != 2:
            raise ValueError("numar parametri invalid!")
        text = self.__params[0]
        pret = int(self.__params[1])
        self.__filtru[0] = text
        self.__filtru[1] = pret
        print(f"Filtrul pentru denumire este {self.__filtru[0]} si filtrul pentru pret este {self.__filtru[1]}")

    def __ui_filtrare_tractoare(self):
        if len(self.__params) != 0:
            raise ValueError("numar parametri invalid!")
        print(self.__service_tractoare.filtrare_tractoare(self.__filtru[0], self.__filtru[1]))

    def run(self):
        while True:
            comanada = input("adauga_tractor\nsterge_tractor_dupa_cifra\nmodifica_filtru\nfiltrare_tractoare\n>>>")
            comanada = comanada.strip()
            if comanada == "":
                continue
            if comanada == "exit":
                return
            parti = comanada.split()
            nume_comanada = parti[0]
            self.__params = parti[1:]
            if nume_comanada in self.__comenzi:
                try:
                    self.__comenzi[nume_comanada]()
                except ValueError:
                    print("Eroare UI: tip numeric invalid")
                except ValidError as ve:
                    print(f"Validation Error: {ve}")
                except RepoError as re:
                    print(f"Repository Error: {re}")
            else:
                print("Comanda Invalida!")