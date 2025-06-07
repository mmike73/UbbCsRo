class ValidareJucator:
    def valideaza_jucator(self, jucator):
        """
        verifica fiecare atribut al unui obiect de tip jucator
        :param jucator: Jucator
        :raises: error - cada jucatorul e invalid
        """
        errors = ""
        if jucator.get_id() <= 0:
            errors += "ID-ul trebuie sa fie intreg mai mare sau egal cu 1!!!\n"
        if jucator.get_nume() == "" or len(jucator.get_nume()) > 20:
            errors += "Numele jucatorului trebuie sa fie nevid si mai mic sau egal de 20 de caractere!!!\n"
        if jucator.get_prenume() == "" or len(jucator.get_prenume()) > 20:
            errors += "Prenumele jucatorului trebuie sa fie nevid si mai mic sau egal de 20 de caractere!!!\n"
        if jucator.get_inaltime() <= 140:
            errors += "Inaltimea jucatorului trebuie sa fie mai mare se 140!!!\n"
        if (jucator.get_post() in ["Fundas","Pivot","Extrema"]) == False:
            errors += "Postul poate fi doar Fundas,Pivot sau Extrema!!!\n"
        if errors != "":
            raise Exception(errors)
