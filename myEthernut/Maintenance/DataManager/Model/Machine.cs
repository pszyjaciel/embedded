using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using DataSoure.ObjectTemplates;
using System.ComponentModel;


namespace DataSoure.Model
{
    public class Machine
    {
        public List<Machine_part> Parts;
        public List<Breakdown_history> History;
        public Machine_Values RtValues;
        public string Machine_name;
        public int Total_Panels_made;
        public int Day_Panels_made;
        
        public Machine(){
            
            Parts = new List<Machine_part>();
            History = new List<Breakdown_history>();
 
        }
        public bool Create_Part( int module, string part, 
                                int panels_made)
        {
            Machine_part newpart = new Machine_part
            {
                Module = module,
                Part = part,
                Panels_made = panels_made 
            };
            if (!ContainsPart(newpart))
            {
                Parts.Add(newpart);
                return true;
            }
            return false;
        }
        public void Create_History(int module , string part, 
                                   DateTime date)
        {
           Breakdown_history history = new Breakdown_history 
           {
               Module = module, 
               Part = part, 
               date = date 
           };
           if (!ContainsHistory(history))
           {
               History.Add(history);
           }
        }
        public void set_Rtvalues(Machine_Values values)
        { 
            RtValues = values;
        }

        public List<Machine_part> Get_Parts()
        {
            return Parts;
        }
        public List<Breakdown_history> Get_History()
        {
            return History;
        }

        public Machine_Values GetRtValues()
        {
            return RtValues;
        }
        private bool ContainsHistory( Breakdown_history target){
            int count = 0;
            for (int i = 0; i < History.Count; i++)
            {
                if (History[i].Equals(target))
                {
                    count++;
                }
            }
            if (count==0)
            {
                return false;
            }
            return true;

        }
        private bool ContainsPart(Machine_part target)
        {
            int count = 0;
            for (int i = 0; i < Parts.Count; i++)
            {
                if (Parts[i].Part == target.Part  && Parts[i].Module == target.Module)
                {
                    count++;
                }
            }
            if (count == 0)
            {
                return false;
            }
            return true;
        }
        
    }
    
}
