from erori.validation_error import ValidError

class ValidatorTractor:

    def valideaza_tractor(self,tractor):
        erori = ""
        if tractor.get_id_tractor() < 0:
            erori += "id invalid!\n"
        if tractor.get_pret() < 0:
            erori += "pret invalid!\n"
        if len(erori) != 0:
            raise ValueError(erori)