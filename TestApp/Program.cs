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
            DBootStrapper.LoadLibrary();

            Test.Run();
        }
    }
}
