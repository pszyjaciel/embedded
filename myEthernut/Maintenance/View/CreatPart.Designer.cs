namespace View
{
    partial class CreatPart
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
            this.MachineNames = new System.Windows.Forms.ComboBox();
            this.MachineSelectTxt = new System.Windows.Forms.Label();
            this.PartNoTxt = new System.Windows.Forms.Label();
            this.Moduletxt = new System.Windows.Forms.Label();
            this.PanelsMadetxt = new System.Windows.Forms.Label();
            this.PartNo = new System.Windows.Forms.TextBox();
            this.Module = new System.Windows.Forms.TextBox();
            this.PanelsMade = new System.Windows.Forms.TextBox();
            this.Create = new System.Windows.Forms.Button();
            this.Cancel = new System.Windows.Forms.Button();
            this.SuspendLayout();
            // 
            // MachineNames
            // 
            this.MachineNames.FormattingEnabled = true;
            this.MachineNames.Location = new System.Drawing.Point(167, 54);
            this.MachineNames.Name = "MachineNames";
            this.MachineNames.Size = new System.Drawing.Size(164, 24);
            this.MachineNames.TabIndex = 0;
            this.MachineNames.SelectedIndexChanged += new System.EventHandler(this.comboBox1_SelectedIndexChanged);
            // 
            // MachineSelectTxt
            // 
            this.MachineSelectTxt.AutoSize = true;
            this.MachineSelectTxt.Location = new System.Drawing.Point(53, 57);
            this.MachineSelectTxt.Name = "MachineSelectTxt";
            this.MachineSelectTxt.Size = new System.Drawing.Size(108, 17);
            this.MachineSelectTxt.TabIndex = 1;
            this.MachineSelectTxt.Text = "Select Machine:";
            // 
            // PartNoTxt
            // 
            this.PartNoTxt.AutoSize = true;
            this.PartNoTxt.Location = new System.Drawing.Point(53, 88);
            this.PartNoTxt.Name = "PartNoTxt";
            this.PartNoTxt.Size = new System.Drawing.Size(58, 17);
            this.PartNoTxt.TabIndex = 2;
            this.PartNoTxt.Text = "Part no:";
            // 
            // Moduletxt
            // 
            this.Moduletxt.AutoSize = true;
            this.Moduletxt.Location = new System.Drawing.Point(53, 122);
            this.Moduletxt.Name = "Moduletxt";
            this.Moduletxt.Size = new System.Drawing.Size(58, 17);
            this.Moduletxt.TabIndex = 3;
            this.Moduletxt.Text = "Module:";
            // 
            // PanelsMadetxt
            // 
            this.PanelsMadetxt.AutoSize = true;
            this.PanelsMadetxt.Location = new System.Drawing.Point(53, 156);
            this.PanelsMadetxt.Name = "PanelsMadetxt";
            this.PanelsMadetxt.Size = new System.Drawing.Size(90, 17);
            this.PanelsMadetxt.TabIndex = 4;
            this.PanelsMadetxt.Text = "Panels Made";
            // 
            // PartNo
            // 
            this.PartNo.Location = new System.Drawing.Point(167, 88);
            this.PartNo.Name = "PartNo";
            this.PartNo.Size = new System.Drawing.Size(100, 22);
            this.PartNo.TabIndex = 5;
            // 
            // Module
            // 
            this.Module.Location = new System.Drawing.Point(167, 122);
            this.Module.Name = "Module";
            this.Module.Size = new System.Drawing.Size(100, 22);
            this.Module.TabIndex = 6;
            // 
            // PanelsMade
            // 
            this.PanelsMade.Location = new System.Drawing.Point(167, 156);
            this.PanelsMade.Name = "PanelsMade";
            this.PanelsMade.Size = new System.Drawing.Size(100, 22);
            this.PanelsMade.TabIndex = 7;
            // 
            // Create
            // 
            this.Create.Location = new System.Drawing.Point(86, 239);
            this.Create.Name = "Create";
            this.Create.Size = new System.Drawing.Size(75, 29);
            this.Create.TabIndex = 8;
            this.Create.Text = "Create";
            this.Create.UseVisualStyleBackColor = true;
            this.Create.Click += new System.EventHandler(this.Create_Click);
            // 
            // Cancel
            // 
            this.Cancel.Location = new System.Drawing.Point(198, 239);
            this.Cancel.Name = "Cancel";
            this.Cancel.Size = new System.Drawing.Size(75, 29);
            this.Cancel.TabIndex = 9;
            this.Cancel.Text = "Cancel";
            this.Cancel.UseVisualStyleBackColor = true;
            this.Cancel.Click += new System.EventHandler(this.Cancel_Click);
            // 
            // CreatPart
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 16F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(389, 319);
            this.Controls.Add(this.Cancel);
            this.Controls.Add(this.Create);
            this.Controls.Add(this.PanelsMade);
            this.Controls.Add(this.Module);
            this.Controls.Add(this.PartNo);
            this.Controls.Add(this.PanelsMadetxt);
            this.Controls.Add(this.Moduletxt);
            this.Controls.Add(this.PartNoTxt);
            this.Controls.Add(this.MachineSelectTxt);
            this.Controls.Add(this.MachineNames);
            this.Name = "CreatPart";
            this.Text = "Form1";
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.ComboBox MachineNames;
        private System.Windows.Forms.Label MachineSelectTxt;
        private System.Windows.Forms.Label PartNoTxt;
        private System.Windows.Forms.Label Moduletxt;
        private System.Windows.Forms.Label PanelsMadetxt;
        private System.Windows.Forms.TextBox PartNo;
        private System.Windows.Forms.TextBox Module;
        private System.Windows.Forms.TextBox PanelsMade;
        private System.Windows.Forms.Button Create;
        private System.Windows.Forms.Button Cancel;
    }
}