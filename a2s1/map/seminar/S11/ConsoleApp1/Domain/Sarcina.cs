namespace ConsoleApp1;

public enum Dificultate
{
    Usoara,Medie,Grea
}

public class Sarcina:Entity<string>
{
    public Dificultate Dificultate { get; set; }
    public int NrOreEstimate { get; set; }

    public override string ToString()
    {
        return Id+"-"+ Dificultate +"-"+NrOreEstimate;
    }
}