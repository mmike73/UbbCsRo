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
using System.Xml.Linq;

namespace PcPartsManagerGUI2
{
    public partial class Form1: Form
    {
        private string connectionString = @"Server=192.168.64.1,1433;Database=PcPartsManager;User Id=sa;Password=Bullshit@_1234;TrustServerCertificate=True;";
        SqlConnection connection;
        private SqlDataAdapter parentAdapter, childAdapter;
        private DataSet dataset;
        private BindingSource parentBS, childBS;
        private SqlCommandBuilder parentCommandBuilder, childCommandBuilder;
        private string childTableName, childForeignKey, parentTableName, parentPrimaryKey;
        private string childQuery;
       

        public Form1()
        {
            LoadConfiguration();
            InitializeComponent();
            connection = new SqlConnection(connectionString);
            Form1_Load();

        }
        private void Form1_Load()
        {
            
            try
            {
                    connection.Open();

                    dataset = new DataSet();

                    parentAdapter = new SqlDataAdapter($"SELECT * FROM {parentTableName}", connection);
                    parentCommandBuilder = new SqlCommandBuilder(parentAdapter);
                    parentAdapter.Fill(dataset, parentTableName);

                    childAdapter = new SqlDataAdapter($"SELECT * FROM {childTableName}", connection);
                    childCommandBuilder = new SqlCommandBuilder(childAdapter);
                    childAdapter.Fill(dataset, childTableName);

                    DataColumn parentPK = dataset.Tables[parentTableName].Columns[parentPrimaryKey];
                    DataColumn childFK = dataset.Tables[childTableName].Columns[childForeignKey];

                    DataRelation relation = new DataRelation("fk_Parent_Child", parentPK, childFK);
                    dataset.Relations.Add(relation);

                    parentBS = new BindingSource();
                    parentBS.DataSource = dataset.Tables[parentTableName];
                    dataGridViewParent.DataSource = parentBS;

                    childBS = new BindingSource();
                    childBS.DataSource = parentBS;
                    childBS.DataMember = "fk_Parent_Child";
                    dataGridViewChild.DataSource = childBS;
       
            }
            catch (Exception err)
            {
                MessageBox.Show(err.Message);
            }
        }

        private void btnSaveChanges_Click(object sender, EventArgs e)
        {
            try
            {
                    parentAdapter.Update(dataset, parentTableName);
                    childAdapter.Update(dataset, childTableName);
                    MessageBox.Show("Updates successfully made");
            }
            catch (Exception ex)
            {
                MessageBox.Show("Error saving modifications!" + ex.Message, "Error");
            }
        }









        private void dataGridViewParent_CellContentClick(object sender, DataGridViewCellEventArgs e)
        {

        }

        private void btnUpdate_Click(object sender, EventArgs e)
        {

        }

        private void Form1_Load(object sender, EventArgs e)
        {

        }

        private void LoadConfiguration()
        {
            try
            {
                XElement config = XElement.Load("../../config.xml");

                var parentTable = config.Element("masterTable");
                parentTableName = parentTable.Attribute("name").Value;
                parentPrimaryKey = parentTable.Element("primaryKey").Value;

                var childTable = config.Element("detailTable");
                childForeignKey = childTable.Element("foreignKey").Value;
                childTableName = childTable.Attribute("name").Value;
                var childSql = childTable.Element("sql");
                childQuery = childSql.Element("select").Value;

                MessageBox.Show("childQuery");

            }
            catch (Exception ex)
            {
                MessageBox.Show("Couldn't load config file." + ex.Message);
            }
        }

        private void Form1_FormClising(object sender, FormClosingEventArgs e)
        {
            if (connection.State == ConnectionState.Open)
            {
                connection.Close();
            }
        }
    }
}



