class Jucator:
    def __init__(self, id_jucator, nume, prenume, inaltime, post):
        """
        :param id: int - unic
        :param nume: str - max 20 de carcatere
        :param prenume: str - max 20 de caractere
        :param inaltime: int > 140
        :param post: Funcad, Pivot, Extrema
        """
        self.__id = id_jucator
        self.__nume = nume
        self.__prenume = prenume
        self.__inaltime = inaltime
        self.__post = post

    def get_id(self):
        """
        :return: int -identificatorul jucatorului
        """
        return self.__id

    def get_nume(self):
        """
        :return: str
        """
        return self.__nume

    def get_prenume(self):
        """
        :return: str
        """
        return self.__prenume

    def get_inaltime(self):
        """
        :return: int
        """
        return self.__inaltime

    def get_post(self):
        """
        :return: str Fundas, Pivor sau Extrema
        """
        return self.__post

    def set_nume(self, nume_nou):
        """
        seteaza numele str
        """
        self.__nume = nume_nou

    def set_prenume(self, prenume_nou):
        """
        prenume_nou: str
        seteaza prenumele
        """
        self.__prenume = prenume_nou

    def set_inaltime(self, inaltime_noua):
        """
        inaltime_noua: int
        seteaza inaltimea
        """
        self.__inaltime = inaltime_noua

    def set_post(self, post_nou):
        """
        seteaza post: str Fundas, Pivor sau Extrema
        """
        self.__post = post_nou

    def __eq__(self, other):
        if self.get_nume() == other.get_nume():
            if self.get_prenume() == other.get_prenume():
                return True
        if self.get_id() == other.get_id():
            return True
        return False

    def __str__(self):
        return f"{self.__id},{self.__nume},{self.__prenume},{self.__inaltime},{self.__post}\n"

