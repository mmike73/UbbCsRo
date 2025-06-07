using ConsoleApp1.Repository;

namespace ConsoleApp1.Service;

public class Service
{
    private IRepository<Angajat,string> AngajatRepository;
    private IRepository<Sarcina,string> SarcinaRepository;
    private IRepository<Pontaj,Tuple<string,string> > PontajRepository;

    public Service(IRepository<Angajat, string> angajatFileRepository,  IRepository<Sarcina, string> sarcinaFileRepository, IRepository<Pontaj,Tuple<string,string>> PontajRepository)
    {
        AngajatRepository = angajatFileRepository;
        SarcinaRepository = sarcinaFileRepository;
        this.PontajRepository = PontajRepository;
    }

    public List<Angajat> findAngajati()
    {
        return AngajatRepository.FindAll().ToList();
    }

    public List<Angajat> findAngajatiByNivel(Nivel nivel){
        ///method/API syntax
        ///return AngajatRepository.FindAll().Where(x=>x.Nivel==nivel).ToList();
        
        ///query syntax
        return (from e in AngajatRepository.FindAll() where e.Nivel==nivel select e).ToList();
    }

    public List<Angajat> findAngajatiOrderedByNivelAndVenit(){
        ///cu method
        ///return AngajatRepository.FindAll().OrderBy(e => e.Nivel).ThenByDescending(e => e.VenitPeOra).ToList();
        
        ///cu query syntax
        return (from e in AngajatRepository.FindAll() orderby e.Nivel, e.VenitPeOra descending select e).ToList();
    }

    public List<KeyValuePair<Dificultate, double>> getAvgTimePerSarcina(){
        /*//cu query
        return (from s in SarcinaRepository.FindAll()
            group s by s.Dificultate
            into g
            select new KeyValuePair<Dificultate, double>(g.Key, g.Average(s => s.NrOreEstimate))).ToList();*/
        
        //cu method
        return SarcinaRepository.FindAll()
            .GroupBy(s => s.Dificultate)
            .Select(g => new KeyValuePair<Dificultate, double>(g.Key, g.Average(s => s.NrOreEstimate)))
            .ToList();
    }
    
    public List<KeyValuePair<string,float>> findBestPaidEmployees(){
        /*//cu query
        return (from p in PontajRepository.FindAll() 
            group p by p.Angajat into g
            let salariu = g.Sum(p => p.Sarcina.NrOreEstimate*p.Angajat.VenitPeOra)
            orderby salariu descending
            select new KeyValuePair<string,float>(g.Key.Nume,salariu)).Take(2).ToList();*/
        
        ///cu method syntax
        return PontajRepository.FindAll()
            .GroupBy(p => p.Angajat)
            .Select(g =>
                new KeyValuePair<string, float>(g.Key.Nume, g.Sum(p => p.Sarcina.NrOreEstimate * p.Angajat.VenitPeOra)))
            .OrderByDescending(p => p.Value)
            .Take(2)
            .ToList();
    }
    
}

