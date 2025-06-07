class Tractor:

    def __init__(self,id,denumire,pret,model,data):
        '''
        Initializez o clasa de tip obiecte cu parametrii urmatori:
        :param id: int
        :param denumire: string
        :param pret: int
        :param model: string
        :param data: string
        '''
        self.__id = id
        self.__denumire = denumire
        self.__pret = pret
        self.__model = model
        self.__data = data

    def get_id_tractor(self):
        '''
        Getter pentru id
        '''
        return int(self.__id)

    def get_denumire(self):
        '''
        Getter pentru denumire
        '''
        return self.__denumire

    def get_pret(self):
        '''
        Getter pentru pret
        '''
        return int(self.__pret)

    def get_model(self):
        '''
        Getter pentru model
        '''
        return self.__model

    def get_data(self):
        '''
        Getter pentru data
        '''
        return self.__data

    def __str__(self):
        '''
        Metoda de afisare ordonata a parametrilor obiectului
        '''
        return f"{self.__id}, {self.__denumire}, {self.__pret}, {self.__model}, {self.__data}\n"