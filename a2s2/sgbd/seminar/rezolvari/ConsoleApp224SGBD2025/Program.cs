using Microsoft.Data.SqlClient;
namespace ConsoleApp224SGBD2025
{
    internal class Program
    {
        static void Main(string[] args)
        {
            Console.ForegroundColor = ConsoleColor.Yellow;
            Console.BackgroundColor = ConsoleColor.Red;
            Console.Clear();
            Console.WriteLine("Hello, World of ADO.NET!");
            //connectionString trebuie modificat pentru a va putea conecta la instanta SQL Server proprie
            string connectionString = @"Server=DESKTOP-T42EI2V;Database=Seminar1224SGBD2025;Integrated Security
            =true;TrustServerCertificate=true;";
            try
            {
                using(SqlConnection con = new SqlConnection(connectionString))
                {
                    Console.WriteLine("Starea conexiunii: {0}", con.State);
                    //deschiderea conexiunii
                    con.Open();
                    Console.WriteLine("Starea conexiunii: {0}", con.State);
                    //adaugarea datelor
                    SqlCommand insertCommand = new SqlCommand("INSERT INTO Produse (nume, pret, producator) " +
                        "VALUES (@nume1, @pret1, @prod1), (@nume2, @pret2, @prod2);", con);
                    insertCommand.Parameters.AddWithValue("@nume1", "plastelina");
                    insertCommand.Parameters.AddWithValue("@pret1", 20);
                    insertCommand.Parameters.AddWithValue("@prod1", "Playdoh");
                    insertCommand.Parameters.AddWithValue("@nume2", "telefon");
                    insertCommand.Parameters.AddWithValue("@pret2", 7000);
                    insertCommand.Parameters.AddWithValue("@prod2", "Xiaomi");
                    int insertRowCount = insertCommand.ExecuteNonQuery();
                    Console.WriteLine("Insert Row Count: {0}", insertRowCount);
                    //citirea si afisarea datelor
                    Console.WriteLine("Citirea si afisarea datelor din tabelul Produse");
                    SqlCommand selectCommand = new SqlCommand("SELECT nume, pret, producator FROM Produse;", con);
                    SqlDataReader reader = selectCommand.ExecuteReader();
                    if(reader.HasRows)
                    {
                        while(reader.Read())
                        {
                            Console.WriteLine("{0}\t{1}\t{2}", reader.GetString(0), reader.GetFloat(1),
                                reader.GetString(2));
                        }
                    }
                    reader.Close();
                    //actualizarea datelor
                    SqlCommand updateCommand = new SqlCommand("UPDATE Produse SET pret=@pretnou WHERE nume=@nume;", con);
                    updateCommand.Parameters.AddWithValue("@pretnou", 3000);
                    updateCommand.Parameters.AddWithValue("@nume", "plastelina");
                    int updateRowCount = updateCommand.ExecuteNonQuery();
                    Console.WriteLine("Update Row Count: {0}", updateRowCount);
                    //stergerea datelor
                    SqlCommand deleteCommand = new SqlCommand("DELETE FROM Produse WHERE nume=@nume;", con);
                    deleteCommand.Parameters.AddWithValue("@nume", "telefon");
                    /*putem sa apelam direct metoda ExecuteNonQuery() pe obiectul de tip SqlCommand fara a stoca intr-o 
                    variabila numarul de inregistrari afectate de comanda*/
                    int deleteRowCount = deleteCommand.ExecuteNonQuery();
                    Console.WriteLine("Delete Row Count: {0}", deleteRowCount);
                    //citirea si afisarea datelor dupa actualizare si stergere
                    Console.WriteLine("Citirea si afisarea datelor din tabelul Produse dupa actualizare si stergere");
                    reader = selectCommand.ExecuteReader();
                    if (reader.HasRows)
                    {
                        while (reader.Read())
                        {
                            Console.WriteLine("{0}\t{1}\t{2}", reader.GetString(0), reader.GetFloat(1),
                                reader.GetString(2));
                        }
                    }
                    reader.Close();
                }
            }
            catch(Exception ex)
            {
                Console.ForegroundColor = ConsoleColor.Cyan;
                Console.WriteLine("Mesajul exceptiei: {0}", ex.Message);
            }
        }
    }
}
