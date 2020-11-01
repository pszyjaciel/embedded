using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using DataSoure.Control;
using View;
using DataSoure.ObjectTemplates;



namespace View
{
    
    public partial class MainWindow : Form
    {
  
       public Data_Manager maneger;
       private List<MachinePartTemp> PartList;
       private List<TempRTvalues> Rtlist;
        public MainWindow()
        {
            maneger = new Data_Manager();
            maneger.UpdateAll();

            InitializeComponent();
       

            this.DisplayerRTvalues.AutoSizeColumnsMode = DataGridViewAutoSizeColumnsMode.DisplayedCells;
            this.DisplayDaylyLoad.AutoSizeColumnsMode = DataGridViewAutoSizeColumnsMode.DisplayedCells;
            this.DisplayMachineLoad.AutoSizeColumnsMode = DataGridViewAutoSizeColumnsMode.DisplayedCells;
            //this.DisplayMaintenace.AutoSizeColumnsMode = DataGridViewAutoSizeColumnsMode.DisplayedCells;
            
        }
      
        private void dataGridView1_CellContentClick(object sender, DataGridViewCellEventArgs e)
        {

        }
        private void CreateMachine_Click(object sender, EventArgs e)
        {
            maneger.UpdateAll();
           //MessageBox.Show("The data was upadated");
            AddMachine win = new AddMachine();
            win.ShowDialog();
            string machinename = win.Machinename;
            if (maneger.addMachine(machinename, 0)&& machinename !=null)
            {
                MessageBox.Show("Machine was successful created");
            }
            else
            {
                DialogResult dialog = MessageBox.Show("Machine allready exist, try again?", "Try again", MessageBoxButtons.YesNo);
                if (dialog== DialogResult.Yes)
                {
                    CreateMachine_Click(sender,e);
                }
               
            }
        }
        private void CreatPart_Click(object sender, EventArgs e)
        {
            CreatPart win = new CreatPart();
            win.ShowDialog();
        }
        public bool addmachine(string name)
        {
           return maneger.addMachine(name, 0);
        }
        private void Settingstable()
        {
            
             try
            {
                for (int i = 0; i < DisplayerRTvalues.Rows.Count; i++)
            {

                if (Rtlist[i].Frequency == 0)
                {
                    DisplayerRTvalues.Rows[i].Cells[0].Style.BackColor = System.Drawing.Color.FromArgb(0xbf, 0xbf, 0xbf);
                    DisplayerRTvalues.Rows[i].Cells[1].Style.BackColor = System.Drawing.Color.FromArgb(0xbf, 0xbf, 0xbf);
                    DisplayerRTvalues.Rows[i].Cells[2].Style.BackColor = System.Drawing.Color.FromArgb(0xbf, 0xbf, 0xbf);
                    DisplayerRTvalues.Rows[i].Cells[3].Style.BackColor = System.Drawing.Color.FromArgb(0xbf, 0xbf, 0xbf);
                    DisplayerRTvalues.Rows[i].Cells[4].Style.BackColor = System.Drawing.Color.FromArgb(0xbf, 0xbf, 0xbf);
                    DisplayerRTvalues.Rows[i].Cells[5].Style.BackColor = System.Drawing.Color.FromArgb(0xbf, 0xbf, 0xbf);
                    DisplayerRTvalues.Rows[i].Cells[6].Style.BackColor = System.Drawing.Color.FromArgb(0xbf, 0xbf, 0xbf);
                }
               
            }
            }
            catch (Exception)
            {
                
            }

            try
            {
                for (int i = 0; i < DisplayDaylyLoad.Rows.Count; i++)
                {

                    if (i % 2 == 0)
                    {
                        DisplayDaylyLoad.Rows[i].Cells[0].Style.BackColor = System.Drawing.Color.FromArgb(240, 240, 240);
                        DisplayDaylyLoad.Rows[i].Cells[1].Style.BackColor = System.Drawing.Color.FromArgb(240, 240, 240);
                    }
                }
            }
            catch (Exception)
            {

            }

            try
            {
                for (int i = 0; i < DisplayDaylyLoad.Rows.Count; i++)
                {

                    if (i % 2 == 0)
                    {
                        DisplayMachineLoad.Rows[i].Cells[0].Style.BackColor = System.Drawing.Color.FromArgb(240, 240, 240);
                        DisplayMachineLoad.Rows[i].Cells[1].Style.BackColor = System.Drawing.Color.FromArgb(240, 240, 240);
                    }
                }
            }
            catch (Exception)
            {
               
            }

            try
            {
                for (int i = 0; i < DisplayMaintenace.Rows.Count; i++)
                {
                    if (PartList[i].Maintenance.Date < DateTime.Today.Date)
                    {
                        DisplayMaintenace.Rows[i].Cells[0].Style.BackColor = System.Drawing.Color.FromArgb(0xff,0x55,0x55 ); //red
                        DisplayMaintenace.Rows[i].Cells[1].Style.BackColor = System.Drawing.Color.FromArgb(0xff, 0x55, 0x55);
                        DisplayMaintenace.Rows[i].Cells[2].Style.BackColor = System.Drawing.Color.FromArgb(0xff, 0x55, 0x55);
                        DisplayMaintenace.Rows[i].Cells[3].Style.BackColor = System.Drawing.Color.FromArgb(0xff, 0x55, 0x55);
                        DisplayMaintenace.Rows[i].Cells[4].Style.BackColor = System.Drawing.Color.FromArgb(0xff, 0x55, 0x55);
                    }
                    else if (DateTime.Today.Date <= PartList[i].Maintenance.Date && PartList[i].Maintenance.Date <= DateTime.Today.AddDays(10).Date)
                    {
                        DisplayMaintenace.Rows[i].Cells[0].Style.BackColor = System.Drawing.Color.FromArgb(0xff, 0xAA, 0x55); // orange
                        DisplayMaintenace.Rows[i].Cells[1].Style.BackColor = System.Drawing.Color.FromArgb(0xff, 0xAA, 0x55);
                        DisplayMaintenace.Rows[i].Cells[2].Style.BackColor = System.Drawing.Color.FromArgb(0xff, 0xAA, 0x55);
                        DisplayMaintenace.Rows[i].Cells[3].Style.BackColor = System.Drawing.Color.FromArgb(0xff, 0xAA, 0x55);
                        DisplayMaintenace.Rows[i].Cells[4].Style.BackColor = System.Drawing.Color.FromArgb(0xff, 0xAA, 0x55);
                    }
                    else{
                        DisplayMaintenace.Rows[i].Cells[0].Style.BackColor = System.Drawing.Color.FromArgb(0xaa, 0xff, 0x55); //green
                        DisplayMaintenace.Rows[i].Cells[1].Style.BackColor = System.Drawing.Color.FromArgb(0xaa, 0xff, 0x55);
                        DisplayMaintenace.Rows[i].Cells[2].Style.BackColor = System.Drawing.Color.FromArgb(0xaa, 0xff, 0x55);
                        DisplayMaintenace.Rows[i].Cells[3].Style.BackColor = System.Drawing.Color.FromArgb(0xaa, 0xff, 0x55);
                        DisplayMaintenace.Rows[i].Cells[4].Style.BackColor = System.Drawing.Color.FromArgb(0xaa, 0xff, 0x55);
                    }
                }
            }
            catch (Exception)
            {
                
                throw;
            }
            }
        private void FewSec_Tick(object sender, EventArgs e)
        {
            maneger.UpdateAll();
            
            DisplayDaylyLoad.DataSource = maneger.MachineDaylyLoad();
            DisplayMachineLoad.DataSource = maneger.getMashines();
            PartList = maneger.getAllParts();
            Rtlist = maneger.getRtValues();
            DisplayerRTvalues.DataSource = Rtlist;
            DisplayMaintenace.DataSource = PartList;
            Settingstable();

           
        }

        private void MainWindow_Load(object sender, EventArgs e)
        {

        }

    }
}

