using System;
using System.Collections.Generic;
using System.Data.SqlClient;
using System.Linq;
using System.Text;
using System.Threading;

namespace DeadlockSim
{
    class Program
    {
        static string ConStr = @"Server=192.168.64.1,1433;Database=PcPartsManager;User Id=sa;Password=Bullshit@_1234;TrustServerCertificate=True;";

        // fix - the same order
        static void Thread1()
        {
            int attempts = 0;
            while (attempts < 3)
            {
                attempts++;
                using (SqlConnection conn = new SqlConnection(ConStr))
                {
                    conn.Open();
                    SqlTransaction tx = conn.BeginTransaction();

                    try
                    {
                        Console.WriteLine("T1: Locking CPU row");
                        var cmd1 = new SqlCommand("UPDATE CPUs SET model='Intel DEADLOCK31' WHERE cpuId=23155", conn, tx);
                        cmd1.ExecuteNonQuery();

                        Thread.Sleep(1000);

                        Console.WriteLine("T1: Trying to lock Motherboard row");
                        var cmd2 = new SqlCommand("UPDATE Motherboards SET model='Asus DEADLOCK31' WHERE motherboardId=23084", conn, tx);
                        cmd2.ExecuteNonQuery();

                        tx.Commit();
                        return;

                    }
                    catch (Exception ex)
                    {
                        Console.WriteLine("T1: Exception - " + ex.Message);
                        try { tx.Rollback(); } catch { }
                    }
                }
            }
            Console.WriteLine("T1: ABORTED");
        }

        static void Thread2()
        {
            int attempts = 0;
            while (attempts < 3)
            {
                attempts++;
                using (SqlConnection conn = new SqlConnection(ConStr))
                {
                    conn.Open();
                    SqlTransaction tx = conn.BeginTransaction();

                    try
                    {
                        Console.WriteLine("T2: Locking Motherboard row");
                        var cmd1 = new SqlCommand("UPDATE Motherboards SET model='Asus DEADLOCK32' WHERE motherboardId=23084\r\n", conn, tx);
                        cmd1.ExecuteNonQuery();

                        Thread.Sleep(1000);

                        Console.WriteLine("T2: Trying to lock CPU row");
                        var cmd2 = new SqlCommand("UPDATE CPUs SET model='Intel DEADLOCK32' WHERE cpuId=23155", conn, tx);
                        cmd2.ExecuteNonQuery();

                        tx.Commit();
                        return;
                    }
                    catch (Exception ex)
                    {
                        Console.WriteLine("T2 Exception: " + ex.Message);
                        try { tx.Rollback(); } catch { }
                    }
                }
            }
            Console.WriteLine("T2: ABORTED");

        }

        static void Main(string[] args)
        {
            Thread t1 = new Thread(Thread1);
            Thread t2 = new Thread(Thread2);

            t1.Start();
            t2.Start();

            t1.Join();
            t2.Join();

            Console.WriteLine("Execution completed.");
        }
    }
}
