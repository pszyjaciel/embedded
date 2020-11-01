using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Data;
using System.Threading.Tasks;
using DataSoure.Model;
using DataSoure.ObjectTemplates;
using System.ComponentModel;

namespace DataSoure.Control
{
    public class Data_Manager
    {
        public Machine_park park;
        public Database_adapter db;


        public Data_Manager() { 
        park = new Machine_park();
        db = new Database_adapter();
        
        }
        public Data_Manager(string DbServer)
        {
            park = new Machine_park();
            db = new Database_adapter(DbServer);
        }
        public Data_Manager(string DbServer, string DbName,string user,string password)
        {
            park = new Machine_park();
            db = new Database_adapter(DbServer,DbName,user,password);
        }
        public void UpdateAll()
        {
            if (UpdateMachines())
            {
                UpdateMachineParts();
                UpdateHistory();
                UpdateRtValues();
            } 
            
        }
        private bool UpdateMachines()
        {
            if (db.GetMachines() !=null)
            {
                foreach (var item in db.GetMachines())
                {
                    park.Create_Machine(item.Machine_name, item.Total_Panels_made, 0);
                }
                return true;
            }
           return false;

        }
        private void UpdateMachineParts()
        {
            if (db.GetParts() != null)
            {
                foreach (var item in db.GetParts())
                {
                    park.Add_part_to_mashine(item.Machine, item.Module, item.Part, item.PanelsMade);
                } 
            }
            
        }
        private void UpdateHistory()
        {
            if (db.getHisotry() != null)
            {
                foreach (var item in db.getHisotry())
                {
                    park.Add_hitory_to_machine(item.Machine, item.Module, item.Part, item.date);
                }
            }
            
        }
        private void UpdateRtValues()
        {
            if (db.GetRTvalues() != null)
            {
                foreach (var item in db.GetRTvalues())
                {
                    Machine_Values RtValues = new Machine_Values
                    {
                        Frequency = item.Frequency,
                        MotorCurent = item.MotorCurent,
                        MotorTorquyProc = item.MotorTorquyProc,
                        DCvolage = item.DCvolage,
                        MotorRPM = item.MotorRPM,
                        TimeStamp = item.TStamp
                    };
                    park.AddRtValues(item.Machine, RtValues);
                }  
            }
          

        }
        public void addHistory(string machine, int module, string part, DateTime date)
        {
            park.Add_hitory_to_machine(machine, module, part, date);
            db.Addhistory(machine, module, part, date);
        }
        public bool addMachine(string machine , int panelsMade)
        {

            if (!park.IfMachineExist(machine)&& machine!=null)
            {
                park.Create_Machine(machine, panelsMade,0);
                db.creteMachine(machine, panelsMade);
                return true;
            }
            return false;

        }
        public string addPart(string machine , int module , string part, int panelsMade){

           
              
                db.AddPart(machine, module, part, panelsMade);
                return park.Add_part_to_mashine(machine, module, part, panelsMade);
            
        }
        public List<MachineLoadTemp> getMashines()
        {

            return park.GetMachinesLoad();
          }
        public List<Machine_part> getParts(string MashineName)
        {
            return park.Get_part(MashineName);
      
        }
        public List<Breakdown_history> getHistory(string MashineName)
        {
            return park.Get_history(MashineName);
        }
        public void machinePanelsUpdate(string MaschineName, int PanelsMade)
        {
            park.UpdatePanelsMade(MaschineName, PanelsMade);
            db.UpdateMachinePanelsMade(MaschineName, PanelsMade);
        }
        public List<TempRTvalues> getRtValues()
        {
            return park.GetRtvalues();
        }
        public List<string> GetMachineName()
        {
            List<string> names = new List<string>();
            foreach (var item in park.GetMachinesLoad())
	         {
                 names.Add(item.Machine);
             }
            return names;
        }
        public List<EventsTemplate>GetEvents(){
            return db.GetEvenData();
        }
        public List<MachineDaylyLoud> MachineDaylyLoad()
        {
            return park.GetMachinesDaylyLoad();
        }
        public List<MachinePartTemp> getAllParts()
        {
           return park.getAllparts();
        }
      
    }
}
