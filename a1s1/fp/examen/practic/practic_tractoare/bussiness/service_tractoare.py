from domain.tractor import Tractor

class ServiceTractoare:

    def __init__(self,repo_tractoare,validator_tractor):
        '''
        Initializam o clasa ServiceTractoare care va prelua datele de la consola si le va transmite la repository
        :param repo_tractoare:face legatura dintre cele doua clase
        :param validator_tractor:face legatura dintre cele doua clase
        '''
        self.__repo_tractoare = repo_tractoare
        self.__validator_tractoare = validator_tractor

    def adauga_tractor(self,id,denumire,pret,model,data):
        '''
        Adauga un tractor nou in fisiere
        :param id: int
        :param denumire: string
        :param pret: int
        :param model: string
        :param data: string
        '''
        tractor = Tractor(id,denumire,pret,model,data)
        self.__validator_tractoare.valideaza_tractor(tractor)
        self.__repo_tractoare.adauga_tractor(tractor)

    def sterge_tractoare(self,cifra):
        '''
        Sterge tractoarele pentru care pretul contine cifra data, si afiseaza numarul de tractoare sterse
        :param cifra: int, data de utilizator
        :return:
        '''
        tractoare = self.__repo_tractoare.get_all_tractoare()
        ct = 0
        for tractor in tractoare:
            valid = False
            pret = int(tractor.get_pret())
            while pret > 0:
                uc = int(pret % 10)
                if uc == cifra:
                    valid = True
                pret = pret / 10
            if valid:
                ct += 1
                self.__repo_tractoare.sterge_tractor(tractor.get_id_tractor())
        print(f"Numarul de tractoare sterse este {ct}")

    def filtrare_tractoare(self,denumire,pret):
        '''
        Filtreaza tractoarele a caror denumire contine stringul dat de la tastatura si a caror pret este mai mic
        ca numarul dat de la tastatura
        Daca stringul dat de utilizator este "/" atunci filtrul se aplica doar pentru pret
        Daca pretul dat de utilizator este -1 atunci filtrul se aplica doar pentru denumire
        :param denumire: string
        :param pret: int
        :return:
        '''
        output = ""
        tractoare = self.__repo_tractoare.get_all_tractoare()
        for tractor in tractoare:
            denumireTractor = tractor.get_denumire()
            pretTractor = tractor.get_pret()
            if denumire == "/":
                if pretTractor < pret:
                    output = output + str(tractor)
            elif pret == -1:
                if denumire in denumireTractor:
                    output = output + str(tractor)
            else:
                if denumire in denumireTractor and pretTractor < pret:
                    output = output + str(tractor)
        return output