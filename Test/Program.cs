using Djondb;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Test
{
    class Program
    {
        static void Main(string[] args)
        {
            DjondbConnection con = new DjondbConnection("localhost", 1243);
            try
            {
                con.Open();
                con.ShowDbs();
                con.ShowNamespaces("ItsmDb");
                BSONObj o = new BSONObj();
                o.add("name", "John");
                o.add("lastName", "Smith");
                o.add("age", 10);

                con.Insert("TestDB", "TestNS", o);

                DjondbCursor cursor = con.Find("ItsmDb", "ORDERS", "*", "");
                while (cursor.MoveNext())
                {
                    BSONObj res = cursor.Current;
                    res["test"] = 10;
                    con.Update("ItsmDb", "ORDERS", res);
                    Console.WriteLine(res);
                }


                con.BeginTransaction();
                o.add("age", 15);
                con.Insert("TestDB", "TestNS", o);

                DjondbCursor res1 = con.ExecuteQuery("SELECT * FROM TestDB:TestNS where age > 10");
                if (!res1.MoveNext())
                {
                    Console.WriteLine("Error, expected at least one result");
                }
                con.RollbackTransaction();
                DjondbCursor res2 = con.ExecuteQuery("SELECT * FROM TestDB:TestNS where age > 10");
                if (res1.MoveNext())
                {
                    Console.WriteLine("Error, expected none");
                }

                DjondbCursor cur = con.ExecuteQuery("select * from ItsmDb:ORDERS");
                while (cur.MoveNext())
                {
                    BSONObj o2 = cur.Current;
                    Console.WriteLine(o2);
                }
                try
                {
                    con.ExecuteUpdate("select * from ItsmDb:ORDERS");
                    throw new ApplicationException("This should break, Select are not allowed on ExecuteUpdate");
                }
                catch (DjondbException)
                {
                    // Expected
                }
            }
            catch (DjondbException e)
            {
                Console.WriteLine(e.Message);
            }
        }
    }
}
