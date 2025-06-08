using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Data.SqlClient;

namespace PcPartsManagerGui
{
    public partial class Form1: Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            string connectionString = @"Server=192.168.64.1,1433;Database=PcPartsManager;User Id=sa;Password=Bullshit@_1234;TrustServerCertificate=True;";
        
            try
            {
                using (SqlConnection connection = new SqlConnection(connectionString))
                {
                    connection.Open();


                    MessageBox.Show("Starea conectiunii: " + connection.State.ToString());

                    DataSet dataset = new DataSet();

                    SqlDataAdapter parentAdapter = new SqlDataAdapter("SELECT * FROM Manufacturers", connection);
                    SqlDataAdapter childAdapter = new SqlDataAdapter("SELECT * FROM GPUs", connection);

                    parentAdapter.Fill(dataset, "Manufacturers");
                    childAdapter.Fill(dataset, "GPUs");

                    BindingSource parentBS = new BindingSource();
                    BindingSource childBS = new BindingSource();

                    parentBS.DataSource = dataset.Tables["Manufacturers"];
                    dataGridViewParent.DataSource = parentBS;

                    DataColumn parentPK = dataset.Tables["Manufacturers"].Columns["manufacturerId"];

                    DataColumn childFK = dataset.Tables["GPUs"].Columns["manufacturerId"];

                    DataRelation relation = new DataRelation("fk_parent_child", parentPK, childFK);

                    dataset.Relations.Add(relation);

                    childBS.DataSource = parentBS;
                    childBS.DataMember = "fk_parent_child";
                    dataGridViewChild.DataSource = childBS;
                }
            }
            catch (Exception err)
            {
                MessageBox.Show(err.Message.ToString());
            }
        }

        
        private void dataGridViewParent_CellContentClick(object sender, DataGridViewCellEventArgs e)
        {
            if (e.RowIndex >= 0)
            {
                DataGridViewRow row = dataGridViewChild.Rows[e.RowIndex];
                textBox18.Text = row.Cells["model"].Value.ToString();
                textBox17.Text = row.Cells["slot"].Value.ToString();
                textBox16.Text = row.Cells["vramType"].Value.ToString();
                textBox15.Text = row.Cells["sizeGb"].Value.ToString();
                textBox11.Text = row.Cells["baseClock"].Value.ToString();
                textBox10.Text = row.Cells["boostClock"].Value.ToString();
                textBox12.Text = row.Cells["memoryBus"].Value.ToString();
                textBox13.Text = row.Cells["powerW"].Value.ToString();
                textBox14.Text = row.Cells["price"].Value.ToString();
            }
        }


        private void label1_Click(object sender, EventArgs e)
        {

        }

        private void label10_Click(object sender, EventArgs e)
        {

        }

        private void button2_Click(object sender, EventArgs e)
        {

        }

    }
}
