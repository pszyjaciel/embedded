namespace View
{
    partial class AddMachine
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
            this.NameMachine = new System.Windows.Forms.Label();
            this.MachineName = new System.Windows.Forms.TextBox();
            this.CreateMachine = new System.Windows.Forms.Button();
            this.Cancel = new System.Windows.Forms.Button();
            this.SuspendLayout();
            // 
            // NameMachine
            // 
            this.NameMachine.AutoSize = true;
            this.NameMachine.Location = new System.Drawing.Point(114, 40);
            this.NameMachine.Name = "NameMachine";
            this.NameMachine.Size = new System.Drawing.Size(106, 17);
            this.NameMachine.TabIndex = 0;
            this.NameMachine.Text = "Machine Name:";
            // 
            // MachineName
            // 
            this.MachineName.Location = new System.Drawing.Point(256, 37);
            this.MachineName.Name = "MachineName";
            this.MachineName.Size = new System.Drawing.Size(100, 22);
            this.MachineName.TabIndex = 1;
            // 
            // CreateMachine
            // 
            this.CreateMachine.Location = new System.Drawing.Point(145, 88);
            this.CreateMachine.Name = "CreateMachine";
            this.CreateMachine.Size = new System.Drawing.Size(75, 23);
            this.CreateMachine.TabIndex = 2;
            this.CreateMachine.Text = "Create Machine";
            this.CreateMachine.UseVisualStyleBackColor = true;
            this.CreateMachine.Click += new System.EventHandler(this.CreateMachine_Click);
            // 
            // Cancel
            // 
            this.Cancel.Location = new System.Drawing.Point(256, 88);
            this.Cancel.Name = "Cancel";
            this.Cancel.Size = new System.Drawing.Size(75, 23);
            this.Cancel.TabIndex = 3;
            this.Cancel.Text = "Cancel";
            this.Cancel.UseVisualStyleBackColor = true;
            this.Cancel.Click += new System.EventHandler(this.Cancel_Click);
            // 
            // AddMachine
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 16F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(476, 141);
            this.Controls.Add(this.Cancel);
            this.Controls.Add(this.CreateMachine);
            this.Controls.Add(this.MachineName);
            this.Controls.Add(this.NameMachine);
            this.Name = "AddMachine";
            this.Text = "Form2";
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Label NameMachine;
        private System.Windows.Forms.TextBox MachineName;
        private System.Windows.Forms.Button CreateMachine;
        private System.Windows.Forms.Button Cancel;
    }
}