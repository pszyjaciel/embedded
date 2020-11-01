using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using DataSoure.Control;

namespace test
{
    class Program
    {

        static void Main(string[] args)
        {
            Data_Manager manager = new Data_Manager();
            manager.UpdateAll();

            foreach (var item in manager.getRtValues())
            {
                Console.WriteLine(item.Machine.ToString());
                Console.WriteLine(item.MotorCurent);
                Console.WriteLine(DateTime.Now);
            }
       /*     foreach (var item in manager.GetEvents())
            {
                Console.Write(item.Machine+ " ");
                Console.Write(item.Module + " ");
                Console.Write(item.Senor + " ");
                Console.Write(item.State + " ");
                Console.WriteLine(item.Date);
            }*/
            Console.ReadKey();
        }
    }
}
