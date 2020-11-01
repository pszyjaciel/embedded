using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace DataSoure.Model
{
   public class Machine_Values
    {
       public int Frequency { get; set; }
       public int MotorCurent { get; set; }
       public int MotorTorquyProc { get; set; }
       public int DCvolage { get; set; }
       public int MotorRPM { get; set; }
       public DateTime TimeStamp { get; set; }
    }
     
}
