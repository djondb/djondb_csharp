using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Djondb;

namespace TestApp
{
    class Program
    {
        static void Main(string[] args)
        {
            Djondb.DjondbConnection con = Djondb.DjondbConnectionManager.getConnection("localhost");

            if (con.open())
            {
                Console.WriteLine("Connected");

                Djondb.BSONObj o = new Djondb.BSONObj();
                o.add("int", 1);
                o.add("c", "Test");
                o.add("bool", true);
                o.add("double", 10.2d);


                con.insert("testdb", "testns", o);

                DjondbCursor cursor = con.find("testdb", "testns");

                BSONArrayObj<BSONObj> arr = new BSONArrayObj<BSONObj>();
                while (cursor.next())
                {
                    arr.add(cursor.current());
                    Console.WriteLine(cursor.current().toChar());
                }

                con.releaseCursor(cursor);

                Console.WriteLine("Array: " + arr.toChar());

                Console.WriteLine(o.toChar());
            }
        }
    }
}
