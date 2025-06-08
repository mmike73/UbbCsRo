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
using static System.Windows.Forms.VisualStyles.VisualStyleElement;

namespace PcPartsManagerApp
{
    public partial class Form1: Form
    {
        string connectionString = @"Server=192.168.64.1,1433;Database=PcPartsManager;User Id=sa;Password=Bullshit@_1234;TrustServerCertificate=True;";

        public Form1()
        {
            InitializeComponent();
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            try
            {
                using (SqlConnection connection = new SqlConnection(connectionString))
                {
                    connection.Open();

                    //MessageBox.Show("Starea conectiunii: " + connection.State.ToString());

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

        private void dataGridViewChild_CellClick(object sender, DataGridViewCellEventArgs e)
        {
            if (e.RowIndex >= 0)
            {
                DataGridViewRow row = dataGridViewChild.Rows[e.RowIndex];
                textBoxModel2.Text = row.Cells["model"].Value.ToString();
                textBoxSlot2.Text = row.Cells["slot"].Value.ToString();
                textBoxVram2.Text = row.Cells["vramType"].Value.ToString();
                textBoxMemory2.Text = row.Cells["sizeGb"].Value.ToString();
                textBoxBase2.Text = row.Cells["baseClock"].Value.ToString();
                textBoxBoost2.Text = row.Cells["boostClock"].Value.ToString();
                textBoxBus2.Text = row.Cells["memoryBus"].Value.ToString();
                textBoxPower2.Text = row.Cells["powerW"].Value.ToString();
                textBoxPrice2.Text = row.Cells["price"].Value.ToString();
            }
        }

        private void DeleteGPU_Click(object sender, EventArgs e)
        {        
            if (dataGridViewChild.SelectedRows.Count > 0)
            {
                foreach (DataGridViewRow row in dataGridViewChild.SelectedRows)
                {
                    var gpuId = row.Cells["gpuId"].Value;

                    try
                    {
                        using (SqlConnection connection = new SqlConnection(connectionString))
                        {
                            connection.Open();

                            SqlCommand deleteCommand = new SqlCommand("DELETE FROM GPUs WHERE gpuId=@gpuId", connection);

                            deleteCommand.Parameters.AddWithValue("@gpuId", gpuId);

                            deleteCommand.ExecuteNonQuery();

                            MessageBox.Show("GPU deleted successfully!");

                            Form1_Load(null, null);

                            connection.Close();
                        }

                    }
                    catch (Exception err)
                    {
                        MessageBox.Show(err.Message.ToString());
                    }

                }
            }
        }


        private void EditGPU_Click(object sender, EventArgs e)
        {
            if (dataGridViewChild.SelectedRows.Count > 0)
            {
                foreach (DataGridViewRow row in dataGridViewChild.SelectedRows)
                {
                    var gpuId = row.Cells["gpuId"].Value;

                    try
                    {
                        using (SqlConnection connection = new SqlConnection(connectionString))
                        {
                            connection.Open();

                            SqlCommand updateCommand = new SqlCommand("UPDATE GPUs SET model=@model, slot=@slot, vramType=@vramType, sizeGb=@sizeGb, baseClock=@baseClock, boostClock=@boostClock, memoryBus=@memoryBus, powerW=@power, price=@price  WHERE gpuId=@gpuId", connection);

                            string model = textBoxModel2.Text;
                            if (model.Length > 50) throw new Exception("Model should be at most 50 characters long.");

                            string slot = textBoxSlot2.Text;
                            if (slot.Length > 10) throw new Exception("Slot should be at most 10 characters long.");

                            string vram = textBoxVram2.Text;
                            if (vram.Length > 10) throw new Exception("Vram should be at most 10 characters long.");

                            int memory =Int32.Parse(textBoxMemory2.Text);

                            int baseClock = Int32.Parse(textBoxBase2.Text);

                            int boostClock = Int32.Parse(textBoxBoost2.Text);

                            int bus = Int32.Parse(textBoxBus2.Text);

                            int power = Int16.Parse(textBoxPower2.Text);

                            int price = Int16.Parse(textBoxPrice2.Text);

                            MessageBox.Show(model + " " + slot + " " + vram + " " + memory + " " + baseClock + " " + boostClock + " " + bus + ' ' + power + " " + price);

                            updateCommand.Parameters.AddWithValue("@model", model);
                            updateCommand.Parameters.AddWithValue("@slot", slot);
                            updateCommand.Parameters.AddWithValue("@vramType", vram);
                            updateCommand.Parameters.AddWithValue("@sizeGb", memory);
                            updateCommand.Parameters.AddWithValue("@baseClock", baseClock);
                            updateCommand.Parameters.AddWithValue("@boostClock", boostClock);
                            updateCommand.Parameters.AddWithValue("@memoryBus", bus);
                            updateCommand.Parameters.AddWithValue("@power", power);
                            updateCommand.Parameters.AddWithValue("@price", price);
                            updateCommand.Parameters.AddWithValue("@gpuId", gpuId);

                            int noRows = updateCommand.ExecuteNonQuery();

                            MessageBox.Show("GPU updated successfully!");

                            Form1_Load(null, null);

                            connection.Close();
                        }

                    }
                    catch (Exception err)
                    {
                        MessageBox.Show(err.Message.ToString());
                    }
                }
            }
        }

        private void AddGPU_Click(object sender, EventArgs e)
        {
            if (dataGridViewParent.SelectedRows.Count > 0)
            {
                foreach (DataGridViewRow row in dataGridViewParent.SelectedRows)
                {
                    var manufacturerId = row.Cells["manufacturerId"].Value;

                    try
                    {
                        using (SqlConnection connection = new SqlConnection(connectionString))
                        {
                            connection.Open();

                            SqlCommand updateCommand = new SqlCommand("INSERT INTO GPUs (manufacturerId, model, slot, vramType, sizeGb, baseClock, boostClock, memoryBus, powerW, price) VALUES (@manufacturerId, @model, @slot, @vramType, @sizeGb, @baseClock, @boostClock, @memoryBus, @power, @price);", connection);

                            string model = textBoxModel1.Text;
                            if (model.Length > 50) throw new Exception("Model should be at most 50 characters long.");

                            string slot = textBoxSlot1.Text;
                            if (slot.Length > 10) throw new Exception("Slot should be at most 10 characters long.");

                            string vram = textBoxVram1.Text;
                            if (vram.Length > 10) throw new Exception("Vram should be at most 10 characters long.");

                            int memory = Int32.Parse(textBoxMemory1.Text);

                            int baseClock = Int32.Parse(textBoxBase1.Text);

                            int boostClock = Int32.Parse(textBoxBoost1.Text);

                            int bus = Int32.Parse(textBoxBus1.Text);

                            int power = Int16.Parse(textBoxPower1.Text);

                            int price = Int16.Parse(textBoxPrice1.Text);

                            //int manufacturerIdInt = Int32.Parse(manufacturerId);

                            MessageBox.Show(model + " " + slot + " " + vram + " " + memory + " " + baseClock + " " + boostClock + " " + bus + ' ' + power + " " + price);
                            
                            updateCommand.Parameters.AddWithValue("@manufacturerId", manufacturerId);
                            updateCommand.Parameters.AddWithValue("@model", model);
                            updateCommand.Parameters.AddWithValue("@slot", slot);
                            updateCommand.Parameters.AddWithValue("@vramType", vram);
                            updateCommand.Parameters.AddWithValue("@sizeGb", memory);
                            updateCommand.Parameters.AddWithValue("@baseClock", baseClock);
                            updateCommand.Parameters.AddWithValue("@boostClock", boostClock);
                            updateCommand.Parameters.AddWithValue("@memoryBus", bus);
                            updateCommand.Parameters.AddWithValue("@power", power);
                            updateCommand.Parameters.AddWithValue("@price", price);

                            int noRows = updateCommand.ExecuteNonQuery();

                            MessageBox.Show("GPU updated successfully!");

                            Form1_Load(null, null);

                            connection.Close();
                        }

                    }
                    catch (Exception err)
                    {
                        MessageBox.Show(err.Message.ToString());
                    }
                }
            }
        }

        //unused
        private void dataGridViewChild_CellValueChanged(object sender, DataGridViewCellEventArgs e)
        {
            
        }

        private void label2_Click(object sender, EventArgs e)
        {

        }
    }
}
;