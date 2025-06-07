namespace ConsoleApp1;

public enum Nivel
{
        Junior,Medium,Senior
}

public class Angajat : Entity<string>
{
    public string Nume { get; set; }
    public float VenitPeOra { get; set; }
    public Nivel Nivel { get; set; }

    public override string ToString()
    {
        return Id + "-" + Nume + "-" + VenitPeOra + "-" + Nivel;
    }
}