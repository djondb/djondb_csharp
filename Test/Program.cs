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
            con.Open();
            con.ShowDbs();
            con.ShowNamespaces("ItsmDb");
            BSONObj o = new BSONObj();
            o.add("name", "John");
            o.add("lastName", "Smith");
            o.add("age", 10);

            con.Insert("TestDB", "TestNS", o);

            DjondbCursor cursor = con.Find("ItsmDb", "ORDERS", "*", "");
            con.BeginTransaction();
            while (cursor.Next())
            {
                BSONObj res = cursor.Current;
                res["test"] = 10;
                con.Update("ItsmDb", "ORDERS", res);
                Console.WriteLine(res);
            }
            con.CommitTransaction();

            DjondbCursor cur = con.ExecuteQuery("select * from ItsmDb:ORDERS");
            while (cur.Next())
            {
                BSONObj o2 = cur.Current;
                Console.WriteLine(o2);
            }
            try
            {
                con.ExecuteUpdate("select * from ItsmDb:ORDERS");
                throw new ApplicationException("This should break, Select are not allowed on ExecuteUpdate");
            }
            catch (DjondbException e)
            {
                // Expected
            }

        }
    }
}
