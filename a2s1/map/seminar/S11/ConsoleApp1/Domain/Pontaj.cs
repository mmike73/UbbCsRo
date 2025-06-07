namespace ConsoleApp1;

public class Pontaj:Entity<Tuple<string,string>>
{
    public Angajat Angajat  { get; set; }
    public Sarcina Sarcina  { get; set; }
    public DateTime Data { get; set; }

    public override string ToString()
    {
        return Angajat + " "+ Sarcina +" "+ Data.ToString("dd/MM/yyyy");
    }
}