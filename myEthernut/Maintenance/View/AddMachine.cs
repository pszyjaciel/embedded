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
    public partial class AddMachine : Form
    {
        public string Machinename { get; private set; }
        public AddMachine()
        {
            InitializeComponent();
            
        }

        private void CreateMachine_Click(object sender, EventArgs e)
        {
            if (string.IsNullOrWhiteSpace(MachineName.Text))
            {
                MessageBox.Show("Invalid input");
            }
            else
            {
                this.Machinename = MachineName.Text;
                this.Close();
            }
            
            
        }

        private void Cancel_Click(object sender, EventArgs e)
        {
            this.Close();
        }
    }
}
