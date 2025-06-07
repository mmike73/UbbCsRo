class UI:
    def __init__(self, service_jucatori):
        self.__service = service_jucatori
        self.__commands = {
            "adauga": self.__adauga_jucator,
            "modifica": self.__modiica_inaltime,
            "echipa": self.__construieste_echipa,
            "import": self.__importa_jucatori,
        }
        self.__help = {
            "exit": "opreste programul",
            "adauga": "parametri: id - int, nume - str nevid max 20 char, prenume - str nevid max 20 char, inaltime - int - max 140, post - Fundas, pivot, Extrema",
            "modifica": "parametru: valoare - int modifica inaltimea jucatorilor adunand inaltimile lor",
            "echipa": "construieste schipa cu jucatorii cu media inaltimilor cea mai mare",
            "import": "parametru: str numele fisierului dinc are se imports",
        }

    def __adauga_jucator(self, params):
        """
        params: list - stributele jucatorului
        """
        if len(params) != 5:
            raise Exception("Numar de parametri invalid!!!")
        try:
            id_player = int(params[0])
            nume = str(params[1])
            prenume = str(params[2])
            inaltime = int(params[3])
            post = str(params[4])
            player = self.__service.creaza_jucator(id_player, nume, prenume, inaltime, post)
            self.__service.adauga_jucator(player)
        except:
            raise Exception("Tipuri de date invalide!!!")
        print("Adaugare realizata cu succes!!!")


    def __modiica_inaltime(self, params):
        """
        paramss[0] - se transmite o valoare
        """
        if len(params) != 1:
            raise Exception("Numar de parametri invalid!!!")
        try:
            valoare = int(params[0])
        except:
            raise Exception("Tip de data invalid!!!")
        self.__service.modifica_inaltime(valoare)
        print("Modificare realizata cu succes!!!!")

    def __construieste_echipa(self):
        """

        :return:
        """

    def __importa_jucatori(self, params):
        """

        :return:
        """
        if len(params) != 1:
            raise Exception("Numar de parametri invalid!!!")
        format_cale_fisier = "/Users/mihaimoldovan/Desktop/proiect_practic/"
        cale_fisier = format_cale_fisier + str(params[0])
        self.__service.importa_jucatori_din_fisier(cale_fisier)

    def run(self):
        """
        ruleaza programul
        """
        print("help - pentru a accesa comenzile")
        while True:
            comanda = str(input(">>> "))
            comanda = comanda.strip()
            if comanda == "exit":
                return
            if comanda == "help":
                for i in self.__help:
                    print(i, ":", self.__help[i])
            if comanda != "":
                parti = comanda.split()
                tip_comanda = parti[0]
                if tip_comanda in self.__commands:
                    try:
                        params = parti[1].split(",")
                    except:
                        params = ""

                    try:
                        self.__commands[tip_comanda](params)
                    except Exception as ex:
                        print(ex)


                else:
                    print("Comanda invalida!")