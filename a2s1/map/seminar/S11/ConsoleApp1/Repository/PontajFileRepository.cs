using Microsoft.VisualBasic;

namespace ConsoleApp1.Repository;

public class PontajFileRepository : FileRepository<Pontaj , Tuple<string,string>>{
    private const string dateFormat = "yyyy:MM:dd";
    public PontajFileRepository(string filePath , string filePathAngajati, string filePathSarcini) : base(filePath, StringToEntity, EntityToString){
        ReadSubEntities(filePathAngajati, filePathSarcini);
    }

    private void ReadSubEntities(string filePathAngajati, string filePathSarcini){
        List<Angajat> angajati = base.ReadFromFile(filePathAngajati, AngajatFileRepository.StringToEntity);
        List<Sarcina> sarcini = base.ReadFromFile(filePathSarcini, SarcinaFileRepository.StringToEntity);
        foreach (var value in base.Dictionary.Values){
            value.Angajat = angajati.Find(x => x.Id == value.Id.Item1);
            value.Sarcina = sarcini.Find(x => x.Id == value.Id.Item2);
        }
    }

    public static Pontaj StringToEntity(string line){
        string[] campuri = line.Split(',');
        string idAngajat = campuri[0];
        string idSarcina = campuri[1];
        DateTime data = DateTime.ParseExact(campuri[2],dateFormat, System.Globalization.CultureInfo.InvariantCulture);
        Pontaj p = new Pontaj();
        p.Id = new Tuple<string,string>(idAngajat,idSarcina);
        p.Data = data;
        return p;
    }
    
    public static string EntityToString(Pontaj p){
        return p.Id.Item1 + "," + p.Id.Item2 + "," + p.Data.ToString(dateFormat);
    }
}