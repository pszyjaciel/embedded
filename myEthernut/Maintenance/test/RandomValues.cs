using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using MySql.Data.MySqlClient;
namespace DataSoure
{

    class RandomValues
    {
        private static string Server = "localhost";
        private static string DateBase_Name = "maintainenc_db";
        private static string User = "root";
        private static string Password = "";
        private static string ConnectionString;
        private static MySqlConnection Conection;
        private RandomDateTime time;
        private RandomIntChar rnd;
        private MySqlCommand sqlstatment;
        private bool isOpen;
         public RandomValues(string server , string database_name ,
                                string user, string password)
        {
            Server = server;
            DateBase_Name = database_name;
            User = user;
            Password = password;
            ConnectionString = null;
            isOpen = false;
        }
        public RandomValues(string datebase_name)
        {
            DateBase_Name = datebase_name;
            ConnectionString = null;
            isOpen = false;
        }
        public RandomValues()
        {
            isOpen = false;
            time = new RandomDateTime();
            rnd = new RandomIntChar();
        }
        public bool Open_Datebase()
        {
            if (isOpen)
            {
                return true;   
            }
            try
            {
                ConnectionString = "SERVER=" + Server + ";" + "DATABASE="
                + DateBase_Name + ";" + "UID=" + User + ";" + "PASSWORD=" + Password + ";";
                Conection = new MySqlConnection(ConnectionString);
                Conection.Open();
                Console.WriteLine("Database open");
                isOpen = true;
                
            }
            catch (Exception ex)
            {
                Console.WriteLine(ex.Message);
            }
            return false;
            
        }
        public bool Close_Datebase() 
        {
            try
            {
                isOpen = false;
                if (Conection != null)
                {
                    Conection.Close();
                    Console.WriteLine("database close");
                    return true;
                    
                }
            }
            catch (Exception ex)
            {

                Console.WriteLine(ex.Message);
            }
            return false;
        }
        public void events(string machine,int amount)
        {
            while (amount != 0)
            {
            if (!isOpen)
            {
                Open_Datebase();
            }
            sqlstatment = Conection.CreateCommand();
          
                
                sqlstatment.CommandText = @"INSERT INTO `events`(`Sensor_id`, `Module_id`, `Machine`, `State`, `Date`) 
                                            VALUES ('" + rnd.ranodomint() + "','" + rnd.ranodomint() + "','" + machine + "','" + rnd.randomstatus() + "','" + time.Next().ToString("yyyy/MM/dd,HH:mm:ss") + "')";
                sqlstatment.ExecuteNonQuery();
                Console.WriteLine(time.Next().ToString("yyyy/MM/dd,HH:mm:ss") + "  " + rnd.randomstatus());
                amount--;
            
            
            Close_Datebase();
            }
        }           
    }
    class RandomDateTime
    {
        DateTime start;
        Random gen = new Random();
        int range;

        public RandomDateTime()
        {
            start = new DateTime(1995, 1, 1);
            gen = new Random();
            range = (DateTime.Today - start).Days;
        }

        public DateTime Next()
        {
            return start.AddDays(gen.Next(range)).AddHours(gen.Next(0, 24)).AddMinutes(gen.Next(0, 60)).AddSeconds(gen.Next(0, 60));
        }
    }
    class RandomIntChar
    {
        Random rnd = new Random();

        public int ranodomint()
        {
            
            int module = rnd.Next(1, 15);
            return module;
        }
        public char randomstatus()
        {
            string st = "YN";
            char c = st[rnd.Next(st.Length)];
            return c;
        }
}
}
