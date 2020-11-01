using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace DataSoure.ObjectTemplates
{
   public class TempRTvalues
    {
       public string Machine { get; set; }
       public int Frequency { get; set; }
       public int MotorCurent { get; set; }
       public int MotorTorquyProc { get; set; }
       public int DCvolage { get; set; }
       public int MotorRPM { get; set; }
       public DateTime TStamp { get; set; }
    }
}
