namespace PcPartsManagerApp
{
    partial class Form1
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
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
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.dataGridViewParent = new System.Windows.Forms.DataGridView();
            this.dataGridViewChild = new System.Windows.Forms.DataGridView();
            this.textBoxModel1 = new System.Windows.Forms.TextBox();
            this.label1 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.label3 = new System.Windows.Forms.Label();
            this.label4 = new System.Windows.Forms.Label();
            this.label5 = new System.Windows.Forms.Label();
            this.label6 = new System.Windows.Forms.Label();
            this.label7 = new System.Windows.Forms.Label();
            this.label8 = new System.Windows.Forms.Label();
            this.label9 = new System.Windows.Forms.Label();
            this.label10 = new System.Windows.Forms.Label();
            this.textBoxBus1 = new System.Windows.Forms.TextBox();
            this.textBoxBoost1 = new System.Windows.Forms.TextBox();
            this.textBoxBase1 = new System.Windows.Forms.TextBox();
            this.textBoxMemory1 = new System.Windows.Forms.TextBox();
            this.textBoxVram1 = new System.Windows.Forms.TextBox();
            this.textBoxSlot1 = new System.Windows.Forms.TextBox();
            this.textBoxPower1 = new System.Windows.Forms.TextBox();
            this.textBoxPrice1 = new System.Windows.Forms.TextBox();
            this.button1 = new System.Windows.Forms.Button();
            this.button2 = new System.Windows.Forms.Button();
            this.textBoxPrice2 = new System.Windows.Forms.TextBox();
            this.textBoxPower2 = new System.Windows.Forms.TextBox();
            this.textBoxSlot2 = new System.Windows.Forms.TextBox();
            this.textBoxVram2 = new System.Windows.Forms.TextBox();
            this.textBoxMemory2 = new System.Windows.Forms.TextBox();
            this.textBoxBase2 = new System.Windows.Forms.TextBox();
            this.textBoxBoost2 = new System.Windows.Forms.TextBox();
            this.textBoxBus2 = new System.Windows.Forms.TextBox();
            this.label11 = new System.Windows.Forms.Label();
            this.label12 = new System.Windows.Forms.Label();
            this.label13 = new System.Windows.Forms.Label();
            this.label14 = new System.Windows.Forms.Label();
            this.label15 = new System.Windows.Forms.Label();
            this.label16 = new System.Windows.Forms.Label();
            this.label17 = new System.Windows.Forms.Label();
            this.label18 = new System.Windows.Forms.Label();
            this.label19 = new System.Windows.Forms.Label();
            this.label20 = new System.Windows.Forms.Label();
            this.textBoxModel2 = new System.Windows.Forms.TextBox();
            this.button3 = new System.Windows.Forms.Button();
            ((System.ComponentModel.ISupportInitialize)(this.dataGridViewParent)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.dataGridViewChild)).BeginInit();
            this.SuspendLayout();
            // 
            // dataGridViewParent
            // 
            this.dataGridViewParent.BackgroundColor = System.Drawing.SystemColors.InactiveCaption;
            this.dataGridViewParent.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.dataGridViewParent.Location = new System.Drawing.Point(13, 13);
            this.dataGridViewParent.MultiSelect = false;
            this.dataGridViewParent.Name = "dataGridViewParent";
            this.dataGridViewParent.Size = new System.Drawing.Size(304, 150);
            this.dataGridViewParent.TabIndex = 0;
            // 
            // dataGridViewChild
            // 
            this.dataGridViewChild.BackgroundColor = System.Drawing.SystemColors.InactiveCaption;
            this.dataGridViewChild.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.dataGridViewChild.Location = new System.Drawing.Point(323, 14);
            this.dataGridViewChild.MultiSelect = false;
            this.dataGridViewChild.Name = "dataGridViewChild";
            this.dataGridViewChild.ReadOnly = true;
            this.dataGridViewChild.Size = new System.Drawing.Size(551, 150);
            this.dataGridViewChild.TabIndex = 1;
            this.dataGridViewChild.CellClick += new System.Windows.Forms.DataGridViewCellEventHandler(this.dataGridViewChild_CellClick);
            this.dataGridViewChild.CellValueChanged += new System.Windows.Forms.DataGridViewCellEventHandler(this.dataGridViewChild_CellValueChanged);
            // 
            // textBoxModel1
            // 
            this.textBoxModel1.Location = new System.Drawing.Point(217, 217);
            this.textBoxModel1.Name = "textBoxModel1";
            this.textBoxModel1.Size = new System.Drawing.Size(100, 20);
            this.textBoxModel1.TabIndex = 2;
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(10, 185);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(206, 13);
            this.label1.TabIndex = 3;
            this.label1.Text = "New GPU with the selected manufacturer:";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(10, 220);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(39, 13);
            this.label2.TabIndex = 4;
            this.label2.Text = "Model:";
            this.label2.Click += new System.EventHandler(this.label2_Click);
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(10, 246);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(28, 13);
            this.label3.TabIndex = 5;
            this.label3.Text = "Slot:";
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(10, 272);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(64, 13);
            this.label4.TabIndex = 6;
            this.label4.Text = "VRAM type:";
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Location = new System.Drawing.Point(10, 298);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(92, 13);
            this.label5.TabIndex = 7;
            this.label5.Text = "Memory size (GB):";
            // 
            // label6
            // 
            this.label6.AutoSize = true;
            this.label6.Location = new System.Drawing.Point(10, 324);
            this.label6.Name = "label6";
            this.label6.Size = new System.Drawing.Size(93, 13);
            this.label6.TabIndex = 8;
            this.label6.Text = "Base clock (GHz):";
            // 
            // label7
            // 
            this.label7.AutoSize = true;
            this.label7.Location = new System.Drawing.Point(10, 350);
            this.label7.Name = "label7";
            this.label7.Size = new System.Drawing.Size(96, 13);
            this.label7.TabIndex = 9;
            this.label7.Text = "Boost clock (GHz):";
            // 
            // label8
            // 
            this.label8.AutoSize = true;
            this.label8.Location = new System.Drawing.Point(10, 380);
            this.label8.Name = "label8";
            this.label8.Size = new System.Drawing.Size(67, 13);
            this.label8.TabIndex = 10;
            this.label8.Text = "Memory bus:";
            // 
            // label9
            // 
            this.label9.AutoSize = true;
            this.label9.Location = new System.Drawing.Point(10, 406);
            this.label9.Name = "label9";
            this.label9.Size = new System.Drawing.Size(60, 13);
            this.label9.TabIndex = 11;
            this.label9.Text = "Power (W):";
            // 
            // label10
            // 
            this.label10.AutoSize = true;
            this.label10.Location = new System.Drawing.Point(10, 431);
            this.label10.Name = "label10";
            this.label10.Size = new System.Drawing.Size(34, 13);
            this.label10.TabIndex = 12;
            this.label10.Text = "Price:";
            // 
            // textBoxBus1
            // 
            this.textBoxBus1.Location = new System.Drawing.Point(217, 377);
            this.textBoxBus1.Name = "textBoxBus1";
            this.textBoxBus1.Size = new System.Drawing.Size(100, 20);
            this.textBoxBus1.TabIndex = 13;
            // 
            // textBoxBoost1
            // 
            this.textBoxBoost1.Location = new System.Drawing.Point(217, 347);
            this.textBoxBoost1.Name = "textBoxBoost1";
            this.textBoxBoost1.Size = new System.Drawing.Size(100, 20);
            this.textBoxBoost1.TabIndex = 14;
            // 
            // textBoxBase1
            // 
            this.textBoxBase1.Location = new System.Drawing.Point(217, 321);
            this.textBoxBase1.Name = "textBoxBase1";
            this.textBoxBase1.Size = new System.Drawing.Size(100, 20);
            this.textBoxBase1.TabIndex = 15;
            // 
            // textBoxMemory1
            // 
            this.textBoxMemory1.Location = new System.Drawing.Point(217, 295);
            this.textBoxMemory1.Name = "textBoxMemory1";
            this.textBoxMemory1.Size = new System.Drawing.Size(100, 20);
            this.textBoxMemory1.TabIndex = 16;
            // 
            // textBoxVram1
            // 
            this.textBoxVram1.Location = new System.Drawing.Point(217, 269);
            this.textBoxVram1.Name = "textBoxVram1";
            this.textBoxVram1.Size = new System.Drawing.Size(100, 20);
            this.textBoxVram1.TabIndex = 17;
            // 
            // textBoxSlot1
            // 
            this.textBoxSlot1.Location = new System.Drawing.Point(217, 243);
            this.textBoxSlot1.Name = "textBoxSlot1";
            this.textBoxSlot1.Size = new System.Drawing.Size(100, 20);
            this.textBoxSlot1.TabIndex = 18;
            // 
            // textBoxPower1
            // 
            this.textBoxPower1.Location = new System.Drawing.Point(217, 403);
            this.textBoxPower1.Name = "textBoxPower1";
            this.textBoxPower1.Size = new System.Drawing.Size(100, 20);
            this.textBoxPower1.TabIndex = 19;
            // 
            // textBoxPrice1
            // 
            this.textBoxPrice1.Location = new System.Drawing.Point(217, 428);
            this.textBoxPrice1.Name = "textBoxPrice1";
            this.textBoxPrice1.Size = new System.Drawing.Size(100, 20);
            this.textBoxPrice1.TabIndex = 20;
            // 
            // button1
            // 
            this.button1.ForeColor = System.Drawing.Color.Green;
            this.button1.Location = new System.Drawing.Point(13, 454);
            this.button1.Name = "button1";
            this.button1.Size = new System.Drawing.Size(304, 35);
            this.button1.TabIndex = 21;
            this.button1.Text = "Add GPU";
            this.button1.UseVisualStyleBackColor = true;
            this.button1.Click += new System.EventHandler(this.AddGPU_Click);
            // 
            // button2
            // 
            this.button2.ForeColor = System.Drawing.Color.Green;
            this.button2.Location = new System.Drawing.Point(379, 454);
            this.button2.Name = "button2";
            this.button2.Size = new System.Drawing.Size(167, 35);
            this.button2.TabIndex = 41;
            this.button2.Text = "Edit GPU";
            this.button2.UseVisualStyleBackColor = true;
            this.button2.Click += new System.EventHandler(this.EditGPU_Click);
            // 
            // textBoxPrice2
            // 
            this.textBoxPrice2.Location = new System.Drawing.Point(594, 428);
            this.textBoxPrice2.Name = "textBoxPrice2";
            this.textBoxPrice2.Size = new System.Drawing.Size(100, 20);
            this.textBoxPrice2.TabIndex = 40;
            // 
            // textBoxPower2
            // 
            this.textBoxPower2.Location = new System.Drawing.Point(594, 403);
            this.textBoxPower2.Name = "textBoxPower2";
            this.textBoxPower2.Size = new System.Drawing.Size(100, 20);
            this.textBoxPower2.TabIndex = 39;
            // 
            // textBoxSlot2
            // 
            this.textBoxSlot2.Location = new System.Drawing.Point(594, 243);
            this.textBoxSlot2.Name = "textBoxSlot2";
            this.textBoxSlot2.Size = new System.Drawing.Size(100, 20);
            this.textBoxSlot2.TabIndex = 38;
            // 
            // textBoxVram2
            // 
            this.textBoxVram2.Location = new System.Drawing.Point(594, 269);
            this.textBoxVram2.Name = "textBoxVram2";
            this.textBoxVram2.Size = new System.Drawing.Size(100, 20);
            this.textBoxVram2.TabIndex = 37;
            // 
            // textBoxMemory2
            // 
            this.textBoxMemory2.Location = new System.Drawing.Point(594, 295);
            this.textBoxMemory2.Name = "textBoxMemory2";
            this.textBoxMemory2.Size = new System.Drawing.Size(100, 20);
            this.textBoxMemory2.TabIndex = 36;
            // 
            // textBoxBase2
            // 
            this.textBoxBase2.Location = new System.Drawing.Point(594, 321);
            this.textBoxBase2.Name = "textBoxBase2";
            this.textBoxBase2.Size = new System.Drawing.Size(100, 20);
            this.textBoxBase2.TabIndex = 35;
            // 
            // textBoxBoost2
            // 
            this.textBoxBoost2.Location = new System.Drawing.Point(594, 347);
            this.textBoxBoost2.Name = "textBoxBoost2";
            this.textBoxBoost2.Size = new System.Drawing.Size(100, 20);
            this.textBoxBoost2.TabIndex = 34;
            // 
            // textBoxBus2
            // 
            this.textBoxBus2.Location = new System.Drawing.Point(594, 377);
            this.textBoxBus2.Name = "textBoxBus2";
            this.textBoxBus2.Size = new System.Drawing.Size(100, 20);
            this.textBoxBus2.TabIndex = 33;
            // 
            // label11
            // 
            this.label11.AutoSize = true;
            this.label11.Location = new System.Drawing.Point(387, 431);
            this.label11.Name = "label11";
            this.label11.Size = new System.Drawing.Size(34, 13);
            this.label11.TabIndex = 32;
            this.label11.Text = "Price:";
            // 
            // label12
            // 
            this.label12.AutoSize = true;
            this.label12.Location = new System.Drawing.Point(387, 406);
            this.label12.Name = "label12";
            this.label12.Size = new System.Drawing.Size(60, 13);
            this.label12.TabIndex = 31;
            this.label12.Text = "Power (W):";
            // 
            // label13
            // 
            this.label13.AutoSize = true;
            this.label13.Location = new System.Drawing.Point(387, 380);
            this.label13.Name = "label13";
            this.label13.Size = new System.Drawing.Size(67, 13);
            this.label13.TabIndex = 30;
            this.label13.Text = "Memory bus:";
            // 
            // label14
            // 
            this.label14.AutoSize = true;
            this.label14.Location = new System.Drawing.Point(387, 350);
            this.label14.Name = "label14";
            this.label14.Size = new System.Drawing.Size(96, 13);
            this.label14.TabIndex = 29;
            this.label14.Text = "Boost clock (GHz):";
            // 
            // label15
            // 
            this.label15.AutoSize = true;
            this.label15.Location = new System.Drawing.Point(387, 324);
            this.label15.Name = "label15";
            this.label15.Size = new System.Drawing.Size(93, 13);
            this.label15.TabIndex = 28;
            this.label15.Text = "Base clock (GHz):";
            // 
            // label16
            // 
            this.label16.AutoSize = true;
            this.label16.Location = new System.Drawing.Point(387, 298);
            this.label16.Name = "label16";
            this.label16.Size = new System.Drawing.Size(92, 13);
            this.label16.TabIndex = 27;
            this.label16.Text = "Memory size (GB):";
            // 
            // label17
            // 
            this.label17.AutoSize = true;
            this.label17.Location = new System.Drawing.Point(387, 272);
            this.label17.Name = "label17";
            this.label17.Size = new System.Drawing.Size(64, 13);
            this.label17.TabIndex = 26;
            this.label17.Text = "VRAM type:";
            // 
            // label18
            // 
            this.label18.AutoSize = true;
            this.label18.Location = new System.Drawing.Point(387, 246);
            this.label18.Name = "label18";
            this.label18.Size = new System.Drawing.Size(28, 13);
            this.label18.TabIndex = 25;
            this.label18.Text = "Slot:";
            // 
            // label19
            // 
            this.label19.AutoSize = true;
            this.label19.Location = new System.Drawing.Point(387, 220);
            this.label19.Name = "label19";
            this.label19.Size = new System.Drawing.Size(39, 13);
            this.label19.TabIndex = 24;
            this.label19.Text = "Model:";
            // 
            // label20
            // 
            this.label20.AutoSize = true;
            this.label20.Location = new System.Drawing.Point(387, 185);
            this.label20.Name = "label20";
            this.label20.Size = new System.Drawing.Size(206, 13);
            this.label20.TabIndex = 23;
            this.label20.Text = "New GPU with the selected manufacturer:";
            // 
            // textBoxModel2
            // 
            this.textBoxModel2.Location = new System.Drawing.Point(594, 217);
            this.textBoxModel2.Name = "textBoxModel2";
            this.textBoxModel2.Size = new System.Drawing.Size(100, 20);
            this.textBoxModel2.TabIndex = 22;
            // 
            // button3
            // 
            this.button3.ForeColor = System.Drawing.Color.Red;
            this.button3.Location = new System.Drawing.Point(552, 454);
            this.button3.Name = "button3";
            this.button3.Size = new System.Drawing.Size(142, 35);
            this.button3.TabIndex = 42;
            this.button3.Text = "Delete GPU";
            this.button3.UseVisualStyleBackColor = true;
            this.button3.Click += new System.EventHandler(this.DeleteGPU_Click);
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackColor = System.Drawing.SystemColors.Control;
            this.ClientSize = new System.Drawing.Size(886, 494);
            this.Controls.Add(this.button3);
            this.Controls.Add(this.button2);
            this.Controls.Add(this.textBoxPrice2);
            this.Controls.Add(this.textBoxPower2);
            this.Controls.Add(this.textBoxSlot2);
            this.Controls.Add(this.textBoxVram2);
            this.Controls.Add(this.textBoxMemory2);
            this.Controls.Add(this.textBoxBase2);
            this.Controls.Add(this.textBoxBoost2);
            this.Controls.Add(this.textBoxBus2);
            this.Controls.Add(this.label11);
            this.Controls.Add(this.label12);
            this.Controls.Add(this.label13);
            this.Controls.Add(this.label14);
            this.Controls.Add(this.label15);
            this.Controls.Add(this.label16);
            this.Controls.Add(this.label17);
            this.Controls.Add(this.label18);
            this.Controls.Add(this.label19);
            this.Controls.Add(this.label20);
            this.Controls.Add(this.textBoxModel2);
            this.Controls.Add(this.button1);
            this.Controls.Add(this.textBoxPrice1);
            this.Controls.Add(this.textBoxPower1);
            this.Controls.Add(this.textBoxSlot1);
            this.Controls.Add(this.textBoxVram1);
            this.Controls.Add(this.textBoxMemory1);
            this.Controls.Add(this.textBoxBase1);
            this.Controls.Add(this.textBoxBoost1);
            this.Controls.Add(this.textBoxBus1);
            this.Controls.Add(this.label10);
            this.Controls.Add(this.label9);
            this.Controls.Add(this.label8);
            this.Controls.Add(this.label7);
            this.Controls.Add(this.label6);
            this.Controls.Add(this.label5);
            this.Controls.Add(this.label4);
            this.Controls.Add(this.label3);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.textBoxModel1);
            this.Controls.Add(this.dataGridViewChild);
            this.Controls.Add(this.dataGridViewParent);
            this.Name = "Form1";
            this.Text = "Form1";
            this.Load += new System.EventHandler(this.Form1_Load);
            ((System.ComponentModel.ISupportInitialize)(this.dataGridViewParent)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.dataGridViewChild)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.DataGridView dataGridViewParent;
        private System.Windows.Forms.DataGridView dataGridViewChild;
        private System.Windows.Forms.TextBox textBoxModel1;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.Label label6;
        private System.Windows.Forms.Label label7;
        private System.Windows.Forms.Label label8;
        private System.Windows.Forms.Label label9;
        private System.Windows.Forms.Label label10;
        private System.Windows.Forms.TextBox textBoxBus1;
        private System.Windows.Forms.TextBox textBoxBoost1;
        private System.Windows.Forms.TextBox textBoxBase1;
        private System.Windows.Forms.TextBox textBoxMemory1;
        private System.Windows.Forms.TextBox textBoxVram1;
        private System.Windows.Forms.TextBox textBoxSlot1;
        private System.Windows.Forms.TextBox textBoxPower1;
        private System.Windows.Forms.TextBox textBoxPrice1;
        private System.Windows.Forms.Button button1;
        private System.Windows.Forms.Button button2;
        private System.Windows.Forms.TextBox textBoxPrice2;
        private System.Windows.Forms.TextBox textBoxPower2;
        private System.Windows.Forms.TextBox textBoxSlot2;
        private System.Windows.Forms.TextBox textBoxVram2;
        private System.Windows.Forms.TextBox textBoxMemory2;
        private System.Windows.Forms.TextBox textBoxBase2;
        private System.Windows.Forms.TextBox textBoxBoost2;
        private System.Windows.Forms.TextBox textBoxBus2;
        private System.Windows.Forms.Label label11;
        private System.Windows.Forms.Label label12;
        private System.Windows.Forms.Label label13;
        private System.Windows.Forms.Label label14;
        private System.Windows.Forms.Label label15;
        private System.Windows.Forms.Label label16;
        private System.Windows.Forms.Label label17;
        private System.Windows.Forms.Label label18;
        private System.Windows.Forms.Label label19;
        private System.Windows.Forms.Label label20;
        private System.Windows.Forms.TextBox textBoxModel2;
        private System.Windows.Forms.Button button3;
    }
}

