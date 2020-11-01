using System;
using System.Collections;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.ComponentModel;
using DataSoure.ObjectTemplates;


namespace DataSoure.Model
{
   public class Machine_park
    {
       
       public List<Machine> MachinePark;
       private RandomInt rnd;

        public Machine_park()
        {
            MachinePark = new List<Machine>();
            rnd = new RandomInt();
        }
        public void Create_Machine(string name , int panels ,int Daylypanels)
        {
            Machine machine = new Machine { Machine_name = name, 
                                            Total_Panels_made = panels,
                                            Day_Panels_made= Daylypanels };
            if (Containsmachine(machine))
            {
                MachinePark.Add(machine);
            }
            
        }
        public string Add_part_to_mashine(string machine , int module ,  string part, int panels_made)
                                        
        {
            for (int i = 0; i < MachinePark.Count; i++)
            {
                if (MachinePark[i].Machine_name == machine)
	            {
                    if(MachinePark[i].Create_Part(module, part, panels_made)){
                        return "Part was Created"; 
                    }else{
                        return "Part allready exist";
                    }
               	}
                
            }
            return "machine dosin't exist";
        }
        public void Add_hitory_to_machine(string machine, int module , string part_name, DateTime date)
        {
            for (int i = 0; i < MachinePark.Count; i++)
            {
                if (MachinePark[i].Machine_name == machine)
                {
                    MachinePark[i].Create_History(module, part_name, date);
                }

            }
        }
        public void AddRtValues(string machine , Machine_Values values)
        {
           
           for (int i = 0; i < MachinePark.Count; i++)
            {
                if (MachinePark[i].Machine_name == machine)
                {
                    MachinePark[i].
                        set_Rtvalues(values);
                }
            }
              
            
        }
        public void UpdatePanelsMade(string machine, int Panels)
        {
            for (int i = 0; i < MachinePark.Count; i++)
            {
                if (MachinePark[i].Machine_name == machine)
                {
                    MachinePark[i].Total_Panels_made = Panels;
                }

            }
        }
        public List<TempRTvalues> GetRtvalues(){
            //List<TempRTvalues> RtList;
            List<TempRTvalues> RtList = new List<TempRTvalues>();
            TempRTvalues value;
            for (int i = 0; i < MachinePark.Count; i++)
            {
                
                if (MachinePark[i].RtValues != null)
                {
                    value = new TempRTvalues
                    {
                        Machine = MachinePark[i].Machine_name,
                        Frequency = MachinePark[i].RtValues.Frequency,
                        DCvolage = MachinePark[i].RtValues.DCvolage,
                        MotorCurent = MachinePark[i].RtValues.MotorCurent,
                        MotorRPM = MachinePark[i].RtValues.MotorRPM,
                        MotorTorquyProc = MachinePark[i].RtValues.MotorTorquyProc,
                        TStamp = MachinePark[i].RtValues.TimeStamp
                    };
                    RtList.Add(value);
                };

                 
            }
            return RtList;
        }
        public List<MachineLoadTemp> GetMachinesLoad()
        {
            List<MachineLoadTemp> list = new List<MachineLoadTemp>();
            MachineLoadTemp values;
            foreach (var item in MachinePark)
            {
                values = new MachineLoadTemp
                {
                    Machine = item.Machine_name,
                    PanelsMade = item.Total_Panels_made
                };
                list.Add(values);
            }
            return list;
        }
        public List<MachineDaylyLoud> GetMachinesDaylyLoad()
        {
            List<MachineDaylyLoud> list = new List<MachineDaylyLoud>();
            MachineDaylyLoud values;
            foreach (var item in MachinePark)
            {
                values = new MachineDaylyLoud
                {
                    Machine = item.Machine_name,
                    DaylyLoad = item.Day_Panels_made
                };
                list.Add(values);
            }
        
            return list;
        }
        public List<Machine_part> Get_part(string name)
        {
            for (int i = 0; i < MachinePark.Count; i++)
            {
                if (MachinePark[i].Machine_name.Equals(name))
                {
                    return MachinePark[i].Get_Parts();
                }

            }
            return null;
        }
        public List<Breakdown_history> Get_history(string name)
        {
            for (int i = 0; i < MachinePark.Count; i++)
            {
                if (MachinePark[i].Machine_name.Equals(name))
                {
                    return MachinePark[i].Get_History();
                }
                
            }
            return null;
        }
        public bool Containsmachine(Machine target)
        {
            int count = 0;
            for (int i = 0; i < MachinePark.Count; i++)
            {
                if (MachinePark[i].Machine_name == target.Machine_name)
                {
                    if (MachinePark[i].Total_Panels_made== target.Total_Panels_made)
                    {
                        count++;
                    }
                    else
                    {
                        MachinePark[i].Total_Panels_made = target.Total_Panels_made;
                        count++;
                    }
                }
            }
            if (count==0)
            {
                return true;
            }
            return false;

        }
        public bool IfMachineExist(string name)
        {

            for (int i = 0; i < MachinePark.Count; i++)
            {
                if (MachinePark[i].Machine_name == name)
                {
                    return true;
                }
            }
            return false;
        }
        public List<MachinePartTemp> getAllparts()
        {
            List<MachinePartTemp> list = new List<MachinePartTemp>();
            for (int i = 0; i < MachinePark.Count; i++)
            {
                for (int j = 0; j < MachinePark[i].Get_Parts().Count; j++)
                {
                    
                    MachinePartTemp part = new MachinePartTemp()
                    {
                        Machine = MachinePark[i].Machine_name,
                        Module = MachinePark[i].Get_Parts()[j].Module,
                        PanelsMade = MachinePark[i].Get_Parts()[j].Panels_made,
                        Part = MachinePark[i].Get_Parts()[j].Part,
                        Maintenance = DateTime.Today.AddDays(rnd.randomstatus())
                    };
                    list.Add(part);
                }
            }

            return list;
        }
        public void setDaylyPanesMade(string Machine , int panels)
        {
            for (int i = 0; i < MachinePark.Count; i++)
            {
                if (MachinePark[i].Machine_name == Machine)
                {
                    MachinePark[i].Day_Panels_made = panels;
                }

            }
        }
        public void setPanelsMade(string Machine, int panels)
        {
            for (int i = 0; i < MachinePark.Count; i++)
            {
                if (MachinePark[i].Machine_name == Machine)
                {
                    MachinePark[i].Total_Panels_made = panels;
                }

            }
        }
    }
   class RandomInt
   {
       Random rnd = new Random();

       public int ranodomint()
       {
           int module = rnd.Next(-5,50);
           return module;
       }
       public int randomstatus()
       {
           int c = ranodomint();
           return c;
       }
   }
}
