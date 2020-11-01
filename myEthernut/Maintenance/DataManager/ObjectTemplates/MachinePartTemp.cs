using System;
using System.Collections.Generic;


namespace DataSoure.ObjectTemplates
{
   public class MachinePartTemp
    {
        public string Machine {get;set;}
        public int Module { get; set; }
        public string Part { get; set; }
        public int PanelsMade { get; set; }
        public DateTime Maintenance { get; set; }
    }
}
