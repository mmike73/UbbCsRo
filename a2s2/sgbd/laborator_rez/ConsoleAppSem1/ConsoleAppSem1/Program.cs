using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Data.SqlClient;

namespace ConsoleAppSem1
{
    class Program
    {
        static void Main(string[] args)
        {
            Console.ForegroundColor = ConsoleColor.Yellow;
            Console.BackgroundColor = ConsoleColor.Red;
            Console.Clear();
            Console.WriteLine("HW!");

            string connectionString = @"Server=192.168.64.1,1433;Database=SemSGBD;User Id=sa;Password=Bullshit@_1234;TrustServerCertificate=True;";

            try
            {
                using (SqlConnection con = new SqlConnection(connectionString))
                {
                    Console.WriteLine(con.State);
                    con.Open();
                    Console.WriteLine(con.State);


                    SqlCommand insertCommand = new SqlCommand(" INSERT INTO Produse(nume, pret, producator) VALUES " +
                        "(@nume1, @pret1, @prod1), (@nume2, @pret2, @prod2);", con);
                    insertCommand.Parameters.AddWithValue("@nume1", "plastelina");
                    insertCommand.Parameters.AddWithValue("@pret1", 20);
                    insertCommand.Parameters.AddWithValue("@prod1", "Playdoh");
                    insertCommand.Parameters.AddWithValue("@nume2", "franzela");
                    insertCommand.Parameters.AddWithValue("@pret2", 50);
                    insertCommand.Parameters.AddWithValue("@prod2", "Panemar");

                    //int insertRowCount = insertCommand.ExecuteNonQuery();
                    //Console.WriteLine("Insert row count: {0}", insertRowCount);

                    Console.WriteLine("Citirea si afisarea datelor dini tabelul Produse");
                    SqlCommand selectedCommand = new SqlCommand("SELECT nume, pret, producator FROM Produse", con);
                    SqlDataReader reader = selectedCommand.ExecuteReader();

                    if (reader.HasRows)
                    {
                        while (reader.Read())
                        {
                            Console.WriteLine("{0}\t{1}\t{2}", reader.GetString(0), reader.GetFloat(1), reader.GetString(2));
                        }
                    }

                    reader.Close();
                }

            }
            catch (Exception ex)
            {
                Console.WriteLine(ex.Message);
            }
        }
    }
}
