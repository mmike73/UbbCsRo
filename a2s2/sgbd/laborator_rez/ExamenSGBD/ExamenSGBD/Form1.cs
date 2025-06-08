using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Data.SqlClient;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace ExamenSGBD
{
    public partial class Form1: Form
    {
        private string connectionString = @"Server=192.168.64.1,1433;Database=GestiuneAuto;User Id=sa;Password=Bullshit@_1234;TrustServerCertificate=True;";
        private SqlConnection connection;
        private SqlDataAdapter parentAdapter, childAdapter;
        private DataSet dataset;
        private BindingSource parentBS, childBS;
        private SqlCommandBuilder parentCommandBuilder, childCommandBuilder;
        private string childTableName = "TipColectie", childForeignKey = "", parentTableName = "Masini", parentPrimaryKey = "marca";


        public Form1()
        {
            InitializeComponent();
            connection = new SqlConnection(connectionString);
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            try
            {
                connection.Open();

                dataset = new DataSet();

                parentAdapter = new SqlDataAdapter($"SELECT * FROM {parentTableName} M INNER JOIN {childTableName} C ON M.id_colectie = C.id_colectie", connection);
                parentCommandBuilder = new SqlCommandBuilder(parentAdapter);
                parentAdapter.Fill(dataset, parentTableName);

                childAdapter = new SqlDataAdapter($"SELECT * FROM {parentTableName}", connection);
                childCommandBuilder = new SqlCommandBuilder(childAdapter);
                childAdapter.Fill(dataset, childTableName);

                DataColumn parentPK = dataset.Tables[parentTableName].Columns[parentPrimaryKey];
                DataColumn childFK = dataset.Tables[childTableName].Columns[childForeignKey];

                DataRelation relation = new DataRelation("fk_Parent_Child", parentPK, childFK);
                dataset.Relations.Add(relation);

                parentBS = new BindingSource();
                parentBS.DataSource = dataset.Tables[parentTableName];
                comboBoxMarca.DataSource = parentBS;

                childBS = new BindingSource();
                childBS.DataSource = parentBS;
                childBS.DataMember = "fk_Parent_Child";
                dataGridViewCars.DataSource = childBS;

            }
            catch (Exception err)
            {
                MessageBox.Show(err.Message);
            }
        }
    }
}
