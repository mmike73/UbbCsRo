namespace ConsoleApp1.Repository;

public class AngajatFileRepository: FileRepository<Angajat, string>
{
    public AngajatFileRepository(string filePath) : base(filePath, StringToEntity, EntityToString){}
    public static Angajat StringToEntity(string line)
    {
        string[] tokens = line.Split(',');
        string id = tokens[0];
        string name = tokens[1];
        float venitPeOra = float.Parse(tokens[2]);
        Nivel nivel = (Nivel)Enum.Parse(typeof(Nivel), tokens[3]);
        return new Angajat { Id= id, Nivel = nivel, Nume = name, VenitPeOra = venitPeOra };
    }

    public static string EntityToString(Angajat angajat)
    {
        return angajat.Id + "," + angajat.Nume + "," + angajat.VenitPeOra + "," + angajat.Nivel;
    }
    
}