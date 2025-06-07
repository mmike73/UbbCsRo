using System.Runtime.InteropServices.Marshalling;
using ConsoleApp1;
using ConsoleApp1.Repository;
using ConsoleApp1.Service;

IRepository<Angajat,string> repositoryA = new AngajatFileRepository("data/angajati.txt");
IRepository<Sarcina,string> repositoryS = new SarcinaFileRepository("data/sarcini.txt");
IRepository<Pontaj,Tuple<string,string>> repositoryP = new PontajFileRepository("data/pontaje.txt","data/angajati.txt","data/sarcini.txt");
Service service = new Service(repositoryA, repositoryS,repositoryP);

service.findBestPaidEmployees().ForEach(pair => {
    Console.WriteLine($"{pair.Key} {pair.Value}");
});
