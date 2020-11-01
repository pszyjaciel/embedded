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

namespace View
{
    public partial class CreatPart : Form
    {
        public Data_Manager manager;
        public CreatPart()
        {
            InitializeComponent();
            manager = new Data_Manager();
            manager.UpdateAll();
            if (manager.GetMachineName() != null)
            {
                MachineNames.DataSource = manager.GetMachineName();
            }
            
            

        }

        private void Cancel_Click(object sender, EventArgs e)
        {
            this.Close();
        }

        private void Create_Click(object sender, EventArgs e)
        {
            int module;
            int panelsmade;
            int.TryParse(Module.Text, out module);
            if (!int.TryParse(Module.Text, out module))
            {
                MessageBox.Show("Module is a number only field");
                return;
            }
            int.TryParse(PanelsMade.Text,out panelsmade);
            if (!int.TryParse(PanelsMade.Text, out panelsmade))
            {
                MessageBox.Show("Panels Made is a number only field");
                return;
            }
           string name = MachineNames.SelectedItem.ToString();
           MessageBox.Show(manager.addPart(MachineNames.SelectedItem.ToString(), module,
                           PartNo.Text.ToString(), panelsmade));
           

        }

        private void comboBox1_SelectedIndexChanged(object sender, EventArgs e)
        {

        }
    }
}
