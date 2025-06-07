from business.service_jucaori import ServiceJucatori
from infrastructure.repo_jucatori import FileRepoJucatori
from validare.validare import ValidareJucator
from test.test import Test
from presentation.ui import UI

t = Test()
t.run_all_tests()

valid_jucatori = ValidareJucator()
repo_jucatori = FileRepoJucatori("/Users/mihaimoldovan/Desktop/proiect_practic/jucatori_db")
service_jucatori = ServiceJucatori(repo_jucatori, valid_jucatori)

console = UI(service_jucatori)
console.run()
