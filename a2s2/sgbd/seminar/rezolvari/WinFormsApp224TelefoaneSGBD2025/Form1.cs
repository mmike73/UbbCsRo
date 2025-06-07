using Microsoft.Data.SqlClient;
using System.Data;
namespace WinFormsApp224TelefoaneSGBD2025
{
    public partial class Form1 : Form
    {
        DataSet ds = new DataSet();
        SqlDataAdapter parentAdapter = new SqlDataAdapter();
        SqlDataAdapter childAdapter = new SqlDataAdapter();
        string connectionString = @"Server=DESKTOP-T42EI2V;Database=Seminar2224SGBD2025;Integrated Security=true;
        TrustServerCertificate=true;";
        BindingSource bsParent = new BindingSource();
        BindingSource bsChild = new BindingSource();

        public Form1()
        {
            InitializeComponent();
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            try
            {
                using(SqlConnection con = new SqlConnection(connectionString))
                {
                    con.Open();
                    parentAdapter.SelectCommand = new SqlCommand("SELECT * FROM Producatori;", con);
                    childAdapter.SelectCommand = new SqlCommand("SELECT * FROM Telefoane;", con);
                    parentAdapter.Fill(ds, "Producatori");
                    childAdapter.Fill(ds, "Telefoane");
                    DataColumn pkColumn = ds.Tables["Producatori"].Columns["cod_p"];
                    DataColumn fkColumn = ds.Tables["Telefoane"].Columns["cod_p"];
                    DataRelation relation = new DataRelation("FK_Producatori_Telefoane", pkColumn, fkColumn, true);
                    ds.Relations.Add(relation);
                    bsParent.DataSource = ds.Tables["Producatori"];
                    dataGridViewParent.DataSource = bsParent;
                    textBox1.DataBindings.Add("Text", bsParent, "nume", true);
                    bsChild.DataSource = bsParent;
                    bsChild.DataMember = "FK_Producatori_Telefoane";
                    dataGridViewChild.DataSource = bsChild;
                }
                
            }
            catch(Exception ex)
            {
                MessageBox.Show(ex.Message);
            }
        }

        private void button1_Click(object sender, EventArgs e)
        {
            try
            {
                using(SqlConnection con = new SqlConnection(connectionString))
                {
                    /* daca folosim doar SqlDataAdapters, putem omite deschiderea explicita a conexiunii, 
                     * deoarece SqlDataAdapters deschid si inchid automat conexiunea atunci cand este 
                     * apelata metoda Fill()
                     */
                    parentAdapter.SelectCommand.Connection = con;
                    childAdapter.SelectCommand.Connection = con;
                    if (ds.Tables.Contains("Telefoane"))
                    {
                        ds.Tables["Telefoane"].Clear();

                    }
                    if (ds.Tables.Contains("Producatori"))
                    {
                        ds.Tables["Producatori"].Clear();
                    }
                    parentAdapter.Fill(ds, "Producatori");
                    childAdapter.Fill(ds,"Telefoane");

                }
            }
            catch(Exception ex)
            {
                MessageBox.Show(ex.Message);
            }
        }
    }
}
