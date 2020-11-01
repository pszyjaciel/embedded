using System;
using DataSoure.ObjectTemplates;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Data;
using System.Threading.Tasks;
using MySql.Data.MySqlClient;
using DataSoure.Model;

namespace DataSoure
{
   public class Database_adapter
    {
//private static string Server = "10.52.234.55";
        private static string Server = "localhost";//10.52.230.200
       private static string DateBase_Name = "maintenance";//maintenance
        private static string User = "root";
        private static string Password = "hakert";
        private static string ConnectionString;
        private static MySqlConnection Connection;
        private MySqlCommand sqlstatment;
        private bool isOpen;

        public Database_adapter(string server, string database_name,
                                string user, string password)
        {
            Server = server;
            DateBase_Name = database_name;
            User = user;
            Password = password;
            ConnectionString = null;
            isOpen = false;
        }
        public Database_adapter(string datebase_name)
        {
            DateBase_Name = datebase_name;
            ConnectionString = null;
            isOpen = false;
        }
        public Database_adapter()
        {
            isOpen = false;
        }
        private bool Open_Datebase()
        {
            if (isOpen)
            {
                return true;
            }
            try
            {
                ConnectionString = "SERVER=" + Server + ";" + "DATABASE="
                + DateBase_Name + ";" + "UID=" + User + ";" + "PASSWORD=" + Password + ";";
                Connection = new MySqlConnection(ConnectionString);
                Connection.Open();
                Console.WriteLine("Database open");
                isOpen = true;

            }
            catch (Exception ex)
            {

                return false;
            }
            return false;

        }
        private bool Close_Datebase()
        {
            try
            {
                isOpen = false;
                if (Connection != null)
                {
                    Connection.Close();
                    Console.WriteLine("database close");
                    return true;

                }
            }
            catch (Exception ex)
            {

                return false;
            }
            return false;
        }
        public List<MachinePartTemp> GetParts()
        {
            MachinePartTemp temp;
            if (!isOpen)
            {
                Open_Datebase();
            }
            List<MachinePartTemp> Parts = new List<MachinePartTemp> { };
            sqlstatment = Connection.CreateCommand();
            sqlstatment.CommandText = "SELECT * FROM `machine_part`";
            try
            {
                MySqlDataReader reder = sqlstatment.ExecuteReader();
                while (reder.Read())
                {
                    temp = new MachinePartTemp
                    {
                        Machine = reder["Machine"].ToString(),
                        Module = (int)reder["Module_id"],
                        Part = reder["Part"].ToString(),
                        PanelsMade = (int)reder["Panels_made"]
                    };
                    Parts.Add(temp);
                }
            }
            catch (Exception)
            {
                
                return null;
            }
            
            Close_Datebase();
            return Parts;

        }
        public List<PartHistoryTemp> getHisotry()
        {
            PartHistoryTemp temp;
            if (!isOpen)
            {
                Open_Datebase();
            }
            List<PartHistoryTemp> hitsory = new List<PartHistoryTemp> { };

            sqlstatment = Connection.CreateCommand();
            sqlstatment.CommandText = "SELECT * FROM `breakdown_history` ";
            try
            {
                MySqlDataReader reder = sqlstatment.ExecuteReader();
                while (reder.Read())
                {
                    temp = new PartHistoryTemp
                    {
                        Machine = reder["Machine"].ToString(),
                        Module = (int)reder["Module_id"],
                        Part = reder["Part"].ToString(),
                        date = (DateTime)reder["Date"]
                    };
                    hitsory.Add(temp);
                }
            }
            catch (Exception)
            {
                
                return null;
            }
           
            Close_Datebase();
            return hitsory;

        }
        public List<Machine> GetMachines()
        {
            Machine temp;
            if (!isOpen)
            {
                Open_Datebase();
            }
            List<Machine> machine = new List<Machine> { };

            sqlstatment = Connection.CreateCommand();
            sqlstatment.CommandText = "SELECT * FROM `machines`";
            try
            {
                MySqlDataReader reder = sqlstatment.ExecuteReader();
                while (reder.Read())
                {
                    temp = new Machine
                    {
                        Machine_name = reder["Machine"].ToString(),
                        Total_Panels_made = (int)reder["Panels_made"]
                    };
                    machine.Add(temp);
                }
            }
            catch (Exception)
            {

                return null;
            }
           
            Close_Datebase();
            return machine;
        }
        public void creteMachine(string Machine, int PanelsMade)
        {
            if (!isOpen)
            {
                Open_Datebase();
            }
            sqlstatment = Connection.CreateCommand();
            if (Machine!= null)
            {
               sqlstatment.CommandText = @"INSERT INTO `machines`(`Machine`, `Panels_made`) VALUES ('"
                   + Machine.ToString() + "'," + PanelsMade.ToString() + ")";
               sqlstatment.ExecuteNonQuery();

            }
           
            Close_Datebase();
        }
        public void AddPart(string machine, int module, string part, int panelsMade)
        {
            if (!isOpen)
            {
                Open_Datebase();
            }
            sqlstatment = Connection.CreateCommand();
            sqlstatment.CommandText = @"INSERT INTO `machine_part`(`Machine`, `Module_id`, `Part`, `Panels_made`) VALUES ('" + machine.ToString()
                                    + "'," + module.ToString() + ",'" + part.ToString() + "'," + panelsMade.ToString() + ")";
            sqlstatment.ExecuteNonQuery();
            Close_Datebase();
        }
        public void Addhistory(string machine, int module, string part, DateTime date)
        {
            if (!isOpen)
            {
                Open_Datebase();
            }
            sqlstatment = Connection.CreateCommand();
            sqlstatment.CommandText = @"INSERT INTO `breakdown_history`(`Machine`, `Module_id`, `Part`, `Date`) VALUES ('" + machine.ToString() + "'," + module.ToString()
                                    + ",'" + part.ToString() + "'," + date.ToString() + ")";
            sqlstatment.ExecuteNonQuery();
            Close_Datebase();
        }
        public void UpdateMachinePanelsMade(string Machine, int Panels)
        {
            if (!isOpen)
            {
                Open_Datebase();
            }
            sqlstatment = Connection.CreateCommand();
            sqlstatment.CommandText = @"UPDATE `machines` SET `Panels_made`=" + Panels + " WHERE `Machine`='" + Machine + "'";
            sqlstatment.ExecuteNonQuery();
            Close_Datebase();
        }
        public List<EventsTemplate> GetEvenData()
        {
            EventsTemplate temp;
            if (!isOpen)
            {
                Open_Datebase();
            }
            List<EventsTemplate> Events = new List<EventsTemplate> { };
            sqlstatment = Connection.CreateCommand();
            sqlstatment.CommandText = "SELECT * FROM `events` ";
            MySqlDataReader reder = sqlstatment.ExecuteReader();
            while (reder.Read())
            {
                temp = new EventsTemplate
                {
                    Senor = (int)reder["Sensor_id"],
                    Module = (int)reder["Module_id"],
                    Machine = reder["Machine"].ToString(),
                    State = (string)reder["State"],
                    Date = (DateTime)reder["Date"]
                };
                Events.Add(temp);
            }
            Close_Datebase();
            return Events;
        }
        public List<TempRTvalues> GetRTvalues()
        {
            TempRTvalues temp;
            if (!isOpen)
            {
                Open_Datebase();
            }
            List<TempRTvalues> RTvalues = new List<TempRTvalues> { };
            sqlstatment = Connection.CreateCommand();
            sqlstatment.CommandText = "SELECT * FROM `values_realtime`";
            try
            {
                MySqlDataReader reder = sqlstatment.ExecuteReader();
                while (reder.Read())
                {
                    temp = new TempRTvalues
                    {
                        Machine = reder["Machine"].ToString(),
                        Frequency = (int)reder["Frequency"],
                        MotorCurent = (int)reder["MotorCurent"],
                        MotorTorquyProc = (int)reder["MotorTorquyProc"],
                        DCvolage = (int)reder["DCvolage"],
                        MotorRPM = (int)reder["MotorRPM"],
                        TStamp = (DateTime)reder["TStamp"]
                    };
                    RTvalues.Add(temp);
                }
            }
            catch (Exception)
            {
                
                return null;
            }
           
            Close_Datebase();
            return RTvalues;

        }
    }
}
//fravia