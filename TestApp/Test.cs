using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Djondb;

namespace TestApp
{
    public class Test
    {

        public static void testInsert()
        {
            BSONObj o = new BSONObj();
            o.add("name", "JOhn");

            BSONObj inner = new BSONObj();
            inner.add("test", 1);
            o.add("inner", inner);

            Djondb.DjondbConnection con = Djondb.DjondbConnectionManager.getConnection("localhost");
            try
            {

                if (con.open())
                {
                    try
                    {
                        con.update("test", "ns", "{'_id': '1234', '_revision': '1234' }");
                    }
                    catch (Exception e)
                    {
                        // Expected exception
                    }

                    con.insert("test", "ns", o);
                }
            }
            catch (Exception e)
            {
                Console.WriteLine("e: " + e.Message);
            }
            finally
            {
                con.close();
            }

        }

        public static void Run()
        {
            testInsert();
            testFind();
        }

        public static void testFind()
        {
            try
            {
                Djondb.DjondbConnection con = Djondb.DjondbConnectionManager.getConnection("localhost");

                if (con.open())
                {
                    Console.WriteLine("Connected");

                    DjondbCursor c1 =  con.find("ItsmDb", "COMPANYPRODUCT");

                    BSONArrayObj<BSONObj> arr = new BSONArrayObj<BSONObj>();
                    while (c1.next())
                    {
                        BSONObj o2 = c1.current();

                        Console.WriteLine(o2.toChar());
                        arr.add(o2);
                    }

                    foreach (BSONObj o in arr)
                    {
                        foreach (string prop in o.properties())
                        {

                            object val = o.get(prop);

                            Console.Write(prop + " " + val);
                        }
                        Console.WriteLine(o.toChar());
                    }

                }
            }
            catch (Exception e)
            {
                Console.WriteLine(e.Message);
            }
        }
    }
}
