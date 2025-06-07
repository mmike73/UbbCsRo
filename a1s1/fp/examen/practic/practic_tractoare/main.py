from bussiness.service_tractoare import ServiceTractoare
from domain.tractor import Tractor
from erori.repo_error import RepoError
from erori.validation_error import ValidError
from persistenta.repository_tractoare import RepoTractoare
from persistenta.file_repo_tractoare import FileRepoTractoare
from prezentare.consola import UI
from validare.validator_tractoare import ValidatorTractor
from testare.teste import Teste

if __name__ == '__main__':
    repo = FileRepoTractoare("tractoare.txt")
    validator = ValidatorTractor()
    service = ServiceTractoare(repo,validator)
    consola = UI(service)
    teste = Teste()
    teste.setUp()
    teste.ruleaza_toate_testele()
    consola.run()

