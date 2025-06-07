namespace ConsoleApp1.Repository;

public class SarcinaFileRepository:FileRepository<Sarcina,string>
{
    public SarcinaFileRepository(string filePath) : base(filePath, StringToEntity, EntityToString){}
    public static Sarcina StringToEntity(string line)
    {
        string[] tokens = line.Split(',');
        string id = tokens[0];
        Dificultate dificultate = (Dificultate)Enum.Parse(typeof(Dificultate), tokens[1]);
        int nrOreEstimate = int.Parse(tokens[2]);
        return new Sarcina { Id= id, Dificultate = dificultate, NrOreEstimate = nrOreEstimate };
    }

    public static string EntityToString(Sarcina sarcina)
    {
        return sarcina.Id + "," + sarcina.Dificultate + "," + sarcina.NrOreEstimate;
    }
}