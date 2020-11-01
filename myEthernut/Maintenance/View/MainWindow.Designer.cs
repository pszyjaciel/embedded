namespace View
{
    partial class MainWindow
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
            this.components = new System.ComponentModel.Container();
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(MainWindow));
            this.DisplayerRTvalues = new System.Windows.Forms.DataGridView();
            this.CreateMachine = new System.Windows.Forms.Button();
            this.CreatPart = new System.Windows.Forms.Button();
            this.update = new System.Windows.Forms.Timer(this.components);
            this.DisplayMachineLoad = new System.Windows.Forms.DataGridView();
            this.DisplayDaylyLoad = new System.Windows.Forms.DataGridView();
            this.RTvalues = new System.Windows.Forms.Label();
            this.Workload = new System.Windows.Forms.Label();
            this.WorkloadDayly = new System.Windows.Forms.Label();
            this.AddBrekdown = new System.Windows.Forms.Button();
            this.History = new System.Windows.Forms.Button();
            this.DisplayMaintenace = new System.Windows.Forms.DataGridView();
            this.Maintenance = new System.Windows.Forms.Label();
            this.DbSettings = new System.Windows.Forms.Button();
            this.pictureBox1 = new System.Windows.Forms.PictureBox();
            ((System.ComponentModel.ISupportInitialize)(this.DisplayerRTvalues)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.DisplayMachineLoad)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.DisplayDaylyLoad)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.DisplayMaintenace)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox1)).BeginInit();
            this.SuspendLayout();
            // 
            // DisplayerRTvalues
            // 
            this.DisplayerRTvalues.Location = new System.Drawing.Point(30, 367);
            this.DisplayerRTvalues.Name = "DisplayerRTvalues";
            this.DisplayerRTvalues.Size = new System.Drawing.Size(936, 342);
            this.DisplayerRTvalues.TabIndex = 0;
            this.DisplayerRTvalues.CellContentClick += new System.Windows.Forms.DataGridViewCellEventHandler(this.dataGridView1_CellContentClick);
            // 
            // CreateMachine
            // 
            this.CreateMachine.Location = new System.Drawing.Point(30, 283);
            this.CreateMachine.Name = "CreateMachine";
            this.CreateMachine.Size = new System.Drawing.Size(143, 23);
            this.CreateMachine.TabIndex = 4;
            this.CreateMachine.Text = "Create Machine";
            this.CreateMachine.UseVisualStyleBackColor = true;
            this.CreateMachine.Click += new System.EventHandler(this.CreateMachine_Click);
            // 
            // CreatPart
            // 
            this.CreatPart.Location = new System.Drawing.Point(30, 313);
            this.CreatPart.Name = "CreatPart";
            this.CreatPart.Size = new System.Drawing.Size(143, 23);
            this.CreatPart.TabIndex = 5;
            this.CreatPart.Text = "Create Part";
            this.CreatPart.UseVisualStyleBackColor = true;
            this.CreatPart.Click += new System.EventHandler(this.CreatPart_Click);
            // 
            // update
            // 
            this.update.Enabled = true;
            this.update.Interval = 5000;
            this.update.Tick += new System.EventHandler(this.FewSec_Tick);
            // 
            // DisplayMachineLoad
            // 
            this.DisplayMachineLoad.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.DisplayMachineLoad.Location = new System.Drawing.Point(1009, 367);
            this.DisplayMachineLoad.Name = "DisplayMachineLoad";
            this.DisplayMachineLoad.RowTemplate.Height = 24;
            this.DisplayMachineLoad.Size = new System.Drawing.Size(303, 342);
            this.DisplayMachineLoad.TabIndex = 6;
            // 
            // DisplayDaylyLoad
            // 
            this.DisplayDaylyLoad.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.DisplayDaylyLoad.Location = new System.Drawing.Point(1009, 48);
            this.DisplayDaylyLoad.Name = "DisplayDaylyLoad";
            this.DisplayDaylyLoad.RowTemplate.Height = 24;
            this.DisplayDaylyLoad.Size = new System.Drawing.Size(303, 288);
            this.DisplayDaylyLoad.TabIndex = 7;
            // 
            // RTvalues
            // 
            this.RTvalues.AutoSize = true;
            this.RTvalues.Location = new System.Drawing.Point(27, 343);
            this.RTvalues.Name = "RTvalues";
            this.RTvalues.Size = new System.Drawing.Size(112, 17);
            this.RTvalues.TabIndex = 8;
            this.RTvalues.Text = "Real time values";
            // 
            // Workload
            // 
            this.Workload.AutoSize = true;
            this.Workload.Location = new System.Drawing.Point(1006, 343);
            this.Workload.Name = "Workload";
            this.Workload.Size = new System.Drawing.Size(99, 17);
            this.Workload.TabIndex = 9;
            this.Workload.Text = "Workload total";
            // 
            // WorkloadDayly
            // 
            this.WorkloadDayly.AutoSize = true;
            this.WorkloadDayly.Location = new System.Drawing.Point(1006, 25);
            this.WorkloadDayly.Name = "WorkloadDayly";
            this.WorkloadDayly.Size = new System.Drawing.Size(101, 17);
            this.WorkloadDayly.TabIndex = 11;
            this.WorkloadDayly.Text = "Workload daily";
            // 
            // AddBrekdown
            // 
            this.AddBrekdown.Location = new System.Drawing.Point(30, 254);
            this.AddBrekdown.Name = "AddBrekdown";
            this.AddBrekdown.Size = new System.Drawing.Size(143, 23);
            this.AddBrekdown.TabIndex = 12;
            this.AddBrekdown.Text = "Add A Breakdown";
            this.AddBrekdown.UseVisualStyleBackColor = true;
            // 
            // History
            // 
            this.History.Location = new System.Drawing.Point(30, 225);
            this.History.Name = "History";
            this.History.Size = new System.Drawing.Size(143, 23);
            this.History.TabIndex = 13;
            this.History.Text = "Breakdown History";
            this.History.UseVisualStyleBackColor = true;
            // 
            // DisplayMaintenace
            // 
            this.DisplayMaintenace.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.DisplayMaintenace.Location = new System.Drawing.Point(218, 48);
            this.DisplayMaintenace.Name = "DisplayMaintenace";
            this.DisplayMaintenace.RowTemplate.Height = 24;
            this.DisplayMaintenace.Size = new System.Drawing.Size(748, 288);
            this.DisplayMaintenace.TabIndex = 14;
            // 
            // Maintenance
            // 
            this.Maintenance.AutoSize = true;
            this.Maintenance.Location = new System.Drawing.Point(224, 25);
            this.Maintenance.Name = "Maintenance";
            this.Maintenance.Size = new System.Drawing.Size(160, 17);
            this.Maintenance.TabIndex = 15;
            this.Maintenance.Text = "Upcoming maintenance ";
            // 
            // DbSettings
            // 
            this.DbSettings.Location = new System.Drawing.Point(30, 174);
            this.DbSettings.Name = "DbSettings";
            this.DbSettings.Size = new System.Drawing.Size(143, 23);
            this.DbSettings.TabIndex = 16;
            this.DbSettings.Text = "DataBase Settings";
            this.DbSettings.UseVisualStyleBackColor = true;
            // 
            // pictureBox1
            // 
            this.pictureBox1.AccessibleRole = System.Windows.Forms.AccessibleRole.None;
            this.pictureBox1.Image = ((System.Drawing.Image)(resources.GetObject("pictureBox1.Image")));
            this.pictureBox1.InitialImage = ((System.Drawing.Image)(resources.GetObject("pictureBox1.InitialImage")));
            this.pictureBox1.Location = new System.Drawing.Point(23, 12);
            this.pictureBox1.Name = "pictureBox1";
            this.pictureBox1.Size = new System.Drawing.Size(150, 150);
            this.pictureBox1.SizeMode = System.Windows.Forms.PictureBoxSizeMode.Zoom;
            this.pictureBox1.TabIndex = 17;
            this.pictureBox1.TabStop = false;
            // 
            // MainWindow
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 16F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(1348, 721);
            this.Controls.Add(this.pictureBox1);
            this.Controls.Add(this.DbSettings);
            this.Controls.Add(this.Maintenance);
            this.Controls.Add(this.DisplayMaintenace);
            this.Controls.Add(this.History);
            this.Controls.Add(this.AddBrekdown);
            this.Controls.Add(this.WorkloadDayly);
            this.Controls.Add(this.Workload);
            this.Controls.Add(this.RTvalues);
            this.Controls.Add(this.DisplayDaylyLoad);
            this.Controls.Add(this.DisplayMachineLoad);
            this.Controls.Add(this.CreatPart);
            this.Controls.Add(this.CreateMachine);
            this.Controls.Add(this.DisplayerRTvalues);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedSingle;
            this.Name = "MainWindow";
            this.Text = "Monitoring";
            this.Load += new System.EventHandler(this.MainWindow_Load);
            ((System.ComponentModel.ISupportInitialize)(this.DisplayerRTvalues)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.DisplayMachineLoad)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.DisplayDaylyLoad)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.DisplayMaintenace)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox1)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.DataGridView DisplayerRTvalues;
        private System.Windows.Forms.Button CreateMachine;
        private System.Windows.Forms.Button CreatPart;
        private System.Windows.Forms.Timer update;
        private System.Windows.Forms.DataGridView DisplayMachineLoad;
        private System.Windows.Forms.DataGridView DisplayDaylyLoad;
        private System.Windows.Forms.Label RTvalues;
        private System.Windows.Forms.Label Workload;
        private System.Windows.Forms.Label WorkloadDayly;
        private System.Windows.Forms.Button AddBrekdown;
        private System.Windows.Forms.Button History;
        private System.Windows.Forms.DataGridView DisplayMaintenace;
        private System.Windows.Forms.Label Maintenance;
        private System.Windows.Forms.Button DbSettings;
        private System.Windows.Forms.PictureBox pictureBox1;
        
      

    }
}

