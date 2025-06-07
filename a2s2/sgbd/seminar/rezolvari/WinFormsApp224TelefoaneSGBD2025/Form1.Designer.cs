namespace WinFormsApp224TelefoaneSGBD2025
{
    partial class Form1
    {
        /// <summary>
        ///  Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        ///  Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        ///  Required method for Designer support - do not modify
        ///  the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            label1 = new Label();
            label2 = new Label();
            dataGridViewParent = new DataGridView();
            dataGridViewChild = new DataGridView();
            label3 = new Label();
            textBox1 = new TextBox();
            button1 = new Button();
            ((System.ComponentModel.ISupportInitialize)dataGridViewParent).BeginInit();
            ((System.ComponentModel.ISupportInitialize)dataGridViewChild).BeginInit();
            SuspendLayout();
            // 
            // label1
            // 
            label1.AutoSize = true;
            label1.Font = new Font("Segoe UI", 12F, FontStyle.Bold, GraphicsUnit.Point, 0);
            label1.ForeColor = Color.Indigo;
            label1.Location = new Point(26, 24);
            label1.Name = "label1";
            label1.Size = new Size(239, 32);
            label1.TabIndex = 0;
            label1.Text = "Tabelul Producatori";
            // 
            // label2
            // 
            label2.AutoSize = true;
            label2.Font = new Font("Segoe UI", 12F, FontStyle.Bold, GraphicsUnit.Point, 0);
            label2.ForeColor = Color.Indigo;
            label2.Location = new Point(714, 24);
            label2.Name = "label2";
            label2.Size = new Size(213, 32);
            label2.TabIndex = 1;
            label2.Text = "Tabelul Telefoane";
            // 
            // dataGridViewParent
            // 
            dataGridViewParent.ColumnHeadersHeightSizeMode = DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            dataGridViewParent.Location = new Point(26, 68);
            dataGridViewParent.Name = "dataGridViewParent";
            dataGridViewParent.RowHeadersWidth = 62;
            dataGridViewParent.Size = new Size(654, 225);
            dataGridViewParent.TabIndex = 2;
            // 
            // dataGridViewChild
            // 
            dataGridViewChild.ColumnHeadersHeightSizeMode = DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            dataGridViewChild.Location = new Point(714, 68);
            dataGridViewChild.Name = "dataGridViewChild";
            dataGridViewChild.RowHeadersWidth = 62;
            dataGridViewChild.Size = new Size(792, 225);
            dataGridViewChild.TabIndex = 3;
            // 
            // label3
            // 
            label3.AutoSize = true;
            label3.Font = new Font("Segoe UI", 12F, FontStyle.Bold, GraphicsUnit.Point, 0);
            label3.ForeColor = Color.Indigo;
            label3.Location = new Point(26, 319);
            label3.Name = "label3";
            label3.Size = new Size(377, 32);
            label3.TabIndex = 4;
            label3.Text = "Numele producatorului selectat";
            // 
            // textBox1
            // 
            textBox1.Location = new Point(26, 364);
            textBox1.Name = "textBox1";
            textBox1.Size = new Size(654, 31);
            textBox1.TabIndex = 5;
            // 
            // button1
            // 
            button1.Font = new Font("Segoe UI", 11F, FontStyle.Bold, GraphicsUnit.Point, 0);
            button1.ForeColor = Color.Indigo;
            button1.Location = new Point(26, 418);
            button1.Name = "button1";
            button1.Size = new Size(221, 76);
            button1.TabIndex = 6;
            button1.Text = "Reload Data";
            button1.UseVisualStyleBackColor = true;
            button1.Click += button1_Click;
            // 
            // Form1
            // 
            AutoScaleDimensions = new SizeF(10F, 25F);
            AutoScaleMode = AutoScaleMode.Font;
            BackColor = Color.LightSkyBlue;
            ClientSize = new Size(1518, 588);
            Controls.Add(button1);
            Controls.Add(textBox1);
            Controls.Add(label3);
            Controls.Add(dataGridViewChild);
            Controls.Add(dataGridViewParent);
            Controls.Add(label2);
            Controls.Add(label1);
            Name = "Form1";
            Text = "Telefoane 224";
            Load += Form1_Load;
            ((System.ComponentModel.ISupportInitialize)dataGridViewParent).EndInit();
            ((System.ComponentModel.ISupportInitialize)dataGridViewChild).EndInit();
            ResumeLayout(false);
            PerformLayout();
        }

        #endregion

        private Label label1;
        private Label label2;
        private DataGridView dataGridViewParent;
        private DataGridView dataGridViewChild;
        private Label label3;
        private TextBox textBox1;
        private Button button1;
    }
}
